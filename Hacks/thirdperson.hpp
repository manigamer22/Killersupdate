#pragma once


#include "../Interfaces/hooks.h"
#include "../main.h"

    //Hooks
namespace ThirdPerson
{
    
    void OverrideView(CViewSetup* pSetup);
    void FrameStageNotify(ClientFrameStage_t stage);
}
