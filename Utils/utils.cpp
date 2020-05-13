#include "main.h"

void AngleVectors(const Vector &angles, Vector *forward)
{
    Assert(s_bMathlibInitialized);
    Assert(forward);
    
    float	sp, sy, cp, cy;
    
    sy = sin(DEG2RAD(angles[1]));
    cy = cos(DEG2RAD(angles[1]));
    
    sp = sin(DEG2RAD(angles[0]));
    cp = cos(DEG2RAD(angles[0]));
    
    forward->x = cp*cy;
    forward->y = cp*sy;
    forward->z = -sp;
}
void AngleVector5(const Vector& angles, Vector& forward, Vector& right, Vector& up) {
    float sr, sp, sy, cr, cp, cy;

    SinCos(DEG2RAD(angles[0]), &sp, &cp);
    SinCos(DEG2RAD(angles[1]), &sy, &cy);
    SinCos(DEG2RAD(angles[2]), &sr, &cr);

    forward.x = (cp * cy);
    forward.y = (cp * sy);
    forward.z = (-sp);
    right.x = (-1 * sr * sp * cy + -1 * cr * -sy);
    right.y = (-1 * sr * sp * sy + -1 * cr * cy);
    right.z = (-1 * sr * cp);
    up.x = (cr * sp * cy + -sr * -sy);
    up.y = (cr * sp * sy + -sr * cy);
    up.z = (cr * cp);
}

void AngleVectors3(const QAngle &angles, Vector& forward)
{
    float sp, sy, cp, cy;
    
    SinCos(DEG2RAD(angles[YAW]), &sy, &cy);
    SinCos(DEG2RAD(angles[PITCH]), &sp, &cp);
    
    forward.x = cp * cy;
    forward.y = cp * sy;
    forward.z = -sp;
}

void AngleVectors4(const QAngle &angles, Vector& forward, Vector& right, Vector& up)
{
    float sr, sp, sy, cr, cp, cy;
    
    SinCos(DEG2RAD(angles[1]), &sy, &cy);
    SinCos(DEG2RAD(angles[0]), &sp, &cp);
    SinCos(DEG2RAD(angles[2]), &sr, &cr);
    
    forward.x = (cp * cy);
    forward.y = (cp * sy);
    forward.z = (-sp);
    right.x = (-1 * sr * sp * cy + -1 * cr * -sy);
    right.y = (-1 * sr * sp * sy + -1 * cr *  cy);
    right.z = (-1 * sr * cp);
    up.x = (cr * sp * cy + -sr * -sy);
    up.y = (cr * sp * sy + -sr * cy);
    up.z = (cr * cp);
}
void AngleVectors6(const QAngle &angles, Vector& forward, Vector& right, Vector& up)
{
    float sr, sp, sy, cr, cp, cy;
    
    SinCos(DEG2RAD(angles[1]), &sy, &cy);
    SinCos(DEG2RAD(angles[0]), &sp, &cp);
    SinCos(DEG2RAD(angles[2]), &sr, &cr);
    
    forward.x = (cp * cy);
    forward.y = (cp * sy);
    forward.z = (-sp);
    right.x = (-1 * sr * sp * cy + -1 * cr * -sy);
    right.y = (-1 * sr * sp * sy + -1 * cr *  cy);
    right.z = (-1 * sr * cp);
    up.x = (cr * sp * cy + -sr * -sy);
    up.y = (cr * sp * sy + -sr * cy);
    up.z = (cr * cp);
}
void AngleVectors2(const Vector & angles, Vector * forward, Vector * right, Vector * up)
{
    float angle;
    static float sr, sp, sy, cr, cp, cy;
    
    angle = angles[1] * (M_PI * 2 / 360);
    sy = sin(angle);
    cy = cos(angle);
    
    angle = angles[0] * (M_PI * 2 / 360);
    sp = sin(angle);
    cp = cos(angle);
    
    angle = angles[2] * (M_PI * 2 / 360);
    sr = sin(angle);
    cr = cos(angle);
    
    if (forward)
    {
        forward->x = cp*cy;
        forward->y = cp*sy;
        forward->z = -sp;
    }
    if (right)
    {
        right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
        right->y = (-1 * sr*sp*sy + -1 * cr*cy);
        right->z = -1 * sr*cp;
    }
    if (up)
    {
        up->x = (cr*sp*cy + -sr*-sy);
        up->y = (cr*sp*sy + -sr*cy);
        up->z = cr*cp;
    }
}

