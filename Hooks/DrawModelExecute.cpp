#include "main.h"

matrix3x4_t localfakelagmatrix[128];

string DirName(string source)
{
    source.erase(find(source.rbegin(), source.rend(), '/').base(), source.end());
    return source;
}

string GetWorkingPath()
{
    char pathbuf[PROC_PIDPATHINFO_MAXSIZE];
    proc_pidpath(getpid(), pathbuf, sizeof(pathbuf));
    auto dirname = DirName(pathbuf);
    return dirname;
}

void AngleMatrix(const Vector angles, matrix3x4_t& matrix)
{
    float sr, sp, sy, cr, cp, cy;
    
    sy = sin(DEG2RAD(angles[1]));
    cy = cos(DEG2RAD(angles[1]));
    
    sp = sin(DEG2RAD(angles[0]));
    cp = cos(DEG2RAD(angles[0]));
    
    sr = sin(DEG2RAD(angles[2]));
    cr = cos(DEG2RAD(angles[2]));
    
    //matrix = (YAW * PITCH) * ROLL
    matrix[0][0] = cp * cy;
    matrix[1][0] = cp * sy;
    matrix[2][0] = -sp;
    
    float crcy = cr * cy;
    float crsy = cr * sy;
    float srcy = sr * cy;
    float srsy = sr * sy;
    
    matrix[0][1] = sp * srcy - crsy;
    matrix[1][1] = sp * srsy + crcy;
    matrix[2][1] = sr * cp;
    
    matrix[0][2] = (sp * crcy + srsy);
    matrix[1][2] = (sp * crsy - srcy);
    matrix[2][2] = cr * cp;
    
    matrix[0][3] = 0.0f;
    matrix[1][3] = 0.0f;
    matrix[2][3] = 0.0f;
}

void MatrixSetColumn(const Vector &in, int column, matrix3x4_t& out)
{
    out[0][column] = in.x;
    out[1][column] = in.y;
    out[2][column] = in.z;
}

void AngleMatrix(const Vector &angles, const Vector &position, matrix3x4_t& matrix_out)
{
    AngleMatrix(angles, matrix_out);
    MatrixSetColumn(position, 3, matrix_out);
}

void MatrixCopy(const matrix3x4_t& source, matrix3x4_t& target)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            target[i][j] = source[i][j];
        }
    }
}

void MatrixMultiply(matrix3x4_t& in1, const matrix3x4_t& in2)
{
    matrix3x4_t out;
    if (&in1 == &out)
    {
        matrix3x4_t in1b;
        MatrixCopy(in1, in1b);
        MatrixMultiply(in1b, in2);
        return;
    }
    if (&in2 == &out)
    {
        matrix3x4_t in2b;
        MatrixCopy(in2, in2b);
        MatrixMultiply(in1, in2b);
        return;
    }
    out[0][0] = in1[0][0] * in2[0][0] + in1[0][1] * in2[1][0] +
    in1[0][2] * in2[2][0];
    out[0][1] = in1[0][0] * in2[0][1] + in1[0][1] * in2[1][1] +
    in1[0][2] * in2[2][1];
    out[0][2] = in1[0][0] * in2[0][2] + in1[0][1] * in2[1][2] +
    in1[0][2] * in2[2][2];
    out[0][3] = in1[0][0] * in2[0][3] + in1[0][1] * in2[1][3] +
    in1[0][2] * in2[2][3] + in1[0][3];
    out[1][0] = in1[1][0] * in2[0][0] + in1[1][1] * in2[1][0] +
    in1[1][2] * in2[2][0];
    out[1][1] = in1[1][0] * in2[0][1] + in1[1][1] * in2[1][1] +
    in1[1][2] * in2[2][1];
    out[1][2] = in1[1][0] * in2[0][2] + in1[1][1] * in2[1][2] +
    in1[1][2] * in2[2][2];
    out[1][3] = in1[1][0] * in2[0][3] + in1[1][1] * in2[1][3] +
    in1[1][2] * in2[2][3] + in1[1][3];
    out[2][0] = in1[2][0] * in2[0][0] + in1[2][1] * in2[1][0] +
    in1[2][2] * in2[2][0];
    out[2][1] = in1[2][0] * in2[0][1] + in1[2][1] * in2[1][1] +
    in1[2][2] * in2[2][1];
    out[2][2] = in1[2][0] * in2[0][2] + in1[2][1] * in2[1][2] +
    in1[2][2] * in2[2][2];
    out[2][3] = in1[2][0] * in2[0][3] + in1[2][1] * in2[1][3] +
    in1[2][2] * in2[2][3] + in1[2][3];
    
    in1 = out;
}

