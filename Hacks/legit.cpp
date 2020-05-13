//
//  legit.cpp
//  vHook
//
//  Created by Timothy Dillan on 3/8/19.
//  Copyright © 2019 ViKiNG. All rights reserved.
//

#include "legit.hpp"
#include "autoshoot.h"
#include "antiaim.h"
#include "autowall.h"

C_BaseEntity* LegitAim::curTarget = nullptr; //here


//here
int MakeLegitHitscan(C_BaseEntity* entity, CUserCmd* cmd)
{
    vector<int> hitboxes;
    
    switch (vars.aimbot.legitHitscanType)//here
    {
        case 0:
            hitboxes.push_back(HITBOX_HEAD);
            // hitboxes.push_back(HITBOX_NECK);
            break;
        case 1:
            hitboxes.push_back(HITBOX_UPPER_CHEST);
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            // hitboxes.push_back(HITBOX_BELLY);
            //    hitboxes.push_back(HITBOX_PELVIS);
            break;
        case 2:
            hitboxes.push_back(HITBOX_RIGHT_THIGH);
            hitboxes.push_back(HITBOX_LEFT_THIGH);
            hitboxes.push_back(HITBOX_RIGHT_CALF);
            hitboxes.push_back(HITBOX_LEFT_CALF);
            
            break;
            
    }
    
    if(vars.aimbot.legitHitscan)
    {
        
        int highestdamage_hitbox = 0;
        int highestdamage = 0;
        
        for(auto hit : hitboxes)
        {
            Vector vDest = GetHitboxPosition(entity, hit);
            float thisDamage = 0.f;
            Autowall::FireBulletData data;
            
            thisDamage = Autowall::GetDamage(vDest, true, data);
            
            
            if(thisDamage > highestdamage)
            {
                highestdamage = thisDamage;
                highestdamage_hitbox = hit;
            }
            
        }
        
        return highestdamage_hitbox;
    }
    else
    {
        return vars.aimbot.hitbox;
    }
    
}

int MakeLegitHitscanPistol(C_BaseEntity* entity, CUserCmd* cmd)
{
    vector<int> hitboxes;
    
    switch (vars.aimbot.legitPistolHitscanType)//here
    {
        case 0:
            hitboxes.push_back(HITBOX_HEAD);
            // hitboxes.push_back(HITBOX_NECK);
            break;
        case 1:
            hitboxes.push_back(HITBOX_UPPER_CHEST);
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            // hitboxes.push_back(HITBOX_BELLY);
            //    hitboxes.push_back(HITBOX_PELVIS);
            break;
        case 2:
            hitboxes.push_back(HITBOX_RIGHT_THIGH);
            hitboxes.push_back(HITBOX_LEFT_THIGH);
            hitboxes.push_back(HITBOX_RIGHT_CALF);
            hitboxes.push_back(HITBOX_LEFT_CALF);
            break;
        default:
            break;
            
    }
    
    if(vars.aimbot.legitPistolHitscan)
    {
        
        int highestdamage_hitbox = 0;
        int highestdamage = 0;
        
        for(auto hit : hitboxes)
        {
            Vector vDest = GetHitboxPosition(entity, hit);
            float thisDamage = 0.f;
            Autowall::FireBulletData data;
            
            thisDamage = Autowall::GetDamage(vDest, true, data);
            
            
            if(thisDamage > highestdamage)
            {
                highestdamage = thisDamage;
                highestdamage_hitbox = hit;
            }
            
        }
        
        return highestdamage_hitbox;
    }
    else
    {
        return vars.aimbot.hitbox;
    }
    
}

int MakeLegitHitscanRifle(C_BaseEntity* entity, CUserCmd* cmd)
{
    vector<int> hitboxes;
    
    switch (vars.aimbot.legitRifleHitscanType)//here
    {
        case 0:
            hitboxes.push_back(HITBOX_HEAD);
            // hitboxes.push_back(HITBOX_NECK);
            break;
        case 1:
            hitboxes.push_back(HITBOX_UPPER_CHEST);
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            // hitboxes.push_back(HITBOX_BELLY);
            //    hitboxes.push_back(HITBOX_PELVIS);
            break;
        case 2:
            hitboxes.push_back(HITBOX_RIGHT_THIGH);
            hitboxes.push_back(HITBOX_LEFT_THIGH);
            hitboxes.push_back(HITBOX_RIGHT_CALF);
            hitboxes.push_back(HITBOX_LEFT_CALF);
            break;
        default:
            break;
            
    }
    
    if(vars.aimbot.legitRifleHitscan)
    {
        
        int highestdamage_hitbox = 0;
        int highestdamage = 0;
        
        for(auto hit : hitboxes)
        {
            Vector vDest = GetHitboxPosition(entity, hit);
            float thisDamage = 0.f;
            Autowall::FireBulletData data;
            
            thisDamage = Autowall::GetDamage(vDest, true, data);
            
            
            if(thisDamage > highestdamage)
            {
                highestdamage = thisDamage;
                highestdamage_hitbox = hit;
            }
            
        }
        
        return highestdamage_hitbox;
    }
    else
    {
        return vars.aimbot.hitbox;
    }
    
}

