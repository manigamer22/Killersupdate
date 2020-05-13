//
//  menu.cpp
//  macOS base
//

#include "menu.h"
#include "Config.h"
#include "../Hacks/namechanger.hpp"

cMenu* menu = new cMenu();
Config cfg;

// Colours

Color nagatoro = Color(255, 0, 0, 255);
Color Red             = Color(255, 0, 57, 255);
Color inactive          = Color(82, 82, 82, 255);
Color MainColor         = Red;

Color FontColor         = Color(255, 255, 255, 250);
Color background        = Color(28, 28, 28, 255);
Color outline           = Color(43, 43, 43, 255);
Color backgroundalpha   = Color(28, 28, 28, 255); // 225 alpha
Color border1           = Color(60, 60, 60, 255);
Color border2           = Color(40, 40, 40, 255);
Color black             = Color(0, 0, 0, 255);
Color Avoz              = Color(163, 12, 224, 255);
Color greycolor = Color(189, 195, 199, 255);
Color FontColorDeselect = Color(190, 190, 190, 255);

bool WasPressed, WasReleased;

static std::string GetLocalName()
{
    player_info_t playerInfo;
    pEngine->GetPlayerInfo(pEngine->GetLocalPlayer(), &playerInfo);
    return std::string(playerInfo.name);
}

auto Pressed (ButtonCode_t code) -> void {
    
    if (pInputSystem->IsButtonDown(code)) {
        
        WasPressed = true;
        
    } else if (!(pInputSystem->IsButtonDown(code))) {
        
        if (WasPressed) {
            
            WasReleased = true;
            
        } else {
            
            WasReleased = false;
            
        }
        
        WasPressed = false;
        
    }
    
}

// Menu components

void cMenu::renderCheckbox(int x, int y, const char* str, bool *var) {
    
    draw->fillrgba(x, y, 18, 8, Color(56,56,56,242));
    draw->fillrgba(x + 1, y + 1, 10 - 2, 8 - 2, Color(252,252,252,255));
    
    if (*var) {
        draw->fillrgba( x, y, 18, 8, Color(124, 200, 0,242));
        draw->fillrgba( x + 9, y + 1, 10 - 1, 8 - 2, Color(252,252,252,255));
    }
    
    if (draw->inArea(x, y, 18, 8)) {
        
        if (*var) {
            draw->fillrgba( x, y, 18, 8, Color(124, 200, 0,242));
            draw->fillrgba( x + 9, y + 1, 10 - 1, 8 - 2, Color(252,252,252,255));
        }
        
        if (WasReleased)
            *var = !*var;
    }
    
    draw->drawbox(x, y, 18, 8, Color(2,2,2,255)); // Outline
    
    draw->drawstring(x + 25, y - 3, FontColor, mFont, str);
    
}


// The sliders are kinda broken, if you click past the ends itll still move
// for ints
void cMenu::renderSlider_c(int x, int y, int w, const char* szString, int& value, int max, int min, Color &col) {
    
    int h = 6;
    int curValue = value * ((float)w / (float)(max));
    
    if (draw->GetMouse().x > x - 4 && draw->GetMouse().y > y - 2 && draw->GetMouse().x < x + w + 4 && draw->GetMouse().y < y + h + 2) {
        
        Color col = Color(40, 45, 55, 255);
        
        if (pInputSystem->IsButtonDown(MOUSE_LEFT)) {
            
            value = (draw->CalcPos(x) / ((float)w / (float)(max)));
            
            if (value > max)
                value = max;
            
            if (value < min)
                value = min;
            
        }
        
    }
    
    // draw->RectOutlined(x, y + 5, w + 2, h, 1, background, Color::Black());
    //  draw->fillrgba(x, y + 5, w + 2, h, Color(40, 45, 55, 255));
    //draw->fillrgba(x, y + 5, curValue, h, Color(40, 45, 55, 255));
    draw->RectOutlined(x + 5, y + 5, w, h, 1, Color(58, 58, 58, 255), Color::Black());
    draw->fillrgba( x + 5, y + 5, curValue, h, col );                       // Color till cursor
    
    draw->drawstring(x + w + 15, y + 3, Color::White(), mFont, to_string(value).c_str());
    draw->drawstring(x + 5, y - 9, FontColor, supremacy, szString);
    //better one
    // draw->fillrgba(x + curValue, y - 1, 4, h + 2, Color(10, 145, 190, 255));
    //  draw->drawbox(x, y, w, h, Color(10, 145, 190, 255));
    //   draw->drawstring(x + curValue - 5, y + 7, FontColor, mFont, to_string(value).c_str());
    
}
void cMenu::renderSlider(int x, int y, int w, const char* szString, int& value, int max, int min) {
    
    int h = 6;
    int curValue = value * ((float)w / (float)(max));
    
    if (draw->GetMouse().x > x - 4 && draw->GetMouse().y > y - 2 && draw->GetMouse().x < x + w + 4 && draw->GetMouse().y < y + h + 2) {
        
        Color col = Color(40, 45, 55, 255);
        
        if (pInputSystem->IsButtonDown(MOUSE_LEFT)) {
            
            value = (draw->CalcPos(x) / ((float)w / (float)(max)));
            
            if (value > max)
                value = max;
            
            if (value < min)
                value = min;
            
        }
        
    }
    
    // draw->RectOutlined(x, y + 5, w + 2, h, 1, background, Color::Black());
    //  draw->fillrgba(x, y + 5, w + 2, h, Color(40, 45, 55, 255));
    //draw->fillrgba(x, y + 5, curValue, h, Color(40, 45, 55, 255));
    draw->RectOutlined(x + 5, y + 5, w, h, 1, Color(58, 58, 58, 255), Color::Black());
    draw->fillrgba( x + 5, y + 5, curValue, h, nagatoro );                       // Color till cursor
    
    draw->drawstring(x + w + 15, y + 3, Color::White(), mFont, to_string(value).c_str());
    draw->drawstring(x + 5, y - 9, FontColor, mFont, szString);
    //better one
    // draw->fillrgba(x + curValue, y - 1, 4, h + 2, Color(10, 145, 190, 255));
    //  draw->drawbox(x, y, w, h, Color(10, 145, 190, 255));
    //   draw->drawstring(x + curValue - 5, y + 7, FontColor, mFont, to_string(value).c_str());
    
}

// for floats
void cMenu::renderSlider(int x, int y, int w, const char* szString, float& value, int max, int min) {
    
    int h = 8;
    int curValue = value * ((float)w / (float)(max));
    
    if (draw->GetMouse().x > x - 4 && draw->GetMouse().y > y - 2 && draw->GetMouse().x < x + w + 4 && draw->GetMouse().y < y + h + 2) {
        
        if (pInputSystem->IsButtonDown(MOUSE_LEFT)) {
            
            value = (draw->CalcPos(x) / ((float)w / (float)(max)));
            
            if (value > max)
                value = max;
            
            if (value < min)
                value = min;
            
        }
        
    }
    /*
     draw->fillrgba(x + curValue, y - 1, 4, h + 2, Color(10, 145, 190, 255));
     draw->drawbox(x, y, w, h, Color(10, 145, 190, 255));
     draw->drawstring(x + curValue - 5, y + 7, FontColor, mFont, to_string(value).c_str());
     */
    char buffer[16];
    
    sprintf(buffer, "%.2f", value);
    
    draw->RectOutlined(x + 5, y + 5, w, h, 1, Color(58, 58, 58, 255), Color(2, 2, 2, 255));
    draw->fillrgba( x + 5, y + 5, curValue, h, nagatoro );                       // Color till cursor
    
    draw->drawstring(x + w + 15, y + 3, Color::White(), mFont, buffer);
    draw->drawstring(x + 5, y - 9, FontColor, mFont, szString);
}




