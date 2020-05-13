struct Vertex_t
{
    Vector2D    m_Position;
    Vector2D    m_TexCoord;
    
    Vertex_t() {}
    Vertex_t(const Vector2D &pos, const Vector2D &coord = Vector2D(0, 0))
    {
        m_Position = pos;
        m_TexCoord = coord;
    }
    void Init(const Vector2D &pos, const Vector2D &coord = Vector2D(0, 0))
    {
        m_Position = pos;
        m_TexCoord = coord;
    }
};

typedef  Vertex_t FontVertex_t;

class ISurface {
public:
    void DrawSetTextFont(HFONT font) {
        typedef void (* oDrawSetTextFont)(void*, HFONT);
        return getvfunc<oDrawSetTextFont>(this, 23)(this, font);
    }
    
    void DrawSetTextColor(int r, int g, int b, int a) {
        typedef void (* oDrawSetTextColor)(void*, int, int, int, int);
        return getvfunc<oDrawSetTextColor>(this, 24)(this, r, g, b, a);
    }
    
    void DrawSetTextColor(Color color) {
        typedef void (* oDrawSetTextColor)(void*, int, int, int, int);
        return getvfunc<oDrawSetTextColor>(this, 24)(this, color.r(), color.g(), color.b(), color.a());
    }
    
    void DrawSetTextPos(int x, int y) {
        typedef void (* oDrawSetTextPos)(void*, int, int);
        return getvfunc<oDrawSetTextPos>(this, 26)(this, x, y);
    }
    
    void DrawPrintText(const wchar_t *text, int textLen) {
        typedef void (* oDrawPrintText)(void*, const wchar_t *, int, int);
        return getvfunc<oDrawPrintText>(this, 28)(this, text, textLen, 0);
    }
    void DrawSetColor(int r, int g, int b) {
        typedef void (* oDrawSetColor)(void*, int, int, int, int);
        return getvfunc<oDrawSetColor>(this, 14)(this, r, g, b, 255);
    }
    
    void DrawSetColor(int r, int g, int b, int a) {
        typedef void (* oDrawSetColor)(void*, int, int, int, int);
        return getvfunc<oDrawSetColor>(this, 14)(this, r, g, b, a);
    }
    
    void DrawSetColor(Color color) {
        typedef void(* oDrawSetColor)(void*, int, int, int, int);
        return getvfunc<oDrawSetColor>(this, 14)(this, color.r(), color.g(), color.b(), color.a());
    }
    
    void DrawFilledRect(int x0, int y0, int x1, int y1) {
        typedef void (* oDrawFilledRect)(void*, int, int, int, int);
        return getvfunc<oDrawFilledRect>(this, 16)(this, x0, y0, x1, y1);
    }
    
    void DrawOutlinedRect(int x0, int y0, int x1, int y1) {
        typedef void (* oDrawOutlinedRect)(void*, int, int, int, int);
        return getvfunc<oDrawOutlinedRect>(this, 18)(this, x0, y0, x1, y1);
    }
    
    void DrawOutlinedCircle(int x0, int y0, int x1, int y1)
    {
        typedef void(* oDrawOutlinedCircle)(void*, int, int, int, int);
        return getvfunc<oDrawOutlinedCircle>(this, 103)(this, x0, y0, x1, y1);
    }
    
    inline void DrawTexturedRect(int x, int y, int w, int h) {
        typedef void(* origFn)(void *, int, int, int, int);
        return getvfunc<origFn>(this, 41)(this, x, y, w, h);
    }
    
    void DrawSetTexture(int textureID)
    {
        typedef void(* oDrawSetTextColor)(void*, int);
        return getvfunc<oDrawSetTextColor>(this, 38)(this, textureID);
    }
    
    void DrawSetTextureRGBA(int textureID, unsigned char  const* colors, int w, int h)
    {
        typedef void(* oDrawSetTextColor)(void*, int, unsigned char  const*, int, int);
        return getvfunc< oDrawSetTextColor >(this, 37)(this, textureID, colors, w, h);
    }
    
    void DrawColoredCircle(int centerx, int centery, float radius, int r, int g, int b, int a)
    {
        typedef void(* origFn)(void*, int, int, float, int, int, int, int);
        return getvfunc<origFn>(this, 162)(this, centerx, centery, radius, r, g, b, a);
    }
    
