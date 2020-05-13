#pragma once

class OverlayText_t {
public:
    OverlayText_t() {
        nextOverlayText = 0;
        origin.Init();
        bUseOrigin = false;
        lineOffset = 0;
        flXPos = 0;
        flYPos = 0;
        text[ 0 ] = 0;
        m_flEndTime = 0.0f;
        m_nServerCount = -1;
        m_nCreationTick = -1;
        r = g = b = a = 255;
    }
    
    bool            IsDead();
    void            SetEndTime( float duration );
    
    Vector          origin;
    bool            bUseOrigin;
    int             lineOffset;
    float           flXPos;
    float           flYPos;
    char            text[512];
    float           m_flEndTime;        // When does this text go away
    int             m_nCreationTick;    // If > 0, show only one server frame
    int             m_nServerCount;     // compare server spawn count to remove stale overlays
    int             r;
    int             g;
    int             b;
    int             a;
    OverlayText_t*  nextOverlayText;
};

class IVDebugOverlay {
public:
    virtual void AddEntityTextOverlay(int ent_index, int line_offset, float duration, int r, int g, int b, int a, const char *format, ...) = 0;
    virtual void AddBoxOverlay(const Vector& origin, const Vector& mins, const Vector& max, QAngle const& orientation, int r, int g, int b, int a, float duration) = 0;
    virtual void AddSphereOverlay(const Vector& p1, const Vector& p2, const Vector& p3, int r, int g, int b, int a, bool noDepthTest, float duration) = 0;
    virtual void AddTriangleOverlay(const Vector& origin, const Vector& origin2, const Vector& origin3, int r, int g, int b, int a, bool noDepthTest, float duration) = 0;
    //   virtual void AddLineOverlay(const Vector& origin, const Vector& dest, int r, int g, int b,bool noDepthTest, float duration) = 0;
    virtual void AddTextOverlay(const Vector& origin, float duration, const char *format, ...) = 0;
    virtual void AddTextOverlay(const Vector& origin, int line_offset, float duration, const char *format, ...) = 0;
    virtual void AddScreenTextOverlay(float flXPos, float flYPos, float flDuration, int r, int g, int b, int a, const char *text) = 0;
    virtual void AddSweptBoxOverlay(const Vector& start, const Vector& end, const Vector& mins, const Vector& max, const QAngle & angles, int r, int g, int b, int a, float flDuration) = 0;
    virtual void AddGridOverlay(const Vector& origin) = 0;
    virtual void AddCoordFrameOverlay(const matrix3x4_t& vmatrix, float unk, int* unk2[3]) = 0;
    //   virtual int ScreenPosition(const Vector& point, Vector& screen) = 0;
    virtual int ScreenPosition(float flXPos, float flYPos, Vector& screen) = 0;
    
    virtual OverlayText_t* GetFirst(void) = 0;
    virtual OverlayText_t* GetNext(OverlayText_t* current) = 0;
    virtual void ClearDeadOverlays(void) = 0;
    virtual void ClearAllOverlays(void) = 0;
    virtual void __UnkFunc(void) = 0;
    virtual void AddTextOverlayRGB(const Vector& origin, int line_offset, float duration, float r, float g, float b, float alpha, const char *format, ...) = 0;
    virtual void AddLineOverlayAlpha(const Vector& origin, int line_offset, float duration, int r, int g, int b, int a, const char *format, ...) = 0;
    virtual void AddBoxOverlay2(const Vector& origin, const Vector& mins, const Vector& max, QAngle const& orientation, const Color& faceColor, const Color& edgeColor, float duration) = 0;
    virtual void AddLineOverlay(const Vector& origin, int line_offset, float duration, int r, int g, int b, int a, const char *format, ...) = 0;
    virtual void PurgeTextOverlays(void) = 0;
    bool ScreenPosition(const Vector& vIn, Vector& vOut) {
        typedef bool (* oScreenPosition)(void*, const Vector&, Vector&);
        return getvfunc<oScreenPosition>(this, 11)(this, vIn, vOut);
    }
    
    void AddLineOverlay( const Vector& origin, const Vector& dest, int r, int g, int b, bool noDepthTest, float duration ) {
        typedef void(*oAddLineOverlay)(void*, const Vector&, const Vector&, int, int, int, bool, float);
        return getvfunc<oAddLineOverlay>(this, 4)(this, origin, dest, r, g, b, noDepthTest, duration);
    }
    
    void DrawPill(const Vector& mins, const Vector& max, float& diameter, int r, int g, int b, int a, float duration)
    {
        typedef void(* OriginalFn)(void*, const Vector&, const Vector&, float&, int, int, int, int, float);
        return getvfunc<OriginalFn>(this, 23)(this, mins, max, diameter, r, g, b, a, duration);
    }
    
    void DrawPill2(const Vector& mins, const Vector& max, float& diameter, Color color, float duration)
    {
        typedef void(* OriginalFn)(void*, const Vector&, const Vector&, float&, Color, float);
        return getvfunc<OriginalFn>(this, 23)(this, mins, max, diameter, color, duration);
    }
    void DrawPillReal(const Vector& mins, const Vector& max, float& diameter, int r, int g, int b, int a, float duration)
    {
        typedef void(*OriginalFn)(void*, const Vector&, const Vector&, float&, int, int, int, int, float);
        return getvfunc<OriginalFn>(this, 23)(this, mins, max, diameter, r, g, b, a, duration);
    }
    void AddCapsuleOverlay(Vector& mins, Vector& maxs, float pillradius, int r, int g, int b, int a, float duration)
    {
        typedef void(* OriginalFn)(void*, Vector&, Vector&, float&, int, int, int, int, float);
        return getvfunc<OriginalFn>(this, 24)(this, mins, maxs, pillradius, r, g, b, a, duration); //this shit should be 23 but its crashing me so fuckt this imma sleep now!
    }
};

class IVRenderView
{
public:
    void SetBlend(float alpha)
    {
        typedef void(* oDrawModelExecute)(void*, float);
        return getvfunc< oDrawModelExecute >(this, 4)(this, alpha);
    }
    
    void SetColorModulation(float const* colors)
    {
        typedef void(* oDrawModelExecute)(void*, float const*);
        return getvfunc< oDrawModelExecute >(this, 6)(this, colors);
    }
    inline void                 SetColorModulation(float r, float g, float b)
    {
        float clr[3] = { r, g, b };
        SetColorModulation(clr);
    }
};
