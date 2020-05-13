#include "main.h"


int __attribute__((constructor)) Init()
{

    InitializeInterfaces();
    
    InitializeVMTs();
    
    InitializeHooks();
    
    NetVarManager::DumpNetvars();
    
    Offsets::getOffsets();
    
    PrintInfo();
    
    //UpdateResolver();
    
    return 0;
}

void __attribute__((destructor)) DeInit() {
    Unhook();
    return 0;
}