void NormalizeAngles(Vector& angle)
{
    while (angle.x > 89.0f)
        angle.x -= 180.f;
    
    while (angle.x < -89.0f)
        angle.x += 180.f;
    
    while (angle.y > 180.f)
        angle.y -= 360.f;
    
    while (angle.y < -180.f)
        angle.y += 360.f;
}
void SinCos(float a, float* s, float*c)
{
    *s = sin(a);
    *c = cos(a);
}
void marquee(std::string& panicova_zlomena_noha)
{
    std::string temp_string = panicova_zlomena_noha;
    panicova_zlomena_noha.erase(0, 1);
    panicova_zlomena_noha += temp_string[0];
}

void ClampAngles(Vector& angle)
{
    if (angle.y > 180.0f)
        angle.y = 180.0f;
    else if (angle.y < -180.0f)
        angle.y = -180.0f;
    
    if (angle.x > 89.0f)
        angle.x = 89.0f;
    else if (angle.x < -89.0f)
        angle.x = -89.0f;
    
    angle.z = 0;
}

float ClampYaw(float val)
{
    
    while(val > 180)
    {
        val -= 360;
    }
    
    while(val < -180)
    {
        val += 360;
    }
    
    return val;
}

void VectorAngles(const Vector& forward, Vector &angles)
{
    float	tmp, yaw, pitch;
    
    if (forward[1] == 0 && forward[0] == 0)
    {
        yaw = 0;
        if (forward[2] > 0)
            pitch = 270;
        else
            pitch = 90;
    }
    else
    {
        yaw = (atan2(forward[1], forward[0]) * 180 / M_PI);
        if (yaw < 0)
            yaw += 360;
        
        tmp = sqrt (forward[0]*forward[0] + forward[1]*forward[1]);
        pitch = (atan2(-forward[2], tmp) * 180 / M_PI);
        if (pitch < 0)
            pitch += 360;
    }
    
    angles[0] = pitch;
    angles[1] = yaw;
    angles[2] = 0;
}

void VectorAngles2(const Vector& forward, QAngle &angles)
{
    if (forward[1] == 0.0f && forward[0] == 0.0f)
    {
        angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f; // Pitch (up/down)
        angles[1] = 0.0f;  //yaw left/right
    }
    else
    {
        angles[0] = atan2(-forward[2], forward.Length2D()) * -180 / M_PI;
        angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI;
        
        if (angles[1] > 90)
            angles[1] -= 180;
        else if (angles[1] < 90)
            angles[1] += 180;
        else if (angles[1] == 90)
            angles[1] = 0;
    }
    
    angles[2] = 0.0f;
}


