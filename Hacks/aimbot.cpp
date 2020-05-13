//
//  aimbot.cpp
//  vHook
//

#include "aimbot.h"
#include "autoshoot.h"
#include "antiaim.h"
#include "autowall.h"
#include "logshots.hpp"

C_BaseEntity* Aimbot::curTarget = nullptr;

inline float FasttSqrt(float x)
{
    unsigned int i = *(unsigned int*)& x;
    i += 127 << 23;
    i >>= 1;
    return *(float*)& i;
}
#define square( x ) ( x * x )

template<class T, class U>
inline T clamp(T in, U low, U high)
{
    if (in <= low)
        return low;
    else if (in >= high)
        return high;
    else
        return in;
}

float LagFix()
{
    float updaterate = pCvar->FindVar("cl_updaterate")->GetFloat();
    ConVar* minupdate = pCvar->FindVar("sv_minupdaterate");
    ConVar* maxupdate = pCvar->FindVar("sv_maxupdaterate");
    
    if (minupdate && maxupdate)
        updaterate = maxupdate->GetFloat();
    
    float ratio = pCvar->FindVar("cl_interp_ratio")->GetFloat();
    
    if (ratio == 0)
        ratio = 1.0f;
    
    float lerp = pCvar->FindVar("cl_interp")->GetFloat();
    ConVar* cmin = pCvar->FindVar("sv_client_min_interp_ratio");
    ConVar* cmax = pCvar->FindVar("sv_client_max_interp_ratio");
    
    if (cmin && cmax && cmin->GetFloat() != 1)
        ratio = clamp(ratio, cmin->GetFloat(), cmax->GetFloat());
    
    return std::max(lerp, ratio / updaterate);
}

bool shouldBaim(C_BaseEntity* pEnt){
    
    auto LocalPlayer = pEntList->GetClientEntity(pEngine->GetLocalPlayer());

    if (LocalPlayer->GetVelocity().Length2D() > 125 && vars.aimbot.baim_high_inaccuracy)
        return true;

    if (!(pEnt->GetFlags() & FL_ONGROUND) && vars.aimbot.baim_in_air)
        return true;
    
    if (vars.aimbot.baim_slow_walk && (pEnt->GetVelocity().Length2D() > 15 && pEnt->GetVelocity().Length2D() < 150))
        return true;
    
    if (pEnt->GetHealth() <= vars.aimbot.bodyaim_health + 1 && vars.aimbot.bodyaim_health > 0 && vars.aimbot.baimhp)
        return true;

}

