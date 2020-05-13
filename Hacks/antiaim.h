//
//  antiaim.hpp
//  vHook
//
#pragma once

#include "main.h"

void DoAntiAim(CUserCmd* cmd, C_BaseCombatWeapon* weapon);
void LegitAA(CUserCmd* cmd, C_BaseCombatWeapon* activeWeapon);
void doManual(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon);
void FakeDuck(CUserCmd* cmd);
void nigga(CUserCmd* cmd, C_BaseCombatWeapon* weapon_handle);

namespace AntiAim
{
    extern Vector realAngle;
    extern Vector fakeAngle;
}
