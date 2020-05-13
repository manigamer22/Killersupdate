#include "crosshair.h"
//#include "C_BaseEntity.h"
#include <array>
#include "antiaim.h"

void rCrosshair(C_BaseEntity* local)
{
    C_BasePlayer* localPlayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if ( !localPlayer )
        return;
    
    C_BaseCombatWeapon *activeWeapon = (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(localPlayer->GetActiveWeapon());
    
    if (!activeWeapon)
        return;
    
    if (vars.misc.snipercrosshair && (CSWeaponType)activeWeapon->GetCSWpnData()->m_WeaponType == CSWeaponType::WEAPONTYPE_SNIPER_RIFLE)
        return;
    
    if(!vars.visuals.rcrosshair)
        return;
    
    if(!pEngine->IsInGame())
        return;
    
    static int Height, Width;
    pEngine->GetScreenSize(Width, Height);
    
    int x = Width / 2;
    int y = Height / 2;
    
    Vector punchAngles = local->GetPunchAngles();
    
    int dy = Height / 90;
    int dx = Width / 90;
    int X = x - (dx * punchAngles.y);
    int Y = y + (dy * punchAngles.x);
    
    draw->drawCrosshair(X, Y, Color::White());
}

void DrawScope(C_BaseEntity* local)
{
    if(!vars.misc.noscope || !local || (local && !local->IsScoped()))
        return;
    
    auto weapon = GetActiveWeapon(local);
    
    if(!weapon)
        return;
    if(*weapon->GetItemDefinitionIndex() == WEAPON_AUG || *weapon->GetItemDefinitionIndex() == WEAPON_SG556)
        return;

    
    int w, h;
    pEngine->GetScreenSize(w, h);
    
    draw->drawline(w / 2, 0, w / 2, h, Color::Black());
    draw->drawline(0, h / 2, w, h / 2, Color::Black());
}

static auto percent_col = [](int per) -> Color {
    int red = per < 50 ? 255 : floorf(255 - (per * 2 - 100) * 255.f / 100.f);
    int green = per > 50 ? 255 : floorf((per * 2) * 255.f / 100.f);
    
    return Color(red, green, 0, 255);
};

void DrawFakeAngle(C_BaseEntity* local) {
    
    if(!local)
        return;
    
    if(!local->GetAlive())
        return;
    
    if (vars.misc.antiaim)
        draw->drawstring(10, 25, percent_col(fabs(AntiAim::fakeAngle.y - AntiAim::realAngle.y)), hhhfont, "FAKE");
}

void players_behind(){
    if(!vars.misc.offscreen)
        return;
    
    C_BasePlayer* pLocal = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(!pLocal)
        return;
    
    static auto alpha = 0.f;
    static auto plus_or_minus = false;
    if (alpha <= 0.f || alpha >= 255.f)
        plus_or_minus = !plus_or_minus;
    
    alpha += plus_or_minus ? (255.f / 0.5f * pGlobals->frametime) : -(255.f / 0.5f * pGlobals->frametime);
    alpha = std::clamp<float>(alpha, 0.f, 255.f);
    
    int screen_width, screen_height;
    pEngine->GetScreenSize(screen_width, screen_height);
    
    const auto screen_center_x = screen_width / 2;
    const auto screen_center_y = screen_height / 2;
    
    for (auto i = 1; i <= 64; i++)
    {
        C_BasePlayer* player = (C_BasePlayer*) pEntList->GetClientEntity(i);
        
        if (!player
            || player == pLocal
            || player->GetDormant()
            || !player->GetAlive()
            || player->GetImmune()
            || player->GetTeam() == pLocal->GetTeam())
            continue;
        
        Vector screen_point;
        pOverlay->ScreenPosition(player->GetAbsOrigin(), screen_point);
        
        if (screen_point.x < 0 || screen_point.y < 0 || screen_point.x > screen_width || screen_point.y > screen_height)
        {
            auto angle = Vector();
            VectorAngles(Vector(screen_center_x - screen_point.x, screen_center_y - screen_point.y, 0), angle);
            
            const auto angle_yaw_rad = degrees_to_radians(angle.y);
            
            const auto new_point_x = screen_center_x +
            vars.misc.offscreenESPRange * cosf(angle_yaw_rad);
            const auto new_point_y = screen_center_y +
            vars.misc.offscreenESPRange * sinf(angle_yaw_rad);
            
            std::array<Vector2D, 3>points{ Vector2D(new_point_x - 10, new_point_y - 10),
                Vector2D(new_point_x + 25, new_point_y),
                Vector2D(new_point_x - 10, new_point_y + 10) };
            
            draw->rotate_triangle(points, angle.y);
            draw->add_triangle_filled(points, Color(255, 255, 0, alpha));
        }
    }
}
void manualaa(C_BaseEntity* Local, int keynum)
{
    if (!vars.visuals.antiaim_indicator )
        return;
    if(!vars.misc.manualaa)
        return;
    if(!pEngine->IsInGame() && !pEngine->IsConnected())
        return;
    
    
    static bool switchsideleft = false;
       static bool switchsideright = false;
       static float resttime;
       static float resttime1;
       //int SwitchSideKey = KEY_SLASH;
       if (pInputSystem->IsButtonDown(KEY_LEFT) && abs(resttime - pGlobals->curtime) > 0.5)
       {
           switchsideleft = !switchsideleft;
           if(switchsideleft){
           switchsideright = false;
           }
           resttime = pGlobals->curtime;
       }
       if (pInputSystem->IsButtonDown(KEY_RIGHT) && abs(resttime1 - pGlobals->curtime) > 0.5)
       {
           switchsideright = !switchsideright;
           if(switchsideright){
           switchsideleft = false;
           }
           resttime1 = pGlobals->curtime;
       }
    
    int Height, Width;
    pEngine->GetScreenSize(Height, Width);
    
    int x = Width / 2;
    int y = Height / 2;
    
     //cmd->viewangles.y += (switchside) ? -90 : 90;
    
    if(vars.visuals.indicatorAA_types == 1){
        
        if( switchsideleft  )
        {
            draw->drawstring(25, 600, Color(255, 0, 0, 255), copyright, ("LEFT"));
        }
        
        if( switchsideright )
        {
            draw->drawstring(25, 600, Color(255, 0, 0, 255), copyright, ("RIGHT"));
        }
    }
    
    if(vars.visuals.indicatorAA_types == 2){
        
        
        if( switchsideleft  ) {
            draw->drawstring(y + 40, x, Color(255, 0, 0, 125), indicatorFont, ("B")); // Blue
            draw->drawstring(y - 60, x, Color(192, 192, 192, 125), indicatorFont, ("A")); // White
        }
        
        if( switchsideright ){
            draw->drawstring(y + 40, x, Color(192, 192, 192, 125), indicatorFont, ("B")); // White
            draw->drawstring(y - 60, x, Color(255, 0, 0, 125), indicatorFont, ("A")); // Blue
        }
    }
    
    
}
