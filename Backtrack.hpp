//
//  backtrack.hpp
//  vHook
//
//  Created by xxxSkies on 2018-06-20.
//  Copyright © 2018 ViKiNG. All rights reserved.
//

#pragma once
#include "main.h"


struct lbyRecords
{
    int tick_count;
    float lby;
    Vector headPosition;
};
struct backtrackData
{
    float simtime;
    Vector hitboxPos;
    Vector origin;
    QAngle angs;
};

class BackTrack
{
    int latest_tick;
    bool IsTickValid(int tick);
    void UpdateRecord(int i);
public:
    lbyRecords records[64];
    bool RunLBYBackTrack(int i, CUserCmd* cmd, Vector& aimPoint);
    void Update(int tick_count);
    void legitBackTrack(CUserCmd* cmd, C_BaseEntity* pLocal);
};

extern backtrackData headPositions[64][12];

extern BackTrack* backtracking;
