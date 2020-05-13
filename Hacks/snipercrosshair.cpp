//
//  snipercrosshair.cpp
//  vHook
//
//  Created by Timothy Dillan on 11/8/19.
//  Copyright © 2019 ViKiNG. All rights reserved.
//

#include "snipercrosshair.hpp"
void SniperCrosshair::Paint( )
{
    if(!vars.misc.snipercrosshair )
        return;
    
    if(!pEngine->IsInGame() )
        return;
    
    C_BasePlayer* localPlayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if ( !localPlayer || !localPlayer->GetAlive() )
        return;
    
    C_BaseCombatWeapon *activeWeapon = (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(localPlayer->GetActiveWeapon());
    
    if ( !activeWeapon )
        return;
    
    if (!activeWeapon || (CSWeaponType)activeWeapon->GetCSWpnData()->m_WeaponType != CSWeaponType::WEAPONTYPE_SNIPER_RIFLE)
        return;
    
    int width, height;
    pEngine->GetScreenSize( width, height );
    
    int x = width / 2;
    int y = height / 2;
    
    // outline horizontal
    draw->FilledRectangle( Vector2D( x - 4, y - 1 ), Vector2D( x + 5, y + 2 ), Color( 0, 0, 0, 170 ) );
    // outline vertical
     draw->FilledRectangle( Vector2D( x - 1, y - 4 ), Vector2D( x + 2, y + 5 ), Color( 0, 0, 0, 170 ) );
    
    int r = pCvar->FindVar("cl_crosshaircolor_r")->GetInt();
    int g =  pCvar->FindVar("cl_crosshaircolor_g")->GetInt();
    int b =  pCvar->FindVar("cl_crosshaircolor_b")->GetInt();
    int alpha =  pCvar->FindVar("cl_crosshairalpha")->GetInt();
    
    // line horizontal
     draw->Line( Vector2D( x - 3, y ), Vector2D( x + 4, y ), Color(r, g, b, alpha));
    // line vertical
    draw->Line( Vector2D( x, y + 3 ), Vector2D( x, y - 4 ), Color(r, g, b, alpha));
}
