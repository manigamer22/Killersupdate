#include "main.h"
#include "../Drawings/menu.h"
#include "../Hacks/crosshair.h"
#include "../Hacks/esp.h"
#include "../Hacks/spectators.h"
#include "../Hacks/antiaiminfos.h"
#include "../Hacks/hitmarker.h"
#include "../Hacks/asuswalls.h"
#include "../Hacks/snipercrosshair.hpp"
#include "../Hacks/eventlog.hpp"
#include "../Hacks/dlights.hpp"
#include "../Hacks/logshots.hpp"
#include "../Hacks/grenadeprediction.hpp"
void hkPaintTraverse(void* thisptr, VPANEL panel, bool forceRepaint, bool allowForce)
{
    
    if (vars.misc.noscope && !strcmp("HudZoom", pPanel->GetName(panel)))
        return;
    
    paintVMT->GetOriginalMethod<tPaintTraverse>(42)(thisptr, panel, forceRepaint, allowForce);
    
    C_BaseEntity* local = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    int keynum = 0;
    
    static VPANEL last = 0;
    
    if(!last)
    {
        if(strstr(pPanel->GetName(panel), "FocusOverlayPanel"))
        {
            espfont = pSurface->CreateFont();
            pSurface->SetFontGlyphSet(espfont, "Smallest Pixel-7", 12, 300, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);
            
            
            mFont = pSurface->CreateFont();
            pSurface->SetFontGlyphSet(mFont, "Consolas", 12, 400, 0, 0, FONTFLAG_ANTIALIAS);
            
            
            bombfont = pSurface->CreateFont();
            pSurface->SetFontGlyphSet(bombfont, "Verdana", 45, 1000, 0, 0, FONTFLAG_ANTIALIAS);
            
            hhfont = pSurface->CreateFont();
            pSurface->SetFontGlyphSet(hhfont, "Segoe UI", 12, 0, 0, 0, FONTFLAG_ANTIALIAS);
            
            hhhfont = pSurface->CreateFont();
            pSurface->SetFontGlyphSet(hhhfont, "Segoe UI", 12, 0, 0, 0, FONTFLAG_OUTLINE);
            
            
            framefont       = draw->createfont(framefont, "BigNoodleTitling", 14, FONTFLAG_ANTIALIAS);
            //espfont         = draw->createfont(espfont, "Segoe UI", 11,  FONTFLAG_ANTIALIAS);
            csgo_icons      = draw->createfont(csgo_icons, "icomoon", 11, FONTFLAG_ANTIALIAS);
            
           // mFont           = draw->createfont(mFont, "Verdana", 1, FONTFLAG_ANTIALIAS);
            sFont           = draw->createfont(sFont, "BigNoodleTitling", 12, FONTFLAG_ANTIALIAS);     // Used for sliders
            tFont           = draw->createfont(tFont, "BigNoodleTitling", 18, FONTFLAG_ANTIALIAS);     // Used for tabs
            heading         = draw->createfont(heading, "BigNoodleTitling", 21, FONTFLAG_ANTIALIAS);   // Used for headings
            osFont          = draw->createfont(osFont, "ProggyCleanTT", 16, FONTFLAG_ANTIALIAS);
            copyright       =  draw->createfont(copyright, "Segoe UI", 25,  FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW | FONTFLAG_OUTLINE);
            cFont           = draw->createfont(cFont, "BigNoodleTitling", 14, FONTFLAG_ANTIALIAS);     // Combos
            titleFont       = draw->createfont(cFont, "BigNoodleTitling", 52, FONTFLAG_ANTIALIAS);     // vlone.cc Title
            // vlone.cc Subtitle
            o4Font_03       = draw->createfont(o4Font_03, "04b03", 12, FONTFLAG_ANTIALIAS);
            o4Font_11       = draw->createfont(o4Font_11, "04b11", 12, FONTFLAG_ANTIALIAS);
            o4Font_20       = draw->createfont(o4Font_20, "04b_20", 12, FONTFLAG_ANTIALIAS);
            eFont       = draw->createfont(eFont, "Verdana", 12, FONTFLAG_DROPSHADOW);  // ESP font // v
            //       sFont       = draw->createfont(sFont, "Verdana", 11, FONTFLAG_OUTLINE);     // Used for sliders
            xFont          = draw->createfont(xFont, "osmiummenufont", 60, FONTFLAG_ANTIALIAS);
            xFontGay          = draw->createfont(xFontGay, "Verdana", 60, FONTFLAG_ANTIALIAS);
            lbyfont         = draw->createfont(lbyfont, "Verdana", 30, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);
            pFont           = draw->createfont(pFont, "Verdana", 50, FONTFLAG_ANTIALIAS);
            supremacy           = draw->createfont(supremacy, "Verdana", 12, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);     // Used for sliders // v
            slider           = draw->createfont(slider, "Verdana", 12, FONTFLAG_ANTIALIAS);     // Used for sliders // v // fontflag_none
            subtitleFont    = draw->createfont(cFont, "Verdana", 30, FONTFLAG_ANTIALIAS);     // vlone.cc Subtitle
            indicatorFont    = draw->createfont(indicatorFont, "Glyphter", 22, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);    
            iFont    = draw->createfont(cFont, "Verdana", 90, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);     // skrrt
            mSection    = draw->createfont(cFont, "Verdana", 14, FONTFLAG_ANTIALIAS);     // vlone.cc Subtitle
            iFont2    = draw->createfont(cFont, "Verdana", 90, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);     //
            iFont3    = draw->createfont(cFont, "Verdana", 90, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);     //skrrt
            
            weapfont        = draw->createfont(cFont, "Verdana", 20,FONTFLAG_ANTIALIAS);                              // Weapon Font
            test        = draw->createfont(cFont, "Verdana", 20,FONTFLAG_ANTIALIAS);                              // Weapon Font
            LBY        = draw->createfont(LBY, "Verdana", 37,FONTFLAG_ANTIALIAS);
            last = panel;
        }
        
        {   // Initialisation
          //  vars.colors.ctchams     = Color::White();
           // vars.colors.ctchams_ign = Color::Red();
            
            vars.colors.scopedchams = Color::White();
            
           // vars.colors.tchams      = Color::White();
           // vars.colors.tchams_ign  = Color::Red();
            
            vars.colors.tbox        = Color(18, 18, 18, 255);
            vars.colors.tbox_ign    = Color(18, 18, 18, 255);
            
            vars.colors.ctbox       = Color(18, 18, 18, 255);
            vars.colors.ctbox_ign   = Color(18, 18, 18, 255);
            
            vars.colors.hands       = Color(255, 0, 83, 255);
            vars.colors.weapon      = Color(18, 18, 18, 255);
            
            vars.colors.scope       = Color::Red();
            vars.colors.world       = Color::Test();
            vars.colors.sky         = Color::Red();
            
            vars.colors.fakelag = Color::Red();
            
            vars.colors.dlight = Color::Red();
            
            
            vars.colors.fakelag_a = 125;
            vars.colors.fakelag_r = 255;
            vars.colors.fakelag_g = 255;
            vars.colors.fakelag_b = 255;
        }
        
    }
    
    
    if(panel == last)
    {
        
        if(vars.misc.antiscreenshot && pEngine->IsTakingScreenshot())
            return;
        
        pwnmymenu();
        
        {   // Drawing features / own scope just for readablity
            DrawOtherESP();     // Other ESP
            
            DrawPlayerESP();    // Player esp
        
            
            DrawScope(local);   // Draws the crosshar for noscope
            
            rCrosshair(local);  // Draws recoil crosshair
            LogShots::Paint();
            manualaa(local, keynum);        // Manual AA idicator
            Dlights::Paint();
            NightMode();
            FullBright();
            Hitmarkers::Paint();
            Spectatorlist();    // Draws speclist
            DrawAngles(local);
            DrawSpread(local);
            players_behind();
            SniperCrosshair::Paint();
            Eventlog::Paint();
            grenade_prediction::get().Paint();
            BulletTracers::Paint();
            DrawFakeAngle(local);
        
            //aw_hitmarker->initilisze();
        }
        
        if(vars.menu)
        {   // Draw menu items
            menu->renderMenu();
            draw->drawmouse();
            pCvar->FindVar("cl_mouseenable");
        }
    
        
        if(vars.misc.watermark)
        {
            std::string name = (" killers.cc | ");
            std::string fps = "fps: " + std::to_string(static_cast<int>(1.f / pGlobals->frametime)) + " |  ";
            std::string creator = ("Credits | i'm tim#9436");
            //std::string ping = "ms: " + std::to_string((int)(nci->GetAvgLatency(FLOW_INCOMING) + nci->GetAvgLatency(FLOW_OUTGOING) * 1000));
            
            std::string watermarktext = name + fps.c_str() + creator;
            
            
            
            draw->drawstring(10, 15, Color::White(), hhhfont, watermarktext.c_str());
        }
        
        
    }
}

