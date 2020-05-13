#include "main.h"
#include "skinconfigchanger.hpp"
#include "index.h"
#include "../EventListener.h"
EventListener* eventlistener = nullptr;
bool* bSendPacket = nullptr;
int* nPredictionRandomSeed  = nullptr;
CMoveData* g_MoveData = nullptr;

void InitializeInterfaces()
{
    pSurface        = GetInterface<ISurface>("./bin/osx64/vguimatsurface.dylib", "VGUI_Surface");
    pPanel          = GetInterface<IPanel>("./bin/osx64/vgui2.dylib", "VGUI_Panel");
    pEffects        = GetInterface<CEffects>("./bin/osx64/engine.dylib", "VEngineEffects"); 
    pCvar           = GetInterface<ICvar>("./bin/osx64/materialsystem.dylib", "VEngineCvar");
    pClient         = GetInterface<IBaseClientDLL>("./csgo/bin/osx64/client_panorama.dylib", "VClient");
    pEngine         = GetInterface<IEngineClient>("./bin/osx64/engine.dylib", "VEngineClient");
    pEntList        = GetInterface<IClientEntityList>("./csgo/bin/osx64/client_panorama.dylib", "VClientEntityList");
    pOverlay        = GetInterface<IVDebugOverlay>("./bin/osx64/engine.dylib", "VDebugOverlay");
    pEngineTrace    = GetInterface<IEngineTrace>("./bin/osx64/engine.dylib", "EngineTraceClient");
    pModelInfo      = GetInterface<IVModelInfo>("./bin/osx64/engine.dylib", "VModelInfoClient");
    pInputSystem    = GetInterface<IInputSystem>("./bin/osx64/inputsystem.dylib", "InputSystemVersion");
    pModelRender    = GetInterface<IVModelRender>("./bin/osx64/engine.dylib", "VEngineModel");
    pPrediction         = GetInterface<IPrediction>("./csgo/bin/osx64/client_panorama.dylib", "VClientPrediction");
    pMatSystem      = GetInterface<IMaterialSystem>("./bin/osx64/materialsystem.dylib", "VMaterialSystem");
    pEngineGUI      = GetInterface<IEngineVGui>("./bin/osx64/engine.dylib", "VEngineVGui");
    pGameMovement   = GetInterface<IGameMovement>("./csgo/bin/osx64/client_panorama.dylib", "GameMovement");
    pPhysics        = GetInterface<IPhysicsSurfaceProps>("./bin/osx64/vphysics.dylib", "VPhysicsSurfaceProps");
    pGameEventManager = GetInterface<IGameEventManager2>("./bin/osx64/engine.dylib", "GAMEEVENTSMANAGER002", true);
    eventlistener = new EventListener({ "cs_game_disconnected", "player_connect_full", "player_death", "player_hurt", "bullet_impact", "round_start", "round_end", "weapon_fire", "switch_team", "player_death", "item_purchase", "item_remove", "item_pickup", "bomb_begindefuse", "enter_bombzone", "bomb_beginplant" });
    
    
}

uintptr_t Offsets::playerAnimStateOffset = *reinterpret_cast<uint32_t*>(CPatternScanner::Instance()->GetProcedure("client_panorama.dylib", (unsigned char*)"\x48\x8B\xBB\x00\x00\x00\x00\x48\x85\xFF\x74\x41\xE8\x00\x00\x00\x00\x4C", "xxx????xxxxxx????x", 0) + 3);

void ProtectAddr(void* addr, int prot)
{
    long pagesize = sysconf(_SC_PAGESIZE);
    void* address = (void *)((long)(uintptr_t)addr & ~(pagesize - 1));
    mprotect(address, sizeof(address), prot);
}

