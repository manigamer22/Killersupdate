#include "main.h"
#include "../Hacks/skinconfigchanger.hpp"
#include "asuswalls.h"
#include "../Backtrack.hpp"
#include "../Hacks/nosmoke.hpp"
#include "../Hacks/antiaim.h"
#include "../Hacks/resolver.h"
#include "../Hacks/thirdperson.hpp"

void RemoveFlash(ClientFrameStage_t stage)
{
    if (!pEngine->IsInGame())
        return;
    
    if(!vars.misc.noflash)
        return;
    
    if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
        return;
    
    C_BaseEntity* localplayer = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if (!localplayer)
        return;
    
    if (vars.misc.noflash)
    {
        *localplayer->GetFlashMaxAlpha() = 255.0f - vars.misc.flashalpha;
    }
    else
    {
        *localplayer->GetFlashMaxAlpha() = 255.0f;
    }
    
}
void hkFrameStage(void* thisptr, ClientFrameStage_t curStage)
{
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(!local)
        return;
    
    Vector* PointerPunch    = nullptr;
    Vector* PointerView     = nullptr;
    
    Vector VecPunch, VecView;
    
    if(curStage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
    {
        if(vars.aimbot.backtrack)
        {
            for(int i = 0; i < 64; i++ )
            {
                auto entity = (C_BaseEntity*)pEntList->GetClientEntity(i);
                
                if(!entity)
                    continue;
                
                if(entity == local)
                    continue;
                
                if(entity->GetDormant())
                    continue;
                
                if(entity->IsGhost())
                    continue;
                
                if(entity->GetImmune())
                    continue;
                
                //if(entity->GetTeam() == Global::local->GetTeam())
                //continue;
                
                if(!entity->GetAlive())
                    continue;
                
                backtracking->Update(pGlobals->tickcount);
            }
        }
    }
    
    if(vars.visuals.skinc) {
        skinchanger->FrameStageNotify(curStage);
    }
    if(vars.misc.asuswalls)
        asuswalls(curStage);
    
    if(curStage == FRAME_NET_UPDATE_POSTDATAUPDATE_END)
    {
        remove_smoke(curStage);
    }
    if(vars.misc.thirdpersonmode) {
        if (pEngine->IsConnected() && pEngine->IsInGame()) {
            if(local->GetLifeState() == LIFE_ALIVE)
            {
                *reinterpret_cast<Vector*>(reinterpret_cast<uintptr_t>(local) + offsets.DT_BasePlayer.deadflag + 0x4) = tpangles;
            }
        }
    }
    Resolver::FrameStageNotify(curStage);
    if(curStage == FRAME_RENDER_START && local) {
        if(vars.misc.novisual)
        {
            if(local->GetLifeState() == LIFE_ALIVE)
            {
                PointerPunch = (Vector*)((uintptr_t)local + offsets.DT_BasePlayer.m_aimPunchAngle);
                PointerView = (Vector*)((uintptr_t)local + offsets.DT_BasePlayer.m_viewPunchAngle);
                
                VecPunch = *PointerPunch;
                VecView = *PointerView;
                
                PointerPunch->Init();
                PointerView->Init();
            }
        }
    }
    {
        RemoveFlash(curStage);
        ViewmodelHVH();
        InverseRagdoll();
    }
    clientVMT->GetOriginalMethod<tFrameStage>(37)(thisptr, curStage);
    if(PointerPunch && PointerView)
    {
        *PointerPunch   = VecPunch;
        *PointerView    = VecView;
    }
    
}
