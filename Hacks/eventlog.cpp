//
//  eventlog.cpp

#include "../main.h"
#include "eventlog.hpp"

std::vector<std::pair<std::string, long>> logToShow;
long lastLogTimestamp = 0;

void Eventlog::Paint(void) {
    if (!vars.visuals.enabled)
        return;
    
    if ( !vars.misc.showenemieslog && !vars.misc.showallieslog && !vars.misc.showlocalplayer)
        return;
    
    if ( !pEngine->IsInGame() )
        return;
    
    C_BasePlayer* localplayer = ( C_BasePlayer* ) pEntList->GetClientEntity( pEngine->GetLocalPlayer() );
    if ( !localplayer )
        return;
    
    if ( !localplayer->GetAlive() )
        return;
    
    int duration = vars.misc.loggerduration;
    long now = GetEpochTime();
    
    long diff = lastLogTimestamp + duration - now;
    if ( diff <= 0 )
        return;
    
    int w, h;
    pEngine->GetScreenSize(w, h);
    
    Color color = Color::White();
    //float sc = 1.0f/255.0f;
    color.SetAlpha(min(color.a(), (int)(diff * color.a() / duration * 2)));
    
    
    int textHeight = (int)draw->GetTextSize( "[cool]", hhhfont ).y;
    
    for ( unsigned int i = 0; i < logToShow.size(); i++ ) {
        long timestamp = logToShow[i].second;
        long hitDiff = timestamp + duration - now;
        
        if ( hitDiff <= 0 ) {
            logToShow.erase( logToShow.begin() + i );
            continue;
        }
        
        if ( i >= vars.misc.loggerlines )
            return;
        
        std::string showLog = logToShow[i].first;
        Vector2D pos = Vector2D(w / 5, h / 6.5 - textHeight * i);
        color.SetAlpha(std::min(color.a(), (int)(diff * color.a() / duration * 2)));
        
        draw->drawstring(pos, showLog.c_str(), hhhfont, color);
        
    }
}