std::vector<Hitbox> Aimbot::get_target_hitboxes(C_BaseEntity* entity)
{
    std::vector<Hitbox> hitboxes;
    bool Baim = shouldBaim(entity);
    if(Baim){
            hitboxes.push_back(HITBOX_PELVIS);
            hitboxes.push_back(HITBOX_THORAX);
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            hitboxes.push_back(HITBOX_UPPER_CHEST);

            hitboxes.push_back(HITBOX_RIGHT_FOOT);
            hitboxes.push_back(HITBOX_LEFT_FOOT);
            hitboxes.push_back(HITBOX_RIGHT_UPPER_ARM);
            hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
            hitboxes.push_back(HITBOX_LEFT_THIGH);
            hitboxes.push_back(HITBOX_RIGHT_THIGH);
    }else{
        if (vars.aimbot.hitscantype == HITSCAN::low)
        { // low
            hitboxes.push_back(HITBOX_HEAD);
            hitboxes.push_back(HITBOX_NECK);
            hitboxes.push_back(HITBOX_PELVIS);
            hitboxes.push_back(HITBOX_BELLY);
            hitboxes.push_back(HITBOX_THORAX);
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            hitboxes.push_back(HITBOX_UPPER_CHEST);
        }
        if (vars.aimbot.hitscantype == HITSCAN::normal)
        { //normal
            hitboxes.push_back(HITBOX_HEAD);
            hitboxes.push_back(HITBOX_NECK);
            hitboxes.push_back(HITBOX_BELLY);
            hitboxes.push_back(HITBOX_PELVIS);
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            hitboxes.push_back(HITBOX_UPPER_CHEST);
            hitboxes.push_back(HITBOX_RIGHT_UPPER_ARM);
            hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
            hitboxes.push_back(HITBOX_RIGHT_THIGH);
            hitboxes.push_back(HITBOX_LEFT_THIGH);
            
        }
        if (vars.aimbot.hitscantype == HITSCAN::high)
        { //high
            hitboxes.push_back(HITBOX_HEAD);
            hitboxes.push_back(HITBOX_NECK);
            hitboxes.push_back(HITBOX_BELLY);
            hitboxes.push_back(HITBOX_UPPER_CHEST);
            hitboxes.push_back(HITBOX_RIGHT_UPPER_ARM);
            hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
            hitboxes.push_back(HITBOX_RIGHT_THIGH);
            hitboxes.push_back(HITBOX_LEFT_THIGH);
            hitboxes.push_back(HITBOX_RIGHT_CALF);
            hitboxes.push_back(HITBOX_LEFT_CALF);
            hitboxes.push_back(HITBOX_LEFT_FOREARM);
            hitboxes.push_back(HITBOX_RIGHT_FOREARM);
        }
        
        if (vars.aimbot.hitscantype == HITSCAN::extreme)
        {
            //extreme
            hitboxes.push_back(HITBOX_HEAD);
            hitboxes.push_back(HITBOX_NECK);
            hitboxes.push_back(HITBOX_PELVIS);
            hitboxes.push_back(HITBOX_BELLY);
            hitboxes.push_back(HITBOX_THORAX);
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            hitboxes.push_back(HITBOX_UPPER_CHEST);
            hitboxes.push_back(HITBOX_RIGHT_THIGH);
            hitboxes.push_back(HITBOX_LEFT_THIGH);
            hitboxes.push_back(HITBOX_RIGHT_CALF);
            hitboxes.push_back(HITBOX_LEFT_CALF);
            hitboxes.push_back(HITBOX_RIGHT_FOOT);
            hitboxes.push_back(HITBOX_LEFT_FOOT);
            hitboxes.push_back(HITBOX_RIGHT_HAND);
            hitboxes.push_back(HITBOX_LEFT_HAND);
            hitboxes.push_back(HITBOX_RIGHT_UPPER_ARM);
            hitboxes.push_back(HITBOX_RIGHT_FOREARM);
            hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
            hitboxes.push_back(HITBOX_LEFT_FOREARM);
        }
        if (vars.aimbot.hitscantype == HITSCAN::baim)
        {
            hitboxes.push_back(HITBOX_PELVIS);
            hitboxes.push_back(HITBOX_BELLY);
            hitboxes.push_back(HITBOX_THORAX);
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            hitboxes.push_back(HITBOX_UPPER_CHEST);
        }
        if (vars.aimbot.hitscantype == HITSCAN::head){
            hitboxes.push_back(HITBOX_HEAD);
        }
        if (vars.aimbot.hitscantype == HITSCAN::upperbody){
            hitboxes.push_back(HITBOX_HEAD);
            hitboxes.push_back(HITBOX_BELLY);
            hitboxes.push_back(HITBOX_PELVIS);
        }
        if (vars.aimbot.hitscantype == HITSCAN::lowerbody){
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            hitboxes.push_back(HITBOX_BELLY);
            hitboxes.push_back(HITBOX_PELVIS);
            hitboxes.push_back(HITBOX_LEFT_THIGH);
            hitboxes.push_back(HITBOX_RIGHT_THIGH);
            hitboxes.push_back(HITBOX_RIGHT_FOOT);
            hitboxes.push_back(HITBOX_LEFT_FOOT);
            hitboxes.push_back(HITBOX_RIGHT_UPPER_ARM);
            hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
            hitboxes.push_back(HITBOX_RIGHT_FOREARM);
            hitboxes.push_back(HITBOX_LEFT_FOREARM);
            hitboxes.push_back(HITBOX_RIGHT_HAND);
            hitboxes.push_back(HITBOX_LEFT_HAND);
        }
        if (vars.aimbot.hitscantype == HITSCAN::arms){
            hitboxes.push_back(HITBOX_RIGHT_UPPER_ARM);
            hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
            hitboxes.push_back(HITBOX_RIGHT_FOREARM);
            hitboxes.push_back(HITBOX_LEFT_FOREARM);
            hitboxes.push_back(HITBOX_RIGHT_HAND);
            hitboxes.push_back(HITBOX_LEFT_HAND);
        }
        if (vars.aimbot.hitscantype == HITSCAN::legs){
            hitboxes.push_back(HITBOX_PELVIS);
            hitboxes.push_back(HITBOX_LEFT_THIGH);
            hitboxes.push_back(HITBOX_RIGHT_THIGH);
            hitboxes.push_back(HITBOX_RIGHT_FOOT);
            hitboxes.push_back(HITBOX_LEFT_FOOT);
        }
        if(vars.aimbot.hitscantype == HITSCAN::baimlowerbody){
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            hitboxes.push_back(HITBOX_BELLY);
            hitboxes.push_back(HITBOX_PELVIS);
            hitboxes.push_back(HITBOX_LEFT_THIGH);
            hitboxes.push_back(HITBOX_RIGHT_THIGH);
            hitboxes.push_back(HITBOX_RIGHT_FOOT);
            hitboxes.push_back(HITBOX_LEFT_FOOT);
            hitboxes.push_back(HITBOX_RIGHT_UPPER_ARM);
            hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
            hitboxes.push_back(HITBOX_RIGHT_FOREARM);
            hitboxes.push_back(HITBOX_LEFT_FOREARM);
            hitboxes.push_back(HITBOX_RIGHT_HAND);
            hitboxes.push_back(HITBOX_LEFT_HAND);
            hitboxes.push_back(HITBOX_THORAX);
            hitboxes.push_back(HITBOX_UPPER_CHEST);
            hitboxes.push_back(HITBOX_RIGHT_CALF);
            hitboxes.push_back(HITBOX_LEFT_CALF);
        }
    }
    return hitboxes;
}

