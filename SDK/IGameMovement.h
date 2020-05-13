class CMoveData
{
public:
    bool            m_bFirstRunOfFunctions : 1;
    bool            m_bGameCodeMovedPlayer : 1;
    
    int                m_nPlayerHandle;    // edict index on server, client entity handle on client
    
    int                m_nImpulseCommand;    // Impulse command issued.
    Vector            m_vecViewAngles;    // Command view angles (local space)
    Vector            m_vecAbsViewAngles;    // Command view angles (world space)
    int                m_nButtons;            // Attack buttons.
    int                m_nOldButtons;        // From host_client->oldbuttons;
    float            m_flForwardMove;
    float            m_flSideMove;
    float            m_flUpMove;
    
    float            m_flMaxSpeed;
    float            m_flClientMaxSpeed;
    
    // Variables from the player edict (sv_player) or entvars on the client.
    // These are copied in here before calling and copied out after calling.
    Vector            m_vecVelocity;        // edict::velocity        // Current movement direction.
    Vector            m_vecAngles;        // edict::angles
    Vector            m_vecOldAngles;
    
    // Output only
    float            m_outStepHeight;    // how much you climbed this move
    Vector            m_outWishVel;        // This is where you tried
    Vector            m_outJumpVel;        // This is your jump velocity
    
    // Movement constraints    (radius 0 means no constraint)
    Vector            m_vecConstraintCenter;
    float            m_flConstraintRadius;
    float            m_flConstraintWidth;
    float            m_flConstraintSpeedFactor;
    
    float            m_flUnknown[5];
    
    Vector            m_vecAbsOrigin;        // edict::origin
};

class IGameMovement
{
public:
    virtual            ~IGameMovement(void) {}

    virtual void    ProcessMovement(C_BaseEntity *pPlayer, CMoveData *pMove) = 0;
    virtual void    Reset(void) = 0;
    virtual void    StartTrackPredictionErrors(C_BaseEntity *pPlayer) = 0;
    virtual void    FinishTrackPredictionErrors(C_BaseEntity *pPlayer) = 0;
    virtual void    DiffPrint(char const *fmt, ...) = 0;

    virtual Vector const&    GetPlayerMins(bool ducked) const = 0;
    virtual Vector const&    GetPlayerMaxs(bool ducked) const = 0;
    virtual Vector const&   GetPlayerViewOffset(bool ducked) const = 0;

    virtual bool            IsMovingPlayerStuck(void) const = 0;
    virtual C_BaseEntity*    GetMovingPlayer(void) const = 0;
    virtual void            UnblockPusher(C_BaseEntity* pPlayer, C_BaseEntity *pPusher) = 0;

    virtual void    SetupMovementBounds(CMoveData *pMove) = 0;
};

class IMoveHelper
{
public:
    void SetHost(C_BaseEntity* host)
    {
        typedef void (* oSetHost)(void*, C_BaseEntity*);
        return getvfunc<oSetHost>(this, 1)(this, host);
    }
};
