#include "main.h"

// CLEAN CODE > ALL
CGlowObjectManager* glowManager = nullptr;
ISurface*           pSurface        = nullptr;
CEffects*           pEffects        = nullptr;
IPanel*             pPanel          = nullptr;
ICvar*              pCvar           = nullptr;
IBaseClientDLL*     pClient         = nullptr;
IClientEntityList*  pEntList        = nullptr;
IVDebugOverlay*     pOverlay        = nullptr;
IEngineClient*      pEngine         = nullptr;
IMaterialSystem*    material = nullptr;
IVModelInfo*        pModelInfo      = nullptr;
IEngineTrace*       pEngineTrace    = nullptr;
IClientMode*        pClientMode     = nullptr;
CGlobalVarsBase*    pGlobals        = nullptr;
IInputSystem*       pInputSystem    = nullptr;
CInput*             pInput          = nullptr;
IMaterialSystem*    pMatSystem      = nullptr;
IPrediction*        pPrediction     = nullptr;
IEngineVGui*        pEngineGUI = nullptr;
IVModelRender*      pModelRender    = nullptr;
IMoveHelper*        pMoveHelper     = nullptr;
IGameMovement*      pGameMovement   = nullptr;
//IFileSystem* fileSystem = nullptr;
IPhysicsSurfaceProps* pPhysics      = nullptr;
IGameEventManager2* pGameEventManager = nullptr;
INetChannelInfo*    nci             = nullptr;

CMoveData* MoveData         = nullptr;

//unsigned int Offsets::playerAnimStateOffset = 0;
//unsigned int Offsets::playerAnimOverlayOffset = 0;

SendClanTagFn       SetClanTag;
RandomIntFn         RandomInt;
//RandomFloatFn       RandomFloat;

MsgFunc_ServerRankRevealAllFn MsgFunc_ServerRankRevealAll;


VMT* paintVMT = nullptr;
VMT* createmoveVMT = nullptr;
VMT* clientVMT = nullptr;
VMT* modelVMT = nullptr;
VMT* predVMT = nullptr;
VMT* engineVGUIvmt = nullptr;
VMT* game_event_vmt = nullptr;

RecvVarProxyFn g_pSequence;


