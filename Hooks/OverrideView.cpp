#include "../main.h"
#include "../Hacks/thirdperson.hpp"
#include "../Hacks/grenadeprediction.hpp"

void hkOverrideView(void* thisptr, CViewSetup* setup)
{
    
    C_BasePlayer* local = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
   if(vars.misc.fovt && vars.misc.fov > 0) {
    if(local && !local->IsScoped()){
            setup->fov += vars.misc.fov;
        }

   }
    if(pEngine->IsInGame() && !local->GetAlive() && vars.misc.spectatorfirstperson && pEngine->IsConnected()){
        *local->GetObserverMode() = OBS_MODE_CHASE;
    }
    if (pEngine->IsInGame() && local && local->GetAlive() && local->GetHealth() > 0)
    {   
        ThirdPerson::OverrideView(setup);
    }
     grenade_prediction::get().View(setup);
    
    createmoveVMT->GetOriginalMethod<tOverrideView>(19)(thisptr, *setup);
   
}

