//fuzion nigger
#include "airstuck.hpp"
void Airstuck::CreateMove(CUserCmd* cmd)
{
    if (!vars.misc.airstuck)
        return;
    
    if (cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2)
        return;
    
    if (pInputSystem->IsButtonDown(KEY_Z))
        cmd->tick_count = 16777216;
}