void CorrectMovement(Vector vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove)
{
    // side/forward move correction
    float deltaView;
    float f1;
    float f2;
    
    if (vOldAngles.y < 0.f)
        f1 = 360.0f + vOldAngles.y;
    else
        f1 = vOldAngles.y;
    
    if (pCmd->viewangles.y < 0.0f)
        f2 = 360.0f + pCmd->viewangles.y;
    else
        f2 = pCmd->viewangles.y;
    
    if (f2 < f1)
        deltaView = abs(f2 - f1);
    else
        deltaView = 360.0f - abs(f1 - f2);
    
    deltaView = 360.0f - deltaView;
    
    pCmd->forwardmove = cos(DEG2RAD(deltaView)) * fOldForward + cos(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
    pCmd->sidemove = sin(DEG2RAD(deltaView)) * fOldForward + sin(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
    
    
}

void correct_movement(CUserCmd* cmd, Vector& old_angles)
{
    CorrectMovement(old_angles, cmd, cmd->forwardmove, cmd->sidemove);
}
bool IsScopeable(ItemDefinitionIndex index)
{
    switch (index)
    {
        case ItemDefinitionIndex::WEAPON_AUG:
        case ItemDefinitionIndex::WEAPON_AWP:
        case ItemDefinitionIndex::WEAPON_G3SG1:
        case ItemDefinitionIndex::WEAPON_SCAR20:
        case ItemDefinitionIndex::WEAPON_SG556:
        case ItemDefinitionIndex::WEAPON_SSG08:
            return true;
        default:
            return false;
    }
}

#define rad_pi 57.295779513082f
#define pi 3.14159265358979323846f

float degrees_to_radians(const float deg)
{
    return deg * (pi / 180.f);
}

float radians_to_degrees(const float rad)
{
    return rad * rad_pi;
}

bool WorldToScreen(Vector& vFrom, Vector& vTo)
{
    return (pOverlay->ScreenPosition(vFrom, vTo) != 1);
}

//bool World

bool DrawPlayerBox(C_BaseEntity* pEntity, boxstruct& str) // Credit's to dude719 & keybode.
{
    if (!pEntity)
        return false;
    
    Vector vOrigin = pEntity->GetVecOrigin(); // Not sure if this is the right one...
    Vector min = pEntity->GetCollideable()->OBBMins() + vOrigin;
    Vector max = pEntity->GetCollideable()->OBBMaxs() + vOrigin;
    
    Vector points[] =
    {
        Vector(min.x, min.y, min.z),
        Vector(min.x, max.y, min.z),
        Vector(max.x, max.y, min.z),
        Vector(max.x, min.y, min.z),
        Vector(max.x, max.y, max.z),
        Vector(min.x, max.y, max.z),
        Vector(min.x, min.y, max.z),
        Vector(max.x, min.y, max.z)
    };
    
    Vector flb;
    Vector brt;
    Vector blb;
    Vector frt;
    Vector frb;
    Vector brb;
    Vector blt;
    Vector flt;
    
    
    if (!WorldToScreen(points[3], flb) ||
        !WorldToScreen(points[5], brt) ||
        !WorldToScreen(points[0], blb) ||
        !WorldToScreen(points[4], frt) ||
        !WorldToScreen(points[2], frb) ||
        !WorldToScreen(points[1], brb) ||
        !WorldToScreen(points[6], blt) ||
        !WorldToScreen(points[7], flt))
        return false;
    
    Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };
    
    float left      = flb.x;    // left
    float top       = flb.y;    // top
    float right     = flb.x;    // right
    float bottom    = flb.y;    // bottom
    
    for (int i = 1; i < 8; i++)
    {
        if (left > arr[i].x)
            left = arr[i].x;
        if (bottom < arr[i].y)
            bottom = arr[i].y;
        if (right < arr[i].x)
            right = arr[i].x;
        if (top > arr[i].y)
            top = arr[i].y;
    }
    
    str.x = left;
    str.y = top;
    str.w = right - left;
    str.h = bottom - top;
    return true;
}

void Normalize(Vector & vIn, Vector & vOut)
{
    float flLen = vIn.Length();
    if (flLen == 0)
    {
        vOut.Init(0, 0, 1);
        return;
    }
    flLen = 1 / flLen;
    vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
}

void NormalizeVector(Vector& vecIn) {
    for (int axis = 0; axis < 3; ++axis)
    {
        while (vecIn[axis] > 180.f)
            vecIn[axis] -= 360.f;
        
        while (vecIn[axis] < -180.f)
            vecIn[axis] += 360.f;
        
    }
    
    vecIn[2] = 0.f;
}

void FixMovement(Vector& oang, CUserCmd* pCmd)
{
    Vector vMove(pCmd->forwardmove, pCmd->sidemove, pCmd->upmove);
    float flSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y), flYaw;
    Vector vMove2;
    VectorAngles(vMove, vMove2);
    
    flYaw = DEG2RAD(pCmd->viewangles.y - oang.y + vMove2.y);
    pCmd->forwardmove = cos(flYaw) * flSpeed;
    pCmd->sidemove = sin(flYaw) * flSpeed;
    
    if (pCmd->viewangles.x < -90.f || pCmd->viewangles.x > 90.f)
        pCmd->forwardmove = -pCmd->forwardmove;
}

