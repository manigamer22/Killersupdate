#include "skinconfigchanger.hpp"

int KnifeCT = WEAPON_KNIFE_SKELETON;
int KnifeT = WEAPON_KNIFE_SKELETON;
int GloveCT = GLOVE_MOTORCYCLE;
int GloveT = GLOVE_MOTORCYCLE;

unordered_map<int, cSkin> cSkinchanger::Skins = unordered_map<int, cSkin>( {
    //knife
    make_pair(WEAPON_KNIFE, cSkin(59, -1, KnifeCT, -1, 3, nullptr, 0.00000000001f)),
    make_pair(WEAPON_KNIFE_T, cSkin(59, -1, KnifeCT, -1, 3, nullptr, 0.00000000001f)),
    //glove
    make_pair(GLOVE_CT, cSkin(10026, -1, GloveCT, -1, 3, nullptr, 0.00000000001f)),
    make_pair(GLOVE_T, cSkin(10026, -1, GloveT, -1, 3, nullptr, 0.00000000001f)),
    //guns
    make_pair(WEAPON_AWP, cSkin(756, -1, -1, -1, 0, nullptr, 0.00000000001f)),
    make_pair(WEAPON_SSG08, cSkin(899, -1, -1, -1, 0, nullptr, 0.00000000001f)),
    make_pair(WEAPON_MAC10, cSkin(898, -1, -1, -1, 0, nullptr, 0.00000000001f)),
    make_pair(WEAPON_SG556, cSkin(897, -1, -1, -1, 0, nullptr, 0.00000000001f)),
    make_pair(WEAPON_MP7, cSkin(893, -1, -1, -1, 0, nullptr, 0.00000000001f)),


});

unordered_map<int, const char*> cSkinchanger::ModelList;

std::unique_ptr<RecvPropHook> SkinChanger::sequenceHook;

cSkinchanger* skinchanger = new cSkinchanger;

void cSkinchanger::FrameStageNotify(ClientFrameStage_t stage) {
    if(stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START){
        pLocalPlayer = (C_BaseEntity*)(pEntList->GetClientEntity(pEngine->GetLocalPlayer()));
        
        if(pLocalPlayer && pLocalPlayer->GetHealth() > 0){
            if(!bInit){
                Init();
                bInit = true;
            }
            ForceSkins();
        }
    }
}