int MakeHitscan(C_BaseEntity* entity, CUserCmd* cmd)
{
    auto hitboxes = Aimbot::get_target_hitboxes(entity);
    int best_damage = 0;
    int best_hitbox = HITBOX_HEAD;
    bool Baim = shouldBaim(entity);
    
    for(auto hitbox : hitboxes)
    {
        if(vars.aimbot.autowall || vars.aimbot.hitscan)
        {
            Vector aim_pos = GetHitboxPosition(entity, hitbox);
            
            if(aim_pos.IsZero())
                continue;
            
            Autowall::FireBulletData data;
            
            int damage = Autowall::GetDamage(aim_pos, true, data);
            
            if(damage > best_damage)
            {
                best_damage = damage;
                best_hitbox = hitbox;
            }
            if (Baim && hitbox != 0 && hitbox != 25 && hitbox != 26 && hitbox != 27 && damage >= (entity->GetHealth() + 10))
            {
                Baim = true;
            }
        }
        else
        {
            if(IsVisible1(entity, hitbox))
                return hitbox;
        }
    }
    return best_hitbox;
}
void AutoStop(C_BaseCombatWeapon* weapon, CUserCmd* pCmd)
{
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    ItemDefinitionIndex itemDefinitionIndex = *weapon->GetItemDefinitionIndexx();
    if (itemDefinitionIndex == ItemDefinitionIndex::WEAPON_TASER)
            return;
    
        if (!(localplayer->GetFlags() & FL_ONGROUND))
            return;
    
        Vector Velocity = localplayer->GetVelocity();
        static float Speed = 450.f;
    
        Vector Direction;
        Vector RealView;
        VectorAngles(Velocity, Direction);
        pEngine->GetViewAngles(RealView += 180);
        Direction.y = RealView.y - Direction.y;
    
        Vector Forward;
        AngleVectors(Direction, &Forward);
        Vector NegativeDirection = Forward * -Speed;
    
        pCmd->forwardmove = NegativeDirection.x;
        pCmd->sidemove = NegativeDirection.y;
}
void DoAim(CUserCmd* pCmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, float& flForward, float& flSide, C_BasePlayer* player)
{
    
    if(!vars.aimbot.enabled)
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
        
        if(entity->IsGhost()) ///<== Aimbot.cpp
            continue; // Ghost Fix
        
        if(entity->GetDormant())
            continue;
        
        if(entity->GetImmune())
            continue;
        
        if(weapon->GetAmmo() < 1)
            continue;
        
        if(entity->GetClientClass()->m_ClassID == (int)CHostage)
            continue;
        
        if(weapon->IsKnife() || weapon->IsBomb() || weapon->IsGrenade())
            continue;
        
        if(gCorrections[entity->GetIndex()].whitelist)
            continue;
        
        Vector vFrom, vTo;
        
        Aimbot::curTarget = entity;
        
        vFrom = GetHitboxPosition(entity, MakeHitscan(entity, pCmd));
        
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
            if(GetFOV(pCmd->viewangles, local->GetEyePosition(), vFrom) <= vars.aimbot.FovToPlayer)
            {
                if(vars.aimbot.autoshoot)
                {
                    AutoShoot(player, weapon, pCmd);
                    AutoCock(player, pCmd, weapon);
                }
                
                if(vars.aimbot.autocrouch)
                {
                    pCmd->buttons |= IN_BULLRUSH | IN_DUCK;
                }
                
                if (vars.aimbot.autostop){
                    AutoStop(weapon, pCmd);
                }
                if (pCmd->buttons & IN_ATTACK && vars.misc.logshots && player){
                    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
                    LogShots::shots.push_back(Shots(player, localplayer->GetEyePosition(), pGlobals->curtime));
                }
                bool bAttack = true;
                
                if (weapon->GetNextPrimaryAttack() - pGlobals->interval_per_tick > local->GetTickBase() * pGlobals->interval_per_tick)
                    bAttack = false;
                
                if(pCmd->buttons & IN_ATTACK)
                {
                     pCmd->tick_count = TIME_TO_TICKS(entity->GetSimulationTime() + LagFix());
                    
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
                g::Shot[entity->GetIndex()] = true;
            }
            
        }
        
    }
    
}
    














