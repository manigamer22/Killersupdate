#include "main.h"
#include "../Variables/skins.h"

int keybind(){
    if (vars.misc.tpkeybind == 0) {
        return KEY_A;
    }else if (vars.misc.tpkeybind == 1){
        return KEY_B;
    }else if (vars.misc.tpkeybind == 2){
        return KEY_C;
    }else if (vars.misc.tpkeybind == 3){
        return KEY_D;
    }else if (vars.misc.tpkeybind == 4){
        return KEY_E;
    }else if (vars.misc.tpkeybind == 5){
        return KEY_F;
    }else if (vars.misc.tpkeybind == 6){
        return KEY_G;
    }else if (vars.misc.tpkeybind == 7){
        return KEY_H;
    }else if (vars.misc.tpkeybind == 8){
        return KEY_I;
    }else if (vars.misc.tpkeybind == 9){
        return KEY_J;
    }else if (vars.misc.tpkeybind == 10){
        return KEY_K;
    }else if (vars.misc.tpkeybind == 11){
        return KEY_L;
    }else if (vars.misc.tpkeybind == 12){
        return KEY_M;
    }else if (vars.misc.tpkeybind == 13){
        return KEY_N;
    }else if (vars.misc.tpkeybind == 14){
        return KEY_O;
    }else if (vars.misc.tpkeybind == 15){
        return KEY_P;
    }else if (vars.misc.tpkeybind == 16){
        return KEY_Q;
    }else if (vars.misc.tpkeybind == 17){
        return KEY_R;
    }else if (vars.misc.tpkeybind == 18){
        return KEY_S;
    }else if (vars.misc.tpkeybind == 19){
        return KEY_T;
    }else if (vars.misc.tpkeybind == 20){
        return KEY_U;
    }else if (vars.misc.tpkeybind == 21){
        return KEY_V;
    }else if (vars.misc.tpkeybind == 22){
        return KEY_W;
    }else if (vars.misc.tpkeybind == 23){
        return KEY_X;
    }else if (vars.misc.tpkeybind == 24){
        return KEY_Y;
    }else if (vars.misc.tpkeybind == 25){
        return KEY_Z;
    }else if (vars.misc.tpkeybind == 26){
        return KEY_4;
    }else if (vars.misc.tpkeybind == 27){
        return KEY_6;
    }else if (vars.misc.tpkeybind == 28){
        return KEY_7;
    }else if (vars.misc.tpkeybind == 29){
        return KEY_8;
    }else if (vars.misc.tpkeybind == 30){
        return KEY_9;
    }else if (vars.misc.tpkeybind == 31){
        return KEY_LSHIFT;
    }else if (vars.misc.tpkeybind == 32){
        return KEY_LCONTROL;
    }else if (vars.misc.tpkeybind == 33){
        return KEY_LALT;
    }
}

int hkKeyEvent(void* thisptr, int eventcode, int keynum, const char* currentbinding)
{
    if(eventcode == 0)   // Key pressed
    {
        if(keynum == KEY_INSERT || keynum == KEY_RALT)
        {
            vars.menu = !vars.menu;
            
            if(vars.menu)
                pEngine->ExecuteClientCmd("cl_mouseenable 0");
            else
                pEngine->ExecuteClientCmd("cl_mouseenable 1");
            
        }
        if(vars.misc.thirdpersonkeybindez){
            if(keynum == keybind())
            {
                vars.misc.thirdperson = !vars.misc.thirdperson;
                vars.misc.thirdpersonmode = !vars.misc.thirdpersonmode;
            }
        }
    }
    
    
    
    if(eventcode == 1)  // Key released
    {
        if(vars.menu && (vars.misc.clantag || vars.misc_name || vars.misc_changename))
        {
            draw->handleinput(keynum, draw->m_szCurrentString);
            return 0;
        }
        
    }
    
    return clientVMT->GetOriginalMethod<tKeyEvent>(21)(thisptr, eventcode, keynum, currentbinding);
}
enum
{
    PRESSED  = 0,
    RELEASED = 1,
};



/*
 Too lazy to update if i have time ill do that
 } 
}*/
