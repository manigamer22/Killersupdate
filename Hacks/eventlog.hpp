#pragma once

#include "../SDK/GameEvent.h"

namespace Eventlog
{
    //Hooks
    void FireGameEvent(IGameEvent* event);
    void Paint();
}
