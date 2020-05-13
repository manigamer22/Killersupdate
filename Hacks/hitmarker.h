#pragma once

#include "../main.h"
#include "../SDK/GameEvent.h"

namespace Hitmarkers
{
    //Hooks
    void FireGameEvent(IGameEvent* event);
    void Paint();
}

namespace BulletTracers
{
    //Hooks
    void FireGameEvent(IGameEvent* event);
    void Paint();
}

class cbullet_tracer_info
{
public:
    cbullet_tracer_info(Vector src, Vector dst, float time, Color color)
    {
        this->src = src;
        this->dst = dst;
        this->time = time;
        this->color = color;
    }
    
    Vector src, dst;
    float time;
    Color color;
};

