//
//  antiaim.cpp
//  vHook
//

#include "antiaim.h"


Vector AntiAim::realAngle;
float side = 1.0f;
Vector AntiAim::fakeAngle;

void doManual(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon){
    if(!vars.misc.manualaa)
        return;
    

    static bool switchsideleft = false;
    static bool switchsideright = false;
    static float resttime;
    static float resttime1;
    static bool switchsidedown = false;
    static bool switchsideup = false;
    static float resttime2;
    static float resttime3;
    //int SwitchSideKey = KEY_SLASH;
    if (pInputSystem->IsButtonDown(KEY_LEFT) && std::abs(resttime - pGlobals->curtime) > 0.5)
    {
        switchsideleft = !switchsideleft;
         if(switchsideleft){
             switchsideright = false;
             switchsidedown = false;
             switchsideup = false;
         }
        resttime = pGlobals->curtime;
    }
    if (pInputSystem->IsButtonDown(KEY_RIGHT) && std::abs(resttime1 - pGlobals->curtime) > 0.5)
    {
        switchsideright = !switchsideright;
        if(switchsideright){
            switchsideleft = false;
            switchsidedown = false;
            switchsideup = false;
        }
        resttime1 = pGlobals->curtime;
    }
    if (pInputSystem->IsButtonDown(KEY_DOWN) && std::abs(resttime1 - pGlobals->curtime) > 0.5)
    {
        switchsidedown = !switchsidedown;
        if(switchsidedown){
            switchsideleft = false;
            switchsideright = false;
            switchsideup = false;
        }
        resttime2 = pGlobals->curtime;
    }
    if (pInputSystem->IsButtonDown(KEY_UP) && std::abs(resttime1 - pGlobals->curtime) > 0.5)
    {
        switchsideup = !switchsideup;
        if(switchsideup){
            switchsideleft = false;
            switchsideright = false;
            switchsidedown = false;
        }
        resttime3 = pGlobals->curtime;
    }
    if(switchsideleft){
        cmd->viewangles.y -= 90.f;
    }
    if(switchsideright){
        cmd->viewangles.y+= 90.f;
    }
    if(switchsidedown){
        cmd->viewangles.y += 180.f;
    }
    if(switchsideup){
        cmd->viewangles.y -= 180.f;
    }
}
float GetMaxDeltaLegit(CCSGOAnimState *animState ) {
    
    float speedFraction = std::max(0.0f, std::min(animState->feetShuffleSpeed, 1.0f));
    
    float speedFactor = std::max(0.0f, std::min(1.0f, animState->feetShuffleSpeed2));
    
    float unk1 = ((animState->runningAccelProgress * -0.30000001) - 0.19999999) * speedFraction;
    float unk2 = unk1 + 1.0f;
    
    if (animState->duckProgress > 0)
    {
        unk2 += ((animState->duckProgress * speedFactor) * (0.5f - unk2));// - 1.f
    }
    
    return *(float*)((uintptr_t)animState + 0x3A4) * unk2;
}
float GetMaxDelta(CCSGOAnimState *animState ) {
    
    float speedFraction = std::max(0.0f, std::min(animState->feetShuffleSpeed, 1.0f));

    float speedFactor = std::max(0.0f, std::min(1.0f, animState->feetShuffleSpeed2));

    float unk1 = ((animState->runningAccelProgress * -0.30000001) - 0.19999999) * speedFraction;
    float unk2 = unk1 + 1.0f;
    float delta;

    if (animState->duckProgress > 0)
    {
        unk2 += ((animState->duckProgress * speedFactor) * (0.5f - unk2));// - 1.f
    }

    delta = *(float*)((uintptr_t)animState + 0x3A4) * unk2;

    return delta - 0.5f;
}