void MovementFix(CUserCmd* m_Cmd, Vector wish_angle, Vector old_angles) {
    auto pLocal = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (old_angles.x != wish_angle.x || old_angles.y != wish_angle.y || old_angles.z != wish_angle.z) {
        Vector wish_forward, wish_right, wish_up, cmd_forward, cmd_right, cmd_up;

        auto viewangles = old_angles;
        auto movedata = Vector(m_Cmd->forwardmove, m_Cmd->sidemove, m_Cmd->upmove);
        viewangles.Normalize();

        if (!(pLocal->GetFlags() & FL_ONGROUND) && viewangles.z != 0.f)
            movedata.y = 0.f;

        AngleVector5(wish_angle, wish_forward, wish_right, wish_up);
        AngleVector5(viewangles, cmd_forward, cmd_right, cmd_up);

        auto v8 = sqrt(wish_forward.x * wish_forward.x + wish_forward.y * wish_forward.y), v10 = sqrt(wish_right.x * wish_right.x + wish_right.y * wish_right.y), v12 = sqrt(wish_up.z * wish_up.z);

        Vector wish_forward_norm(1.0f / v8 * wish_forward.x, 1.0f / v8 * wish_forward.y, 0.f),
            wish_right_norm(1.0f / v10 * wish_right.x, 1.0f / v10 * wish_right.y, 0.f),
            wish_up_norm(0.f, 0.f, 1.0f / v12 * wish_up.z);

        auto v14 = sqrt(cmd_forward.x * cmd_forward.x + cmd_forward.y * cmd_forward.y), v16 = sqrt(cmd_right.x * cmd_right.x + cmd_right.y * cmd_right.y), v18 = sqrt(cmd_up.z * cmd_up.z);

        Vector cmd_forward_norm(1.0f / v14 * cmd_forward.x, 1.0f / v14 * cmd_forward.y, 1.0f / v14 * 0.0f),
            cmd_right_norm(1.0f / v16 * cmd_right.x, 1.0f / v16 * cmd_right.y, 1.0f / v16 * 0.0f),
            cmd_up_norm(0.f, 0.f, 1.0f / v18 * cmd_up.z);

        auto v22 = wish_forward_norm.x * movedata.x, v26 = wish_forward_norm.y * movedata.x, v28 = wish_forward_norm.z * movedata.x, v24 = wish_right_norm.x * movedata.y, v23 = wish_right_norm.y * movedata.y, v25 = wish_right_norm.z * movedata.y, v30 = wish_up_norm.x * movedata.z, v27 = wish_up_norm.z * movedata.z, v29 = wish_up_norm.y * movedata.z;

        Vector correct_movement;
        correct_movement.x = cmd_forward_norm.x * v24 + cmd_forward_norm.y * v23 + cmd_forward_norm.z * v25 + (cmd_forward_norm.x * v22 + cmd_forward_norm.y * v26 + cmd_forward_norm.z * v28) + (cmd_forward_norm.y * v30 + cmd_forward_norm.x * v29 + cmd_forward_norm.z * v27);
        correct_movement.y = cmd_right_norm.x * v24 + cmd_right_norm.y * v23 + cmd_right_norm.z * v25 + (cmd_right_norm.x * v22 + cmd_right_norm.y * v26 + cmd_right_norm.z * v28) + (cmd_right_norm.x * v29 + cmd_right_norm.y * v30 + cmd_right_norm.z * v27);
        correct_movement.z = cmd_up_norm.x * v23 + cmd_up_norm.y * v24 + cmd_up_norm.z * v25 + (cmd_up_norm.x * v26 + cmd_up_norm.y * v22 + cmd_up_norm.z * v28) + (cmd_up_norm.x * v30 + cmd_up_norm.y * v29 + cmd_up_norm.z * v27);

        correct_movement.x = std::clamp(correct_movement.x, -450.f, 450.f);
        correct_movement.y = std::clamp(correct_movement.y, -450.f, 450.f);
        correct_movement.z = std::clamp(correct_movement.z, -320.f, 320.f);

        m_Cmd->forwardmove = correct_movement.x;
        m_Cmd->sidemove = correct_movement.y;
        m_Cmd->upmove = correct_movement.z;

        m_Cmd->buttons &= ~(IN_MOVERIGHT | IN_MOVELEFT | IN_BACK | IN_FORWARD);
        if (m_Cmd->sidemove != 0.0) {
            if (m_Cmd->sidemove <= 0.0)
                m_Cmd->buttons |= IN_MOVELEFT;
            else
                m_Cmd->buttons |= IN_MOVERIGHT;
        }

        if (m_Cmd->forwardmove != 0.0) {
            if (m_Cmd->forwardmove <= 0.0)
                m_Cmd->buttons |= IN_BACK;
            else
                m_Cmd->buttons |= IN_FORWARD;
        }
    }
}
long GetEpochTime()
{
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

void VectorTransform(Vector& in1, matrix3x4_t& in2, Vector& out)
{
    out.x = DotProduct(in1, Vector(in2[0][0], in2[0][1], in2[0][2])) + in2[0][3];
    out.y = DotProduct(in1, Vector(in2[1][0], in2[1][1], in2[1][2])) + in2[1][3];
    out.z = DotProduct(in1, Vector(in2[2][0], in2[2][1], in2[2][2])) + in2[2][3];
}



Vector GetHitboxPosition(C_BaseEntity* pEntity, int Hitbox)
{
    matrix3x4_t matrix[128];
    
    if (!pEntity->SetupBones(matrix, 128, 0x100, pGlobals->curtime))
        return Vector(0, 0, 0);
    
    studiohdr_t* hdr = pModelInfo->GetStudioModel(pEntity->GetModel());
    mstudiohitboxset_t* set = hdr->pHitboxSet(0);
    
    mstudiobbox_t* hitbox = set->pHitbox(Hitbox);
    
    if (!hitbox)
        return Vector(0, 0, 0);
    
    Vector vMin, vMax, vCenter, sCenter;
    VectorTransform(hitbox->bbmin, matrix[hitbox->bone], vMin);
    VectorTransform(hitbox->bbmax, matrix[hitbox->bone], vMax);
    vCenter = (vMin + vMax) *0.5f;
    
    if(vars.aimbot.enabled && vars.aimbot.pointscale != 101)
    {
        float ptwoz = 50 - vars.aimbot.pointscale;
        float zval  = (ptwoz*vMin.z + vars.aimbot.pointscale*vMax.z) / 50;
        vCenter.z = zval;
    }
    
    return vCenter;
}

bool IsVisible(C_BaseEntity* entity)
{
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(!localplayer || !pEngineTrace || !entity)
        return false;
    
    Ray_t ray;
    ray.Init(localplayer->GetEyePosition(), entity->GetEyePosition());
    trace_t trace;
    CTraceFilter filter;
    filter.pSkip = localplayer;
    
    pEngineTrace->TraceRay(ray, 0x4600400b, &filter, &trace);

    return (trace.m_pEnt == entity || trace.fraction > 0.99f);
}

bool IsVisible1(C_BaseEntity* entity, int hitbox)
{
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(!localplayer || !pEngineTrace || !entity)
        return false;
    
    Ray_t ray;
    ray.Init(localplayer->GetEyePosition(), GetHitboxPosition(entity, hitbox));
    trace_t trace;
    CTraceFilter filter;
    filter.pSkip = localplayer;
    
    pEngineTrace->TraceRay(ray, 0x4600400b, &filter, &trace);

    return (trace.m_pEnt == entity || trace.fraction > 0.99f);
}

string GetWeaponName(C_BaseCombatWeapon* pWeapon) {
    if(!pWeapon) { return "nullptr"; }
    short ID = *pWeapon->GetItemDefinitionIndex();
    
    switch (ID) {
            /*pistols*/
        case 4:
            return "Glock";
        case 2:
            return "Dualies";
        case 36:
            return "P250";
        case 30:
            return "Tec 9";
        case 1:
            return "Deagle";
        case 32:
            return "P2000";
        case 3:
            return "Five Seven";
        case 64:
            return "Revolver";
        case 63:
            return "CZ75";
        case 61:
            return "USP";
            /*heavy*/
        case 35:
            return "Nova";
        case 25:
            return "XM1014";
        case 29:
            return "Sawed Off";
        case 14:
            return "M249";
        case 28:
            return "Negev";
        case 27:
            return "Mag 7";
            /*smgs*/
        case 17:
            return "Mac 10";
        case 33:
            return "MP7";
        case 24:
            return "UMP45";
        case 19:
            return "P90";
        case 26:
            return "Bizon";
        case 34:
            return "MP9";
            /*C4*/
        case 49:
            return "C4";
            /*rifles*/
        case 10:
            return "Famas";
        case 16:
            return "M4A1";
        case 40:
            return "Scout";
        case 8:
            return "AUG";
        case 9:
            return "AWP";
        case 38:
            return "Scar 20";
        case 13:
            return "Galil";
        case 7:
            return "AK47";
        case 39:
            return "SG553";
        case 11:
            return "G3SG1";
        case 60:
            return "M4A1-S";
            /*grenades*/
        case 46:
        case 48:
            return "Molotov";
        case 44:
            return "Grenade";
        case 43:
            return "Flash";
        case 45:
            return "Smoke";
        case 47:
            return "Decoy";
            /*other*/
        case 31:
            return "Zeus";
        default:
            return "Knife";
    }
}

string GetWeaponName1(C_BaseCombatWeapon* pWeapon) {
    if(!pWeapon) { return "nullptr"; }
    short ID = *pWeapon->GetItemDefinitionIndex();
    
    switch (ID) {
            /*pistols*/
        case 4:
            return "s";
        case 2:
            return "m";
        case 36:
            return "u";
        case 30:
            return "R";
        case 1:
            return "k";
        case 32:
            return "J";
        case 3:
            return "o";
        case 64:
            return "K";
        case 63:
            return "j";
        case 61:
            return "T";
            /*heavy*/
        case 35:
            return "H";
        case 25:
            return "U";
        case 29:
            return "L";
        case 14:
            return "A";
        case 28:
            return "G";
        case 27:
            return "C";
            /*smgs*/
        case 17:
            return "B";
        case 33:
            return "E";
        case 24:
            return "S";
        case 19:
            return "I";
        case 26:
            return "h";
        case 34:
            return "F";
            /*C4*/
        case 49:
            return "i";
            /*rifles*/
        case 10:
            return "n";
        case 16:
            return "z";
        case 40:
            return "P";
        case 8:
            return "e";
        case 9:
            return "f";
        case 38:
            return "M";
        case 13:
            return "r";
        case 7:
            return "d";
        case 39:
            return "N";
        case 11:
            return "q";
        case 60:
            return "y";
            /*grenades*/
        case 46:
        case 48:
            return "v";
        case 44:
            return "t";
        case 43:
            return "p";
        case 45:
            return "O";
        case 47:
            return "l";
            /*other*/
        case 31:
            return "Q";
        default:
            return "x";
    }
}

void MoveFix(CUserCmd *cmd, Vector &realvec)
{
    Vector vMove(cmd->forwardmove, cmd->sidemove, cmd->upmove);
    float flSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y), flYaw;
    Vector vMove2;
    VectorAngles(vMove, vMove2);
    
    flYaw = DEG2RAD(cmd->viewangles.y - realvec.y + vMove2.y);
    cmd->forwardmove = cos(flYaw) * flSpeed;
    cmd->sidemove = sin(flYaw) * flSpeed;
    
    if (cmd->viewangles.x < -90.f || cmd->viewangles.x > 90.f)
        cmd->forwardmove = -cmd->forwardmove;
}

