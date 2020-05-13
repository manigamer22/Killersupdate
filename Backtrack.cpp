//
//  backtrack.cpp
//  vHook
//
//  Created by xxxSkies on 2018-06-20.
//  Copyright © 2018 ViKiNG. All rights reserved.
//

#include "Backtrack.hpp"

#define TICK_INTERVAL            (pGlobals->interval_per_tick)

inline Vector btAngleVector(Vector angle)
{
    auto sy = sin(angle.y / 180.f * static_cast<float>(M_PI));
    auto cy = cos(angle.y / 180.f * static_cast<float>(M_PI));
    
    auto sp = sin(angle.x / 180.f * static_cast<float>(M_PI));
    auto cp = cos(angle.x / 180.f* static_cast<float>(M_PI));
    
    return Vector(cp * cy, cp * sy, -sp);
}

inline float distanceToPoint(Vector point, Vector lineOrigin, Vector dir)
{
    Vector pointDir = point - lineOrigin;
    
    float tempOffset = pointDir.Dot(dir) / (dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    if (tempOffset < 0.000001f)
        return MAXFLOAT;
    
    Vector perpendicularPoint = lineOrigin + (dir * tempOffset);
    
    return (point - perpendicularPoint).Length();
}

void BackTrack::Update(int tick_count)
{
    if (!vars.aimbot.backtrack)
        return;
    
    latest_tick = tick_count;
    for (int i = 0; i < 64; i++)
    {
        UpdateRecord(i);
    }
}

bool BackTrack::IsTickValid(int tick)
{
    int delta = latest_tick - tick;
    float deltaTime = delta * pGlobals->interval_per_tick;
    return (fabs(deltaTime) <= 0.2f);
}

void BackTrack::UpdateRecord(int i)
{
    C_BaseEntity* pEntity = pEntList->GetClientEntity(i);
    if (pEntity && pEntity->GetAlive() && !pEntity->GetDormant())
    {
        float lby = pEntity->GetLowerBodyYawTarget();
        if (lby != records[i].lby)
        {
            records[i].tick_count = latest_tick;
            records[i].lby = lby;
            records[i].headPosition = GetHitboxPosition(pEntity, 0);
        }
    }
    else
    {
        records[i].tick_count = 0;
    }
}

bool BackTrack::RunLBYBackTrack(int i, CUserCmd* cmd, Vector& aimPoint)
{
    if (IsTickValid(records[i].tick_count))
    {
        aimPoint = records[i].headPosition;
        cmd->tick_count = records[i].tick_count;
        return true;
    }
    return false;
}

void BackTrack::legitBackTrack(CUserCmd* cmd, C_BaseEntity* pLocal)
{
    if (vars.aimbot.backtrack)
    {
        int bestTargetIndex = -1;
        float bestFov = MAXFLOAT;
        if (!pLocal->GetAlive())
            return;
        
        for (int i = 0; i < pEngine->GetMaxClients(); i++)
        {
            auto entity = (C_BaseEntity*)pEntList->GetClientEntity(i);
            
            if (!entity || !pLocal)
                continue;
            
            if (entity == pLocal)
                continue;
            
            //if (!pEngine->GetPlayerInfo(pEngine->GetLocalPlayer(), &info))
            //continue; //I am retarded
            
            if (entity->GetDormant())
                continue;
            
            if (entity->GetTeam() == pLocal->GetTeam())
                continue;
            
            if (entity->GetAlive())
            {
                
                float simtime = entity->GetSimulationTime();
                Vector hitboxPos = GetHitboxPosition(entity, 0);
                
                headPositions[i][cmd->command_number % 13] = backtrackData{ simtime, hitboxPos };
                Vector ViewDir    = btAngleVector(cmd->viewangles + (pLocal->GetPunchAngles() * 2.f));
                float FOVDistance = distanceToPoint(hitboxPos, pLocal->GetEyePosition(), ViewDir);
                
                if (bestFov > FOVDistance)
                {
                    bestFov = FOVDistance;
                    bestTargetIndex = i;
                }
            }
        }
        
        float bestTargetSimTime = 0.0;
        if (bestTargetIndex != -1)
        {
            float tempFloat = MAXFLOAT;
            Vector ViewDir    = btAngleVector(cmd->viewangles + (pLocal->GetPunchAngles() * 2.f));
            for (int t = 0; t < 12; ++t)
            {
                float tempFOVDistance = distanceToPoint(headPositions[bestTargetIndex][t].hitboxPos, pLocal->GetEyePosition(), ViewDir);
                if (tempFloat > tempFOVDistance && headPositions[bestTargetIndex][t].simtime > pLocal->GetSimulationTime() - 1)
                {
                    tempFloat = tempFOVDistance;
                    bestTargetSimTime = headPositions[bestTargetIndex][t].simtime;
                }
            }
            if (cmd->buttons & IN_ATTACK)
            {
                cmd->tick_count = TIME_TO_TICKS(bestTargetSimTime);
            }
        }
    }
}

BackTrack* backtracking = new BackTrack();
backtrackData headPositions[64][12];