int MakeLegitHitscanSniper(C_BaseEntity* entity, CUserCmd* cmd)
{
    vector<int> hitboxes;
    
    switch (vars.aimbot.legitSniperHitscanType)//here
    {
        case 0:
            hitboxes.push_back(HITBOX_HEAD);
            // hitboxes.push_back(HITBOX_NECK);
            break;
        case 1:
            hitboxes.push_back(HITBOX_UPPER_CHEST);
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            // hitboxes.push_back(HITBOX_BELLY);
            //    hitboxes.push_back(HITBOX_PELVIS);
            break;
        case 2:
            hitboxes.push_back(HITBOX_RIGHT_THIGH);
            hitboxes.push_back(HITBOX_LEFT_THIGH);
            hitboxes.push_back(HITBOX_RIGHT_CALF);
            hitboxes.push_back(HITBOX_LEFT_CALF);
            break;
            
        default:
            break;
            
    }
    
    if(vars.aimbot.legitSniperHitscan)
    {
        
        int highestdamage_hitbox = 0;
        int highestdamage = 0;
        
        for(auto hit : hitboxes)
        {
            Vector vDest = GetHitboxPosition(entity, hit);
            float thisDamage = 0.f;
            Autowall::FireBulletData data;
            
            thisDamage = Autowall::GetDamage(vDest, true, data);
            
            
            if(thisDamage > highestdamage)
            {
                highestdamage = thisDamage;
                highestdamage_hitbox = hit;
            }
            
        }
        
        return highestdamage_hitbox;
    }
    else
    {
        return vars.aimbot.hitbox;
    }
    
}

int MakeLegitHitscanSmg(C_BaseEntity* entity, CUserCmd* cmd)
{
    vector<int> hitboxes;
    
    switch (vars.aimbot.legitSmgHitscanType)//here
    {
        case 0:
            hitboxes.push_back(HITBOX_HEAD);
            // hitboxes.push_back(HITBOX_NECK);
            break;
        case 1:
            hitboxes.push_back(HITBOX_UPPER_CHEST);
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            // hitboxes.push_back(HITBOX_BELLY);
            //    hitboxes.push_back(HITBOX_PELVIS);
            break;
        case 2:
            hitboxes.push_back(HITBOX_RIGHT_THIGH);
            hitboxes.push_back(HITBOX_LEFT_THIGH);
            hitboxes.push_back(HITBOX_RIGHT_CALF);
            hitboxes.push_back(HITBOX_LEFT_CALF);
            
            break;
        default:
            break;
            
    }
    
    if(vars.aimbot.legitSmgHitscan)
    {
        
        int highestdamage_hitbox = 0;
        int highestdamage = 0;
        
        for(auto hit : hitboxes)
        {
            Vector vDest = GetHitboxPosition(entity, hit);
            float thisDamage = 0.f;
            Autowall::FireBulletData data;
            
            thisDamage = Autowall::GetDamage(vDest, true, data);
            
            
            if(thisDamage > highestdamage)
            {
                highestdamage = thisDamage;
                highestdamage_hitbox = hit;
            }
            
        }
        
        return highestdamage_hitbox;
    }
    else
    {
        return vars.aimbot.hitbox;
    }
    
}

int MakeLegitHitscanHeavy(C_BaseEntity* entity, CUserCmd* cmd)
{
    vector<int> hitboxes;
    
    switch (vars.aimbot.legitHeavyHitscanType)//here
    {
        case 0:
            hitboxes.push_back(HITBOX_HEAD);
            // hitboxes.push_back(HITBOX_NECK);
            break;
        case 1:
            hitboxes.push_back(HITBOX_UPPER_CHEST);
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            // hitboxes.push_back(HITBOX_BELLY);
            //    hitboxes.push_back(HITBOX_PELVIS);
            break;
        case 2:
            hitboxes.push_back(HITBOX_RIGHT_THIGH);
            hitboxes.push_back(HITBOX_LEFT_THIGH);
            hitboxes.push_back(HITBOX_RIGHT_CALF);
            hitboxes.push_back(HITBOX_LEFT_CALF);
            
            break;
         default:
            break;
    }
    
    if(vars.aimbot.legitHeavyHitscan)
    {
        
        int highestdamage_hitbox = 0;
        int highestdamage = 0;
        
        for(auto hit : hitboxes)
        {
            Vector vDest = GetHitboxPosition(entity, hit);
            float thisDamage = 0.f;
            Autowall::FireBulletData data;
            
            thisDamage = Autowall::GetDamage(vDest, true, data);
            
            
            if(thisDamage > highestdamage)
            {
                highestdamage = thisDamage;
                highestdamage_hitbox = hit;
            }
            
        }
        
        return highestdamage_hitbox;
    }
    else
    {
        return vars.aimbot.hitbox;
    }
    
}

