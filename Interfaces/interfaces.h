#pragma once

extern ISurface*            pSurface;
extern CEffects*            pEffects;
extern IPanel*              pPanel;
extern ICvar*               pCvar;
extern IBaseClientDLL*      pClient;
extern IClientEntityList*   pEntList;
extern IVRenderView*        pRenderView;
extern IVDebugOverlay*      pOverlay;
extern IEngineVGui*         pEngineGUI;
//extern IFileSystem* fileSystem;
extern IEngineClient*       pEngine;
extern IVModelInfo*         pModelInfo;
extern IEngineTrace*        pEngineTrace;
extern IClientMode*         pClientMode;
extern CGlobalVarsBase*     pGlobals;
//extern CViewRender*         viewRender;
extern IInputSystem*        pInputSystem;
extern CInput*              pInput;
extern IMaterialSystem*     pMatSystem;
extern IVModelRender*       pModelRender;
extern IGameMovement*       pGameMovement;
extern int* nPredictionRandomSeed;
extern CMoveData* g_MoveData;
extern IMoveHelper*         pMoveHelper;
extern IPhysicsSurfaceProps*pPhysics;
extern CGlowObjectManager* glowManager;
extern RandomSeedFn         RandomSeed;
extern RandomIntFn          RandomInt;
extern SendClanTagFn        SetClanTag;
extern MsgFunc_ServerRankRevealAllFn MsgFunc_ServerRankRevealAll;
//extern RandomFloatFn RandomFloat;
extern IPrediction*         pPrediction;
extern IGameEventManager2* pGameEventManager;
extern INetChannelInfo*     nci;


extern VMT* paintVMT;
extern VMT* createmoveVMT;
extern VMT* clientVMT;
extern VMT* modelVMT;
extern VMT* predVMT;
extern VMT* game_event_vmt;
extern VMT* engineVGUIvmt;
extern VMT* gameEventsVMT;
extern int* nPredictionRandomSeed;
extern RecvVarProxyFn g_pSequence;