    void PolygonOutline(int count, std::vector< Vector2D >points, Color colorLine)
    {
        static int x[128];
        static int y[128];
        std::vector< Vertex_t >vertices{ Vertex_t(points.at(0)), Vertex_t(points.at(1)), Vertex_t(points.at(2)) };
        
        for (int i = 0; i < count; i++)
        {
            x[i] = vertices[i].m_Position.x;
            y[i] = vertices[i].m_Position.y;
        }
        
        PolyLine(x, y, count, colorLine);
    }
    void PolyLine(int* x, int* y, int count, Color color)
    {
        DrawSetColor(color);
        DrawPolyLine(x, y, count);
    }
    void draw_filled_triangle(std::vector< Vector2D>points, Color colour) {
        std::vector< Vertex_t >vertices{ Vertex_t(points.at(0)), Vertex_t(points.at(1)), Vertex_t(points.at(2)) };
        add_textured_polygon(3, vertices.data(), colour.r(), colour.g(), colour.b(), colour.a());
    }
    
    void DrawTexturedPolygon(int vtxCount, FontVertex_t *vtx, bool bClipVertices = true)
    {
        typedef void(* oDrawSetTextColor)(void*, int, FontVertex_t*, bool);
        return getvfunc< oDrawSetTextColor >(this, 106)(this, vtxCount, vtx, bClipVertices);
    }
    void set_drawing_color(int r, int g, int b, int a = 255) {
        using original_fn = void(*)(ISurface*, int, int, int, int);
        return (*(original_fn**)this)[15](this, r, g, b, a);
    }
    void add_textured_polygon(int n, Vertex_t* vertice, int r, int g, int b, int a) {
        static int texture_id = CreateNewTextureID(true);
        set_drawing_color(r, g, b, a);
        DrawSetTexture(texture_id);
        DrawTexturedPolygon(n, vertice);
    }
    
    void DrawFilledCircle(int centerx, int centery, float radius, int r, int g, int b, int a)
    {
        for (int i = 0; i < radius; i++)
        {
            DrawColoredCircle(centerx, centery, i, r, g, b, a);
        }
    }
    
    int CreateNewTextureID(bool procedural)
    {
        typedef int(* oDrawSetTextColor)(void*, bool);
        return getvfunc< oDrawSetTextColor >(this, 43)(this, procedural);
    }
    
    void DrawLine(int x0, int y0, int x1, int y1) {
        typedef void (* oDrawLine)(void*, int, int, int, int);
        return getvfunc<oDrawLine>(this, 19)(this, x0, y0, x1, y1);
    }
    
    void DrawPolyLine(int* x, int* y, int count)
    {
        typedef void(* OriginalFn)(void*, int*, int*, int);
        return getvfunc< OriginalFn >(this, 19 + 1)(this, x, y, count);
    }
    
    void UnlockCursor() {
        typedef void(* oUnlockCursor)(void*);
        return getvfunc<oUnlockCursor>(this, 66)(this);
    }
    
    void LockCursor() {
        typedef void(* oLockCursor)(void*);
        return getvfunc<oLockCursor>(this, 67)(this);
    }
    
    HFONT CreateFont() {
        typedef HFONT (* oCreateFont)(void*);
        return getvfunc<oCreateFont>(this, 71)(this);
    }
    
    void SetFontGlyphSet(HFONT &font, const char *FontName, int tall, int weight, int blur, int scanlines, int flags) {
        typedef void (* oSetFontGlyphSet)(void*, HFONT, const char*, int, int, int, int, int, int, int);
        return getvfunc<oSetFontGlyphSet>(this, 72)(this, font, FontName, tall, weight, blur, scanlines, flags, 0, 0);
    }
    
    void GetTextSize(HFONT font, const wchar_t *text, int &wide, int &tall) {
        typedef void (* oGetTextSize)(void*, HFONT font, const wchar_t *text, int &wide, int &tall);
        return getvfunc<oGetTextSize>(this, 79)(this, font, text, wide, tall);
    }
    void PlaySound(const char* fileName) {
        typedef void(* oPlaySound)(void*, const char*);
        return getvfunc<oPlaySound>(this, 82)(this, fileName);
    }

};

