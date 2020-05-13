#include "main.h"
// Hacks

bool FireEvent_hk(void* thisptr, IGameEvent* event, bool bDontBroadcast) {

    return game_event_vmt->GetOriginalMethod<oFireEvent>(9)(thisptr, event, bDontBroadcast);
}
