//
//  dlights.cpp
//  vHook
//
//  Created by Timothy Dillan on 12/8/19.
//  Copyright © 2019 ViKiNG. All rights reserved.
//

#include "dlights.hpp"
#include "../main.h"

/*bool Settings::Dlights::enabled = false;
float Settings::Dlights::radius = 500.0f;*/

void Dlights::Paint()
{
    if (!vars.visuals.enabled || !vars.misc.dlight)
        return;
    
    if (!vars.misc.dlightenemy && !vars.misc.dlightallies)
        return;
    
    if (!pEngine->IsInGame())
        return;
    
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (!localplayer)
        return;
    
    for (int i = 1; i < pEngine->GetMaxClients(); ++i)
    {
        C_BaseEntity* player = pEntList->GetClientEntity(i);
        if (!player)
            continue;
        
        if (player == localplayer)
            continue;
        
        if (player->GetTeam() != localplayer->GetTeam() && !vars.misc.dlightenemy)
            return;
        
        if (player->GetTeam() == localplayer->GetTeam() && !vars.misc.dlightallies)
            return;
        
        Color color = vars.colors.dlight;
        
        dlight_t* dLight = pEffects->CL_AllocDlight(i);
        dLight->key = i;
        dLight->color.r = (unsigned char) color.r();
        dLight->color.g = (unsigned char) color.g();
        dLight->color.b = (unsigned char) color.b();
        dLight->color.exponent = true;
        dLight->flags = DLIGHT_NO_MODEL_ILLUMINATION;
        dLight->m_Direction = player->GetVecOrigin();
        dLight->origin = player->GetVecOrigin();
        dLight->radius = vars.misc.dlightradius;
        dLight->die = pGlobals->curtime + 0.1f;
        dLight->decay = 20.0f;
    }
}
