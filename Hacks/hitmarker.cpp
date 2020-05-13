#include "hitmarker.h"

std::vector<std::pair<int, long>> damages;
std::vector<cbullet_tracer_info> logs;
long lastHitmarkerTimestamp = 0;

//CHitmarkers* hitmarker = new CHitmarkers();

void Hitmarkers::Paint(void){
    
    if(!pEngine->IsInGame())
        return;
    if(!vars.visuals.hitmarker)
        return;
    C_BasePlayer* localplayer = (C_BasePlayer*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if(!localplayer)
        return;
    
    if(!localplayer->GetAlive())
        return;
    
    int duration = vars.visuals.hitduration;
    long now = GetEpochTime();
    
    long diff = lastHitmarkerTimestamp + duration - now;
    if(diff <= 0)
        return;
    
    int w, h;
    pEngine->GetScreenSize(w, h);
    
    Color color = Color::Red();
    color.SetAlpha(min(color.a(), (int)(diff * color.a() / duration * 2)));
    int sides[4][2] = {
        { -1, -1 },
        { 1,  1 },
        { -1, 1 },
        { 1,  -1 }
    };
    for (auto& it : sides)
        draw->drawline(w / 2 +  (vars.visuals.hitinnergap * it[0]), h / 2 + (vars.visuals.hitinnergap * it[1]), w / 2 + (vars.visuals.hitsize * it[0]), h / 2 + (vars.visuals.hitsize * it[1]), color);
    float textHeight = draw->GetTextSize("[cool]", hhhfont).y;
    for (unsigned int i = 0; i < damages.size(); i++) {
        long timestamp = damages[i].second;
        long hitDiff = timestamp + duration - now;
        
        if(hitDiff <= 0) {
            damages.erase(damages.begin() + i);
            continue;
        }
        Vector2D pos = Vector2D(w / 2 + vars.visuals.hitsize + 4, h / 2 - vars.visuals.hitsize - textHeight * i + 4);
        
        int damage = damages[i].first;
        std::string damageStr = '-' + std::to_string(damage);
        color.SetAlpha(std::min(color.a(), (int)(diff * color.a() / duration * 2)));
        
        draw->drawstring(pos, damageStr.c_str(), hhhfont, color);
        //draw->AddText(w / 2 + vars.visuals.hitsize + 4, h / 2 - vars.visuals.hitsize - textHeight * i + 4, damageStr.c_str(), color);
    }
}

void Hitmarkers::FireGameEvent(IGameEvent* event)
{    
    if(!pEngine->IsInGame())
        return;
    
    if(!vars.visuals.hitmarker)
        return;
    
    
    if (strcmp(event->GetName(), "player_hurt") != 0)
        return;
    
    int hurt_player_id = event->GetInt("userid");
    int attacker_id = event->GetInt("attacker");
    
    if(pEngine->GetPlayerForUserID(hurt_player_id) == pEngine->GetLocalPlayer())
        return;
    
    if(pEngine->GetPlayerForUserID(attacker_id) != pEngine->GetLocalPlayer())
        return;
    
    C_BasePlayer* localplayer = (C_BasePlayer*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if(!localplayer)
        return;
    C_BasePlayer* hurt_player = (C_BasePlayer*)pEntList->GetClientEntity(pEngine->GetPlayerForUserID(hurt_player_id));
    if(!hurt_player)
        return;
    if (hurt_player->GetTeam() == localplayer->GetTeam() && !vars.visuals.allieshit)
        return;
    
    if (hurt_player->GetTeam() != localplayer->GetTeam() && !vars.visuals.enemyhit)
        return;
    
    long now = GetEpochTime();
    lastHitmarkerTimestamp = now;
    damages.insert(damages.begin(), std::pair<int, long>(event->GetInt("dmg_health"), now));
    
    if(vars.visuals.hitmarkersounds){
    pCvar->ConsoleColorPrintf(Color::Green(), "[DEAD] Player hurt.");
    pEngine->ExecuteClientCmd("play buttons\\arena_switch_press_02.wav");
    }
    
}


void BulletTracers::FireGameEvent(IGameEvent* event)
{
    
    //if we receive bullet_impact event
    if (strstr(event->GetName(), "bullet_impact"))
    {
        //get the user who fired the bullet
        auto index = pEngine->GetPlayerForUserID(event->GetInt("userid"));
        
        //return if the userid is not valid or we werent the entity who was fireing
        if (index != pEngine->GetLocalPlayer())
            return;
        
        //get local player
        auto local = static_cast<C_BasePlayer*>(pEntList->GetClientEntity(index));
        if (!local)
            return;
        
        //get the bullet impact's position
        Vector position(event->GetFloat("x"), event->GetFloat("y"), event->GetFloat("z"));
        
        Ray_t ray;
        ray.Init(local->GetEyePosition(), position);
        
        //skip local player
        CTraceFilter filter;
        filter.pSkip = local;
        
        //trace a ray
        trace_t tr;
        pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);
        
        //use different color when we hit a player
        auto color = (tr.m_pEnt && reinterpret_cast<C_BasePlayer*>(tr.m_pEnt)->IsPlayer()) ? Color(0, 119, 255, 220)  :  Color(255, 0, 0, 220);
        
        //push info to our vector
        logs.push_back(cbullet_tracer_info(local->GetEyePosition(), position, pGlobals->curtime, color));
    }
}
void BulletTracers::Paint(void)
{
    if (!vars.visuals.bullett)
        return;
    //get local player
    auto local = static_cast<C_BasePlayer*>(pEntList->GetClientEntity(pEngine->GetLocalPlayer()));
    if (!local)
        return;
    
    //loop through our vector
    for (size_t i = 0; i < logs.size(); i++)
    {
        //get the current item
        auto current = logs.at(i);
        
        //draw a line from local player's head position to the hit point
        //draws also a box at the hit point
        
        pOverlay->AddLineOverlay(current.src, current.dst, current.color.r(), current.color.g(), current.color.b(), true, 1.f);
        pOverlay->AddBoxOverlay(current.dst, Vector(-2, -2, -2), Vector(2, 2, 2), QAngle(0, 0, 0), 255, 0, 0, 127, 1.f);
        //if the item is older than 5 seconds, delete it
        if (fabs(pGlobals->curtime - current.time) > 5.f)
            logs.erase(logs.begin() + i);
    }
}



