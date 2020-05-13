//
//  nosmoke.cpp
//  vHook
//
//  Copyright © 2019 ViKiNG. All rights reserved.
//

#include "nosmoke.hpp"


void remove_smoke(ClientFrameStage_t stage)
{
    if(!pEngine->IsInGame())
        return;
    
    static bool done;
    static bool last_setting;
    
    const vector<const char*> smoke_materials =
    {
        "particle/vistasmokev1/vistasmokev1_emods",
        "particle/vistasmokev1/vistasmokev1_emods_impactdust",
        "particle/vistasmokev1/vistasmokev1_fire",
        "particle/vistasmokev1/vistasmokev1_smokegrenade",
    };
    
    if(!done)
    {
        for(auto material : smoke_materials)
        {
            IMaterial* mat = pMatSystem->FindMaterial(material, TEXTURE_GROUP_OTHER);
            mat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, vars.visuals.nosmoke);
        }
        
        done = true;
    }
    
    if(last_setting != vars.visuals.nosmoke)
    {
        last_setting = vars.visuals.nosmoke;
        done = false;
    }
}