FORCEINLINE_CVAR float DotProduct( const float *v1, const float *v2 ) {
    return v1 [ 0 ] * v2 [ 0 ] + v1 [ 1 ] * v2 [ 1 ] + v1 [ 2 ] * v2 [ 2 ];
}

void VectorRotate(const float *in1, const matrix3x4_t& in2, float *out)
{
    out[0] = DotProduct(in1, in2[0]);
    out[1] = DotProduct(in1, in2[1]);
    out[2] = DotProduct(in1, in2[2]);
}

void VectorRotate(const Vector& in1, const matrix3x4_t &in2, Vector &out)
{
    VectorRotate(&in1.x, in2, &out.x);
}

void VectorRotate(const Vector &in1, const Vector &in2, Vector &out)
{
    matrix3x4_t matRotate;
    AngleMatrix(in2, matRotate);
    VectorRotate(in1, matRotate, out);
}

bool IsFileExists(const string& name)
{
    int res = access(name.c_str(), R_OK);
    if (res < 0)
    {
        if (errno == ENOENT)
        {
            return false;
        }
        else if (errno == EACCES)
        {
            return true;
        }
        else
        {
            return true;
        }
    }
    return true;
}

void AddMaterial(string filename, string type, bool ignorez, bool wireframe)
{
    if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append(filename).append(".vmt")))
    {
        stringstream ss;
        
        ss << "\"" + type + "\"\n" << endl;
        ss << "{\n" << endl;
        ss << "\t\"$basetexture\" \"VGUI/white_additive\"\n" << endl;
        ss << "\t\"$nofog\" \"1\"\n" << endl;
        ss << "\t\"$ignorez\" \"" + to_string(ignorez) + "\"\n" << endl;
        ss << "\t\"$wireframe\" \""+ to_string(wireframe) +"\"\n" << endl;
        ss << "\t\"$halflambert\" \"1\"\n" << endl;
        
        ss << "}\n" << endl;
        
        ofstream(GetWorkingPath().append("csgo/materials/").append(filename).append(".vmt").c_str()) << ss.str();
    }
}

void AddMaterial1(string filename, string type, bool ignorez, bool wireframe)
{
    if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append(filename).append(".vmt")))
    {
        stringstream ss;
        
        ss << "\"" + type + "\"\n" << endl;
        ss << "{\n" << endl;
        ss << "\t\"$basetexture\" \"vgui/white_additive\"\n" << endl;
        ss << "\t\"$ignorez\" \"" + to_string(ignorez) + "\"\n" << endl;
        ss << "\t\"$additive\" \"0\"\n" << endl;
        ss << "\t\"$envmap\" \"models/effects/cube_white\"\n" << endl;
        ss << "\t\"$normalmapalphaenvmapmask\" \"1\"\n" << endl;
        ss << "\t\"$envmaptint\" \"[0 0.26 1]\"\n" << endl;
        ss << "\t\"$envmapfresnel\" \"1\"\n" << endl;
        ss << "\t\"$envmapfresnelminmaxexp\" \"[0 1 2]\"\n" << endl;
        ss << "\t\"$alpha\" \"0.3\"\n" << endl;
        ss << "\t\"$envmapcontrast\" \"1\"\n" << endl;
        ss << "\t\"$nofog\" \"1\"\n" << endl;
        ss << "\t\"$model\" \"1\"\n" << endl;
        ss << "\t\"$nocull\" \"0\"\n" << endl;
        ss << "\t\"$selfillum\" \"1\"\n" << endl;
        ss << "\t\"$halflambert\" \"1\"\n" << endl;
        ss << "\t\"$znearer\" \"0\"\n" << endl;
        ss << "\t\"$flat\" \"1\"\n" << endl;
        
        ss << "}\n" << endl;
        
        ofstream(GetWorkingPath().append("csgo/materials/").append(filename).append(".vmt").c_str()) << ss.str();
    }
}