void cMenu::renderCombo(int x, int y, int w, int h, const char* szString, vector<string> szValue, int& currValue, bool* bOpend) {
    
    int Y = y + h;
    
    if(draw->inArea(x, y, w, h)) {
        if(WasReleased) {
            *bOpend = !*bOpend;
        }
    }
    
    if (*bOpend) {
        
        for ( int i = 0; i < szValue.size(); i++ ) {
            
            auto bHover = draw->inArea(x, Y + 2 + ( i * 20 ), w, 18);
            
            draw->RectOutlined(x, Y + 1 + ( i * 20 ), w + 2, 18, 1, bHover ? Color(37, 52, 60, 255) : Color(58, 58, 58, 255), Color(2, 2, 2, 255));
            draw->drawstring(x + 5, Y + 2 + (i*20), Color::White(), mFont, szValue[i].c_str());
            
            if (draw->inArea(x, Y + 2 + ( i * 20 ), w, 18)) {
                if(WasPressed){
                    currValue = i;
                    *bOpend = false;
                }
            }
        }
    }
    
    if(currValue == 0)
        szString = szString;
    else
        szString = szValue[currValue].c_str();
    
    // Draws the box
    draw->RectOutlined(x, y, w + 2, h, 1, Color(58, 58, 58, 255), Color(2, 2, 2, 255));
    ;
    draw->drawstring(x + 5, y + (h/2) - 7, FontColor, mFont, szString);
    
    
    if (!*bOpend)
    {
        // draw arrow pointing down
        draw->fillrgba( ( x + w - h + 113 - 107 ), ( y + 8 ), 1, 1, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 114 - 107 ), ( y + 8 ), 1, 2, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 115 - 107 ), ( y + 8 ), 1, 3, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 116 - 107 ), ( y + 8 ), 1, 4, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 117 - 107 ), ( y + 8 ), 1, 3, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 118 - 107 ), ( y + 8 ), 1, 2, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 119 - 107 ), ( y + 8 ), 1, 1, Color( 255, 255, 255, 255 ) );
    }
    else
    {
        // draw arrow pointing up
        draw->fillrgba( ( x + w - h + 113 - 107 ), ( y + 11 ), 1, 1, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 114 - 107 ), ( y + 10 ), 1, 2, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 115 - 107 ), ( y + 9 ), 1, 3, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 116 - 107 ), ( y + 8 ), 1, 4, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 117 - 107 ), ( y + 9 ), 1, 3, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 118 - 107 ), ( y + 10 ), 1, 2, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 119 - 107 ), ( y + 11 ), 1, 1, Color( 255, 255, 255, 255 ) );
    }
}

void cMenu::renderButton(int x, int y, const char* szString, bool* var) {
    
      int w = 60;
      int h = 20;
      
      if(draw->inArea(x, y, w, h)) {
          if(WasPressed) {
              *var = true;
          }
      } else {
          *var = false;
      }
      
      bool bHovering = draw->inArea(x, y, w, h);
      draw->drawgradient(x, y, w, h, bHovering ? Color(37, 52, 60, 255) : Color(25, 25, 25, 255), Color(25, 25, 25, 255));
      draw->drawbox(x + 1, y + 1, w - 2, h - 2, bHovering ? Color(64, 91, 106, 255) : Color(67, 67, 67, 255));
      draw->drawbox(x, y, w, h, bHovering ? Color(25, 35, 40, 255) : Color(9, 9, 9, 255));
      
      draw->drawstring(x + w / 2, y + h / 2, FontColor, framefont, szString, true);
      
    
}

void cMenu::renderButton1(int x, int y, const char* szString, bool* var) {
    
    int w = 175;
    int h = 20;
    
    if(draw->inArea(x, y, w, h)) {
        if(WasPressed) {
            *var = true;
        }
    } else {
        *var = false;
    }
    
    bool bHovering = draw->inArea(x, y, w, h);
    draw->drawbox(x + 1, y + 1, w - 2, h - 2, bHovering ? Color(64, 91, 106, 255) : Color(67, 67, 67, 255));
    
    draw->drawstring(x + w / 2, y + h / 2, FontColor, framefont, szString, true);
    
}

void cMenu::playerbutton(int x, int y, int w, int h, int index, int& playercount, const char* szString)
{
    y += index * 24;
    
    if(draw->inArea(x, y, w, h))
    {
        if(WasReleased)
        {
            playercount = index;
        }
    }
    
    bool bHovering = draw->inArea(x, y, w, h);
    draw->drawgradient(x, y, w, h, bHovering ? Color(30, 30, 30, 255), FontColor : Color(15, 15, 15, 255), Color(15, 15, 15, 255));
    draw->drawbox(x, y, w, h, Color::Black());
    draw->drawstring(x + w / 2, y + h / 2, FontColor, mFont, szString, true);
}

void cMenu::render_section(int x, int y, int w, int h, const char* label)
{
    
    draw->RectOutlined(x, y, w, h, 1, Color(28, 28, 28, 255), Color(43, 43, 43, 255));
    // ImGui::PushFont(Fonts::section);
    
    auto text_size = draw->GetTextSize(label, mFont);
    
    draw->fillrgba(x + 12, y - 1, text_size.x + 7, 3, Color(28, 28, 28, 255));
    // draw->drawbox(x + 12, y - 1, text_size.x + 7, 3, Color(255, 20, 20, 255));
    draw->drawstring(x + 15, y - 6, FontColor, mFont, label);
}

void cMenu::render_tab_section(int x, int y, int w, int h)
{
    draw->RectOutlined(x, y, w, h, 1, Color(28, 28, 28, 255), Color(43, 43, 43, 255));
}

