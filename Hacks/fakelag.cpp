

#include "fakelag.hpp"
static int ticks = 0;
int ticksMax = 16;

void FakeLag(CUserCmd *cmd) {
    if (!vars.misc.fakelag)
        return;
    if(!pEngine->IsInGame())
        return;
    
    C_BasePlayer* localplayer = (C_BasePlayer*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if (!localplayer || !localplayer->GetAlive())
        return;
    if (localplayer->GetFlags() & FL_ONGROUND && vars.misc.adaptive)
        return;
    
    
    if (cmd->buttons & IN_ATTACK) {
        CreateMove::sendPacket = true;
        return;
    }
    
    if (ticks >= ticksMax) {
        CreateMove::sendPacket = true;
        ticks = 0;
    } else {
        if (vars.misc.adaptive) {
            int packetsToChoke;
            if (localplayer->GetVelocity().Length() > 0.f) {
                packetsToChoke = (int)((64.f / pGlobals->interval_per_tick) / localplayer->GetVelocity().Length()) + 1;
                if (packetsToChoke >= 15)
                    packetsToChoke = 14;
                if (packetsToChoke < vars.misc.fakelagfactor)
                    packetsToChoke = vars.misc.fakelagfactor;
            } else
                packetsToChoke = 0;
            
            CreateMove::sendPacket = ticks < 16 - packetsToChoke;
        } else
            CreateMove::sendPacket = ticks < 16 - vars.misc.fakelagfactor;
    }
    
    ticks++;
    
}