IMaterial* CreateMaterial(bool ignorez, bool wireframe, string szType)
{
    IMaterial* createdMaterial = nullptr;
    
    
    if(szType == "VertexLitGeneric")
    {
        if(ignorez)
        {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("barbossa_chamsmat_textured_ignorez").append(".vmt")))
            {
                AddMaterial("barbossa_chamsmat_textured_ignorez", szType, ignorez, wireframe);
            }
            createdMaterial = pMatSystem->FindMaterial("barbossa_chamsmat_textured_ignorez", TEXTURE_GROUP_MODEL);
        }
        else
        {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("barbossa_chamsmat_textured").append(".vmt")))
            {
                AddMaterial("barbossa_chamsmat_textured", szType, ignorez, wireframe);
            }
            createdMaterial = pMatSystem->FindMaterial("barbossa_chamsmat_textured", TEXTURE_GROUP_MODEL);
        }
    }

    if(szType == "UnlitGeneric")
    {
        if(ignorez)
        {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("barbossa_chamsmat_unlit_ignorez").append(".vmt")))
            {
                AddMaterial("barbossa_chamsmat_unlit_ignorez", szType, ignorez, wireframe);
            }
            
            createdMaterial = pMatSystem->FindMaterial("barbossa_chamsmat_unlit_ignorez", TEXTURE_GROUP_MODEL);
        }
        else
        {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("barbossa_chamsmat_unlit").append(".vmt")))
            {
                AddMaterial("barbossa_chamsmat_unlit", szType, ignorez, wireframe);
            }
            
            createdMaterial = pMatSystem->FindMaterial("barbossa_chamsmat_unlit", TEXTURE_GROUP_MODEL);
        }
    }
    
    
    if(szType == "WireFrame")
    {
        if(ignorez)
        {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("barbossa_chamsmat_unlit_ignorez_wirefame").append(".vmt")))
            {
                AddMaterial("barbossa_chamsmat_unlit_ignorez_wireframe", szType, ignorez, true);
            }
            
            createdMaterial = pMatSystem->FindMaterial("barbossa_chamsmat_unlit_ignorez_wireframe", TEXTURE_GROUP_MODEL);
        }
        else
        {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("barbossa_chamsmat_unlit_wireframe").append(".vmt")))
            {
                AddMaterial("barbossa_chamsmat_unlit_wireframe", szType, ignorez, true);
            }
            
            createdMaterial = pMatSystem->FindMaterial("barbossa_chamsmat_unlit_wireframe", TEXTURE_GROUP_MODEL);
        }
    }
    
    createdMaterial->IncrementReferenceCount();
    return createdMaterial;
}

IMaterial* CreateMaterial1(bool ignorez, bool wireframe, string szType)
{
    IMaterial* createdMaterial1 = nullptr;
    
    
    if(szType == "VertexLitGeneric")
    {
        if(ignorez)
        {
        }
        else
        {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("killerss_chamsmat_metallic").append(".vmt")))
            {
                AddMaterial1("killerss_chamsmat_metallic", szType, ignorez, wireframe);
                
            }
            createdMaterial1 = pMatSystem->FindMaterial("killerss_chamsmat_metallic", TEXTURE_GROUP_MODEL);
        }
    }
    
    createdMaterial1->IncrementReferenceCount();
    return createdMaterial1;
}

void CallOriginalModel(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld)
{
    modelVMT->GetOriginalMethod<tDrawModelExecute>(21)(thisptr, context, state, pInfo, pCustomBoneToWorld);
}

void hkDrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld, CUserCmd* cmd)
{
    
    
    static IMaterial* firstLayer = CreateMaterial(false, false, "VertexLitGeneric");
    static IMaterial* secondLayer = CreateMaterial(true, false, "VertexLitGeneric");
    
    static IMaterial* firstLit = CreateMaterial(false, false, "UnlitGeneric");
    //static IMaterial* secondLit = CreateMaterial(true, false, "UnlitGeneric");
    
    static IMaterial* firstWire = CreateMaterial(false, true, "WireFrame");
    //static IMaterial* secondWire = CreateMaterial(true, true, "WireFrame");
    
    static IMaterial* metalNigga = CreateMaterial1(false, false, "VertexLitGeneric");
   // static IMaterial* GLOWNIGGA = CreateMaterial2(false, false, "VertexLitGeneric");
   
    static IMaterial* Plastic = pMatSystem->FindMaterial("models/inventory_items/trophy_majors/crystal_blue", TEXTURE_GROUP_OTHER);
    static IMaterial* Glass = pMatSystem->FindMaterial("models/inventory_items/cologne_prediction/cologne_prediction_glass", TEXTURE_GROUP_OTHER);
    static IMaterial* Gold = pMatSystem->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", TEXTURE_GROUP_OTHER);
    static IMaterial* crystal = pMatSystem->FindMaterial("models/inventory_items/dogtags/dogtags_outline", TEXTURE_GROUP_OTHER);
    static IMaterial* Mp3 = pMatSystem->FindMaterial("models/inventory_items/wildfire_gold/wildfire_gold_detail", TEXTURE_GROUP_OTHER);
    static IMaterial* Random = pMatSystem->FindMaterial("dev/glow_armsrace.vmt", TEXTURE_GROUP_OTHER);
    static IMaterial* Random1 = pMatSystem->FindMaterial("models/props_shacks/fishing_net01", TEXTURE_GROUP_OTHER);
    static IMaterial* Random2 = pMatSystem->FindMaterial("models/props_foliage/urban_tree03_branches", TEXTURE_GROUP_OTHER);
    static IMaterial* Random3 = pMatSystem->FindMaterial("models/inventory_items/trophy_majors/gloss", TEXTURE_GROUP_OTHER);
   // static IMaterial* GLOWNIGGA = pMatSystem->FindMaterial("glowoverlay", nullptr);
    
    if(pInfo.pModel)
    {
        string pszModel = pModelInfo->GetModelName(pInfo.pModel);
        
        if(vars.misc.antiscreenshot && pEngine->IsTakingScreenshot())
        {
            CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
            pModelRender->ForcedMaterialOverride(NULL);
            return;
        }
        
        
        for (MaterialHandle_t i = pMatSystem->FirstMaterial(); i != pMatSystem->InvalidMaterial(); i = pMatSystem->NextMaterial(i))
        {
            IMaterial *pMaterial = pMatSystem->GetMaterial(i);
            
            if (!pMaterial)
                continue;
            
            if(!vars.misc.worldpaint)
                continue;
            
            if (strstr(pMaterial->GetTextureGroupName(), TEXTURE_GROUP_WORLD))
            {
                pMaterial->ColorModulate(vars.colors.world);
            }
            
        }
        
        // Weapon Chams
        if(pszModel.find("models/weapons/") != string::npos && pszModel.find("arms") == string::npos && vars.visuals.weaponchams)
        {
            IMaterial* materialCheckFirst = [&]() -> IMaterial*
            {
                if(vars.visuals.weaponType == 0)
                    return metalNigga;
                else if(vars.visuals.weaponType == 1)
                    return firstLayer;
                else if (vars.visuals.weaponType == 2)
                    return firstWire;
                else if(vars.visuals.weaponType == 3)
                    return Plastic;
                else if(vars.visuals.weaponType == 4)
                    return Gold;
                else if(vars.visuals.weaponType == 5)
                    return crystal;
                else if(vars.visuals.weaponType == 6)
                    return Glass;
                else if(vars.visuals.weaponType == 7)
                    return Mp3;
                else if(vars.visuals.weaponType == 8)
                    return Random;
                else if(vars.visuals.weaponType == 9)
                    return Random1;
                else if(vars.visuals.weaponType == 10)
                    return Random2;
                else if(vars.visuals.weaponType == 11)
                    return Random3;
            }();
            
            materialCheckFirst->ColorModulate(Color(vars.visuals.weapon_red, vars.visuals.weapon_green, vars.visuals.weapon_blue, 255));
            materialCheckFirst->AlphaModulate(vars.visuals.weaponchams_alpha / 255.f);
            pModelRender->ForcedMaterialOverride(materialCheckFirst);
            CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
        }
        
        
        // Hand Chams
        if(pszModel.find("arms") != string::npos && vars.visuals.handchams)
        {
            IMaterial* materialCheckFirst = [&]() -> IMaterial*
            {
                if(vars.visuals.handsType == 0)
                    return metalNigga;
                else if(vars.visuals.handsType == 1)
                    return firstLayer;
                else if (vars.visuals.handsType == 2)
                    return firstWire;
                else if(vars.visuals.handsType == 3)
                    return Plastic;
                else if(vars.visuals.handsType == 4)
                    return Gold;
                else if(vars.visuals.handsType == 5)
                    return crystal;
                else if(vars.visuals.handsType == 6)
                    return Glass;
                else if(vars.visuals.handsType == 7)
                    return Mp3;
                else if(vars.visuals.handsType == 8)
                    return Random;
                else if(vars.visuals.handsType == 9)
                    return Random1;
                else if(vars.visuals.handsType == 10)
                    return Random2;
                else if(vars.visuals.handsType == 11)
                    return Random3;
            }();
            
            materialCheckFirst->ColorModulate(Color(vars.visuals.arm_red, vars.visuals.arm_green, vars.visuals.arm_blue, 255));
            materialCheckFirst->AlphaModulate(vars.visuals.handchams_alpha / 255.f);
            pModelRender->ForcedMaterialOverride(materialCheckFirst);
            CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
        }
        
        // Player Chams
        if(pszModel.find("models/player") != string::npos && vars.visuals.chams)
        {
            auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
            auto* entity = pEntList->GetClientEntity(pInfo.entity_index);
        
            
            if(entity)
            {
                if(entity->GetHealth() > 0)
                {
                    
                    Color FakeLagColor = [&]() -> Color
                    {
                        if(entity->GetTeam() == 2)
                            return vars.colors.fakelag;
                        else if(entity->GetTeam() == 3)
                            return vars.colors.fakelag;
                    }();
                    
                    Color ScopedColors = [&]() -> Color
                    {
                        if(entity->GetTeam() == 2)
                            return vars.colors.scopedchams;
                        else if(entity->GetTeam() == 3)
                            return vars.colors.scopedchams;
                    }();
                    
                    IMaterial* materialCheckFirst = [&]() -> IMaterial*
                    {
                        if(vars.visuals.playersType == 0)
                            return metalNigga;
                        else if(vars.visuals.playersType == 1)
                            return firstLayer;
                        else if (vars.visuals.playersType == 2)
                            return firstWire;
                        else if(vars.visuals.playersType == 3)
                            return Plastic;
                        else if(vars.visuals.playersType == 4)
                            return Gold;
                        else if(vars.visuals.playersType == 5)
                            return crystal;
                        else if(vars.visuals.playersType == 6)
                            return Glass;
                        else if(vars.visuals.playersType == 7)
                            return Mp3;
                        else if(vars.visuals.playersType == 8)
                            return Random;
                        else if(vars.visuals.playersType == 9)
                            return Random1;
                        else if(vars.visuals.playersType == 10)
                            return Random2;
                        else if(vars.visuals.playersType == 11)
                            return Random3;
                    }();
                    
                    
                    
                    /*IMaterial* materialCheckSecond = [&]() -> IMaterial*
                    {
                        if(vars.visuals.playersType == 0)
                            return secondLit;
                        else if(vars.visuals.playersType == 1)
                            return secondLayer;
                        else if (vars.visuals.playersType == 2)
                            return secondWire;
                    }();*/
                    
                    IMaterial* materialFakelag = [&]() -> IMaterial*
                    {
                        if(vars.visuals.fakelagtype == 0)
                            return metalNigga;
                            
                        else if(vars.visuals.fakelagtype == 1)
                            return firstLayer;
                        else if (vars.visuals.fakelagtype == 2)
                            return firstWire;
                        else if(vars.visuals.fakelagtype == 3)
                            return Plastic;
                        else if(vars.visuals.fakelagtype == 4)
                            return Gold;
                        else if(vars.visuals.fakelagtype == 5)
                            return crystal;
                        else if(vars.visuals.fakelagtype == 6)
                            return Glass;
                        else if(vars.visuals.fakelagtype == 7)
                            return Mp3;
                        else if(vars.visuals.fakelagtype == 8)
                            return Random;
                        else if(vars.visuals.fakelagtype == 9)
                            return Random1;
                        else if(vars.visuals.fakelagtype == 10)
                            return Random2;
                        else if(vars.visuals.fakelagtype == 11)
                            return Random3;
                    }();
                    IMaterial* materialLocal = [&]() -> IMaterial*
                    {
                        if(vars.visuals.localchamstype == 0)
                            return metalNigga;
                        else if(vars.visuals.localchamstype == 1)
                            return firstLayer;
                        else if (vars.visuals.localchamstype == 2)
                            return firstWire;
                        else if(vars.visuals.localchamstype == 3)
                            return Plastic;
                        else if(vars.visuals.localchamstype == 4)
                            return Gold;
                        else if(vars.visuals.localchamstype == 5)
                            return crystal;
                        else if(vars.visuals.localchamstype == 6)
                            return Glass;
                        else if(vars.visuals.localchamstype == 7)
                            return Mp3;
                        else if(vars.visuals.localchamstype == 8)
                            return Random;
                        else if(vars.visuals.localchamstype == 9)
                            return Random1;
                        else if(vars.visuals.localchamstype == 10)
                            return Random2;
                        else if(vars.visuals.localchamstype == 11)
                            return Random3;
                        else if(vars.visuals.localchamstype == 12)
                            return firstLit;
                    }();
                    
                    
                    if (CreateMove::sendPacket == true)
                        local->SetupBones(localfakelagmatrix, 128, BONE_USED_BY_HITBOX, pGlobals->curtime);
                    
                    
                    if (vars.misc.flagchams && vars.misc.thirdperson && local->GetVelocity().Length2D() > 30 && !local->IsScoped())
                    {
                        materialFakelag->AlphaModulate(vars.visuals.fakelagchams_alpha / 255.0f - 0.1);
                        materialFakelag->ColorModulate(FakeLagColor);
                        pModelRender->ForcedMaterialOverride(materialFakelag);
                        CallOriginalModel(thisptr, context, state, pInfo, localfakelagmatrix);
                        pModelRender->ForcedMaterialOverride(nullptr);
                        
                    }
                    
                    if(vars.misc.thirdperson && local->IsScoped() && entity == local) {
                        materialCheckFirst->AlphaModulate(25 / 255.f);
                        materialCheckFirst->ColorModulate(ScopedColors);
                        pModelRender->ForcedMaterialOverride(materialCheckFirst);
                        CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
                        pModelRender->ForcedMaterialOverride(nullptr);
                        return;
                    }
                    if(vars.visuals.localchams && entity == local) {
                        materialLocal->AlphaModulate(vars.visuals.localchams_alpha / 255.f);
                        materialLocal->ColorModulate(ScopedColors);
                        pModelRender->ForcedMaterialOverride(materialLocal);
                        CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
                        pModelRender->ForcedMaterialOverride(nullptr);
                        return;
                    }
                    if(vars.misc.noscope && entity == local && vars.misc.thirdperson){
                        IMaterial *xblur_mat = pMatSystem->FindMaterial("dev/blurfilterx_nohdr", TEXTURE_GROUP_OTHER, true);
                        IMaterial *yblur_mat = pMatSystem->FindMaterial("dev/blurfiltery_nohdr", TEXTURE_GROUP_OTHER, true);
                        IMaterial *scope = pMatSystem->FindMaterial("dev/scope_bluroverlay", TEXTURE_GROUP_OTHER, true);
                        xblur_mat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
                        yblur_mat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
                        scope->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
                    }
                    if(vars.visuals.enemyonly && local->GetTeam() == entity->GetTeam())
                    {
                        CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
                        pModelRender->ForcedMaterialOverride(NULL);
                    }
                    else
                    {
                        if(!vars.visuals.visonly)
                        {
                            secondLayer->AlphaModulate(vars.visuals.playerchams_alpha / 255.f);
                            if(entity->GetTeam() == 2){
                                 secondLayer->ColorModulate(Color(vars.visuals.Tchamhid_red, vars.visuals.Tchamhid_green, vars.visuals.Tchamhid_blue, 255));
                            }
                            else if(entity->GetTeam() == 3){
                                secondLayer->ColorModulate(Color(vars.visuals.CTchamhid_red, vars.visuals.CTchamhid_green, vars.visuals.CTchamhid_blue, 255));
                            }
                            else if(pEngine->GetLocalPlayer() == 3){
                                secondLayer->ColorModulate(Color(vars.visuals.CTchamhid_red, vars.visuals.CTchamhid_green, vars.visuals.CTchamhid_blue, 255));
                            }
                            pModelRender->ForcedMaterialOverride(secondLayer);
                            CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
                        }
                        
                        if(entity->GetTeam() == 2){
                             materialCheckFirst->ColorModulate(Color(vars.visuals.Tcham_red, vars.visuals.Tcham_green, vars.visuals.Tcham_blue, 255));
                        }
                        else if(entity->GetTeam() == 3){
                            materialCheckFirst->ColorModulate(Color(vars.visuals.CTcham_red, vars.visuals.CTcham_green, vars.visuals.CTcham_blue, 255));
                        }
                        else if(pEngine->GetLocalPlayer() == 3){
                            materialCheckFirst->ColorModulate(Color(vars.visuals.CTcham_red, vars.visuals.CTcham_green, vars.visuals.CTcham_blue, 255));
                        }
                       
                        materialCheckFirst->AlphaModulate(vars.visuals.playerchams_alpha / 255.f);
                        pModelRender->ForcedMaterialOverride(materialCheckFirst);
                        CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
                    }
                }
            }
        }
    }
    
    CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
    pModelRender->ForcedMaterialOverride(NULL);
}
