#include "main.h"
#include "noduckcooldown.hpp"

void DuckCool(CUserCmd* cmd)
{
    if (!vars.misc.noduckcooldown)
        return;
     cmd->buttons |= IN_BULLRUSH;
    
}