void NormalizeAnglesLol(Vector& angle) {
    while (angle.x > 89.0f)
        angle.x -= 180.f;
    
    while (angle.x < -89.0f)
        angle.x += 180.f;
    
    while (angle.y > 180.f)
        angle.y -= 360.f;
    
    while (angle.y < -180.f)
        angle.y += 360.f;
}

Vector Smooth(Vector& angle, C_BaseCombatWeapon* activeWeapon)
{
    if (!vars.aimbot.LegitEnabled)
        return;
    
    if (!vars.aimbot.smooth) // here
        return;
    
    if (vars.aimbot.silent)
        return;
    
    // if(activeWeapon->IsSnipScope() || activeWeapon->IsShotGun())
    //     vars.aimbot.smooth = false;
    
    Vector viewAngles = Vector(0.f, 0.f, 0.f);
    pEngine->GetViewAngles(viewAngles);
    
    Vector delta = angle - viewAngles;
    NormalizeAnglesLol(delta);
    //here
    float smooth = powf(vars.aimbot.smoothf, 0.4f); // Makes more slider space for actual useful values
    
    smooth = min(0.959999f, smooth); //std::min
    
    
    Vector toChange = Vector();
    //  switch (vars.aimbot.smoothtype)
    
    toChange = delta - delta * smooth;
    
    
    return angle = viewAngles + toChange;
}

Vector SmoothPistol(Vector& angle, C_BaseCombatWeapon* activeWeapon)
{
    if (!vars.aimbot.LegitEnabled)
        return;
    
    if (!vars.aimbot.pistolsmooth) // here
        return;
    
    if (vars.aimbot.silent)
        return;
    
    if (!activeWeapon->IsPistol())
        return;
    
    Vector viewAngles = Vector(0.f, 0.f, 0.f);
    pEngine->GetViewAngles(viewAngles);
    
    Vector delta = angle - viewAngles;
    NormalizeAnglesLol(delta);
    //here
    float smooth = powf(vars.aimbot.pistolsmoothf, 0.4f); // Makes more slider space for actual useful values
    
    smooth = min(0.959999f, smooth); //std::min
    
    
    Vector toChange = Vector();
    //  switch (vars.aimbot.smoothtype)
    
    toChange = delta - delta * smooth;
    
    
    return angle = viewAngles + toChange;
}

Vector SmoothRifle(Vector& angle, C_BaseCombatWeapon* activeWeapon)
{
    if (!vars.aimbot.LegitEnabled)
        return;
    
    if (!vars.aimbot.riflesmooth) // here
        return;
    
    if (vars.aimbot.silent)
        return;
    
    if (!activeWeapon->IsRifle())
        return;
    
    Vector viewAngles = Vector(0.f, 0.f, 0.f);
    pEngine->GetViewAngles(viewAngles);
    
    Vector delta = angle - viewAngles;
    NormalizeAnglesLol(delta);
    //here
    float smooth = powf(vars.aimbot.riflesmoothf, 0.4f); // Makes more slider space for actual useful values
    
    smooth = min(0.959999f, smooth); //std::min
    
    
    Vector toChange = Vector();
    //  switch (vars.aimbot.smoothtype)
    
    toChange = delta - delta * smooth;
    
    
    return angle = viewAngles + toChange;
}

Vector SmoothSniper(Vector& angle, C_BaseCombatWeapon* activeWeapon)
{
    if (!vars.aimbot.LegitEnabled)
        return;
    
    if (!vars.aimbot.snipersmooth) // here
        return;
    
    if (vars.aimbot.silent)
        return;
    
    if (!activeWeapon->IsSnipScope1())
        return;
    
    Vector viewAngles = Vector(0.f, 0.f, 0.f);
    pEngine->GetViewAngles(viewAngles);
    
    Vector delta = angle - viewAngles;
    NormalizeAnglesLol(delta);
    //here
    float smooth = powf(vars.aimbot.snipersmoothf, 0.4f); // Makes more slider space for actual useful values
    
    smooth = min(0.959999f, smooth); //std::min
    
    
    Vector toChange = Vector();
    //  switch (vars.aimbot.smoothtype)
    
    toChange = delta - delta * smooth;
    
    
    return angle = viewAngles + toChange;
}