void cSkinchanger::FindModels() {
    ModelList[pModelInfo->GetModelIndex("models/weapons/v_knife_default_ct.mdl")] = KnifeToModelMatrix[KnifeCT].c_str();
    ModelList[pModelInfo->GetModelIndex("models/weapons/v_knife_default_t.mdl")] = KnifeToModelMatrix[KnifeT].c_str();
    ModelList[pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_hardknuckle/v_glove_hardknuckle.mdl")] = GloveToModelMatrix[GloveCT].c_str();
    ModelList[pModelInfo->GetModelIndex("models/weapons/v_models/arms/glove_fingerless/v_glove_fingerless.mdl")] = GloveToModelMatrix[GloveT].c_str();
}

void cSkinchanger::ForceSkins() {
    player_info_t player_info;
    
    if(pEngine->GetPlayerInfo(pLocalPlayer->GetId(), &player_info)){
        
        int* pWeapons = pLocalPlayer->GetWeapons();
        
        C_BaseViewModel* LocalPlayerViewModel = (C_BaseViewModel*)pEntList->GetClientEntityFromHandle(pLocalPlayer->GetViewModel());
        
        C_BaseAttributableItem* WeaponViewModel = nullptr;
        
        if(LocalPlayerViewModel)
            WeaponViewModel = (C_BaseAttributableItem*)pEntList->GetClientEntityFromHandle(LocalPlayerViewModel->GetWeapon());
        
        C_BaseCombatWeapon* localWeapon = (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(pLocalPlayer->GetActiveWeapon());
        
        if(pWeapons){
            for(int i = 0; pWeapons[i]; i++){
                C_BaseAttributableItem* attributableItem = (C_BaseAttributableItem*)pEntList->GetClientEntityFromHandle(pWeapons[i]);
                if(attributableItem) {
                    short* Definition = attributableItem->GetItemDefinitionIndex();
                    
                    unordered_map<int, cSkin>::iterator SkinIter = (*Definition == WEAPON_KNIFE ? (*Definition == WEAPON_KNIFE ? Skins.find(WEAPON_KNIFE) : Skins.find(WEAPON_KNIFE_T)) : Skins.find(*Definition));
                    
                    if(SkinIter != Skins.end()) {
                        if(*attributableItem->GetOriginalOwnerXuidLow() == player_info.xuidlow && *attributableItem->GetOriginalOwnerXuidHigh() == player_info.xuidhigh){
                            
                            int* model_index = attributableItem->GetModelIndex();
                            
                            unordered_map<int, const char*>::iterator model_iter = ModelList.find(*model_index);
                            
                            if(model_iter != ModelList.end()){
                                *model_index = pModelInfo->GetModelIndex(model_iter->second);
                            }
                            
                            cSkin skin = move(SkinIter->second);
                            
                            if(KnifeCT && (*Definition == WEAPON_KNIFE))
                                *attributableItem->GetItemDefinitionIndex() = KnifeCT;
                            else if(KnifeT && (*Definition == WEAPON_KNIFE_T))
                                *attributableItem->GetItemDefinitionIndex() = KnifeT;
                            
                            if(skin.name) {
                                sprintf(attributableItem->GetCustomName(), "%s", skin.name);
                            }
                            
                            *attributableItem->GetItemIDHigh() = -1;
                            *attributableItem->GetFallbackPaintKit() = skin.Paintkit;
                            *attributableItem->GetFallbackStatTrak() = skin.StatTrack;
                            *attributableItem->GetEntityQuality() = skin.EntityQuality;
                            *attributableItem->GetFallbackSeed() = skin.Seed;
                            *attributableItem->GetFallbackWear() = skin.Wear;
                            *attributableItem->GetAccountID() = player_info.xuidlow;
                            
                            ApplyCustomGloves();
                            Init();
                        }
                    }
                    
                    if (WeaponViewModel && WeaponViewModel == attributableItem) {
                        int* model_index = ((C_BaseEntity*)LocalPlayerViewModel)->GetModelIndex();
                        
                        unordered_map<int, const char*>::iterator model_iter = ModelList.find(*model_index);
                        
                        if (model_iter != ModelList.end()) {
                            *model_index = pModelInfo->GetModelIndex(model_iter->second);
                        }
                    }
                }
            }
            
            if(LocalPlayerViewModel && localWeapon) {
                
                int* model_index = ((C_BaseEntity*)LocalPlayerViewModel)->GetModelIndex();
                
                unordered_map<int, const char*>::iterator model_iter = ModelList.find(*((C_BaseEntity*)localWeapon)->GetModelIndex());
                
                if(model_iter != ModelList.end()){
                    *model_index = pModelInfo->GetModelIndex(model_iter->second);
                }
            }
        }
    }
}

void cSkinchanger::ApplyCustomGloves() {
    
    C_BaseEntity* pLocal = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if (!pEntList->GetClientEntityFromHandle((void*)pLocal->GetWearables())) {
        for (ClientClass* pClass = pClient->GetAllClasses(); pClass; pClass = pClass->m_pNext) {
            if (pClass->m_ClassID != (int)EClassIds::CEconWearable)
                continue;
            
            int entry = (pEntList->GetHighestEntityIndex() + 1);
            int serial = RandomInt(0x0, 0xFFF);
            
            pClass->m_pCreateFn(entry, serial);
            pLocal->GetWearables()[0] = entry | serial << 16;
            
            glovesUpdated = true;
            
            break;
        }
    }
    
    player_info_t LocalPlayerInfo;
    pEngine->GetPlayerInfo(pEngine->GetLocalPlayer(), &LocalPlayerInfo);
    
    C_BaseAttributableItem* glove = (C_BaseAttributableItem*)pEntList->GetClientEntity(pLocal->GetWearables()[0] & 0xFFF);
    
    if (!glove)
        return;
    
    int* glove_index = glove->GetModelIndex();
    unordered_map<int, const char*>::iterator glove_iter = ModelList.find(*glove_index);
    unordered_map<int, cSkin>::iterator Iter = (pLocal->GetTeam() == TEAM_COUNTER_TERRORIST ? Skins.find(GLOVE_CT) : Skins.find(GLOVE_T));
    cSkin gloveskin = move(Iter->second);
    
    if(glove_iter != ModelList.end())
        *glove_index = pModelInfo->GetModelIndex(glove_iter->second);
    
    if(GloveCT && pLocal->GetTeam() == TEAM_COUNTER_TERRORIST)
        *glove->GetItemDefinitionIndex() = GloveCT;
    if(GloveT && pLocal->GetTeam() == TEAM_TERRORIST)
        *glove->GetItemDefinitionIndex() = GloveT;
    
    *glove->GetItemIDHigh() = -1;
    *glove->GetFallbackPaintKit() = gloveskin.Paintkit;
    *glove->GetFallbackWear() = gloveskin.Wear;
    *glove->GetAccountID() = LocalPlayerInfo.xuidlow;
    
    if(glovesUpdated) {
        glove->GetNetworkable()->PreDataUpdate(DATA_UPDATE_CREATED);
        glovesUpdated = false;
    }
}

void cSkinchanger::Init() {
    ModelList.clear();
    FindModels();
}

void cSkinchanger::FireEventClientSide(IGameEvent *event) {
    if (!vars.visuals.skinc)
           return;
    
    if (!pEngine->IsInGame())
           return;
       
    if (!event || strcmp(event->GetName(), "player_death") != 0)
           return;
       
    if (!event->GetInt("attacker") || pEngine->GetPlayerForUserID(event->GetInt("attacker")) != pEngine->GetLocalPlayer())
           return;
    
    if(!strcmp(event->GetName(), "game_newmap")) {
        Init();
    }
    
    //f(const auto icon_override = (event->GetString("weapon"))) event->SetString("weapon", icon_override);
}

inline const int RandomSequence1(int low, int high) {
    return (rand() % (high - low + 1) + low);
}

void HSequenceProxyFn(const CRecvProxyData *pDataConst, void *pStruct, void *pOut) {
    CRecvProxyData* pData = const_cast<CRecvProxyData*>(pDataConst);
    C_BaseViewModel* pViewModel = (C_BaseViewModel*)pStruct;
    
    if(!pViewModel)
        return g_pSequence(pDataConst, pStruct, pOut);
    
    C_BaseEntity* pOwner = (C_BaseEntity*)pEntList->GetClientEntityFromHandle(pViewModel->GetOwner());
    
    if (pViewModel && pOwner) {
        if (pOwner->GetIndex() == pEngine->GetLocalPlayer()) {
            
            const model_t* knife_model = pModelInfo->GetModel(*pViewModel->GetModelIndex());
            const char* model_filename = pModelInfo->GetModelName(knife_model);
            
            int m_nSequence = (int)pData->m_Value.m_Int;
            
            if (!strcmp(model_filename, "models/weapons/v_knife_butterfly.mdl")) {
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_DRAW:
                        m_nSequence = RandomSequence1(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
                        break;
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence = RandomSequence1(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03);
                        break;
                    default:
                        m_nSequence++;
                }
            } else if (!strcmp(model_filename, "models/weapons/v_knife_falchion_advanced.mdl")) {
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_IDLE2:
                        m_nSequence = SEQUENCE_FALCHION_IDLE1;
                        break;
                    case SEQUENCE_DEFAULT_HEAVY_MISS1:
                        m_nSequence = RandomSequence1(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP);
                        break;
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence = RandomSequence1(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02);
                        break;
                    case SEQUENCE_DEFAULT_DRAW:
                    case SEQUENCE_DEFAULT_IDLE1:
                        break;
                    default:
                        m_nSequence--;
                }
            } else if (!strcmp(model_filename, "models/weapons/v_knife_push.mdl")) {
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_IDLE2:
                        m_nSequence = SEQUENCE_DAGGERS_IDLE1;
                        break;
                    case SEQUENCE_DEFAULT_LIGHT_MISS1:
                    case SEQUENCE_DEFAULT_LIGHT_MISS2:
                        m_nSequence = RandomSequence1(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5);
                        break;
                    case SEQUENCE_DEFAULT_HEAVY_MISS1:
                        m_nSequence = RandomSequence1(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1);
                        break;
                    case SEQUENCE_DEFAULT_HEAVY_HIT1:
                    case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence += 3;
                        break;
                    case SEQUENCE_DEFAULT_DRAW:
                    case SEQUENCE_DEFAULT_IDLE1:
                        break;
                    default:
                        m_nSequence += 2;
                }
            } else if (!strcmp(model_filename, "models/weapons/v_knife_survival_bowie.mdl")) {
                
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_DRAW:
                    case SEQUENCE_DEFAULT_IDLE1:
                        break;
                    case SEQUENCE_DEFAULT_IDLE2:
                        m_nSequence = SEQUENCE_BOWIE_IDLE1;
                        break;
                    default:
                        m_nSequence--;
                }
            } else if (!strcmp(model_filename, "models/weapons/v_knife_ursus.mdl")) {
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_DRAW:
                        m_nSequence = RandomSequence1(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
                        break;
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence = RandomSequence1(SEQUENCE_BUTTERFLY_LOOKAT01, 14);
                        break;
                    default:
                        m_nSequence++;
                }
            } else if (!strcmp(model_filename, "models/weapons/v_knife_cord.mdl")) {
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_DRAW:
                        m_nSequence = RandomSequence1(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
                        break;
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence = RandomSequence1(SEQUENCE_BUTTERFLY_LOOKAT01, 14);
                        break;
                    default:
                        m_nSequence++;
                }
            } else if (!strcmp(model_filename, "models/weapons/v_knife_canis.mdl")) {
                    switch (m_nSequence) {
                        case SEQUENCE_DEFAULT_DRAW:
                            m_nSequence = RandomSequence1(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
                            break;
                        case SEQUENCE_DEFAULT_LOOKAT01:
                            m_nSequence = RandomSequence1(SEQUENCE_BUTTERFLY_LOOKAT01, 14);
                            break;
                        default:
                            m_nSequence++;
                    }
            } else if (!strcmp(model_filename, "models/weapons/v_knife_outdoor.mdl")) {
                        switch (m_nSequence) {
                            case SEQUENCE_DEFAULT_DRAW:
                                m_nSequence = RandomSequence1(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
                                break;
                            case SEQUENCE_DEFAULT_LOOKAT01:
                                m_nSequence = RandomSequence1(SEQUENCE_BUTTERFLY_LOOKAT01, 14);
                                break;
                            default:
                                m_nSequence++;
                        }
            } else if (!strcmp(model_filename, "models/weapons/v_knife_skeleton.mdl")) {
                            switch (m_nSequence) {
                                case SEQUENCE_DEFAULT_DRAW:
                                    m_nSequence = RandomSequence1(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
                                    break;
                                case SEQUENCE_DEFAULT_LOOKAT01:
                                    m_nSequence = RandomSequence1(SEQUENCE_BUTTERFLY_LOOKAT01, 14);
                                    break;
                                default:
                                    m_nSequence++;
                            }
            }else if (!strcmp(model_filename, "models/weapons/v_knife_stiletto.mdl")) {
                switch (m_nSequence){
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence = RandomSequence1(12, 13);
                        break;
                }
            } else if(!strcmp(model_filename, "models/weapons/v_knife_widowmaker.mdl")) {
                switch (m_nSequence) {
                    case SEQUENCE_DEFAULT_LOOKAT01:
                        m_nSequence = RandomSequence1(SEQUENCE_TALON_LOOKAT1, SEQUENCE_TALON_LOOKAT2);
                        break;
                }
            }
            pData->m_Value.m_Int = m_nSequence;
        }
    }
    return g_pSequence(pData, pStruct, pOut);
}