void Eventlog::FireGameEvent(IGameEvent* event)
{
    if (!vars.visuals.enabled)
        return;
    
    if (!vars.misc.showenemieslog && !vars.misc.showallieslog  && !vars.misc.showlocalplayer )
        return;
    
    if (!pEngine->IsInGame())
        return;
    
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (!localplayer)
        return;
    
    if (strstr(event->GetName(), ("item_purchase"))){
        
        int buyer_player_id = event->GetInt("userid");
        
        if ((pEngine->GetPlayerForUserID(buyer_player_id) == pEngine->GetLocalPlayer()) && !vars.misc.showallieslog)
            return;
        
        C_BasePlayer* buyer_player = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetPlayerForUserID(buyer_player_id));
        if (!buyer_player)
            return;
        
        if ((localplayer != buyer_player) && buyer_player->GetTeam() == localplayer->GetTeam() && !vars.misc.showallieslog)
            return;
        
        if ((localplayer != buyer_player) && buyer_player->GetTeam() != localplayer->GetTeam() && !vars.misc.showenemieslog)
            return;
        
        
        player_info_t buyerInformation;
        pEngine->GetPlayerInfo(pEngine->GetPlayerForUserID(buyer_player_id), &buyerInformation);
        
        long now = GetEpochTime();
        lastLogTimestamp = now;
        
        std::string boughtLog = std::string(buyerInformation.name);
        boughtLog += (" bought ");
        
        
        std::string weaponname = event->GetString("weapon");
        std::string equipment = event->GetString("item");
    
        
        boughtLog += weaponname;
        boughtLog += equipment;
        
        logToShow.insert(logToShow.begin(), std::pair<std::string, long>(boughtLog, now));
        
    } else if (strstr(event->GetName(), ("enter_bombzone"))){
        
        int bomb_player_id = event->GetInt("userid");
        
        if ((pEngine->GetPlayerForUserID(bomb_player_id) == pEngine->GetLocalPlayer()) && !vars.misc.showlocalplayer)
            return;
        
        C_BasePlayer* bomb_player = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetPlayerForUserID(bomb_player_id));
        if (!bomb_player)
            return;
        
        if ((localplayer != bomb_player) && bomb_player->GetTeam() == localplayer->GetTeam() && !vars.misc.showallieslog)
            return;
        
        if ((localplayer != bomb_player) && bomb_player->GetTeam() != localplayer->GetTeam() && !vars.misc.showenemieslog)
            return;
        
        
        if (!event->GetBool("hasbomb"))
            return;
        
        player_info_t bomberInformation;
        pEngine->GetPlayerInfo(pEngine->GetPlayerForUserID(bomb_player_id), &bomberInformation);
        
        long now = GetEpochTime();
        lastLogTimestamp = now;
        
        std::string bombLog = std::string(bomberInformation.name);
        bombLog += " entering bomb-site with bomb";
        
        logToShow.insert(logToShow.begin(), std::pair<std::string, long>(bombLog, now));
        
    } else if (strstr(event->GetName(), ("bomb_begindefuse"))){
        
        int defuse_player_id = event->GetInt("userid");
        
        if ((pEngine->GetPlayerForUserID(defuse_player_id) == pEngine->GetLocalPlayer()) && !vars.misc.showlocalplayer)
            return;
        
        C_BasePlayer* defuse_player = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetPlayerForUserID(defuse_player_id));
        if (!defuse_player)
            return;
        
        if ((localplayer != defuse_player) && defuse_player->GetTeam() == localplayer->GetTeam() && !vars.misc.showallieslog)
            return;
        
        if ((localplayer != defuse_player) && defuse_player->GetTeam() != localplayer->GetTeam() && !vars.misc.showenemieslog)
            return;
        
        
        player_info_t defuserInformation;
        pEngine->GetPlayerInfo(pEngine->GetPlayerForUserID(defuse_player_id), &defuserInformation);
        
        long now = GetEpochTime();
        lastLogTimestamp = now;
        
        std::string defuseLog = std::string(defuserInformation.name);
        defuseLog += " is defusing the bomb ";
        
        if (event->GetBool("haskit")){
            defuseLog += "with defuse-kit";
        } else if (!event->GetBool("haskit")){
            defuseLog += "without defuse-kit";
        }
        
        logToShow.insert(logToShow.begin(), std::pair<std::string, long>(defuseLog, now));
        
    } else if (strstr(event->GetName(), ("bomb_beginplant"))){
        //To add: check on which bomb-site is player planting
        
        int plant_player_id = event->GetInt("userid");
        
        if ((pEngine->GetPlayerForUserID(plant_player_id) == pEngine->GetLocalPlayer()) && !vars.misc.showlocalplayer)
            return;
        
        C_BasePlayer* planter_player = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetPlayerForUserID(plant_player_id));
        if (!planter_player)
            return;
        
        if ((localplayer != planter_player) && planter_player->GetTeam() == localplayer->GetTeam() && !vars.misc.showallieslog)
            return;
        
        if ((localplayer != planter_player) && planter_player->GetTeam() != localplayer->GetTeam() && !vars.misc.showenemieslog)
            return;
        
        
        player_info_t planterInformation;
        pEngine->GetPlayerInfo(pEngine->GetPlayerForUserID(plant_player_id), &planterInformation);
        
        long now = GetEpochTime();
        lastLogTimestamp = now;
        
        std::string plantLog = std::string(planterInformation.name);
        plantLog += " started planting bomb";
        //plantLog += std::to_string(event->GetInt("site"));
        
        logToShow.insert(logToShow.begin(), std::pair<std::string, long>(plantLog, now));
        
    } else if (strstr(event->GetName(), ("item_pickup"))){
        
        int pickup_player_id = event->GetInt("userid");
        
        if ((pEngine->GetPlayerForUserID(pickup_player_id) == pEngine->GetLocalPlayer()) && !vars.misc.showlocalplayer)
            return;
        
        C_BasePlayer* pickup_player = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetPlayerForUserID(pickup_player_id));
        if (!pickup_player)
            return;
        
        if ((localplayer != pickup_player) && pickup_player->GetTeam() == localplayer->GetTeam() && !vars.misc.showallieslog)
            return;
        
        if ((localplayer != pickup_player) && pickup_player->GetTeam() != localplayer->GetTeam() && !vars.misc.showenemieslog)
            return;
        
        
        player_info_t pickupInformation;
        pEngine->GetPlayerInfo(pEngine->GetPlayerForUserID(pickup_player_id), &pickupInformation);
        
        long now = GetEpochTime();
        lastLogTimestamp = now;
        
        std::string pickupLog = std::string(pickupInformation.name);
        pickupLog += " picked up ";
        pickupLog += std::string(event->GetString("item"));
        
        logToShow.insert(logToShow.begin(), std::pair<std::string, long>(pickupLog, now));
        
    } else if (strstr(event->GetName(), ("item_remove"))){
        
        int drop_player_id = event->GetInt("userid");
        
        if ((pEngine->GetPlayerForUserID(drop_player_id) == pEngine->GetLocalPlayer()) && !vars.misc.showlocalplayer)
            return;
        
        C_BasePlayer* drop_player = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetPlayerForUserID(drop_player_id));
        if (!drop_player)
            return;
        
        if ((localplayer != drop_player) && drop_player->GetTeam() == localplayer->GetTeam() && !vars.misc.showallieslog)
            return;
        
        if ((localplayer != drop_player) && drop_player->GetTeam() != localplayer->GetTeam() && !vars.misc.showenemieslog)
            return;
        
        if (strstr(event->GetString("item"), ("knife")) || strstr(event->GetString("item"), ("vesthelm")))
            return;
        
        player_info_t dropInformation;
        pEngine->GetPlayerInfo(pEngine->GetPlayerForUserID(drop_player_id), &dropInformation);
        
        long now = GetEpochTime();
        lastLogTimestamp = now;
        
        std::string dropLog = std::string(dropInformation.name);
        dropLog += " dropped ";
        dropLog += std::string(event->GetString("item"));
        
        logToShow.insert(logToShow.begin(), std::pair<std::string, long>(dropLog, now));
        
    }
}