// Made by ViKiNG
void cMenu::drawcolorpicker(int x, int y, const char *szString, Color &col) {
    
    int oner = 6;
    float flRnbw = 0.0005f;
    int currPosX, currPosY;
    
    for(int i = 0 ; i < 21; i++) {
        flRnbw += 0.045f;
        
        Color col1 = Color::GetFromHSB(flRnbw, 1.0f, 1.0f);
        Color col2 = Color::GetFromHSB(flRnbw, 0.90f, 0.90f);
        Color col3 = Color::GetFromHSB(flRnbw, 0.80f, 0.80f);
        Color col4 = Color::GetFromHSB(flRnbw, 0.70f, 0.70f);
        Color col5 = Color::GetFromHSB(flRnbw, 0.60f, 0.60f);
        Color col6 = Color::GetFromHSB(flRnbw, 0.50f, 0.50f);
        Color col7 = Color::GetFromHSB(flRnbw, 0.40f, 0.40f);
        Color col8 = Color::GetFromHSB(flRnbw, 0.30f, 0.30f);
        Color col9 = Color::GetFromHSB(flRnbw, 0.20f, 0.20f);
        Color col10 = Color::GetFromHSB(flRnbw, 0.15f, 0.15f);
        Color col11 = Color::GetFromHSB(flRnbw, 0.10f, 0.10f);
        
        draw->fillrgba(x + i * oner, y, oner, oner, Color(col1.r(), col1.g(), col1.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 1, oner, oner, Color(col2.r(), col2.g(), col2.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 2, oner, oner, Color(col3.r(), col3.g(), col3.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 3, oner, oner, Color(col4.r(), col4.g(), col4.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 4, oner, oner, Color(col5.r(), col5.g(), col5.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 5, oner, oner, Color(col6.r(), col6.g(), col6.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 6, oner, oner, Color(col7.r(), col7.g(), col7.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 7, oner, oner, Color(col8.r(), col8.g(), col8.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 8, oner, oner, Color(col9.r(), col9.g(), col9.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 9, oner, oner, Color(col10.r(), col10.g(), col10.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 10, oner, oner, Color(col11.r(), col11.g(), col11.b(), 255));
        
        int x1 = x + i * oner;
        int y2 = y + oner * 1;
        int y3 = y + oner * 2;
        int y4 = y + oner * 3;
        int y5 = y + oner * 4;
        int y6 = y + oner * 5;
        int y7 = y + oner * 6;
        int y8 = y + oner * 7;
        int y9 = y + oner * 8;
        int y10 = y + oner * 9;
        int y11 = y + oner * 10;
        
        if(draw->inArea(x1, y, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col1;
                draw->drawbox(x1, y, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y;
            }
        } else if(draw->inArea(x1, y2, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col2;
                draw->drawbox(x1, y2, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y2;
            }
        } else if(draw->inArea(x1, y3, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col3;
                draw->drawbox(x1, y3, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y3;
            }
        } else if(draw->inArea(x1, y4, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col4;
                draw->drawbox(x1, y4, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y4;
            }
        } else if(draw->inArea(x1, y5, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col5;
                draw->drawbox(x1, y5, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y5;
            }
        } else if(draw->inArea(x1, y6, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col6;
                draw->drawbox(x1, y6, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y6;
            }
        }
        else if(draw->inArea(x1, y7, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col7;
                draw->drawbox(x1, y7, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y7;
            }
        }
        else if(draw->inArea(x1, y8, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col8;
                draw->drawbox(x1, y8, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y8;
            }
        }
        else if(draw->inArea(x1, y9, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col9;
                draw->drawbox(x1, y9, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y9;
            }
        }
        else if(draw->inArea(x1, y10, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col10;
                draw->drawbox(x1, y10, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y10;
            }
        }
        else if(draw->inArea(x1, y11, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col11;
                draw->drawbox(x1, y11, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y11;
            }
        }
    }
    
    draw->fillrgba(x, y + 73, 5, 20, Color(col.r(), col.g(), col.b(), 255));
    draw->drawbox(x, y + 73, 5, 20, Color::Black());
    
    string strPalette;
    
    strPalette.append("R: ");
    strPalette.append(to_string(col.r()));
    
    strPalette.append(" G: ");
    strPalette.append(to_string(col.g()));
    
    strPalette.append(" B: ");
    strPalette.append(to_string(col.b()));
    
    draw->drawstring(x, y - 20, Color::White(), mFont, szString);
    draw->drawstring(x + 10, y + 78, Color::White(), mFont, strPalette.c_str());
}

// Tabs

void cMenu::renderAim(int x, int y) {
    
    vector<string> Hitgroup;  // Resolver
    vector<string> Name;  // Resolver
    
    Hitgroup.push_back("Head");
    Hitgroup.push_back("Body");
    Hitgroup.push_back("Legs");
    
    
    this->renderCheckbox(x - 15, y + 15, "Legit Aimbot", &vars.aimbot.LegitEnabled);
    
    this->renderSlider(x + 5, y + 35, 150, "Pistol FOV", vars.aimbot.pistolFOV, 5.0f, 0.0f);
    this->renderCheckbox(x - 15, y + 55, "Pistol Smooth", &vars.aimbot.pistolsmooth);
    this->renderSlider(x + 5, y + 75, 150, "Amount", vars.aimbot.pistolsmoothf, 1.0f, 0.0f);
    
    this->renderSlider(x + 5, y + 105, 150, "Rifle FOV", vars.aimbot.rifleFOV, 5.0f, 0.0f);
    this->renderCheckbox(x - 15, y + 125, "Rifle Smooth", &vars.aimbot.riflesmooth);
    this->renderSlider(x + 5, y + 145, 150, "Amount", vars.aimbot.riflesmoothf, 1.0f, 0.0f);
    
    this->renderSlider(x + 5, y + 175, 150, "Sniper FOV", vars.aimbot.sniperFOV, 5.0f, 0.0f);
    this->renderCheckbox(x - 15, y + 195, "Sniper Smooth", &vars.aimbot.snipersmooth);
    this->renderSlider(x + 5, y + 215, 150, "Amount", vars.aimbot.snipersmoothf, 1.0f, 0.0f);
    
    this->renderSlider(x + 5, y + 245, 150, "Smg FOV", vars.aimbot.smgFOV, 5.0f, 0.0f);
    this->renderCheckbox(x - 15, y + 265, "Smg Smooth", &vars.aimbot.smgsmooth);
    this->renderSlider(x + 5, y + 285, 150, "Amount", vars.aimbot.smgsmoothf, 1.0f, 0.0f);
    
    this->renderSlider(x + 5, y + 315, 150, "Heavy FOV", vars.aimbot.heavyFOV, 5.0f, 0.0f);
    this->renderCheckbox(x - 15, y + 335, "Heavy Smooth", &vars.aimbot.heavysmooth);
    this->renderSlider(x + 5, y + 355, 150, "Amount", vars.aimbot.heavysmoothf, 1.0f, 0.0f);
    
    this->renderCheckbox(x + 235, y + 15, "Pistol Hitscan", &vars.aimbot.legitPistolHitscan);
    this->renderCombo(x + 235, y + 35, 150, 20, "Head", Hitgroup, vars.aimbot.legitPistolHitscanType, &vars.legithitscanpistolpri_opend);
    
    this->renderCheckbox(x + 235, y + 65, "Rifle Hitscan", &vars.aimbot.legitRifleHitscan);
    this->renderCombo(x + 235, y + 85, 150, 20, "Head", Hitgroup, vars.aimbot.legitRifleHitscanType, &vars.legithitscanriflepri_opend);
    
    this->renderCheckbox(x + 235, y + 115, "Sniper Hitscan", &vars.aimbot.legitSniperHitscan);
    this->renderCombo(x + 235, y + 135, 150, 20, "Head", Hitgroup, vars.aimbot.legitSniperHitscanType, &vars.legithitscansniperpri_opend);
    
    this->renderCheckbox(x + 235, y + 165, "Smg Hitscan", &vars.aimbot.legitSmgHitscan);
    this->renderCombo(x + 235, y + 185, 150, 20, "Head", Hitgroup, vars.aimbot.legitSmgHitscanType, &vars.legithitscansmgpri_opend);
    
    this->renderCheckbox(x + 235, y + 215, "Heavy Hitscan", &vars.aimbot.legitHeavyHitscan);
    this->renderCombo(x + 235, y + 235, 150, 20, "Head", Hitgroup, vars.aimbot.legitHeavyHitscanType, &vars.legithitscanheavypri_opend);
    
    this->renderCheckbox(x + 235, y + 265, "Backtrack", &vars.aimbot.backtrack);

    this->renderCheckbox(x + 235, y + 285, "Triggerbot", &vars.aimbot.trigger);
    this->renderCheckbox(x + 235, y + 305, "Radar", &vars.misc.radar);
    this->renderCheckbox(x + 235, y + 325, "Auto Block", &vars.aimbot.autoaccept);
    this->renderCheckbox(x + 235, y + 345, "Auto Knife", &vars.aimbot.autoknife);
    
    
    
    
}

void cMenu::renderAntiAim(int x, int y) {
    
    vector<string> fakewalk;  // Fake types
    vector<string> Pitch;  // Real Pitch
    vector<string> Yaw;  // Real Yaw
    vector<string> tp;  // Real Yaw
    vector<string> FakeYaw; // Fake Yaw
    vector<string> hitscan;
   
    // Pitch
    Pitch.push_back("None");
    Pitch.push_back("UP");
    Pitch.push_back("DOWN");
    Pitch.push_back("DANCE");
    Pitch.push_back("FRONT");
    Pitch.push_back("FAKE UP");
    Pitch.push_back("FAKE DOWN");
    Pitch.push_back("LISP DOWN");
    Pitch.push_back("ANGEL DOWN");
    Pitch.push_back("ANGEL UP");
    // Yaw
    Yaw.push_back("None");
    Yaw.push_back("MAX_DELTA_LEFT");
    Yaw.push_back("MAX_DELTA_RIGHT");
    Yaw.push_back("MAX_DELTA_FLIPPER");
    Yaw.push_back("MAX_DELTA_JITTER");
     Yaw.push_back("MAX_DELTA_TEST");
    Yaw.push_back("STATIC");
    Yaw.push_back("BALANCE");
    // Fake Yaw
    FakeYaw.push_back("None");
    FakeYaw.push_back("MAX_DELTA_LEFT");
    FakeYaw.push_back("MAX_DELTA_RIGHT");
    FakeYaw.push_back("MAX_DELTA_FLIPPER");
    FakeYaw.push_back("MAX_DELTA_JITTER");

    hitscan.push_back("off");
    hitscan.push_back("low");
    hitscan.push_back("normal");
    hitscan.push_back("high");
    hitscan.push_back("extreme");
    hitscan.push_back("baim");
    hitscan.push_back("head");
    hitscan.push_back("upperbody");
    hitscan.push_back("lowerbody");
    hitscan.push_back("arms");
    hitscan.push_back("legs");
    hitscan.push_back("baimlowerbody");
    
    fakewalk.push_back("Off");
    fakewalk.push_back("v1");
    fakewalk.push_back("v2");
    fakewalk.push_back("v3");
    

    this->renderCheckbox(x - 8, y + 15, "Ragebot Enabled", &vars.aimbot.enabled);
    this->renderCheckbox(x - 8, y + 35, "SilentAim", &vars.aimbot.silent);
    this->renderSlider(x + 10, y + 55, 150, "FOV", vars.aimbot.FovToPlayer, 180, 0);
    this->renderSlider(x + 10, y + 75, 150, "Hitbox", vars.aimbot.hitbox, 19, 0);
    this->renderCheckbox(x - 8, y + 95, "Auto Wall", &vars.aimbot.autowall);
    this->renderSlider(x + 10, y + 115, 150, "Minimum Damage", vars.aimbot.mindmg, 100, 0);
    this->renderCheckbox(x - 8, y + 135, "Hitchance", &vars.aimbot.hitchance);
    this->renderSlider(x + 10, y + 155, 150, "", vars.aimbot.accuracyhithcance, 100, 0);
    this->renderSlider(x + 10, y + 180, 150, "Pointscale", vars.aimbot.pointscale, 100, 0);
    draw->drawstring(x + 27, y + 200 + 10, Color::White(), osFont, "Baim options", true);
    this->renderCheckbox(x - 8, y + 220, "Baim Under x HP", &vars.aimbot.baimhp);
    this->renderSlider(x + 10, y + 240, 150, "", vars.aimbot.bodyaim_health, 100, 0);
    this->renderCheckbox(x - 8, y + 270, "Baim if in air", &vars.aimbot.baim_in_air);
    this->renderCheckbox(x - 8, y + 290, "Baim if not accurate", &vars.aimbot.baim_high_inaccuracy);
    this->renderCheckbox(x - 8, y + 310, "Baim if local slow-walk", &vars.aimbot.baim_slow_walk);
    this->renderCheckbox(x + 235, y + 15, "Fakewalk", &vars.aimbot.fakewalk);
    this->renderCombo(x + 235, y + 32, 90, 20, "Fakewalk", fakewalk, vars.aimbot.fakewalktype, &vars.fakewalk_opend);
    this->renderCheckbox(x + 235, y + 55, "Auto Scope", &vars.aimbot.autoscope);
    this->renderCheckbox(x + 235, y + 75, "Auto Pistol", &vars.aimbot.autopistol);
    this->renderCheckbox(x + 235, y + 95, "Auto Crouch", &vars.aimbot.autocrouch);
    this->renderCheckbox(x + 235, y + 115, "Auto Shoot", &vars.aimbot.autoshoot);
    this->renderCheckbox(x + 235, y + 135, "Hitscan", &vars.aimbot.hitscan);
    this->renderCombo(x + 235, y + 155, 150, 20, "Off", hitscan, vars.aimbot.hitscantype, &vars.hitscan_opend);
    this->renderCheckbox(x + 235, y + 185, "AutoStop", &vars.aimbot.autostop);
    this->renderCheckbox(x + 235, y + 255, "Moonwalk", &vars.misc.moonwalk);
    this->renderCheckbox(x + 235, y + 275, "Slow walk (SHIFT)", &vars.aimbot.autoslow);
    this->renderCheckbox(x + 235, y + 295, "Airstuck (KEY_Z)", &vars.misc.airstuck);
    this->renderCheckbox(x + 235, y + 205, "Yaw Resolver", &vars.aimbot.Yawresolver);
    this->renderCheckbox(x + 235, y + 230, "Legit AA", &vars.misc.legitaa);
    this->renderCheckbox(x + 444, y + 15, "Anti-Aim", &vars.misc.antiaim);
    this->renderCheckbox(x + 444, y + 35, "Show Real Angles", &vars.misc.thirdpersonmode);
    this->renderCheckbox(x + 444, y + 55, "Pitch Enabled", &vars.misc.pitchenabled);
    if(vars.misc.pitchenabled){
        this->renderCombo(x + 444, y + 75, 90, 20, "Pitch", Pitch, vars.misc.aaX, &vars.aaX_opend);
    }
    if(!vars.aaX_opend){
        this->renderCheckbox(x + 444, y + 105, "Yaw Enabled", &vars.misc.desyncenabled);
    }
    if((!vars.aaX_opend) && vars.misc.desyncenabled) {
        this->renderCombo(x + 444, y + 125, 90, 20, "Yaw", Yaw, vars.misc.type, &vars.aaY_opend);
        this->renderCombo(x + 444, y + 155, 90, 20, "Fake Yaw", FakeYaw, vars.misc.typeFake, &vars.FaaY_opend);
    }
    this->renderCheckbox(x + 444, y + 185, "LBY Breaker", &vars.misc.lbybreaker); // 60
    this->renderSlider(x + 444, y + 225, 115, "Offset", vars.misc.lbybreakeroffset, 360.f, 0.f);
    this->renderCheckbox(x + 444, y + 255, "Manual AA", &vars.misc.manualaa); // 60
    this->renderCheckbox(x + 444, y + 285, "Fake Duck (HOLD KEY X)", &vars.misc.fakeduck); // 60
    this->renderCheckbox(x + 444, y + 315, "Thirdperson Spectate", &vars.misc.spectatorfirstperson); // 60
}

void cMenu::renderVis(int x, int y) {
    
    vector<string> Players;
    vector<string> Hands;
    vector<string> Weapons;
    vector<string> fakelag;
    vector<string> localchams;
    
    Players.push_back("SkeetCham");
    Players.push_back("Texture");
    Players.push_back("WireFrame");
    Players.push_back("Crystal Blue");
    Players.push_back("Mexican Cartel");
    Players.push_back("Fading");
    Players.push_back("Glass");
    Players.push_back("Gold");
    Players.push_back("Red Glow");
    Players.push_back("Fishing Net");
    Players.push_back("Branches");
    Players.push_back("Plastic");
    
    Hands.push_back("SkeetCham");
    Hands.push_back("Texture");
    Hands.push_back("Wireframe");
    Hands.push_back("Crystal Blue");
    Hands.push_back("Mexican Cartel");
    Hands.push_back("Fading");
    Hands.push_back("Glass");
    Hands.push_back("Gold");
    Hands.push_back("Red Glow");
    Hands.push_back("Fishing Net");
    Hands.push_back("Branches");
    Hands.push_back("Plastic");
    
    Weapons.push_back("SkeetCham");
    Weapons.push_back("Texture");
    Weapons.push_back("Wireframe");
    Weapons.push_back("Crystal Blue");
    Weapons.push_back("Mexican Cartel");
    Weapons.push_back("Fading");
    Weapons.push_back("Glass");
    Weapons.push_back("Gold");
    Weapons.push_back("Red Glow");
    Weapons.push_back("Fishing Net");
    Weapons.push_back("Branches");
    Weapons.push_back("Plastic");
    
    fakelag.push_back("SkeetCham");
    fakelag.push_back("Texture");
    fakelag.push_back("Wireframe");
    fakelag.push_back("Crystal Blue");
    fakelag.push_back("Mexican Cartel");
    fakelag.push_back("Fading");
    fakelag.push_back("Glass");
    fakelag.push_back("Gold");
    fakelag.push_back("Red Glow");
    fakelag.push_back("Fishing Net");
    fakelag.push_back("Branches");
    fakelag.push_back("Plastic");
    
    localchams.push_back("SkeetCham");
    localchams.push_back("Texture");
    localchams.push_back("Wireframe");
    localchams.push_back("Crystal Blue");
    localchams.push_back("Mexican Cartel");
    localchams.push_back("Fading");
    localchams.push_back("Glass");
    localchams.push_back("Gold");
    localchams.push_back("Red Glow");
    localchams.push_back("Fishing Net");
    localchams.push_back("Branches");
    localchams.push_back("Plastic");
    localchams.push_back("Lit");
    
    this->renderCheckbox(x - 8, y + 15, "Enabled", &vars.visuals.enabled);
    this->renderCheckbox(x - 8, y + 35, "Enemy only", &vars.visuals.enemyonly);
    this->renderCheckbox(x - 8, y + 55, "Vis Only", &vars.visuals.visonly);
    this->renderCheckbox(x - 8, y + 75, "Box", &vars.visuals.box);
    this->renderCheckbox(x - 8, y + 95, "Name", &vars.visuals.name);
    this->renderCheckbox(x - 8, y + 115, "Health", &vars.visuals.health);
    this->renderCheckbox(x - 8, y + 135, "Armour", &vars.visuals.armour);
    this->renderCheckbox(x - 8, y + 155, "Heath text", &vars.visuals.healthtext);
    this->renderCheckbox(x - 8, y + 175, "Skeleton", &vars.visuals.skeleton);
    this->renderCheckbox(x - 8, y + 195, "Snaplines", &vars.visuals.snapline);
    this->renderCheckbox(x - 8, y + 215, "Grenade ESP", &vars.visuals.grenade);
    this->renderCheckbox(x - 8, y + 235, "Weapon ESP", &vars.visuals.active);
    

    this->renderCheckbox(x - 8, y + 255, "Player Chams", &vars.visuals.chams);
    this->renderCheckbox(x - 8, y + 275, "Hand Chams", &vars.visuals.handchams);
    this->renderCheckbox(x - 8, y + 295, "Weapon Chams", &vars.visuals.weaponchams);
    this->renderCheckbox(x - 8, y + 315, "Fake Lag Chams", &vars.misc.flagchams);
    this->renderCheckbox(x - 8, y + 335, "Local Player Chams", &vars.visuals.localchams);
    
   /* this->renderCheckbox(x - 8, y + 455, "Offscreen ESP", &vars.misc.offscreen);
    this->renderSlider(x + 5, y + 485, 115, "Offscreen Range", vars.misc.offscreenESPRange, 100, 0);*/
    
    
    if(vars.visuals.chams) {
        this->renderCombo(x + 15, y + 355, 150, 20, "SkeetCham", Players, vars.visuals.playersType, &vars.players_opend);
    }
    if(vars.visuals.handchams) {
        if(!vars.players_opend)
            this->renderCombo(x + 15, y + 375, 150, 20, "SkeetCham", Hands, vars.visuals.handsType, &vars.hands_opend);
    }
    if(vars.visuals.weaponchams) {
        if((!vars.players_opend) && !vars.hands_opend)
            this->renderCombo(x + 15, y + 395, 150, 20, "SkeetCham", Weapons, vars.visuals.weaponType, &vars.weapons_opend);
    }
    if(vars.misc.flagchams) {
        if(!vars.players_opend)
            this->renderCombo(x + 15, y + 415, 150, 20, "SkeetCham", fakelag, vars.visuals.fakelagtype, &vars.fakelag_opend);
    }
    if(vars.visuals.localchams) {
        if(!vars.players_opend)
            this->renderCombo(x + 15, y + 435, 150, 20, "SkeetCham", localchams, vars.visuals.localchamstype, &vars.local_opend);
    }
    
    
    int iScreenWidth, iScreenHeight;
    pEngine->GetScreenSize(iScreenWidth, iScreenHeight);
    
    //Middle
    this->renderCheckbox(x + 235, y + 15, "SkinChanger", & vars.visuals.skinc);
    this->renderCheckbox(x + 235, y + 35, "Dropped Weapons", & vars.visuals.weapons);
    this->renderCheckbox(x + 235, y + 55, "Bomb Timer", & vars.visuals.bombtimer);
    this->renderCheckbox(x + 235, y + 75, "Defusing", & vars.visuals.defusing);
    this->renderCheckbox(x + 235, y + 95, "Rescuing", & vars.visuals.rescuing);
    this->renderCheckbox(x + 235, y + 115, "Scoping", & vars.visuals.scoped);
    this->renderCheckbox(x + 235, y + 135, "No Flash", & vars.misc.noflash);
    this->renderSlider(x + 230, y + 155, 150, "", vars.misc.flashalpha, 255, 0);
    this->renderCheckbox(x + 235, y + 175, "Recoil Crosshair", & vars.visuals.rcrosshair);
    this->renderCheckbox(x + 235, y + 195, "Spread Crosshair", &vars.misc.spreadcrosshair);
    this->renderCheckbox(x + 235, y + 215, "No Scope", & vars.misc.noscope);
    this->renderCheckbox(x + 235, y + 235, "AA Indicators", & vars.visuals.antiaim_indicator);
    std::vector<std::string> Indicator;
    
    Indicator.push_back("Off");
    Indicator.push_back("Words");
    Indicator.push_back("Arrows");
    
    this->renderCombo(x + 235, y + 252, 125, 20, "Off", Indicator, vars.visuals.indicatorAA_types, &vars.indicatorAA_opend);
    this->renderCheckbox(x + 235, y + 275, "AA Lines", & vars.visuals.aaline);
    this->renderCheckbox(x + 235, y + 295, "Angle Line Names", & vars.visuals.anglelinenames);
    this->renderCheckbox(x + 235, y + 315, "Watermark", &vars.misc.watermark);
    this->renderCheckbox(x + 235, y + 335, "Nightmode", &vars.misc.nightmode);
    this->renderSlider(x + 230, y + 355, 150, "Player Chams", vars.visuals.playerchams_alpha, 255, 0);
    this->renderSlider(x + 230, y + 375, 150, "Hand Chams", vars.visuals.handchams_alpha, 255, 0);
    this->renderSlider(x + 230, y + 395, 150, "Weapon Chams", vars.visuals.weaponchams_alpha, 255, 0);
    this->renderSlider(x + 230, y + 415, 150, "Fake Lag Chams", vars.visuals.fakelagchams_alpha, 255, 0);
    this->renderSlider(x + 230, y + 435, 150, "Local Player Chams", vars.visuals.localchams_alpha, 255, 0);
    this->renderCheckbox(x + 235, y + 455, "Asuswall", &vars.misc.asuswalls);
    this->renderSlider(x + 230, y + 475, 150, "", vars.misc.asusalpha, 1.f, 0.f);
    
    
    this->renderCheckbox(x + 444, y + 15, "Hitmarker", &vars.visuals.hitmarker);
    this->renderCheckbox(x + 444, y + 35, "Hitmarker Sounds", &vars.visuals.hitmarkersounds);
    this->renderSlider(x + 444, y + 55, 115, "Hitmarker Size", vars.visuals.hitsize, 32, 0);
    this->renderSlider(x + 444, y + 75, 115, "Hitmarker Duration", vars.visuals.hitduration, 3000, 0);
    this->renderSlider(x + 444, y + 95, 115, "Hitmarker In-Gap", vars.visuals.hitinnergap, 16, 0);
    this->renderCheckbox(x + 444, y + 115, "Hitmarker Allies", &vars.visuals.allieshit);
    this->renderCheckbox(x + 444, y + 135, "Hitmarker Enemies", &vars.visuals.enemyhit);
    this->renderCheckbox(x + 444, y + 155, "Left-Hand Knife", &vars.visuals.inverseragdoll);
    this->renderCheckbox(x + 444, y + 175, "Sniper Crosshair", &vars.misc.snipercrosshair);
    
    this->renderCheckbox(x + 444, y + 195, "Enemy Event Log", &vars.misc.showenemieslog);
    this->renderCheckbox(x + 444, y + 215, "Allies Event Log", &vars.misc.showallieslog);
    this->renderSlider(x + 444, y + 245, 115, "Logger Duration", vars.misc.loggerduration, 5000.f, 0.f);
    this->renderSlider(x + 444, y + 275, 115, "Logger Lines", vars.misc.loggerlines, 15, 0);
    this->renderCheckbox(x + 444, y + 315, "Local Event Log", &vars.misc.showlocalplayer);
    
    this->renderCheckbox(x + 444, y + 335, "Dlights", &vars.misc.dlight);
    this->renderCheckbox(x + 444, y + 355, "Dlight enemy", &vars.misc.dlightenemy);
    this->renderCheckbox(x + 444, y + 375, "Dlight allies", &vars.misc.dlightallies);
    this->renderSlider(x + 444, y + 405, 115, "Dlight Radius", vars.misc.dlightradius, 1000, 0);
    
    this->renderCheckbox(x + 444, y + 435, "Bullet Tracers", &vars.visuals.bullett);
    this->renderCheckbox(x + 444, y + 455, "Full-Bright", &vars.misc.fullbright);
    this->renderCheckbox(x + 444, y + 475, "Shot Logs", &vars.misc.logshots);
    
    
    
}


void cMenu::renderMisc(int x, int y) {
    
    vector<string> CT;
    // X
    CT.push_back("off");
    CT.push_back("xanax");//xanax moving
    CT.push_back("supremacy");//supremacy $
    CT.push_back("gamesense");//gamesense
    CT.push_back("zeus");
    
    vector<string> fakeping;
    // X
    fakeping.push_back("v1");
    fakeping.push_back("v2");//xanax moving

    
    this->renderCheckbox(x - 8, y + 15, "Bhop", &vars.misc.bhop);
    this->renderCheckbox(x - 8, y + 35, "Auto strafe", &vars.misc.autostrafe);
    this->renderCheckbox(x - 8, y + 55, "Circle Strafe", &vars.misc.cstrafe);
    this->renderCheckbox(x - 8, y + 75, "FOV Changer", &vars.misc.fovt);
    this->renderSlider(x + 1, y + 95, 150, "", vars.misc.fov, 70, 0);
    this->renderCheckbox(x - 8, y + 115, "No recoil", &vars.misc.norecoil);
    this->renderCheckbox(x - 8, y + 135, "No visual recoil", &vars.misc.novisual);
    this->renderCheckbox(x - 8, y + 155, "Chat Spam", &vars.misc.spammer);
    this->renderCheckbox(x - 8, y + 175, "Thirdperson", &vars.misc.thirdperson);
    this->renderSlider(x + 1, y + 195, 150, "", vars.misc.tpoffset, 200, 0);
    
    this->renderCheckbox(x + 235, y + 15, "WorldPaint", &vars.misc.worldpaint);
    this->renderCheckbox(x + 235, y + 35, "Spec List", &vars.misc.showspectators);
    this->renderCheckbox(x + 235, y + 55, "Antiscreenshot", &vars.misc.antiscreenshot);
    this->renderCheckbox(x + 235, y + 75, "Anti untrust", &vars.misc.antiuntrust);
    
    this->renderCheckbox(x + 235, y + 95, "Clantag", & vars.misc.clantag);
    this->renderCheckbox(x + 235, y + 115, "No Smoke", &vars.visuals.nosmoke);
    this->renderCheckbox(x + 235, y + 135, "No Duck Cooldown", &vars.misc.noduckcooldown);
    this->renderCheckbox(x + 235, y + 155, "Anti afk-kick", &vars.visuals.antiafkkick);
    
    this->renderCheckbox(x + 444, y + 15, "Fake Lag", &vars.misc.fakelag);
    this->renderCheckbox(x + 444, y + 35, "Adaptive", &vars.misc.adaptive);
    //this->renderCheckbox(x + 235, y + 220, "Fake Lag Chams", &vars.misc.flagchams);
    this->renderSlider(x + 444, y + 55, 115, "Fake Lag Factor", vars.misc.fakelagfactor, 16, 0);
    this->renderCheckbox(x + 444, y + 85, "Inverse Ragdoll Gravity", &vars.misc.meme);
    this->renderCheckbox(x + 444, y + 105, "HvH Viewmodel", &vars.misc.hvhviewmodel);
    //this->renderCombo(x + 474, y + 95,  150, 20, "v1", fakeping, vars.misc.fakepingtype, &vars.fakeping_opend);
    this->renderSlider(x + 444, y + 135, 115, "Horizontal Viewmodel", vars.misc.viewmodelx, 20, 0);
    this->renderSlider(x + 444, y + 165, 115, "Vertical Viewmodel", vars.misc.viewmodely, 20, 0);
    this->renderSlider(x + 444, y + 195, 115, "Viewmodel FOV", vars.misc.viewmodelfov, 150, 0);
    
    this->renderCheckbox(x + 444, y + 225, "Thirdperson & Real Angles", &vars.misc.thirdpersonkeybindez);
    this->renderCheckbox(x + 444, y + 245, "Grenade Prediction", &vars.misc.grenadepred);

    this->renderButton1(x + 454, y + 265, "Hide Name", &vars.aimbot.hidename);
    this->renderButton1(x + 454, y + 285, "Your Name", &vars.aimbot.yourname);
    this->renderButton1(x + 454, y + 305, "Fake Vote (Hide Name First)", &vars.aimbot.fakevote);
    this->renderButton1(x + 454, y + 325, "Random Name Stealer", &vars.aimbot.namestealer);
    this->renderButton1(x + 454, y + 345, "Fake Ban (hide then set name)", &vars.aimbot.fakeban);
}

void cMenu::renderColors(int x, int y) {
    
    vector<string> Colors;
    
    Colors.push_back("CT Colours");
    Colors.push_back("T Colours");
    Colors.push_back("Hand/Weapon Colours");
    Colors.push_back("World Colours");
    Colors.push_back("FakeLag Colours");
    Colors.push_back("TP Colours");
    Colors.push_back("Local Colours");
    Colors.push_back("Dlight Colours");
    Colors.push_back("Skybox Colours");

    this->renderCombo(x, y + 300 + 14, 125, 20, "CT Colours", Colors, vars.colors.combo, &vars.colors_opend);
    
    if(vars.colors.combo == 0) {
        vars.colors.ctchams = Color(vars.visuals.CTcham_red, vars.visuals.CTcham_green, vars.visuals.CTcham_blue, 255);
        this->renderSlider_c(x + 5, y + 30, 150, "Red", vars.visuals.CTcham_red, 255, 0, vars.colors.ctchams);
        this->renderSlider_c(x + 5, y + 50, 150, "Green", vars.visuals.CTcham_green, 255, 0, vars.colors.ctchams);
        this->renderSlider_c(x + 5, y + 70, 150, "Blue", vars.visuals.CTcham_blue, 255, 0, vars.colors.ctchams);
        draw->drawstring(x, y + 10, FontColor, mFont, "Visible CT Chams");
        
        vars.colors.ctchams_ign = Color(vars.visuals.CTchamhid_red, vars.visuals.CTchamhid_green, vars.visuals.CTchamhid_blue, 255);
        this->renderSlider_c(x + 235, y + 30, 150, "Red", vars.visuals.CTchamhid_red, 255, 0, vars.colors.ctchams_ign);
        this->renderSlider_c(x + 235, y + 50, 150, "Green", vars.visuals.CTchamhid_green, 255, 0, vars.colors.ctchams_ign);
        this->renderSlider_c(x + 235, y + 70, 150, "Blue", vars.visuals.CTchamhid_blue, 255, 0, vars.colors.ctchams_ign);
        draw->drawstring(x + 230, y + 10, FontColor, mFont, "Hidden CT Chams");
    }
    if(vars.colors.combo == 1) {
       vars.colors.tchams = Color(vars.visuals.Tcham_red, vars.visuals.Tcham_green, vars.visuals.Tcham_blue, 255);
        this->renderSlider_c(x + 5, y + 30, 150, "Red", vars.visuals.Tcham_red, 255, 0, vars.colors.tchams);
        this->renderSlider_c(x + 5, y + 50, 150, "Green", vars.visuals.Tcham_green, 255, 0, vars.colors.tchams);
        this->renderSlider_c(x + 5, y + 70, 150, "Blue", vars.visuals.Tcham_blue, 255, 0, vars.colors.tchams);
        draw->drawstring(x,y + 10, FontColor, mFont, "Visible T Chams");
        
        vars.colors.tchams_ign = Color(vars.visuals.Tchamhid_red, vars.visuals.Tchamhid_green, vars.visuals.Tchamhid_blue, 255);
        this->renderSlider_c(x + 235, y + 30, 150, "Red", vars.visuals.Tchamhid_red, 255, 0, vars.colors.tchams_ign);
        this->renderSlider_c(x + 235, y + 50, 150, "Green", vars.visuals.Tchamhid_green, 255, 0, vars.colors.tchams_ign);
        this->renderSlider_c(x + 235, y + 70, 150, "Blue", vars.visuals.Tchamhid_blue, 255, 0, vars.colors.tchams_ign);
        draw->drawstring(x + 230, y + 10, FontColor, mFont, "Hidden T Chams");
    }
    if(vars.colors.combo == 2) {
         vars.colors.hands = Color(vars.visuals.arm_red, vars.visuals.arm_green, vars.visuals.arm_blue, 255);
           this->renderSlider_c(x + 5, y + 30, 150, "Red", vars.visuals.arm_red, 255, 0, vars.colors.hands);
           this->renderSlider_c(x + 5, y + 50, 150, "Green", vars.visuals.arm_green, 255, 0, vars.colors.hands);
           this->renderSlider_c(x + 5, y + 70, 150, "Blue", vars.visuals.arm_blue, 255, 0, vars.colors.hands);
           draw->drawstring(x, y + 10, FontColor, mFont, "Hands");
           
           vars.colors.weapon = Color(vars.visuals.weapon_red, vars.visuals.weapon_green, vars.visuals.weapon_blue, 255);
           this->renderSlider_c(x + 235, y + 30, 150, "Red", vars.visuals.weapon_red, 255, 0, vars.colors.weapon);
           this->renderSlider_c(x + 235, y + 50, 150, "Green", vars.visuals.weapon_green, 255, 0, vars.colors.weapon);
           this->renderSlider_c(x + 235, y + 70, 150, "Blue", vars.visuals.weapon_blue, 255, 0, vars.colors.weapon);
           draw->drawstring(x + 230, y + 10, FontColor, mFont, "Weapons");
           
    }
    if(vars.colors.combo == 3) {
        this->drawcolorpicker(x, y + 30, "World", vars.colors.world);
        this->drawcolorpicker(x + 235, y + 30, "Sky", vars.colors.sky);
    }
    if(vars.colors.combo == 4) {
        this->drawcolorpicker(x, y + 30, "FakeLag", vars.colors.fakelag);

    }
    if(vars.colors.combo == 5) {
        this->drawcolorpicker(x, y + 30, "TP", vars.colors.scopedchams);
        
    }
    if(vars.colors.combo == 6) {
        this->drawcolorpicker(x, y + 30, "Colors", vars.colors.localchams);
        
    }
    if(vars.colors.combo == 7) {
        this->drawcolorpicker(x, y + 30, "Dlight", vars.colors.dlight);
        
    }
    if(vars.colors.combo == 8){
        vars.colors.skybox = Color(vars.visuals.skyboxr, vars.visuals.skyboxg, vars.visuals.skyboxb, 255);
        this->renderSlider_c(x + 5, y + 30, 150, "Red", vars.visuals.skyboxr, 255, 0, vars.colors.skybox);
        this->renderSlider_c(x + 5, y + 50, 150, "Green", vars.visuals.skyboxg, 255, 0, vars.colors.skybox);
        this->renderSlider_c(x + 5, y + 70, 150, "Blue", vars.visuals.skyboxb, 255, 0, vars.colors.skybox);
        draw->drawstring(x, y + 10, FontColor, mFont, "Skybox");
    }

}

void cMenu::renderConfigs(int x, int y) {
    vector<string> conf;
    
    conf.push_back("scout");
    conf.push_back("autos");
    conf.push_back("legit");
    conf.push_back("smg");
    conf.push_back("rifles");
    
    this->renderCombo(x, y + 265,  150, 20, "scout", conf, cfg.cfgcombo, &vars.cfg_opend);
    if(!vars.cfg_opend) {
        this->renderButton(x, y + 285, "Save", &cfg.saveconfig);
        this->renderButton(x + 85, y + 285, "Load", &cfg.loadconfig);
        
    }
}

void cMenu::renderCredits(int x, int y) {
    vector<string> conf;
    vector<string> conf1;
    vector<string> conf2;
    vector<string> conf3;
    
    conf.push_back("A");
    conf.push_back("B");
    conf.push_back("C");
    conf.push_back("D");
    conf.push_back("E");
    conf.push_back("F");
    conf.push_back("G");
    conf.push_back("H");
    conf.push_back("I");
    conf.push_back("J");
    conf.push_back("K");
    conf.push_back("L");
    conf.push_back("M");
    conf.push_back("N");
    conf.push_back("O");
    conf.push_back("P");
    conf.push_back("Q");
    conf.push_back("R");
    conf.push_back("S");
    conf.push_back("T");
    conf.push_back("U");
    conf.push_back("V");
    conf.push_back("W");
    conf.push_back("X");
    conf.push_back("Y");
    conf.push_back("Z");
    conf.push_back("4");
    conf.push_back("6");
    conf.push_back("7");
    conf.push_back("8");
    conf.push_back("9");
    conf.push_back("LeftShift");
    conf.push_back("LControl");
    conf.push_back("LAlt");
    
    conf1.push_back("A");
    conf1.push_back("B");
    conf1.push_back("C");
    conf1.push_back("D");
    conf1.push_back("E");
    conf1.push_back("F");
    conf1.push_back("G");
    conf1.push_back("H");
    conf1.push_back("I");
    conf1.push_back("J");
    conf1.push_back("K");
    conf1.push_back("L");
    conf1.push_back("M");
    conf1.push_back("N");
    conf1.push_back("O");
    conf1.push_back("P");
    conf1.push_back("Q");
    conf1.push_back("R");
    conf1.push_back("S");
    conf1.push_back("T");
    conf1.push_back("U");
    conf1.push_back("V");
    conf1.push_back("W");
    conf1.push_back("X");
    conf1.push_back("Y");
    conf1.push_back("Z");
    conf1.push_back("4");
    conf1.push_back("6");
    conf1.push_back("7");
    conf1.push_back("8");
    conf1.push_back("9");
    conf1.push_back("LeftShift");
    conf1.push_back("LControl");
    conf1.push_back("LAlt");
    
    conf2.push_back("{");
    conf2.push_back("}");
    conf2.push_back(";");
    conf2.push_back("'");
    conf2.push_back("`");
    conf2.push_back(",");
    conf2.push_back(".");
    conf2.push_back("/");
    conf2.push_back("BackSlash");
    conf2.push_back("-");
    conf2.push_back("=");
    conf2.push_back("Enter");
    conf2.push_back("Tab");
    conf2.push_back("Caps");
    conf2.push_back("Escape");
    conf2.push_back("LeftShift");
    conf2.push_back("RShift");
    conf2.push_back("LAlt");
    conf2.push_back("RAlt");
    conf2.push_back("LControl");
    conf2.push_back("RControl");
    
    conf3.push_back("A");
    conf3.push_back("B");
    conf3.push_back("C");
    conf3.push_back("D");
    conf3.push_back("E");
    conf3.push_back("F");
    conf3.push_back("G");
    conf3.push_back("H");
    conf3.push_back("I");
    conf3.push_back("J");
    conf3.push_back("K");
    conf3.push_back("L");
    conf3.push_back("M");
    conf3.push_back("N");
    conf3.push_back("O");
    conf3.push_back("P");
    conf3.push_back("Q");
    conf3.push_back("R");
    conf3.push_back("S");
    conf3.push_back("T");
    conf3.push_back("U");
    conf3.push_back("V");
    conf3.push_back("W");
    conf3.push_back("X");
    conf3.push_back("Y");
    conf3.push_back("Z");
    conf3.push_back("4");
    conf3.push_back("6");
    conf3.push_back("7");
    conf3.push_back("8");
    conf3.push_back("9");
    conf3.push_back("LeftShift");
    conf3.push_back("LControl");
    conf3.push_back("LAlt");
    
    
    this->renderCheckbox(x - 8, y + 15, "Thirdperson OnKey", &vars.misc.thirdpersonkeybindez);
    this->renderCombo(x - 8, y + 35, 150, 20, "A", conf, vars.misc.tpkeybind, &vars.thirdpersonkeyopend);
    this->renderCheckbox(x + 235, y + 15, "Triggerbot OnKey", &vars.misc.triggerbotkey);
    this->renderCombo(x + 235, y + 35, 150, 20, "A", conf1, vars.misc.triggerbotkeybind, &vars.triggerbot_opend);
    this->renderCheckbox(x - 8, y + 165, "Fakewalk OnKey", &vars.misc.fakewalkkey);
    this->renderCombo(x - 8, y + 185, 150, 20, "{", conf2, vars.misc.fakewalkkeybind, &vars.fakewalk1_opend);
    this->renderCheckbox(x + 444, y + 15, "Autoblock Keybind", &vars.misc.autoblockkey);
    this->renderCombo(x + 444, y + 35, 150, 20, "A", conf3, vars.misc.autoblockkeybind, &vars.autoblock_opend);

}


// Menu tabs
enum mTab
{
    Main    = 0,
    LegitBot  = 1,
    RageBot   = 2,
    Visuals  = 3,
    Misc = 4,
    ColorsTab = 5,
    ConfigTab = 6,
    Credits = 7
    
};

static int curTab = mTab::LegitBot;

// This is where the menu is "put together"
void cMenu::renderMenu() {
    
    static int x = 100;
    static int y = 100;
    int w = 695;
    int h = 600;
    int hh = 22; // The height of the dragable area
    
    
    
    draw->fillrgba(x, y, w, h, Color(28, 28, 28, 255));
    draw->GradientH(x, y + 19, w, 3, Color(185, 55, 140, 255), Color(35, 85, 145, 255), Color(144, 238, 144, 200));
    static int counter = 0;
    static float colors[3] = { 1.f, 0.f, 0.f };
    
    if (colors[counter] >= 1.0f)
    {
        colors[counter] = 1.0f;
        counter += 1;
        if (counter > 2)
            counter = 0;
    }
    else
    {
        int prev = counter - 1;
        if (prev < 0) prev = 2;
        colors[prev] -= 0.05f;
        colors[counter] += 0.05f;
    }
    draw->drawstring(x + ( ( w - 4 ) / 2 ) + 2, y + 10, Color::White(), mFont, "killers.cc", true);
    
    if(draw->inArea(x + 2, y + 27, 96, 20)) {
        
        //draw->RectOutlined(x + 2, y + 20 + 5, 96, 25, 1, Color(12, 12, 12, 255), greycolor);
        
        if(WasReleased)
            curTab = mTab::LegitBot;
        
    } else if(draw->inArea(x + 102, y + 27, 96, 20)) {
        
        //draw->RectOutlined(x + 102, y + 20 + 5, 96, 25, 1, Color(12, 12, 12, 255), greycolor);
        
        if(WasReleased)
            curTab = mTab::RageBot;
        
    } else if(draw->inArea(x + 202, y + 27, 96, 20)) {
        
        //draw->RectOutlined(x + 202, y + 20 + 5, 96, 25, 1, Color(12, 12, 12, 255), greycolor);
        
        if(WasReleased)
            curTab = mTab::Visuals;
        
    } else if(draw->inArea(x + 302, y + 27, 96, 20)) {
        
        //draw->RectOutlined(x + 302, y + 20 + 5, 96, 25, 1, Color(12, 12, 12, 255), greycolor);
        
        if(WasReleased)
            curTab = mTab::Misc;
        
    } else if(draw->inArea(x + 402, y + 27, 96, 20)) {
        
       // draw->RectOutlined(x + 402, y + 20 + 5, 96, 25, 1, Color(12, 12, 12, 255), greycolor);
        
        if(WasReleased)
            curTab = mTab::ColorsTab;
        
    } else if(draw->inArea(x + 502, y + 27, 96, 20)) {
        
        //draw->RectOutlined(x + 502, y + 20 + 5, 96, 25, 1, Color(12, 12, 12, 255), greycolor);
        
        if(WasReleased)
            curTab = mTab::ConfigTab;
            
    } else if(draw->inArea(x + 602, y + 27, 96, 20)) {
        
        //draw->RectOutlined(x + 602, y + 20 + 5, 96, 25, 1, Color(12, 12, 12, 255), greycolor);
        
        if(WasReleased)
            curTab = mTab::Credits;
    }
    
    
    
    switch (curTab) {
            
        case mTab::LegitBot:
            render_section(x + 10, y + 55, 220, h - 62, "Main");
            render_section(x + 249, y + 55, 220, h - 62, "Other");
            this->renderAim(x + 35, y + 30 + 20 + 5);
            break;
            
        case mTab::RageBot:
            render_section(x + 26, y + 55, 220, h - 62, "Main");
            render_section(x + 249, y + 55, 220, h - 62, "Other");
            render_section(x + 460, y + 55, 220, h - 62, "Anti-Aim");
            this->renderAntiAim(x + 35, y + 30 + 20 + 5);
            break;
            
        case mTab::Visuals:
            render_section(x + 26, y + 55, 220, h - 62, "Main");
            render_section(x + 249, y + 55, 220, h - 62, "Visuals");
            render_section(x + 460, y + 55, 220, h - 62, "Other");
            this->renderVis(x + 35, y + 30 + 20 + 5);
            break;
            
        case mTab::Misc:
            render_section(x + 26, y + 55, 220, h - 62, "Main");
            render_section(x + 249, y + 55, 220, h - 62, "Other");
            render_section(x + 460, y + 55, 220, h - 62, "HvH");
            this->renderMisc(x + 35, y + 30 + 20 + 5);
            break;
            
        case mTab::ColorsTab:
            render_section(x + 10, y + 55, 220, h - 62, "Main");
            render_section(x + 249, y + 55, 220, h - 62, "Other");
            this->renderColors(x + 35, y + 30 + 20 + 5);

            break;
            
        case mTab::ConfigTab:
            render_section(x + 10, y + 55, 220, h - 62, "Main");
            this->renderConfigs(x + 35, y + 30 + 20 + 5);
            break;
            
        case mTab::Credits:
            render_section(x + 26, y + 55, 220, h - 62, "1");
            render_section(x + 249, y + 55, 220, h - 62, "2");
            render_section(x + 460, y + 55, 220, h - 62, "3");
            this->renderCredits(x + 35, y + 30 + 20 + 5);
            break;
            
        default:
            break;
            
    }

    config->getConfig(cfg.cfgcombo);

    if(cfg.loadconfig) {
        config->LoadConfig();
        skins_cfg->LoadSkins();
    }
    if(cfg.saveconfig) {
        config->SaveConfig();
    }
    
    if(vars.aimbot.hidename){
        ChangeName("\n\xAD\xAD\xAD");
    }
    
    if(vars.aimbot.yourname){
        ChangeName("b e t r a y a l");
    }
    
    if(vars.aimbot.fakevote){
        ChangeName("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPress F1 To Kill All These Damn Niggers!!!\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }
    
    if(vars.aimbot.namestealer){
        auto pLocal = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
        for (int i = 0; i < pEngine->GetMaxClients(); i++)
        {
            C_BaseEntity* player = pEntList->GetClientEntity(i);
            if (!player)
                continue;
            if (player == pLocal)
                continue;
            player_info_t pInfo;
            pEngine->GetPlayerInfo(i, &pInfo);
            if (pInfo.ishltv)
                continue;
            std::string name = "  ";
            name += pInfo.name;
            name += " ";
            char* tekst = &name[0];
            ChangeName(tekst);
            
        }
    }
    if(vars.aimbot.fakeban){
        std::string fakeban = " \x01\x0B\x07 " + GetLocalName() + " has been permanently banned from official CS:GO servers. \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 \x01 You";
        ChangeName(fakeban.c_str());
    }
    
    draw->drawstring(x + 50, y + 22 + 16, Color::White(), osFont, "LEGITBOT", true);
    draw->drawstring(x + 150, y + 22 + 17, Color::White(), osFont, "RAGEBOT", true);
    draw->drawstring(x + 250, y + 22 + 16, Color::White(), osFont, "VISUALS", true);
    draw->drawstring(x + 350, y + 22 + 16, Color::White(), osFont, "MISC", true);
    draw->drawstring(x + 450, y + 22 + 15, Color::White(), osFont, "COLORS", true);
    draw->drawstring(x + 550, y + 22 + 15, Color::White(), osFont, "CONFIG", true);
    draw->drawstring(x + 650, y + 22 + 15, Color::White(), osFont, "KEYBINDS", true);
    
    Pressed(MOUSE_LEFT);
    draw->MoveMenu(x, y, w, hh, 1);
}

