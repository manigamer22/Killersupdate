//
//  aimbot.hpp
//  vHook
//
#pragma once

#include "main.h"
#include "GlobalVars.hpp"

void DoAim(CUserCmd* pCmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, float& flForward, float& flSide, C_BasePlayer* player);
void AutoSlow(C_BasePlayer* player, C_BaseCombatWeapon* active_weapon, CUserCmd* cmd);

//void AutoSlow(C_BasePlayer* player, float& forward, float& sideMove, float& bestDamage, C_BaseCombatWeapon* active_weapon, CUserCmd* cmd);
//void velocityhitchance(C_BaseEntity* local, C_BaseCombatWeapon* weapon);


namespace Aimbot
{
    extern C_BaseEntity* curTarget;
    extern std::vector<Hitbox> get_target_hitboxes(C_BaseEntity* entity);
}


enum HITSCAN
{
    low     = 1,
    normal          = 2,
    high      = 3,
    extreme        = 4,
    baim          = 5,
    head          = 6,
    upperbody = 7,
    lowerbody = 8,
    arms = 9,
    legs = 10,
    baimlowerbody = 11
    //test2       = 6,
    //Mixed       = 7,
};

