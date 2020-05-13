#include "spectators.h"
#include <list>

// Thanks @Bypass for this

std::list<int> GetObservervators(int playerId)
{
    std::list<int> list;
    
    if (!pEngine->IsInGame())
        return list;
    
    C_BasePlayer* player = (C_BasePlayer*) pEntList->GetClientEntity(playerId);
    if (!player)
        return list;
    
    if (!player->GetAlive())
    {
        C_BasePlayer* observerTarget = (C_BasePlayer*) pEntList->GetClientEntityFromHandle(player->GetObserverTarget());
        if (!observerTarget)
            return list;
        
        player = observerTarget;
    }
    
    for (int i = 1; i < pEngine->GetMaxClients(); i++)
    {
        C_BasePlayer* pPlayer = (C_BasePlayer*) pEntList->GetClientEntity(i);
        if (!pPlayer)
            continue;
        
        if (pPlayer->GetDormant() || pPlayer->GetAlive())
            continue;
        
        C_BasePlayer* target = (C_BasePlayer*) pEntList->GetClientEntityFromHandle(pPlayer->GetObserverTarget());
        if (player != target)
            continue;
        
        list.push_back(i);
    }
    
    return list;
}

void Spectatorlist()
{
    if (!vars.misc.showspectators)
        return;
    
    if (!pEngine->IsInGame())
        return;
    
    int wScreen, hScreen;
    pEngine->GetScreenSize(wScreen, hScreen);
    
    // Tab menu measurements
    static int x = 10;
    static int y = 275;
    // Change these to change the location of the window. It doesn't drag.

    std::string spec_title = "Spectators";
    draw->drawstring(x + 30, y + 15, Color::Red(), hhfont, spec_title.c_str());
    
    static int count = 0;
    
    for (int playerId : GetObservervators(pEngine->GetLocalPlayer())) {
        if(playerId == pEngine->GetLocalPlayer())
            continue;
        
        player_info_t entityInformation;
        pEngine->GetPlayerInfo(playerId, &entityInformation);
        
        if (entityInformation.fakeplayer)
            continue;
        
        count += 1;
        draw->drawstring(x + 30, y + 30 + (12 * count), Color::Red(), hhfont, entityInformation.name);

    }
    
    count = 0;
    
}
