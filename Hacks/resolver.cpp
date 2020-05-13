#include "main.h"
#include "resolver.h"
#include "logshots.hpp"
#include "autowall.h"
#include "GlobalVars.hpp"
#define TICKS_TO_TIME( t )        ( pGlobals->interval_per_tick *( t ) )

float GetDelta(CCSGOAnimState *animState ) {
    
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
float YawDistance(float firstangle, float secondangle)
{
    if (firstangle == secondangle)
        return 0.f;

    bool oppositeSides = false;

    if (firstangle > 0 && secondangle < 0)
        oppositeSides = true;
    else if (firstangle < 0 && secondangle > 0)
        oppositeSides = true;

    if (!oppositeSides)
        return fabs(firstangle - secondangle);

    if (firstangle > 90 && secondangle < -90)
    {
        firstangle -= (firstangle - 90);
        secondangle += (secondangle + 90);
    }
    else if (firstangle < -90 && secondangle > 90)
    {
        firstangle += (firstangle + 90);
        secondangle -= (secondangle - 90);
    }

    float oneTwo;

    oneTwo = fabs(firstangle - secondangle);

    return oneTwo;
}
void StaticDesyncResolve(C_BaseEntity* entity)
{
    int angle1[64];
    int angle2[64];
    static float old_simtime[65];
    bool using_fake_angles[65];

    if (old_simtime[entity->GetIndex()] != entity->GetSimulationTime())
        angle1[entity->GetIndex()] = entity->GetEyeAnglesss().y;
    else
        angle2[entity->GetIndex()] = entity->GetEyeAnglesss().y;

    if (angle1[entity->GetIndex()] != angle2[entity->GetIndex()])
        using_fake_angles[entity->GetIndex()] = true;
    else
        using_fake_angles[entity->GetIndex()] = false;

    if (using_fake_angles[entity->GetIndex()])
    {
        if (YawDistance(angle1[entity->GetIndex()], angle2[entity->GetIndex()]) <= 58)
        {
            entity->GetEyeAnglesPointer()->y = entity->GetLowerBodyYawTarget() - YawDistance(angle1[entity->GetIndex()], angle2[entity->GetIndex()]);
        }
    }

    old_simtime[entity->GetIndex()] = entity->GetSimulationTime();
}

void Guess(C_BaseEntity* ent)
{
    // 0,1,2 not 1,2,3. someone doesn't know how '%' works, eh? -swoopae
    switch (LogShots::missedShots[ent->GetIndex()] % 3)
    {
    case 0:
        StaticDesyncResolve(ent); break;
    case 1:
        ent->GetEyeAnglesPointer()->y += GetDelta(ent->GetAnimState()); break;
    case 2:
        ent->GetEyeAnglesPointer()->y -= GetDelta(ent->GetAnimState()); break;
    }
}

void Resolve(C_BaseEntity* pEnt)
{
    auto animState = pEnt->GetAnimState();
    
    if(!animState)
        return;
    
    /*C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if ( pEnt != localplayer && (pEnt->GetTeam() != localplayer->GetTeam()) && vars.aimbot.Yawresolver){
        
        if(LogShots::missedShots[pEnt->GetIndex() < 2]){
            
                        auto v48 = 0.f;
            
                        if (animState->feetShuffleSpeed >= 0.0f)
                        {
                            v48 = fminf(animState->feetShuffleSpeed, 1.0f);
                        }
                        else
                        {
                            v48 = 0.0f;
                        }
            
                        float v49 = ((animState->runningAccelProgress * -0.30000001) - 0.19999999) * v48;
            
                        float flYawModifier = v49 + 1.0;
            
                        if (animState->duckProgress > 0.0)
                        {
                            float v53 = 0.0f;
            
                            if (animState->feetShuffleSpeed2 >= 0.0)
                            {
                                v53 = fminf(animState->feetShuffleSpeed2, 1.0);
                            }
                            else
                            {
                                v53 = 0.0f;
                            }
                        }
            
                        float flMaxYawModifier = flYawModifier * 58.f ;
                        float flMinYawModifier = flYawModifier * -58.f ;
            
                        float newFeetYaw = 0.f;
            
                        auto eyeYaw = animState->yaw;
            
                        auto lbyYaw = animState->goalFeetYaw;
            
                        float eye_feet_delta = fabs(eyeYaw - lbyYaw);
            
                        if (eye_feet_delta <= flMaxYawModifier)
                        {
                            if (flMinYawModifier > eye_feet_delta)
                            {
                                newFeetYaw = fabs(flMinYawModifier) + eyeYaw;
                            }
                        }
                        else
                        {
                            newFeetYaw = eyeYaw - fabs(flMaxYawModifier);
                        }
            
                        float v136 = fmod(newFeetYaw, 360.0);
            
                        if (v136 > 180.0)
                        {
                            v136 = v136 - 360.0;
                        }
            
                        if (v136 < 180.0)
                        {
                            v136 = v136 + 360.0;
                        }
            
                        animState->goalFeetYaw = v136;
        }else{
            Guess(pEnt);
        }
            LogShots::missedShots[pEnt->GetIndex()] = LogShots::missedShots[pEnt->GetIndex()] % 6;
        }*/
    pEnt->GetEyeAnglesPointer()->y = (rand() % 2) ?
    pEnt->GetEyeAnglesPointer()->y + (GetDelta(pEnt->GetAnimState()) * 0.66f) :
    pEnt->GetEyeAnglesPointer()->y - (GetDelta(pEnt->GetAnimState()) * 0.66f);
}
void AnimationFix(C_BaseEntity* pEnt)
{
    const auto player_animation_state = pEnt->GetAnimState();
 
 
    if (!player_animation_state)
        return;
 
    if (LogShots::missedShots[pEnt->GetIndex()] > 2) {
        switch (LogShots::missedShots[pEnt->GetIndex()] % 4) {
            case 0: player_animation_state->goalFeetYaw = player_animation_state->goalFeetYaw + 60; break;
            case 1: player_animation_state->goalFeetYaw = player_animation_state->goalFeetYaw - 60; break;
            case 2: player_animation_state->goalFeetYaw = player_animation_state->goalFeetYaw - 60; break;
            case 3: player_animation_state->goalFeetYaw = player_animation_state->goalFeetYaw + 60; break;
        }
        pEnt->UpdateClientAnimation();
        auto old_curtime = pGlobals->curtime;
        auto old_frametime = pGlobals->frametime;
        auto curtime = pGlobals->curtime;
        auto frametimne = (pGlobals->frametime);
        auto absoluteframtime = (pGlobals->absoluteframetime);
        auto framecount = pGlobals->framecount;
        auto tickcount = pGlobals->tickcount;
        pGlobals->realtime = pEnt->GetSimulationTime();
        pGlobals->curtime = pEnt->GetSimulationTime();
        pGlobals->frametime = pGlobals->interval_per_tick;
        pGlobals->absoluteframetime = pGlobals->interval_per_tick;
        pGlobals->framecount = pEnt->GetSimulationTime();
        pGlobals->tickcount = pEnt->GetSimulationTime();
        pGlobals->interpolation_amount = 0.0f;
        pGlobals->curtime = pEnt->GetSimulationTime();
        pGlobals->frametime = pGlobals->interval_per_tick;
 
        player_animation_state->lastAnimUpdateFrame >= pEnt->GetSimulationTime();
        player_animation_state->lastAnimUpdateFrame = pEnt->GetSimulationTime() - 1;
 
        pEnt->UpdateClientAnimation();
        pGlobals->curtime = old_curtime;
        pGlobals->frametime = old_frametime;
        (pGlobals->realtime) = pGlobals->realtime;
        (pGlobals->curtime) = curtime;
        (pGlobals->frametime) = frametimne;
        (pGlobals->absoluteframetime) = absoluteframtime;
        pGlobals->framecount = framecount;
        pGlobals->tickcount = tickcount;
    }
}
void HandleHits( C_BaseEntity * pEnt )
{
    auto NetChannel = pEngine->GetNetChannelInfo( );

    if ( !NetChannel )
        return;

    static float predTime[ 65 ];
    static bool init[ 65 ];

    if (g::Shot[pEnt->GetIndex()])
    {
        if ( init[ pEnt->GetIndex() ] )
        {
            predTime[ pEnt->GetIndex() ] = pGlobals->curtime + NetChannel->GetAvgLatency( FLOW_INCOMING ) + NetChannel->GetAvgLatency( FLOW_OUTGOING ) + TICKS_TO_TIME( 1 ) + TICKS_TO_TIME( pEngine->GetNetChannel( )->m_nChokedPackets );
            init[ pEnt->GetIndex() ] = false;
        }

        if ( pGlobals->curtime > predTime[ pEnt->GetIndex() ] && !g::Hit[ pEnt->GetIndex() ] )
        {
            LogShots::missedShots[ pEnt->GetIndex() ] += 1;
            g::Shot[ pEnt->GetIndex() ] = false;
        }
        else if ( pGlobals->curtime <= predTime[ pEnt->GetIndex() ] && g::Hit[ pEnt->GetIndex() ] ) {
            g::Shot[ pEnt->GetIndex() ] = false; // missed shot due to spread (?) - no
        }
    }
    else
        init[ pEnt->GetIndex() ] = true;

    g::Hit[ pEnt->GetIndex() ] = false;
}
float GRD_TO_BOG( float GRD ) {
    return ( M_PI / 180 ) * GRD;
}
void Resolver::OnCreateMove() // cancer v2
{
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if (!vars.aimbot.Yawresolver)
        return;

    if (!pEngine->IsInGame() && !pEngine->IsConnected())
        return;

    if (!localplayer->GetAlive())
        return;

    if (!localplayer->GetActiveWeapon())
        return; // why wouldnt u resolve people when u have a knife out retard
    
    bool UseFreestandAngle[65];
    float FreestandAngle[65];

    for (int i = 1; i < pEngine->GetMaxClients(); ++i)
    {
        C_BaseEntity* pPlayerEntity = pEntList->GetClientEntity(i);

        if (!pPlayerEntity
            || !pPlayerEntity->GetAlive()
            || pPlayerEntity->IsDormant()
            || pPlayerEntity == localplayer
            || pPlayerEntity->GetTeam() == localplayer->GetTeam())
        {
            UseFreestandAngle[i] = false;
            continue;
        }

        if (abs(pPlayerEntity->GetVelocity().Length2D()) > 29.f)
            UseFreestandAngle[pPlayerEntity->GetIndex()] = false;

        if (abs(pPlayerEntity->GetVelocity().Length2D()) <= 29.f && !UseFreestandAngle[pPlayerEntity->GetIndex()])
        {
            bool Autowalled = false, HitSide1 = false, HitSide2 = false;

            float angToLocal = CalcAngle(localplayer->GetVecOrigin(), pPlayerEntity->GetVecOrigin()).y;
            Vector ViewPoint = localplayer->GetVecOrigin() + Vector(0, 0, 90);

            Vector2D Side1 = { (45 * sin(GRD_TO_BOG(angToLocal))),(45 * cos(GRD_TO_BOG(angToLocal))) };
            Vector2D Side2 = { (45 * sin(GRD_TO_BOG(angToLocal + 180))) ,(45 * cos(GRD_TO_BOG(angToLocal + 180))) };

            Vector2D Side3 = { (50 * sin(GRD_TO_BOG(angToLocal))),(50 * cos(GRD_TO_BOG(angToLocal))) };
            Vector2D Side4 = { (50 * sin(GRD_TO_BOG(angToLocal + 180))) ,(50 * cos(GRD_TO_BOG(angToLocal + 180))) };

            Vector Origin = pPlayerEntity->GetVecOrigin();

            Vector2D OriginLeftRight[] = { Vector2D(Side1.x, Side1.y), Vector2D(Side2.x, Side2.y) };

            Vector2D OriginLeftRightLocal[] = { Vector2D(Side3.x, Side3.y), Vector2D(Side4.x, Side4.y) };

            for (int side = 0; side < 2; side++)
            {
                Vector OriginAutowall = { Origin.x + OriginLeftRight[side].x,  Origin.y - OriginLeftRight[side].y , Origin.z + 90 };
                Vector OriginAutowall2 = { ViewPoint.x + OriginLeftRightLocal[side].x,  ViewPoint.y - OriginLeftRightLocal[side].y , ViewPoint.z };

                if (Autowall::CanHitFloatingPoint(OriginAutowall, ViewPoint))
                {
                    if (side == 0)
                    {
                        HitSide1 = true;
                        FreestandAngle[pPlayerEntity->GetIndex()] = 90;
                    }
                    else if (side == 1)
                    {
                        HitSide2 = true;
                        FreestandAngle[pPlayerEntity->GetIndex()] = -90;
                    }

                    Autowalled = true;
                }
                else
                {
                    for (int side222 = 0; side222 < 2; side222++)
                    {
                        Vector OriginAutowall222 = { Origin.x + OriginLeftRight[side222].x,  Origin.y - OriginLeftRight[side222].y , Origin.z + 90 };

                        if (Autowall::CanHitFloatingPoint(OriginAutowall222, OriginAutowall2))
                        {
                            if (side222 == 0)
                            {
                                HitSide1 = true;
                                FreestandAngle[pPlayerEntity->GetIndex()] = 90;
                            }
                            else if (side222 == 1)
                            {
                                HitSide2 = true;
                                FreestandAngle[pPlayerEntity->GetIndex()] = -90;
                            }

                            Autowalled = true;
                        }
                    }
                }
            }

            if (Autowalled)
            {
                if (HitSide1 && HitSide2)
                    UseFreestandAngle[pPlayerEntity->GetIndex()] = false;
                else
                    UseFreestandAngle[pPlayerEntity->GetIndex()] = true;
            }
        }
    }
}
void Resolver::FrameStageNotify(ClientFrameStage_t stage)
{
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (!localplayer || !pEngine->IsInGame() || !pEngine->IsConnected())
            return;
    
        if (!vars.aimbot.Yawresolver )
            return;
    
        for ( int i = 1; i < pEngine->GetMaxClients( ); ++i )
        {
            C_BaseEntity* pPlayerEntity = pEntList->GetClientEntity( i );
    
            if ( !pPlayerEntity
                || !pPlayerEntity->GetAlive( ) )
                continue;
    
            if ( pPlayerEntity->IsDormant( ) ) {
                continue;
            }
    
            if ( stage == FRAME_RENDER_START ) {
                HandleHits( pPlayerEntity );
                
                //AnimationFix(pPlayerEntity);
            }
            
            if(stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START){
                Resolve(pPlayerEntity);
            }
        }
}
