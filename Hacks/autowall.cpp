// Pasted from aimtux

#include "../Hacks/autowall.h"
#include "../Hacks/aimbot.h"

Vector aim;

static float GetHitgroupDamageMultiplier(HitGroups iHitGroup)
{
    switch (iHitGroup)
    {
        case HitGroups::HITGROUP_HEAD:
            return 4.0f;
        case HitGroups::HITGROUP_CHEST:
        case HitGroups::HITGROUP_LEFTARM:
        case HitGroups::HITGROUP_RIGHTARM:
            return 1.0f;
        case HitGroups::HITGROUP_STOMACH:
            return 1.25f;
        case HitGroups::HITGROUP_LEFTLEG:
        case HitGroups::HITGROUP_RIGHTLEG:
            return 0.75f;
        default:
            return 1.0f;
    }
}

static void ScaleDamage(HitGroups hitgroup, C_BasePlayer* enemy, float weapon_armor_ratio, float& current_damage)
{
    current_damage *= GetHitgroupDamageMultiplier(hitgroup);
    
    if (enemy->GetArmor() > 0.0f && hitgroup < HITGROUP_LEFTLEG)
    {
        if (hitgroup == HITGROUP_HEAD && !enemy->HasHelmet())
            return;
        
        float armorscaled = (weapon_armor_ratio * 0.5f) * current_damage;
        if ((current_damage - armorscaled) * 0.5f > enemy->GetArmor())
            armorscaled = current_damage - (enemy->GetArmor() * 2.0f);
        current_damage = armorscaled;
    }
}

static bool TraceToExit(Vector& end, trace_t* enter_trace, Vector start, Vector dir, trace_t* exit_trace)
{
    float distance = 0.0f;
    
    while (distance <= 90.0f)
    {
        distance += 4.0f;
        end = start + dir * distance;
        
        auto point_contents = pEngineTrace->GetPointContents(end, MASK_SHOT_HULL | CONTENTS_HITBOX, nullptr);
        
        if (point_contents & MASK_SHOT_HULL && !(point_contents & CONTENTS_HITBOX))
            continue;
        
        auto new_end = end - (dir * 4.0f);
        
        Ray_t ray;
        ray.Init(end, new_end);
        pEngineTrace->TraceRay(ray, MASK_SHOT, 0, exit_trace);
        
        if (exit_trace->startsolid && exit_trace->surface.flags & SURF_HITBOX)
        {
            ray.Init(end, start);
            
            CTraceFilter filter;
            filter.pSkip = exit_trace->m_pEnt;
            
            pEngineTrace->TraceRay(ray, 0x600400B, &filter, exit_trace);
            
            if ((exit_trace->fraction < 1.0f || exit_trace->allsolid) && !exit_trace->startsolid)
            {
                end = exit_trace->endpos;
                return true;
            }
            
            continue;
        }
        
        if (!(exit_trace->fraction < 1.0 || exit_trace->allsolid || exit_trace->startsolid) || exit_trace->startsolid)
        {
            if (exit_trace->m_pEnt)
            {
                if (enter_trace->m_pEnt && enter_trace->m_pEnt == pEntList->GetClientEntity(Aimbot::curTarget->GetIndex()))
                    return true;
            }
            
            continue;
        }
        
        if (exit_trace->surface.flags >> 7 & 1 && !(enter_trace->surface.flags >> 7 & 1))
            continue;
        
        if (exit_trace->plane.normal.Dot(dir) <= 1.0f)
        {
            auto fraction = exit_trace->fraction * 4.0f;
            end = end - (dir * fraction);
            
            return true;
        }
    }
    
    return false;
}

static bool HandleBulletPenetration(CCSWeaponInfo* weaponInfo, Autowall::FireBulletData& data)
{
    surfacedata_t *enter_surface_data = pPhysics->GetSurfaceData(data.enter_trace.surface.surfaceProps);
    int enter_material = enter_surface_data->game.material;
    float enter_surf_penetration_mod = enter_surface_data->game.flPenetrationModifier;
    
    data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
    data.current_damage *= powf(weaponInfo->m_flRangeModifier, data.trace_length * 0.002f);
    
    if (data.trace_length > 3000.f || enter_surf_penetration_mod < 0.1f)
        data.penetrate_count = 0;
    
    if (data.penetrate_count <= 0)
        return false;
    
    Vector dummy;
    trace_t trace_exit;
    
    if (!TraceToExit(dummy, &data.enter_trace, data.enter_trace.endpos, data.direction, &trace_exit))
        return false;
    
    surfacedata_t *exit_surface_data = pPhysics->GetSurfaceData(trace_exit.surface.surfaceProps);
    int exit_material = exit_surface_data->game.material;
    
    float exit_surf_penetration_mod = exit_surface_data->game.flPenetrationModifier;
    
    float final_damage_modifier = 0.16f;
    float combined_penetration_modifier = 0.0f;
    
    if ((data.enter_trace.contents & CONTENTS_GRATE) != 0 || enter_material == 89 || enter_material == 71)
    {
        combined_penetration_modifier = 3.0f;
        final_damage_modifier = 0.05f;
    }
    else
        combined_penetration_modifier = (enter_surf_penetration_mod + exit_surf_penetration_mod) * 0.5f;
    
    if (enter_material == exit_material)
    {
        if (exit_material == 87 || exit_material == 85)
            combined_penetration_modifier = 3.0f;
        else if (exit_material == 76)
            combined_penetration_modifier = 2.0f;
    }
    
    float v34 = fmaxf(0.f, 1.0f / combined_penetration_modifier);
    float v35 = (data.current_damage * final_damage_modifier) + v34 * 3.0f * fmaxf(0.0f, (3.0f / weaponInfo->m_flPenetration) * 1.25f);
    float thickness = (trace_exit.endpos - data.enter_trace.endpos).Length();
    
    thickness *= thickness;
    thickness *= v34;
    thickness /= 24.0f;
    
    float lost_damage = fmaxf(0.0f, v35 + thickness);
    
    if (lost_damage > data.current_damage)
        return false;
    
    if (lost_damage >= 0.0f)
        data.current_damage -= lost_damage;
    
    if (data.current_damage < 1.0f)
        return false;
    
    data.src = trace_exit.endpos;
    data.penetrate_count--;
    
    return true;
}

