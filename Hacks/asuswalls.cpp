//
//  asuswalls.cpp
//  pwned
//
//  Created by Finn Le var on 8/05/17.
//  Copyright © 2017 vlone.cc. All rights reserved.
//

#include "asuswalls.h"

float r = 0.0f, g = 0.0f, b = 0.0f, a = 0.0f;

std::unordered_map<MaterialHandle_t, Color> worldMaterials;
std::unordered_map<MaterialHandle_t, Color> worldMaterials2;

void asuswalls(ClientFrameStage_t stage) {
    
    for (auto i = pMatSystem->FirstMaterial(); i != pMatSystem->InvalidMaterial(); i = pMatSystem->NextMaterial(i))
    {
        auto pMat = pMatSystem->GetMaterial(i);
        
        if (!pMat)
            continue;
        
        if (strstr(pMat->GetTextureGroupName(), "StaticProp"))
        {
            static auto r_DrawSpecificStaticProp = pCvar->FindVar("r_DrawSpecificStaticProp");
            
            std::string modelName = pMat->GetName();
            
            if (vars.misc.asuswalls)
            {
                r_DrawSpecificStaticProp->SetValue(0);
                pMat->AlphaModulate(vars.misc.asusalpha);
            }
            else
            {
                r_DrawSpecificStaticProp->SetValue(1);
                pMat->ColorModulate(1.f, 1.f, 1.f);
                pMat->AlphaModulate(1.f);
            }
        }
        
        
        
        if (strstr(pMat->GetTextureGroupName(), "Particle textures"))
        {
            pMat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, vars.misc.asuswalls);
        }
    }
}
void FullBright(){
    
    if (!pEngine->IsConnected() || !pEngine->IsInGame())
        return;
    
    static ConVar* fullbright = pCvar->FindVar("mat_fullbright");
    fullbright->nFlags &= ~FCVAR_CHEAT;
    
    if (vars.misc.fullbright) {
        fullbright->SetValue(1);
    }
    else{
        fullbright->SetValue(0);
    }
}
void InverseRagdoll(){
    
    if (!pEngine->IsConnected() || !pEngine->IsInGame())
        return;
    
    static ConVar* inverseragdoll = pCvar->FindVar("cl_ragdoll_gravity");
    inverseragdoll->nFlags &= ~FCVAR_CHEAT;
    
    if (vars.misc.meme) {
        inverseragdoll->SetValue(-600);
    }
    else{
        inverseragdoll->SetValue(600);
    }
}
void ViewmodelHVH(){
    
    if (!pEngine->IsConnected() || !pEngine->IsInGame())
        return;
    
       ConVar* inverseragdoll2 = pCvar->FindVar("viewmodel_offset_x");
       *(int*)((uintptr_t)&inverseragdoll2->fnChangeCallback + 0x15) = 0;
    
       ConVar* inverseragdoll3 = pCvar->FindVar("viewmodel_offset_y");
       *(int*)((uintptr_t)&inverseragdoll3->fnChangeCallback + 0x15) = 0;
       
        ConVar* inverseragdoll4 = pCvar->FindVar("viewmodel_offset_z");
        *(int*)((uintptr_t)&inverseragdoll4->fnChangeCallback + 0x15) = 0;
    
        ConVar* inverseragdoll5 = pCvar->FindVar("viewmodel_fov");
        *(int*)((uintptr_t)&inverseragdoll5->fnChangeCallback + 0x15) = 0;
    
        static ConVar* inverseragdoll8 = pCvar->FindVar("fov_cs_debug");
        *(int*)((uintptr_t)&inverseragdoll8->fnChangeCallback + 0x15) = 0;
    
        auto sky = pCvar->FindVar("r_3dsky");

       if (vars.misc.hvhviewmodel) {
           inverseragdoll2->SetValue(vars.misc.viewmodelx);
           inverseragdoll3->SetValue(vars.misc.viewmodely);
           inverseragdoll4->SetValue(-10);
           inverseragdoll5->SetValue(vars.misc.viewmodelfov);
           sky->SetValue(0);
       }else{
           inverseragdoll2->SetValue(2);
           inverseragdoll3->SetValue(2);
           inverseragdoll4->SetValue(-1);
           inverseragdoll5->SetValue(68);
           sky->SetValue(1);
       }
    if (vars.misc.hvhviewmodel && vars.misc.thirdperson && vars.misc.noscope) {
        inverseragdoll8->SetValue(100);
    }else{
        inverseragdoll8->SetValue(0);
    }
        
}
void NightMode()
{
    static bool nightmode_performed = false, nightmode_lastsetting;
    
    if (!pEngine->IsConnected() || !pEngine->IsInGame())
    {
        if (nightmode_performed)
            nightmode_performed = false;
        return;
    }
    
    auto local_player = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if (!local_player)
        return;
    
    if (!local_player)
    {
        if (nightmode_performed)
            nightmode_performed = false;
        return;
    }
    
    if (nightmode_lastsetting != vars.misc.nightmode)
    {
        nightmode_lastsetting = vars.misc.nightmode;
        nightmode_performed = false;
    }
    
    if (!nightmode_performed)
    {
        static ConVar* r_DrawSpecificStaticProp = pCvar->FindVar("r_DrawSpecificStaticProp");
        r_DrawSpecificStaticProp->nFlags &= ~FCVAR_CHEAT;
        
        static ConVar* sv_skyname = pCvar->FindVar("sv_skyname");
        sv_skyname->nFlags &= ~FCVAR_CHEAT;
        
        for (MaterialHandle_t i = pMatSystem->FirstMaterial(); i != pMatSystem->InvalidMaterial(); i = pMatSystem->NextMaterial(i))
        {
            IMaterial *mat = pMatSystem->GetMaterial(i);
            
            if (!mat)
                continue;
            
            if ( vars.misc.nightmode){
                sv_skyname->SetValue("sky_csgo_night02");
            }
            
                            if ( strstr( mat->GetTextureGroupName( ), "World" ) )
                            {
                                if ( vars.misc.nightmode ){
                                    mat->ColorModulate( 0.08, 0.08, 0.05);
                                }else{
                                    mat->ColorModulate( 1, 1, 1 );
                                }
                                if ( vars.misc.nightmode ){
                                    mat->SetMaterialVarFlag( MATERIAL_VAR_TRANSLUCENT, false );
                                    mat->ColorModulate( 0.15, 0.15, 0.15 );
                                }else{
                                    mat->ColorModulate( 1.00, 1.00, 1.00 );
                                }
                            }
                            else if ( strstr( mat->GetTextureGroupName( ), "StaticProp" ) )
                            {
                                if ( vars.misc.nightmode ){
                                    mat->ColorModulate( 0.32, 0.32, 0.32 );
                                }else{
                                    mat->ColorModulate( 1, 1, 1 );
                                }
                            }
                        }
        nightmode_performed = true;
    }
}
                   

