#include "triggerbot.hpp"
ButtonCode_t keybind1(){
    if (vars.misc.triggerbotkeybind == 0) {
        return KEY_A;
    }else if (vars.misc.triggerbotkeybind == 1){
        return KEY_B;
    }else if (vars.misc.triggerbotkeybind == 2){
        return KEY_C;
    }else if (vars.misc.triggerbotkeybind == 3){
        return KEY_D;
    }else if (vars.misc.triggerbotkeybind == 4){
        return KEY_E;
    }else if (vars.misc.triggerbotkeybind == 5){
        return KEY_F;
    }else if (vars.misc.triggerbotkeybind == 6){
        return KEY_G;
    }else if (vars.misc.triggerbotkeybind == 7){
        return KEY_H;
    }else if (vars.misc.triggerbotkeybind == 8){
        return KEY_I;
    }else if (vars.misc.triggerbotkeybind == 9){
        return KEY_J;
    }else if (vars.misc.triggerbotkeybind == 10){
        return KEY_K;
    }else if (vars.misc.triggerbotkeybind == 11){
        return KEY_L;
    }else if (vars.misc.triggerbotkeybind == 12){
        return KEY_M;
    }else if (vars.misc.triggerbotkeybind == 13){
        return KEY_N;
    }else if (vars.misc.triggerbotkeybind == 14){
        return KEY_O;
    }else if (vars.misc.triggerbotkeybind == 15){
        return KEY_P;
    }else if (vars.misc.triggerbotkeybind == 16){
        return KEY_Q;
    }else if (vars.misc.triggerbotkeybind == 17){
        return KEY_R;
    }else if (vars.misc.triggerbotkeybind == 18){
        return KEY_S;
    }else if (vars.misc.triggerbotkeybind == 19){
        return KEY_T;
    }else if (vars.misc.triggerbotkeybind == 20){
        return KEY_U;
    }else if (vars.misc.triggerbotkeybind == 21){
        return KEY_V;
    }else if (vars.misc.triggerbotkeybind == 22){
        return KEY_W;
    }else if (vars.misc.triggerbotkeybind == 23){
        return KEY_X;
    }else if (vars.misc.triggerbotkeybind == 24){
        return KEY_Y;
    }else if (vars.misc.triggerbotkeybind == 25){
        return KEY_Z;
    }else if (vars.misc.triggerbotkeybind == 26){
        return KEY_4;
    }else if (vars.misc.triggerbotkeybind == 27){
        return KEY_6;
    }else if (vars.misc.triggerbotkeybind == 28){
        return KEY_7;
    }else if (vars.misc.triggerbotkeybind == 29){
        return KEY_8;
    }else if (vars.misc.triggerbotkeybind == 30){
        return KEY_9;
    }else if (vars.misc.triggerbotkeybind == 31){
        return KEY_LSHIFT;
    }else if (vars.misc.triggerbotkeybind == 32){
        return KEY_LCONTROL;
    }else if (vars.misc.triggerbotkeybind == 33){
        return KEY_LALT;
    }
}
void DoTrigger(CUserCmd *Cmd, C_BaseCombatWeapon* activeWeapon)
{
    if(!vars.aimbot.trigger)
        return;
    
    if(vars.misc.triggerbotkey){
        if (!pInputSystem->IsButtonDown(keybind1()))
            return;
    }
    
    CSWeaponType weaponType = (CSWeaponType)activeWeapon->GetCSWpnData()->m_WeaponType;
    if (weaponType == CSWeaponType::WEAPONTYPE_KNIFE || weaponType == CSWeaponType::WEAPONTYPE_C4 || weaponType == CSWeaponType::WEAPONTYPE_GRENADE)
        return;
    if(pEngine->IsInGame() && pEngine->IsConnected())
    {
        
        C_BaseEntity* LocalPlayer = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
        
        if (!LocalPlayer || LocalPlayer->GetHealth() < 0)
            return;
        
        
        C_BaseCombatWeapon* activeWeapon = GetActiveWeapon(LocalPlayer);
        
        if (!activeWeapon || activeWeapon->GetAmmo() == 0)
            return;
        
        
        Vector traceStart, traceEnd;
        
        Vector viewAngles;
        pEngine->GetViewAngles(viewAngles);
        Vector viewAngles_rcs = viewAngles + (LocalPlayer->GetPunchAngles() * 2.0f);
        
        AngleVectors(viewAngles_rcs, &traceEnd);
        
        traceStart = LocalPlayer->GetEyePosition();
        traceEnd = traceStart + (traceEnd * 8192.0f);
        
        Ray_t ray;
        trace_t trace;
        CTraceFilter filter;
        filter.pSkip = LocalPlayer;
        
        ray.Init(traceStart, traceEnd);
        pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, &trace);
        
        if (trace.allsolid || trace.startsolid)
            return;
        
        
        C_BaseEntity* player = (C_BaseEntity*)trace.m_pEnt;
        
        if(!player || player->GetHealth() < 0 || player->GetImmune())
            return;
        
        
        if(player->GetClientClass()->m_ClassID != EClassIds::CCSPlayer)
            return;
        
        
        if(LocalPlayer->GetTeam() == player->GetTeam())
            return;
        
        
        if (activeWeapon->GetNextPrimaryAttack() > pGlobals->curtime)
        {
            if (*activeWeapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
            {
                Cmd->buttons &= ~IN_ATTACK2;
            }
            else
            {
                Cmd->buttons &= ~IN_ATTACK;
            }
        }
        else
        {
            if (*activeWeapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
            {
                Cmd->buttons |= IN_ATTACK2;
            }
            else
            {
                Cmd->buttons |= IN_ATTACK;
            }
            
        }
        
    }
    
}

