
#include "autoblock.hpp"

//bool Settings::Autoblock::enabled = false;
//ButtonCode_t Settings::Autoblock::key = ButtonCode_t::KEY_6;
ButtonCode_t keybind3(){
    if (vars.misc.autoblockkeybind == 0) {
        return KEY_A;
    }else if (vars.misc.autoblockkeybind == 1){
        return KEY_B;
    }else if (vars.misc.autoblockkeybind == 2){
        return KEY_C;
    }else if (vars.misc.autoblockkeybind == 3){
        return KEY_D;
    }else if (vars.misc.autoblockkeybind == 4){
        return KEY_E;
    }else if (vars.misc.autoblockkeybind == 5){
        return KEY_F;
    }else if (vars.misc.autoblockkeybind == 6){
        return KEY_G;
    }else if (vars.misc.autoblockkeybind == 7){
        return KEY_H;
    }else if (vars.misc.autoblockkeybind == 8){
        return KEY_I;
    }else if (vars.misc.autoblockkeybind == 9){
        return KEY_J;
    }else if (vars.misc.autoblockkeybind == 10){
        return KEY_K;
    }else if (vars.misc.autoblockkeybind == 11){
        return KEY_L;
    }else if (vars.misc.autoblockkeybind == 12){
        return KEY_M;
    }else if (vars.misc.autoblockkeybind == 13){
        return KEY_N;
    }else if (vars.misc.autoblockkeybind == 14){
        return KEY_O;
    }else if (vars.misc.autoblockkeybind == 15){
        return KEY_P;
    }else if (vars.misc.autoblockkeybind == 16){
        return KEY_Q;
    }else if (vars.misc.autoblockkeybind == 17){
        return KEY_R;
    }else if (vars.misc.autoblockkeybind == 18){
        return KEY_S;
    }else if (vars.misc.autoblockkeybind == 19){
        return KEY_T;
    }else if (vars.misc.autoblockkeybind == 20){
        return KEY_U;
    }else if (vars.misc.autoblockkeybind == 21){
        return KEY_V;
    }else if (vars.misc.autoblockkeybind == 22){
        return KEY_W;
    }else if (vars.misc.autoblockkeybind == 23){
        return KEY_X;
    }else if (vars.misc.autoblockkeybind == 24){
        return KEY_Y;
    }else if (vars.misc.autoblockkeybind == 25){
        return KEY_Z;
    }else if (vars.misc.autoblockkeybind == 26){
        return KEY_4;
    }else if (vars.misc.autoblockkeybind == 27){
        return KEY_6;
    }else if (vars.misc.autoblockkeybind == 28){
        return KEY_7;
    }else if (vars.misc.autoblockkeybind == 29){
        return KEY_8;
    }else if (vars.misc.autoblockkeybind == 30){
        return KEY_9;
    }else if (vars.misc.autoblockkeybind == 31){
        return KEY_LSHIFT;
    }else if (vars.misc.autoblockkeybind == 32){
        return KEY_LCONTROL;
    }else if (vars.misc.autoblockkeybind == 33){
        return KEY_LALT;
    }
}

void Autoblock::CreateMove(CUserCmd* cmd)
{
    if (!vars.aimbot.autoaccept)
        return;
    
    if (!pInputSystem->IsButtonDown(keybind3()))
        return;
    
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    float bestdist = 250.f;
    int index = -1;
    
    for (int i = 1; i < pEngine->GetMaxClients(); i++)
    {
        C_BasePlayer* entity = (C_BasePlayer*) pEntList->GetClientEntity(i);
        
        if (!entity)
            continue;
        
        if (!entity->GetAlive() || entity->GetDormant() || entity == localplayer)
            continue;
        
        float dist = localplayer->GetVecOrigin().DistTo(entity->GetVecOrigin());
        
        if (dist < bestdist)
        {
            bestdist = dist;
            index = i;
        }
    }
    
    if (index == -1)
        return;
    
    C_BasePlayer* target = (C_BasePlayer*) pEntList->GetClientEntity(index);
    
    if (!target)
        return;
    
    QAngle angles = CalccAngle(localplayer->GetVecOrigin(), target->GetVecOrigin());
    
    angles.y -= localplayer->GetEyeAngles()->y;
    normalize_angles(angles);
    
    if (angles.y < 0.0f)
        cmd->sidemove = 250.f;
    else if (angles.y > 0.0f)
        cmd->sidemove = -250.f;
}

