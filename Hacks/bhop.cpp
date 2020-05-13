#include "bhop.h"

void DoBhop(CUserCmd* cmd, C_BaseEntity* local)
{
    static bool bLastJumped = false;
    static bool bShouldFake = false;
    
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if (!localplayer)
        return;
    
    if (!vars.misc.bhop)
        return;
    
    if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
        return;
    
    if (!bLastJumped && bShouldFake)
    {
        bShouldFake = false;
        cmd->buttons |= IN_JUMP;
    }
    else if (cmd->buttons & IN_JUMP)
    {
        if (localplayer->GetFlags() & FL_ONGROUND)
        {
            bLastJumped = true;
            bShouldFake = true;
        }
        else
        {
            cmd->buttons &= ~IN_JUMP;
            bLastJumped = false;
        }
    }
    else
    {
        bLastJumped = false;
        bShouldFake = false;
    }
}

bool backward_style = false;

void RageStrafe(C_BasePlayer* localplayer, CUserCmd* cmd)
{
    
    static bool leftRight;
    bool inMove = cmd->buttons & IN_FORWARD || cmd->buttons & IN_BACK || cmd->buttons & IN_MOVELEFT || cmd->buttons & IN_MOVERIGHT;

    if (cmd->buttons & IN_FORWARD && localplayer->GetVelocity().Length() <= 50.0f)
        cmd->forwardmove = 250.0f;

    float yaw_change = 0.0f;
    if (localplayer->GetVelocity().Length() > 50.f)
        yaw_change = 30.0f * fabsf(30.0f / localplayer->GetVelocity().Length());

    C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) pEntList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
    if (activeWeapon && !(activeWeapon->GetAmmo() == 0) && cmd->buttons & IN_ATTACK)
        yaw_change = 0.0f;

    Vector viewAngles;
    pEngine->GetViewAngles(viewAngles);

    if (!(localplayer->GetFlags() & FL_ONGROUND) && !inMove)
    {
        if (leftRight || cmd->mousedx > 1)
        {
            viewAngles.y += yaw_change;
            cmd->sidemove = 250.0f;
        }
        else if (!leftRight || cmd->mousedx < 1)
        {
            viewAngles.y -= yaw_change;
            cmd->sidemove = -250.0f;
        }

        leftRight = !leftRight;
    }

    NormalizeAngles(viewAngles);
    ClampAngles(viewAngles);

    CorrectMovement(viewAngles, cmd, cmd->forwardmove, cmd->sidemove);
}

void AutoStrafeCreateMove(CUserCmd* cmd){
    if (!vars.misc.autostrafe)
        return;

    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (!localplayer)
        return;

    if (!localplayer->GetAlive())
        return;

    if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
        return;
    
    RageStrafe(localplayer, cmd);
    
    
}

bool CircleDone = false, JustStarted = true;
void CirlceStrafe(C_BaseEntity *localPlayer, CUserCmd *cmd, Vector &oldAngles)
{
    if(!vars.misc.cstrafe)
        return;
    
    static int Angle = 0;
    
    if (oldAngles.y - Angle > 360)
        Angle -= 360;
    
    static bool shouldspin  = false;
    static bool enabled     = false;
    static bool check       = false;
    
    if (pInputSystem->IsButtonDown(KEY_PERIOD))
    {
        if (!check)
            enabled = !enabled;
        check = true;
    }
    else
    {
        check = false;
    }
    
    if (enabled)
    {
        shouldspin = true;
        cmd->buttons |= IN_JUMP;
        cmd->buttons |= IN_DUCK;
    }
    
    if (shouldspin)
    {
        Vector Dir;
        AngleVectors(Vector(0, Angle, 0), &Dir);
        Dir *= 8218;
        
        Ray_t ray;
        CTraceFilterWorldOnly filter;
        trace_t trace;
        
        ray.Init(localPlayer->GetEyePosition(), localPlayer->GetVecOrigin() + Dir);
        pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, &trace);
        auto temp = 3.4f / ((trace.endpos - localPlayer->GetVecOrigin()).Length() / 100.f);
        
        if (temp < 3.4f)
            temp = 3.4f;
        
        if (enabled)
        {
            Angle += temp;
            cmd->sidemove = -450;
        }
        else
        {
            if (oldAngles.y - Angle < temp)
            {
                Angle = oldAngles.y;
                shouldspin = false;
            }
            else
            {
                Angle += temp;
            }
        }
        oldAngles.y = Angle;
    }
    else
    {
        Angle = oldAngles.y;
    }
}