Vector CalcAngle(Vector src, Vector dst)
{
    Vector delta, angles;
    delta.x = (src.x - dst.x);
    delta.y = (src.y - dst.y);
    delta.z = (src.z - dst.z);
    
    double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);
    
    angles.x = (float)(atanf(delta.z / hyp) * M_RADPI);
    angles.y = (float)(atanf(delta.y / delta.x) * M_RADPI);
    
    angles.z = 0.0f;
    if (delta.x >= 0.0)
    {
        angles.y += 180.0f;
    }
    return angles;
}

QAngle CalccAngle(const Vector &src, const Vector &dst)
{
    QAngle angles;
    Vector delta = src - dst;
    
    VectorAngles2(delta, angles);
    
    delta.Normalize();
    
    return angles;
}

C_BaseCombatWeapon* GetActiveWeapon(C_BaseEntity* local)
{
    auto hWeapon = local->GetActiveWeapon();
    if (!hWeapon)
        return nullptr;
    
    return (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(hWeapon);
}

float GetFOV(Vector start, Vector src, Vector dst)
{
    Vector ang, aim;
    ang = CalcAngle(src, dst);
    AngleVectors(start, &aim);
    AngleVectors(ang, &ang);
    
    float mag_s = std::sqrt((aim[0] * aim[0]) + (aim[1] * aim[1]) + (aim[2] * aim[2]));
    float mag_d = mag_s;
    float u_dot_v = aim[0] * ang[0] + aim[1] * ang[1] + aim[2] * ang[2];
    float fov = std::acos(u_dot_v / (mag_s * mag_d)) * (180.f / M_PI_F);
    return fov;
}

Vector ExtrapolateTick( Vector p0, Vector v0 )
{
    return p0 + ( v0 * pGlobals->interval_per_tick );
}

Vector C_BaseEntity::GetPredicted( Vector p0 )
{
    return ExtrapolateTick( p0, this->GetVelocity() );
}

void vector_angles(const Vector& forward, QAngle &angles)
{
    float tmp, yaw, pitch;
    
    if (forward[1] == 0 && forward[0] == 0)
    {
        yaw = 0;
        if (forward[2] > 0)
            pitch = 270;
        else
            pitch = 90;
    }
    else
    {
        yaw = (atan2(forward[1], forward[0]) * 180 / M_PI);
        if (yaw < 0)
            yaw += 360;
        
        tmp     = sqrt (forward[0] * forward[0] + forward[1] * forward[1]);
        pitch   = (atan2(-forward[2], tmp) * 180 / M_PI);
        
        if (pitch < 0)
            pitch += 360;
    }
    
    angles[0] = pitch;
    angles[1] = yaw;
    angles[2] = 0;
}
static void _vector_angles(const Vector& forward, QAngle& angles)
{
    if (forward[1] == 0.0f && forward[0] == 0.0f)
    {
        angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f;   // pitch
        angles[1] = 0.0f;                                   // yaw
    }
    else
    {
        angles[0] = atan2(-forward[2], forward.Length2D()) * -180 / M_PI;
        angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI;
        
        if (angles[1] > 90)
            angles[1] -= 180;
        else if (angles[1] < 90)
            angles[1] += 180;
        else if (angles[1] == 90)
            angles[1] = 0;
    }
    
    angles[2] = 0.0f;
}

void normalize_angles(QAngle& angle)
{
    while (angle.x > 89.0f)
        angle.x -= 180.f;
    
    while (angle.x < -89.0f)
        angle.x += 180.f;
    
    while (angle.y > 180.f)
        angle.y -= 360.f;
    
    while (angle.y < -180.f)
        angle.y += 360.f;
}
template<class T>
void Normalize3(T& vec) {
    for (auto i = 0; i < 2; i++) {
        while (vec[i] < -180.0f) vec[i] += 360.0f;
        while (vec[i] > 180.0f) vec[i] -= 360.0f;
    }
    vec[2] = 0.f;
}

void ClampAngles1(Vector& angles) {
    if (angles.x > 89.0f) angles.y = 89.0f;
    else if (angles.x < -89.0f) angles.y = -89.0f;

    if (angles.y > 180.0f) angles.y = 180.0f;
    else if (angles.y < -180.0f) angles.y = -180.0f;

    angles.z = 0;
}
void FixAngles(Vector& angles){
    Normalize3(angles);
    ClampAngles1(angles);
}

QAngle calculate_angle(Vector src, Vector dst)
{
    QAngle angles;
    Vector delta = src - dst;
    
    _vector_angles(delta, angles);
    delta.Normalize();
    
    return angles;
}

float get_fov(const QAngle& viewAngle, const QAngle& aimAngle)
{
    QAngle delta = aimAngle - viewAngle;
    normalize_angles(delta);
    return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}


void ClampMoves(float& flForward, float& flSide, float& flUp)
{
    if(flForward > 450) flForward = 450;
    if(flSide > 450) flSide = 450;
    if(flUp > 450) flUp = 450;
    if(flForward < -450) flForward = -450;
    if(flSide < -450) flSide = -450;
    if(flUp < -450) flUp = -450;
}



void ClampYaw(float& angle)
{
    while(angle > 180)
    {
        angle -= 360;
    }
    while(angle < -180)
    {
        angle += 360;
    }
}


/*float distance_point_to_line(Vector Point, Vector LineOrigin, Vector Dir)
{
    auto PointDir = Point - LineOrigin;
    
    auto TempOffset = PointDir.Dot(Dir) / (Dir.x*Dir.x + Dir.y*Dir.y + Dir.z*Dir.z);
    if (TempOffset < 0.000001f)
        return FLT_MAX;
    
    auto PerpendicularPoint = LineOrigin + (Dir * TempOffset);
    
    return (Point - PerpendicularPoint).Length();
}*/