Vector SmoothSmg(Vector& angle, C_BaseCombatWeapon* activeWeapon)
{
    if (!vars.aimbot.LegitEnabled)
        return;
    
    if (!vars.aimbot.smgsmooth) // here
        return;
    
    if (vars.aimbot.silent)
        return;
    
    if (!activeWeapon->IsSmg())
        return;
    
    Vector viewAngles = Vector(0.f, 0.f, 0.f);
    pEngine->GetViewAngles(viewAngles);
    
    Vector delta = angle - viewAngles;
    NormalizeAnglesLol(delta);
    //here
    float smooth = powf(vars.aimbot.smgsmoothf, 0.4f); // Makes more slider space for actual useful values
    
    smooth = min(0.959999f, smooth); //std::min
    
    
    Vector toChange = Vector();
    //  switch (vars.aimbot.smoothtype)
    
    toChange = delta - delta * smooth;
    
    
    return angle = viewAngles + toChange;
}

Vector SmoothHeavy(Vector& angle, C_BaseCombatWeapon* activeWeapon)
{
    if (!vars.aimbot.LegitEnabled)
        return;
    
    if (!vars.aimbot.heavysmooth) // here
        return;
    
    if (vars.aimbot.silent)
        return;
    
    if (!activeWeapon->IsHeavy())
        return;
    
    Vector viewAngles = Vector(0.f, 0.f, 0.f);
    pEngine->GetViewAngles(viewAngles);
    
    Vector delta = angle - viewAngles;
    NormalizeAnglesLol(delta);
    //here
    float smooth = powf(vars.aimbot.heavysmoothf, 0.4f); // Makes more slider space for actual useful values
    
    smooth = min(0.959999f, smooth); //std::min
    
    
    Vector toChange = Vector();
    //  switch (vars.aimbot.smoothtype)
    
    toChange = delta - delta * smooth;
    
    
    return angle = viewAngles + toChange;
}

