#pragma once
#define TIME_TO_TICKS(time)     ((int)(0.5f + ((float)time) / pGlobals->interval_per_tick ))


struct boxstruct { int x, y, w, h; };

extern void AngleVectors(const Vector & angles, Vector * forward);
extern void AngleVectors3(const QAngle &angles, Vector &forward);
extern void AngleVectors2(const Vector & angles, Vector * forward, Vector * right, Vector * up);
extern void AngleVectors4(const QAngle &angles, Vector& forward, Vector& right, Vector& up);
extern void AngleVectors6(const Vector &angles, Vector& forward, Vector& right, Vector& up);
extern void VectorAngles(const Vector& forward, Vector &angles);
extern void VectorAngles2(const Vector &forward, QAngle &angles);
extern void FixMovement(Vector& oang, CUserCmd* cmd);
extern void FixMove(CUserCmd* cmd, float yaw);
extern bool WorldToScreen(Vector& vFrom, Vector& vTo);
//extern bool WorldToScreen1( const Vector &origin, ImVec2 * const screen );
extern bool DrawPlayerBox(C_BaseEntity* pEntity, boxstruct& str);
extern void CorrectMovement(Vector vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove);
extern void correct_movement(CUserCmd* cmd, Vector& old_angles);
extern long GetEpochTime();
extern Vector GetHitboxPosition(C_BaseEntity* pEntity, int Hitbox);
extern bool IsVisible(C_BaseEntity* entity);
extern bool IsVisible1(C_BaseEntity* entity, int hitbox);
extern void Normalize(Vector & vIn, Vector & vOut);
extern void FixAngles(Vector& angles);
extern void MovementFix(CUserCmd* m_Cmd, Vector wish_angle, Vector old_angles);
extern void NormalizeVector(Vector & vecIn);
extern C_BaseCombatWeapon* GetActiveWeapon(C_BaseEntity* local);
extern void MoveFix(CUserCmd *cmd, Vector &realvec);
extern Vector CalcAngle(Vector src, Vector dst);
extern QAngle CalccAngle(const Vector &src, const Vector &dst);
extern float GetFOV(Vector start, Vector src, Vector dst);
extern void ClampMoves(float& flForward, float& flSide, float& flUp);
extern void ClampYaw(float& angle);
extern void ClampAngles(Vector& angle);
extern string GetWeaponName(C_BaseCombatWeapon* pWeapon);
extern string GetWeaponName1(C_BaseCombatWeapon* pWeapon);
extern bool IsScopeable(ItemDefinitionIndex index);
extern float distance_point_to_line(Vector Point, Vector LineOrigin, Vector Dir);
extern void SinCos(float a, float* s, float*c);
QAngle  calculate_angle(Vector src, Vector dst);
extern float radians_to_degrees(const float rad);
extern float degrees_to_radians(const float deg);
float   get_distance(Vector a, Vector b);
QAngle  calculate_angle(Vector src, Vector dst);
float   get_fov(const QAngle& viewAngle, const QAngle& aimAngle);
void normalize_angles(QAngle& angle);
void NormalizeAngles(Vector& angle);
void angle_vectors(const Vector& angles, Vector& forward);
void marquee(std::string& panicova_zlomena_noha);
void angle_vectors(const Vector& angles, Vector& forward, Vector& right, Vector& up);
void vector_angles(const Vector& forward, QAngle& angles);

bool is_point_visible(Vector point);
bool is_player_visible(C_BasePlayer* player);
bool is_hitbox_visible(C_BasePlayer* player, int hitbox);
