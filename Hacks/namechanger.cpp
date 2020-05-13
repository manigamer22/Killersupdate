//
//  namestealer.cpp
//  vHook
//
//  Created by Timothy Dillan on 28/8/19.
//  Copyright © 2019 ViKiNG. All rights reserved.
//

#include "namechanger.hpp"

void ChangeName(const char* szName) {
    ConVar* cvar_name = pCvar->FindVar("name");
    *(int*)((uintptr_t)&cvar_name->fnChangeCallback + 0x15) = 0;
    cvar_name->SetValue(szName);
}
