#include "main.h"
#include <cstdio>


std::vector<RecvTable*> NetVarManager::GetTables()
{
    std::vector<RecvTable*> tables;
    
    ClientClass* clientClass = pClient->GetAllClasses();
    if (!clientClass)
        return std::vector<RecvTable*>();
    
    while (clientClass)
    {
        RecvTable* recvTable = clientClass->m_pRecvTable;
        tables.push_back(recvTable);
        
        clientClass = clientClass->m_pNext;
    }
    
    return tables;
}

RecvTable* NetVarManager::GetTable(std::vector<RecvTable*> tables, const char* tableName)
{
    if (tables.empty())
        return NULL;
    
    for (unsigned long i = 0; i < tables.size(); i++)
    {
        RecvTable* table = tables[i];
        
        if (!table)
            continue;
        
        if (strcasecmp(table->m_pNetTableName, tableName) == 0)
            return table;
    }
    
    return NULL;
}

int NetVarManager::GetOffset(std::vector<RecvTable*> tables, const char* tableName, const char* propName)
{
    int offset = GetProp(tables, tableName, propName);
    if (!offset)
        return 0;
    else
        pCvar->ConsoleColorPrintf(Color::Green(), "[+] Found %s -> 0x%X\n", propName, offset);
    return offset;
}


int NetVarManager::GetProp(std::vector<RecvTable*> tables, const char* tableName, const char* propName, RecvProp** prop)
{
    RecvTable* recvTable = GetTable(tables, tableName);
    if (!recvTable)
        return 0;
    
    int offset = GetProp(tables, recvTable, propName, prop);
    if (!offset)
        return 0;
    
    return offset;
}


int NetVarManager::GetProp(std::vector<RecvTable*> tables, RecvTable* recvTable, const char* propName, RecvProp** prop)
{
    int extraOffset = 0;
    
    for (int i = 0; i < recvTable->m_nProps; ++i) {
        RecvProp* recvProp = &recvTable->m_pProps[i];
        RecvTable* child = recvProp->m_pDataTable;
        
        if (child && (child->m_nProps > 0))
        {
            int tmp = GetProp(tables, child, propName, prop);
            if (tmp)
                extraOffset += (recvProp->m_Offset + tmp);
        }
        
        if (strcasecmp(recvProp->m_pVarName, propName))
            continue;
        
        if (prop)
            *prop = recvProp;
        
        return (recvProp->m_Offset + extraOffset);
    }
    
    return extraOffset;
}


std::string NetVarManager::DumpTable(RecvTable* table, int depth)
{
    std::string pre("");
    std::stringstream ss;
    
    for (int i = 0; i < depth; i++)
        pre.append("\t");
    
    ss << pre << table->m_pNetTableName << "\n";
    
    for (int i = 0; i < table->m_nProps; i++) {
        RecvProp* prop = &table->m_pProps[i];
        if (!prop)
            continue;
        
        std::string varName(prop->m_pVarName);
        
        if (varName.find("baseclass") == 0 || varName.find("0") == 0 || varName.find("1") == 0 ||
            varName.find("2") == 0)
            continue;
        
        ss << pre << "\t" << varName << " [0x" << std::hex << prop->m_Offset << "]\n";
        
        if (prop->m_pDataTable)
            ss << DumpTable(prop->m_pDataTable, depth + 1);
    }
    
    return ss.str();
}

uintptr_t NetVarManager::HookProp(const char* tableName, const char* propName, RecvVarProxyFn function) {
    RecvProp* recvProp = 0;
    NetVarManager::GetProp(NetVarManager::GetTables(), tableName, propName, &recvProp);
    
    if (!recvProp)
        return 0;
    
    uintptr_t old = (uintptr_t)recvProp->m_ProxyFn;
    recvProp->m_ProxyFn = function;
    return old;
}

bool NetVarManager::HookRecvProp(const char* className, const char* propertyName, std::unique_ptr<RecvPropHook>& recvPropHook)
{
    // FIXME: Does not search recursively.. yet.
    // Recursion is a meme, stick to reddit mcswaggens.
    for (ClientClass* pClass = pClient->GetAllClasses(); pClass; pClass = pClass->m_pNext)
    {
        if (strcmp(pClass->m_pNetworkName, className) == 0)
        {
            RecvTable* pClassTable = pClass->m_pRecvTable;

            for (int nIndex = 0; nIndex < pClassTable->m_nProps; nIndex++)
            {
                RecvProp* pProp = &pClassTable->m_pProps[nIndex];

                if (!pProp || strcmp(pProp->m_pVarName, propertyName) != 0)
                    continue;

                recvPropHook = std::make_unique<RecvPropHook>(pProp);

                return true;
            }

            break;
        }
    }

    return false;
}

void NetVarManager::DumpNetvars()
{
    std::stringstream ss;
    char cwd[1024];
    
    for (ClientClass* pClass = pClient->GetAllClasses(); pClass != NULL; pClass = pClass->m_pNext)
    {
        RecvTable* table = pClass->m_pRecvTable;
        ss << NetVarManager::DumpTable(table, 0);
    }
    
    getcwd(cwd, sizeof(cwd));
    
    std::string netvarsPath = std::string(cwd) + "/netvars - " __DATE__ ".txt";
    
    std::ofstream(netvarsPath) << ss.str();
}