void DoLegitAim(CUserCmd* pCmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, float& flForward, float& flSide)//here
{
    
    if(!vars.aimbot.LegitEnabled)
        return;
    
    Vector eyepos = local->GetEyePosition();
    
    for(int i = 0; i < pEntList->GetHighestEntityIndex(); i++)
    {
        auto* entity = pEntList->GetClientEntity(i);
        
        if(!entity)
            continue;
        
        if(entity == local)
            continue;
        
        if(entity->GetTeam() == local->GetTeam())
            continue;
        
        if(entity->GetHealth() < 1)
            continue;
        
        if(entity->GetDormant())
            continue;
        
        if(entity->GetImmune())
            continue;
        
        if(weapon->GetAmmo() < 1)
            continue;
        
        if(entity->GetClientClass()->m_ClassID == (int)CHostage)
            continue;
        
        if(weapon->IsKnife() || weapon->IsBomb())
            continue;
        
        if(gCorrections[entity->GetIndex()].whitelist)
            continue;
        
        
        Vector vFrom, vTo;
        
        LegitAim::curTarget = entity;//here
        
        
        
        if(vars.aimbot.legitPistolHitscan && weapon->IsPistol()){
            vFrom = GetHitboxPosition(entity, MakeLegitHitscanPistol(entity, pCmd));//here
        }
        if(vars.aimbot.legitRifleHitscan && weapon->IsRifle()){
            vFrom = GetHitboxPosition(entity, MakeLegitHitscanRifle(entity, pCmd));//here
        }
        if(vars.aimbot.legitSniperHitscan && weapon->IsSnipScope1()){
            vFrom = GetHitboxPosition(entity, MakeLegitHitscanSniper(entity, pCmd));//here
        }
        if(vars.aimbot.legitSmgHitscan && weapon->IsSmg()){
            vFrom = GetHitboxPosition(entity, MakeLegitHitscanSmg(entity, pCmd));//here
        }
        if(vars.aimbot.legitHeavyHitscan && weapon->IsHeavy()){
            vFrom = GetHitboxPosition(entity, MakeLegitHitscanHeavy(entity, pCmd));//here
        }
        
        
        vTo = CalcAngle(eyepos, vFrom);
        
        auto isVISIBLE = IsVisible(entity);
        float getdmg = 0.f;
        Autowall::FireBulletData data;
        bool canHit = false;
        
        if(vars.aimbot.autowall)
        {
            getdmg = Autowall::GetDamage(vFrom, true, data);
            canHit = getdmg >= vars.aimbot.mindmg;
        }
        
        
        if(canHit || isVISIBLE)
        {
            if((GetFOV(pCmd->viewangles, local->GetEyePosition(), vFrom) <= vars.aimbot.pistolFOV && weapon->IsPistol())) //here
            {
                bool bAttack = true;
                
                if (weapon->GetNextPrimaryAttack() - pGlobals->interval_per_tick > local->GetTickBase() * pGlobals->interval_per_tick)
                    bAttack = false;
                
                if(pCmd->buttons & IN_ATTACK)
                {
                    
                    if(vars.aimbot.pistolsmooth){
                        pCmd->viewangles = SmoothPistol(vTo, weapon);
                    }
                    
                    if(!vars.aimbot.silent)
                    {
                        pCmd->viewangles = vTo;
                        pEngine->SetViewAngles(pCmd->viewangles);
                    }
                    else
                    {
                        pCmd->viewangles = vTo;
                    }
                    
                }
                
            }
            if((GetFOV(pCmd->viewangles, local->GetEyePosition(), vFrom) <= vars.aimbot.rifleFOV && weapon->IsRifle())) //here
            {
                bool bAttack = true;
                
                if (weapon->GetNextPrimaryAttack() - pGlobals->interval_per_tick > local->GetTickBase() * pGlobals->interval_per_tick)
                    bAttack = false;
                
                if(pCmd->buttons & IN_ATTACK)
                {
                    
                    if(vars.aimbot.riflesmooth){
                        pCmd->viewangles = SmoothRifle(vTo, weapon);
                    }
                    
                    if(!vars.aimbot.silent)
                    {
                        pCmd->viewangles = vTo;
                        pEngine->SetViewAngles(pCmd->viewangles);
                    }
                    else
                    {
                        pCmd->viewangles = vTo;
                    }
                    
                }
                
            }
            if((GetFOV(pCmd->viewangles, local->GetEyePosition(), vFrom) <= vars.aimbot.sniperFOV && weapon->IsSnipScope1())) //here
            {
                bool bAttack = true;
                
                if (weapon->GetNextPrimaryAttack() - pGlobals->interval_per_tick > local->GetTickBase() * pGlobals->interval_per_tick)
                    bAttack = false;
                
                if(pCmd->buttons & IN_ATTACK)
                {
                    
                    if(vars.aimbot.snipersmooth){
                        pCmd->viewangles = SmoothSniper(vTo, weapon);
                    }
                    
                    if(!vars.aimbot.silent)
                    {
                        pCmd->viewangles = vTo;
                        pEngine->SetViewAngles(pCmd->viewangles);
                    }
                    else
                    {
                        pCmd->viewangles = vTo;
                    }
                    
                }
                
            }
            if((GetFOV(pCmd->viewangles, local->GetEyePosition(), vFrom) <= vars.aimbot.smgFOV && weapon->IsSmg())) //here
            {
                bool bAttack = true;
                
                if (weapon->GetNextPrimaryAttack() - pGlobals->interval_per_tick > local->GetTickBase() * pGlobals->interval_per_tick)
                    bAttack = false;
                
                if(pCmd->buttons & IN_ATTACK)
                {
                    
                    if(vars.aimbot.smgsmooth){
                        pCmd->viewangles = SmoothSmg(vTo, weapon);
                    }
                    
                    if(!vars.aimbot.silent)
                    {
                        pCmd->viewangles = vTo;
                        pEngine->SetViewAngles(pCmd->viewangles);
                    }
                    else
                    {
                        pCmd->viewangles = vTo;
                    }
                    
                }
                
            }
            if((GetFOV(pCmd->viewangles, local->GetEyePosition(), vFrom) <= vars.aimbot.heavyFOV && weapon->IsHeavy())) //here
            {
                bool bAttack = true;
                
                if (weapon->GetNextPrimaryAttack() - pGlobals->interval_per_tick > local->GetTickBase() * pGlobals->interval_per_tick)
                    bAttack = false;
                
                if(pCmd->buttons & IN_ATTACK)
                {
                    
                    if(vars.aimbot.heavysmooth){
                        pCmd->viewangles = SmoothHeavy(vTo, weapon);
                    }
                    
                    if(!vars.aimbot.silent)
                    {
                        pCmd->viewangles = vTo;
                        pEngine->SetViewAngles(pCmd->viewangles);
                    }
                    else
                    {
                        pCmd->viewangles = vTo;
                    }
                    
                }
                
            }
            
        }
        
    }
}
