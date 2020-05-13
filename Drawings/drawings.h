#pragma once

#define PI 3.14159265358979323846f

extern HFONT supremacy, subtitleFont, slider, pFont, framefont, mFont, lbyfont, eFont, sFont, specfont, xFont, cFont, xFontGay, iFont, mSection, iFont2, iFont3, weapfont, test, LBY, framefont, espfont, mFont, osFont, sFont, tFont, cFont, titleFont, subtitleFont, heading, o4Font_20, o4Font_11, o4Font_03, csgo_icons, copyright, indicatorFont, bombfont, hhfont, hhhfont;
// if you want to add more

typedef int ViVec_t;

class ViVecMouse {
public:
    
    ViVec_t x, y;
    ViVecMouse(void);
    ViVecMouse(ViVec_t X, ViVec_t Y);
    
};

class cDrawings {
public:
    
    wstring wstringtostring(string str);
    wstring StringToWstring(string str);
    HFONT createfonttt(HFONT font, const char* szFont, int tall, int flags);
    HFONT createfont(HFONT font, const char* szFont, int tall, int flags);
    HFONT createfontt(HFONT font, const char* szFont, int tall, int flags);
    void textW(bool center, int font, int x, int y, Color c, wchar_t *pszString);
    void drawbox(int x, int y, int w, int h, Color color);
    void drawboxoutline(int x, int y, int w, int h, Color color);
    void Circle3D(Vector position, float points, float radius, Color color);
    void BoxEspShit(int X, int Y, int W, int H, Color Color);
    void Cube3D(float scalar, QAngle angles, Vector middle_origin, Color outline);
    void rotate_triangle(std::array<Vector2D, 3>& points, float rotation);
    void add_textured_polygon(int n, Vertex_t* vertice, Color color);
    void add_triangle_filled(std::array<Vector2D, 3>points, Color color);
    void DrawCornerBox(int X, int Y, int W, int H, int inr, int ing, int inb, int outr, int otug, int outb);
    void fillrgba(int x, int y, int w, int h, Color color);
    void FilledRectangle(Vector2D start_pos, Vector2D end_pos, Color col);
    void FilledRectangle(int x0, int y0, int x1, int y1, Color col);
    void drawline(int x, int y, int xx, int yy, Color color);
    void Line(int x0, int y0, int x1, int y1, Color col);
    void Line(Vector2D start_pos, Vector2D end_pos, Color col);
    void drawstring(int x, int y, Color color, HFONT font, const char* szString, bool bCenter = false);
    void drawString(int font, bool bCenter, int x, int y, Color c, const char *fmt, ...);
    void drawstring(Vector2D pos, const char* szString, HFONT font, Color color);
    void KeyBindButton(ButtonCode_t* key);
    void drawgradient(int x, int y, int w, int h, Color col1, Color col2);
    void Text(int x, int y, const char* text, HFONT font, Color col);
    void Text(Vector2D pos, const char* text, HFONT font, Color col);
    void GradientH(int x, int y, int width, int height, Color color1, Color color2, Color color3);
    void BorderBox(int x, int y, int w, int h, int thickness, Color color);
    void RectOutlined(int x, int y, int w, int h, int thickness, Color color, Color outlined);
    //void Line(Vector2D start_pos, Vector2D end_pos, Color col);
    void DrawCircle(float x, float y, float r, float s, Color color);
    void DrawTexturedPoly(int n, Vertex_t* vertice, Color col);
    void DrawFilledCircle(Vector2D center, Color color, float radius, float points);
    void Clear(int x, int y, int w, int h, Color color);
    void DrawTriangle(Vector pos, float size, Color color);
    void Triangle(std::vector<Vector2D> points);
    void Circle(float x, float y, float r, float s, Color color);
    
    
    void textbox(int x, int y, int w, const char* szString, string szValue[100], int inputIndex, int index, bool* var);
    void handleinput(int eventcode, string arr[100]);
    
    bool inArea(int x, int y, int w, int h);
    Vector2D GetTextSize(const char* text, HFONT font);
    
    int CalcPos(int x);
    bool MoveMenu(int & x, int & y, int w, int h, int index);
    
    ViVecMouse GetMouse();
    void drawmouse();
    
    void drawCrosshair(int x, int y, Color col);
    
    /* Creds to reactiioN @ uc */
    size_t m_nCurrentPos[100];
    string m_szCurrentString[100];
    string m_szChangedValue[100];
    
    bool IsKeyPressed(int eventCode, ButtonCode_t keyCode) {
        return (eventCode == keyCode) ? true : false;
    }
    
};

void setupConfig();

extern cDrawings* draw;