static void TraceLine(Vector vecAbsStart, Vector vecAbsEnd, unsigned int mask, C_BasePlayer* ignore, trace_t* ptr)
{
    Ray_t ray;
    ray.Init(vecAbsStart, vecAbsEnd);
    CTraceFilter filter;
    filter.pSkip = ignore;
    
    pEngineTrace->TraceRay(ray, mask, &filter, ptr);
}

bool VectortoVectorVisible(Vector src, Vector point)
{
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    trace_t Trace;
    TraceLine(src, point, MASK_SOLID, localplayer, &Trace);
    
    if (Trace.fraction == 1.0f)
    {
        return true;
    }
    
    return false;
}

static bool SimulateFireBullet(C_BaseCombatWeapon* pWeapon, bool teamCheck, Autowall::FireBulletData& data)
{
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    CCSWeaponInfo* weaponInfo = pWeapon->GetCSWpnData();
    
    data.penetrate_count = 4;
    data.trace_length = 0.0f;
    data.current_damage = (float) weaponInfo->m_iDamage;
    
    while (data.penetrate_count > 0 && data.current_damage >= 1.0f)
    {
        data.trace_length_remaining = weaponInfo->m_flRange - data.trace_length;
        
        Vector end = data.src + data.direction * data.trace_length_remaining;
        
        // data.enter_trace
        TraceLine(data.src, end, MASK_SHOT, localplayer, &data.enter_trace);
        
        Ray_t ray;
        ray.Init(data.src, end + data.direction * 40.f);
        
        pEngineTrace->TraceRay(ray, MASK_SHOT, &data.filter, &data.enter_trace);
        
        TraceLine(data.src, end + data.direction * 40.f, MASK_SHOT, localplayer, &data.enter_trace);
        
        if (data.enter_trace.fraction == 1.0f)
            break;
        
        if (data.enter_trace.hitgroup <= 7 && data.enter_trace.hitgroup > 0)
        {
            data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
            data.current_damage *= powf(weaponInfo->m_flRangeModifier, data.trace_length * 0.002f);
            
            C_BasePlayer* player = (C_BasePlayer*) data.enter_trace.m_pEnt;
            if (teamCheck && player->GetTeam() == localplayer->GetTeam())
                return false;
            
            ScaleDamage(data.enter_trace.hitgroup, player, weaponInfo->m_flArmorRatio, data.current_damage);
            
            return true;
        }
        
        if (!HandleBulletPenetration(weaponInfo, data))
            break;
    }
    
    return false;
}
bool Autowall::CanHitFloatingPoint(const Vector &point, const Vector &source)
{
    aim = point;
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if (!localplayer)
        return false;
    FireBulletData data;
    
    Vector dst = point;
    
    data.src = localplayer->GetEyePosition();
    
    //  FireBulletData data = FireBulletData(source, localplayer);
    Vector angles = CalcAngle(data.src, dst);
    AngleVectors(angles, &data.direction);
    
    VectorNormalize(data.direction);
    
    C_BaseCombatWeapon* pWeapon = (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
    if (!pWeapon)
        return false;
    
    data.penetrate_count = 1;
    data.trace_length = 0.0f;
    
    CCSWeaponInfo* weaponData = pWeapon->GetCSWpnData();
    
    if (!weaponData)
        return false;
    
    data.current_damage = (float)weaponData->m_iDamage;
    
    data.trace_length_remaining = weaponData->m_flRange - data.trace_length;
    
    Vector end = data.src + data.direction * data.trace_length_remaining;
    
    TraceLine(data.src, end, MASK_SHOT | CONTENTS_HITBOX, localplayer, &data.enter_trace);
    
    if (VectortoVectorVisible(data.src, point))
    {
        return true;
    }
    if (HandleBulletPenetration(weaponData, data))
    {
        return true;
    }
    
    return false;
}
float Autowall::GetDamage(const Vector& point, bool teamCheck, FireBulletData& fData)
{
    float damage = 0.f;
    Vector dst = point;
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    FireBulletData data;
    data.src = localplayer->GetEyePosition();
    data.filter.pSkip = localplayer;
    
    QAngle angles = CalccAngle(data.src, dst);
    AngleVectors3(angles, data.direction);
    
    Vector tmp = data.direction;
    data.direction = tmp.Normalize();
    
    C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) pEntList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
    if (!activeWeapon)
        return -1.0f;
    
    if (SimulateFireBullet(activeWeapon, teamCheck, data))
        damage = data.current_damage;
    
    fData = data;
    
    return damage;
}
