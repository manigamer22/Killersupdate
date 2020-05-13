//
//  moonwalk.cpp
//  vHook
//
//  Copyright © 2019 ViKiNG. All rights reserved.
//

#include "moonwalk.hpp"
void Moonwalk(CUserCmd* cmd)
{
    if(!vars.misc.moonwalk)
        return;
    
    if(!pEngine->IsInGame())
        return;
    
    C_BaseEntity* localplayer = (C_BaseEntity*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if(!localplayer)
        return;
    
    if(cmd->forwardmove > 0)
    {
        cmd->buttons |= IN_BACK;
        cmd->buttons &= ~IN_FORWARD;
    }
    
    if(cmd->forwardmove < 0)
    {
        cmd->buttons |= IN_FORWARD;
        cmd->buttons &= ~IN_BACK;
    }
    
    if(cmd->sidemove < 0)
    {
        cmd->buttons |= IN_MOVERIGHT;
        cmd->buttons &= ~IN_MOVELEFT;
    }
    
    if(cmd->sidemove > 0)
    {
        cmd->buttons |= IN_MOVELEFT;
        cmd->buttons &= ~IN_MOVERIGHT;
    }
}