bool break_lby = false;
float next_update = 0;
void update_lowerbody_breaker() { // from HappyHack by "Incriminating" (unknowncheats)
    C_BasePlayer* local = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    float server_time = local->GetTickBase() * pGlobals->interval_per_tick, speed = local->GetVelocity().Length2DSqr();
    
    if (speed > 0.1) {
        next_update = server_time + 0.22;
    }
    
    break_lby = false;
    
    if (next_update <= server_time) {
        next_update = server_time + 1.1;
        break_lby = true;
    }
    
    
    if (!(local->GetFlags() & FL_ONGROUND)) {
        break_lby = false;
    }
}
bool is_enabled(CUserCmd* cmd)
{
     C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (!localplayer|| !localplayer->GetAlive())
        return false;

    if (!vars.misc.legitaa || (cmd->buttons & IN_USE))
        return false;

    auto* channel_info = pEngine->GetNetChannelInfo();
    if (channel_info && (channel_info->GetAvgLoss(1) > 0.f || channel_info->GetAvgLoss(0) > 0.f))
        return false;

    if (localplayer->GetImmune() || localplayer->GetFlags() & FL_FROZEN)
        return false;

    if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
        return false;

    return true;
}
bool is_firing(CUserCmd* cmd, C_BaseCombatWeapon* weapon)
{
    if (!weapon)
        return false;
    
    CSWeaponType weapon_type = (CSWeaponType)weapon->GetCSWpnData()->m_WeaponType;

    if (weapon_type == CSWeaponType::WEAPONTYPE_GRENADE)
    {
        return true;

        //if (!weapon->m_bPinPulled() && (cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2))
            //return false;
    }
    else if (weapon_type == CSWeaponType::WEAPONTYPE_KNIFE)
    {
        if (cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2)
            return true;
    }
    else if (*weapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
    {
        if (cmd->buttons & IN_ATTACK && (weapon->GetNextPrimaryAttack() > pGlobals->curtime) )
            return true;

        if (cmd->buttons & IN_ATTACK2)
            return true;
    }
    else if (cmd->buttons & IN_ATTACK && (weapon->GetNextPrimaryAttack() > pGlobals->curtime) && weapon_type != CSWeaponType::WEAPONTYPE_C4)
        return true;

    return false;
}

void LegitAA(CUserCmd* cmd, C_BaseCombatWeapon* activeWeapon)
{
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    float yaw_offset;
    CCSGOAnimState* animState = localplayer->GetAnimState();
    bool flip_yaw = false;
    bool flip_packet = false;
    
            if (!CreateMove::sendPacket)
                return;

            if (!is_enabled(cmd))
            {
                yaw_offset = 0.f;

                return;
            }

            assert(animState);

            yaw_offset = GetMaxDeltaLegit(animState);

            Vector old_angles = cmd->viewangles;

            flip_packet = !flip_packet;
            CreateMove::sendPacket = flip_packet;
            if (!flip_packet)
            {
                if (pInputSystem->IsButtonDown(KEY_SLASH))
                    flip_yaw = !flip_yaw;
            }

            static float last_lby = 0.f;
            static float last_update = 0.f;

            const auto current_lby = localplayer->GetLowerBodyYawTarget();
            const float current_time = localplayer->GetTickBase() * pGlobals->interval_per_tick;

            const float delta = ceilf((current_time - last_update) * 100) / 100;
            const auto next_delta = ceilf((delta + pGlobals->interval_per_tick) * 100) / 100;

            if (localplayer->GetVelocity().Length2D() <= 0.f)
            {
                if (current_lby != 180.f && last_lby != current_lby)
                {

                    last_lby = current_lby;
                    last_update = current_time - pGlobals->interval_per_tick;
                }
                else if (next_delta >= 1.1f)
                {

                    CreateMove::sendPacket = flip_packet = true;

                    last_update = current_time;
                }
            }
            else
            {
                last_lby = current_lby;
                last_update = current_time;
            }
            
            const auto low_fps = pGlobals->interval_per_tick * 0.9f < pGlobals->absoluteframetime;
            if (low_fps || is_firing(cmd, activeWeapon))
                CreateMove::sendPacket = flip_packet = true;

            if (CreateMove::sendPacket)
                localplayer->GetAnimState()->goalFeetYaw += flip_yaw ? yaw_offset : -yaw_offset;
            else
            {
                cmd->buttons &= ~(IN_FORWARD | IN_BACK | IN_MOVERIGHT | IN_MOVELEFT);
                cmd->viewangles.y += 180.f;
                cmd->viewangles.Normalize();
                cmd->viewangles.Clamp();
                correct_movement(cmd, old_angles);
            }
}
float get_curtime(CUserCmd* ucmd)
{
    C_BasePlayer* LocalPlayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    int g_tick = 0;
    CUserCmd* g_pLastCmd = nullptr;
    if (!g_pLastCmd || g_pLastCmd->hasbeenpredicted) {
        g_tick = (float)LocalPlayer->GetTickBase();
    }
    else {
        ++g_tick;
    }
    g_pLastCmd = ucmd;
    float curtime = g_tick * pGlobals->interval_per_tick;
    return curtime;
}
bool next_lby_update(CUserCmd* cmd)
{
    C_BasePlayer* LocalPlayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    static float next_lby_update_time = 0;
    float curtime = get_curtime(cmd);
 
    auto animstate = LocalPlayer->GetAnimState();
    if (!animstate)
        return false;
 
    if (!(LocalPlayer->GetFlags() & FL_ONGROUND))
        return false;
 
    if (animstate->speed > 0.1)
        next_lby_update_time = curtime + 0.22f;
 
    if (next_lby_update_time < curtime)
    {
        next_lby_update_time = curtime + 1.1f;
        return true;
    }
 
    return false;
}
void DoAntiAimTest(CUserCmd* cmd){
    
    auto l = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
     
     if (!l)
         return;
         
    cmd->viewangles.x = 89;
         
     if (CreateMove::sendPacket){
             cmd->viewangles.y = 120 - (GetMaxDelta(l->GetAnimState()) * 1);
     }
     else
     {
        if (next_lby_update(cmd))
        {
            cmd->viewangles.y = 120 - (180 * 1);
            return;
        }
        else
        {
         cmd->viewangles.y = 180;
        }
    }
    
}
static float next_lby = 0.0f;


static void DoAntiAimY(C_BasePlayer *const localplayer, Vector& angle, bool bSend, CUserCmd* cmd)
{
    int aa_type = bSend ? vars.misc.typeFake : vars.misc.type;

    static bool bFlip = false;
    
    float maxDelta = GetMaxDelta(localplayer->GetAnimState());
    
    switch (aa_type)
    {
        case 1:
            angle.y = AntiAim::fakeAngle.y - maxDelta;
            break;
        case 2:
            angle.y = AntiAim::fakeAngle.y + maxDelta;
            break;
        case 3:
            bFlip = !bFlip;
            angle.y -= bFlip ? maxDelta : -maxDelta;
            break;
        case 4:
            angle.y += bFlip ? maxDelta : -1 * maxDelta;
            bFlip = !bFlip;
            break;
        default:
            break;
    }
    if( bSend ){
        AntiAim::fakeAngle.y = angle.y;
    } else {
        AntiAim::realAngle.y = angle.y;
    }
}
void nigga(CUserCmd* cmd, C_BaseCombatWeapon* weapon_handle){
    
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(!pEngine->IsInGame())
        return;
    
    if(!localplayer || !localplayer->GetAlive())
        return;
    
        if (!weapon_handle)
            return;
    
        if(!pInputSystem->IsButtonDown(KEY_LSHIFT))
            return;
    
        float amount = 0.0034f * 100.f;
    
        Vector velocity = localplayer->GetVelocity();
        Vector direction;
    
        VectorAngles(velocity, direction);
    
        float speed = velocity.Length2D();
    
        direction.y = cmd->viewangles.y - direction.y;
    
        Vector forward;
    
        AngleVectors(direction, &forward);
    
        Vector source = forward * -speed;
    
        if (speed >= (weapon_handle->GetCSWpnData1()->GetMaxPlayerSpeed() * amount))
        {
            cmd->forwardmove = source.x;
            cmd->sidemove = source.y;
    
        }
}
void FakeDuck(CUserCmd* cmd){
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if(!localplayer)
        return;
    if(!localplayer->GetAlive())
        return;
    static int fakeduckChokeAmount = 0;
    
    if (pInputSystem->IsButtonDown(KEY_X))
    {
        if (fakeduckChokeAmount > 14)
        {
            fakeduckChokeAmount = 0;
            CreateMove::sendPacket = true;
        }
        else
            CreateMove::sendPacket = false;
        fakeduckChokeAmount++;
        auto choke = pEngine->GetNetChannel()->m_nChokedPackets;

        if (localplayer->GetFlags() & FL_ONGROUND)
        {
            if (choke >= 7)
                cmd->buttons |= IN_DUCK;
            else
                cmd->buttons &= ~IN_DUCK;
        }
    }
    else
        fakeduckChokeAmount = 0;
}
static void DoAntiAimX(Vector& angle, bool bFlip, bool& clamp)
{
    static float pDance = 0.0f;

    switch (vars.misc.aaX)
    {
        case 1:
            angle.x = -89.0f;
            break;
        case 2:
            angle.x = 89.0f;
            break;
        case 3:
            pDance += 45.0f;
            if (pDance > 100)
                pDance = 0.0f;
            else if (pDance > 75.f)
                angle.x = -89.f;
            else if (pDance < 75.f)
                angle.x = 89.f;
            break;
        case 4:
            angle.x = 0.0f;
            break;
        case 5:
            clamp = false;
            angle.x = -540.0f;
            break;
        case 6:
            clamp = false;
            angle.x = 540.0f;
            break;
        case 7:
            clamp = false;
            angle.x = 1800089.0f;
            break;
        case 8:
            clamp = false;
            angle.x = 36000088.0f;
            break;
        case 9:
            clamp = false;
            angle.x = 35999912.0f;
            break;
        default:
            break;
    }
}

void DoAntiAim(CUserCmd* cmd, C_BaseCombatWeapon* weapon)
{
    if (!vars.misc.antiaim && !vars.misc.lbybreaker && !vars.misc.desyncenabled && !vars.misc.pitchenabled)
        return;

    Vector oldAngle = cmd->viewangles;
    float oldForward = cmd->forwardmove;
    float oldSideMove = cmd->sidemove;
    
    AntiAim::realAngle = AntiAim::fakeAngle = CreateMove::lastTickViewAngles;

    Vector angle = cmd->viewangles;

    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (!localplayer || !localplayer->GetAlive())
        return;

    C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) pEntList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
    if (!activeWeapon)
        return;
    
    CSWeaponType weaponType = (CSWeaponType)activeWeapon->GetCSWpnData()->m_WeaponType;

    if (weaponType == CSWeaponType::WEAPONTYPE_GRENADE)
    {
        C_BaseCSGrenade* csGrenade = (C_BaseCSGrenade*) activeWeapon;

        if (csGrenade->GetThrowTime() > 0.f)
            return;
    }

    if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK || (cmd->buttons & IN_ATTACK2 && *activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER))
        return;

    if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
        return;

    static bool bSend = true;
    bSend = !bSend;

    bool should_clamp = true;

    bool needToFlick = false;
    static bool lbyBreak = false;
    static float lastCheck;
    float vel2D = localplayer->GetVelocity().Length2D();//localplayer->GetAnimState()->verticalVelocity + localplayer->GetAnimState()->horizontalVelocity;

     if( vars.misc.lbybreaker ){
           
           if( vel2D >= 0.1f || !(localplayer->GetFlags() & FL_ONGROUND) || localplayer->GetFlags() & FL_FROZEN ){
               lbyBreak = false;
               lastCheck = pGlobals->curtime;
           } else {
               if( !lbyBreak && ( pGlobals->curtime - lastCheck ) > 0.22 ){
                   cmd->viewangles.y -= vars.misc.lbybreakeroffset;
                   lbyBreak = true;
                   lastCheck = pGlobals->curtime;
                   needToFlick = true;
               } else if( lbyBreak && ( pGlobals->curtime - lastCheck ) > 1.1 ){
                   cmd->viewangles.y -= vars.misc.lbybreakeroffset;
                   lbyBreak = true;
                   lastCheck = pGlobals->curtime;
                   needToFlick = true;
               }
           }
       }
    Vector OldAngles = cmd->viewangles;

    auto Desync = [OldAngles](CUserCmd* cmd, C_BaseCombatWeapon* weapon)
    {
        C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
        if (cmd->buttons & (IN_ATTACK | IN_ATTACK2 | IN_USE) || localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP
            || !localplayer->GetAlive())
            return;

        if (localplayer->GetImmune() || localplayer->GetFlags() & FL_FROZEN)
            return;

        if (!weapon)
            return;

        auto weapon_index = weapon->GetItemDefinitionIndex();
        if ((*weapon_index == WEAPON_GLOCK || *weapon_index == WEAPON_FAMAS) && weapon->GetNextPrimaryAttack() >= pGlobals->curtime)
            return;

        if (!vars.misc.antiaim)
            return;
        
        CSWeaponType weaponType = (CSWeaponType)weapon->GetCSWpnData()->m_WeaponType;

        if (weaponType == CSWeaponType::WEAPONTYPE_GRENADE)
        {
            C_BaseCSGrenade* csGrenade = (C_BaseCSGrenade*) weapon;
            if(!csGrenade->GetPinPulled()){
                if (csGrenade->GetThrowTime() > 0.f)
                    return;
            }
        }

        static bool broke_lby = false;
        if (vars.misc.type == 6) {
            float minimal_move = 2.0f;
            if (localplayer->GetFlags() & FL_DUCKING)
                minimal_move *= 3.f;

            if (cmd->buttons & IN_WALK)
                minimal_move *= 3.f;

            bool should_move = localplayer->GetVelocity().Length2D() <= 0.0f
                || std::fabsf(localplayer->GetVelocity().z) <= 100.0f;

            if ((cmd->command_number % 2) == 1) {
                cmd->viewangles.y += 120.0f * side; //was 120.0f * side
                if (should_move)
                    cmd->sidemove -= minimal_move;
                CreateMove::sendPacket = false;
            }
            else if (should_move) {
                cmd->sidemove += minimal_move;
            }
        }
        else if (vars.misc.type == 7){
            if (next_lby >= pGlobals->curtime) {
                if (!broke_lby && CreateMove::sendPacket)
                    return;

                broke_lby = false;
                CreateMove::sendPacket = false;
                cmd->viewangles.y += 120.0f * side; //was 120.f
            }else {
                broke_lby = true;
                CreateMove::sendPacket = false;
                cmd->viewangles.y += 120.0f * -side; //was 120.f
            }
        }
    };

    if (vars.misc.desyncenabled && !needToFlick)
    {
        DoAntiAimY(localplayer, angle, bSend, cmd);
        if(vars.misc.type == 5){
            DoAntiAimTest(cmd);
        }
        Desync(cmd, weapon);
        CreateMove::sendPacket = bSend;
    }
    
    if (vars.misc.pitchenabled)
        DoAntiAimX(angle, bSend, should_clamp);

    if( should_clamp ){
        NormalizeAngles(angle);
        ClampAngles(angle);
    }

   cmd->viewangles = angle;

   CorrectMovement(oldAngle, cmd, oldForward, oldSideMove);
}