void InitializeVMTs()
{
    uintptr_t findClientMode = CPatternScanner::Instance()->GetPointer("client_panorama.dylib",(unsigned char*)CLIENTMODE_SIG, CLIENTMODE_MASK, 0xA) + 0x4;
    uintptr_t findGlobalVars = CPatternScanner::Instance()->GetPointer("client_panorama.dylib", (unsigned char*)GLOBALS_SIG, GLOBALS_MASK, 0x3) + 0x4;
    uintptr_t findRankReveal = CPatternScanner::Instance()->GetPointer("client_panorama.dylib",(unsigned char*)RANKREVEAL_SIG, RANKREVEAL_MASK, 0x15) + 0x4;
    uintptr_t findClanTag    = CPatternScanner::Instance()->GetPointer("engine.dylib", (unsigned char*) CLANTAG_SIG, CLANTAG_MASK, 0xB) + 0x4;
    uintptr_t sendPacketPtr =  CPatternScanner::Instance()->GetProcedure("engine.dylib", (unsigned char*)SENDPACKET_SIG, SENDPACKET_MASK, 0x1) + 0x2;
    uint64_t findMoveData = CPatternScanner::Instance()->GetPointer("client_panorama.dylib", (unsigned char*)"\x48\x8D\x05\x00\x00\x00\x00\x48\x8B\x00\x0F\x57\xC0\x0F\x2E\x40\x00\x73\x00", "xxx????xxxxxxxxx?x?", 0x3) + 0x4;
    uintptr_t predictionSeedPointer = CPatternScanner::Instance()->GetPointer("client_panorama.dylib", (unsigned char*)"\x48\x8D\x0D\x00\x00\x00\x00\x89\x01\x5D\xC3", "xxx????xxxx", 0x3) + 0x4;

    bSendPacket = reinterpret_cast<bool*>(sendPacketPtr);
    ProtectAddr(bSendPacket, PROT_READ | PROT_WRITE | PROT_EXEC);
    //Hooker::FindPlayerAnimStateOffset();
    pInput = *reinterpret_cast<CInput**>(GetAbsoluteAddress(getvfunc<uintptr_t>(pClient, 16) + 4, 3, 7));
    
    void* handle = dlopen("./csgo/bin/osx64/client_panorama.dylib", RTLD_NOLOAD | RTLD_NOW);
    RandomInt       = reinterpret_cast<RandomIntFn>(dlsym(handle, "RandomInt"));
    nPredictionRandomSeed      = *reinterpret_cast<int**>(dlsym(handle, "RandomSeed"));
    //g_MoveData = **reinterpret_cast<CMoveData***>(dlsym(handle, "g_MoveData"));
    dlclose(handle);
    
    SetClanTag  = reinterpret_cast<SendClanTagFn>(findClanTag);
    pClientMode = reinterpret_cast<IClientMode*>(findClientMode);
    pGlobals    = *reinterpret_cast<CGlobalVarsBase**>(findGlobalVars);
    nPredictionRandomSeed = reinterpret_cast<int*>(predictionSeedPointer);
    g_MoveData = *reinterpret_cast<CMoveData**>(findMoveData);
    MsgFunc_ServerRankRevealAll = reinterpret_cast<MsgFunc_ServerRankRevealAllFn>(findRankReveal);
    
    paintVMT        = new VMT(pPanel);
    createmoveVMT   = new VMT(pClientMode);
    clientVMT       = new VMT(pClient);
    modelVMT        = new VMT(pModelRender);
    predVMT         = new VMT(pPrediction);
    game_event_vmt  = new VMT(pGameEventManager);
    
}


void InitializeHooks()
{
    
    paintVMT->HookVM((void*)hkPaintTraverse, 42);
    paintVMT->ApplyVMT();
        
    createmoveVMT->HookVM((void*)hkCreateMove, 25);
    createmoveVMT->HookVM((void*)hkOverrideView, 19);
    createmoveVMT->ApplyVMT();
    
    clientVMT->HookVM((void*)hkKeyEvent, 21);
    clientVMT->HookVM((void*)hkFrameStage, 37);
    clientVMT->ApplyVMT();
    
    modelVMT->HookVM((void*)hkDrawModelExecute, 21);
    modelVMT->ApplyVMT();
    
    predVMT->HookVM((void*)hkRunCommand, 20);
    predVMT->ApplyVMT();

    game_event_vmt->HookVM((void*)hkFireEventClientSide, 36);
    game_event_vmt->HookVM((void*)FireEvent_hk, 9);
    game_event_vmt->ApplyVMT();

    g_pSequence = (RecvVarProxyFn)NetVarManager::HookProp("DT_BaseViewModel", "m_nSequence", HSequenceProxyFn);
}


void Unhook()
{
    game_event_vmt  ->ReleaseVMT();
    paintVMT        ->ReleaseVMT();
    createmoveVMT   ->ReleaseVMT();
    clientVMT       ->ReleaseVMT();
    modelVMT        ->ReleaseVMT();
    predVMT         ->ReleaseVMT();
    
    delete game_event_vmt;
    delete paintVMT;
    delete createmoveVMT;
    delete clientVMT;
    delete modelVMT;
    delete predVMT;
    delete eventlistener;
    
    
    pCvar->ConsoleColorPrintf(Color::Green(), "You have Successfully Unloaded Killers\n");
}

void PrintInfo()
{
    pCvar->ConsoleColorPrintf(Color::White(), "[D E A D] Injected successfully!\n");
    pCvar->ConsoleColorPrintf(Color::Red(), "Credits to: \n");
    pCvar->ConsoleColorPrintf(Color::Green(), "Syn/-X making breathless\n");
    pCvar->ConsoleColorPrintf(Color::Yellow(), "ViKiNG making barbossa\n");
    pCvar->ConsoleColorPrintf(Color::Blue(), "Akalisch (netvarmanager/patternscanner)\n");
    pCvar->ConsoleColorPrintf(Color::Purple(), "Warlauke (barbossa)\n");
    pCvar->ConsoleColorPrintf(Color::Avoz(), "Tim (idk he's a fat fuck)\n");
}

