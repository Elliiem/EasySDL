#ifndef EASYSDL_H
#define EASYSDL_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <iostream>

// Visit the wiki at https://github.com/Elliiem/EasySDL/wiki (WIP)

//COLOR (Color)
struct ESDL_Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
    ESDL_Color(unsigned char R,unsigned char G,unsigned char B,unsigned char A)
    {
        r = R;
        g = G;
        b = B;
        a = A;
    }
    ESDL_Color()
    {

    }

};

extern ESDL_Color red;
extern ESDL_Color green;
extern ESDL_Color blue;
extern ESDL_Color white;
extern ESDL_Color black;
extern ESDL_Color gray;

//DATA STRUCTS
struct ESDL_Point
{
    float x;
    float y;
    ESDL_Point(float X,float Y)
    {
        x = X;
        y = Y;
    }

    ESDL_Point()
    {

    }

    ESDL_Point operator+(ESDL_Point other)
    {
        return ESDL_Point(x+other.x,y+other.y);
    }

    ESDL_Point operator-(ESDL_Point other)
    {
        return ESDL_Point(x-other.x,y-other.y);
    }
};

struct ESDL_Polar_Point
{
    int deg;
    int r;
    ESDL_Polar_Point(int R,int Deg)
    {
        deg = Deg;
        r = R;
    }

    ESDL_Polar_Point()
    {

    }
};

struct ESDL_Vector
{
    float x;
    float y;

    ESDL_Vector(float X,float Y)
    {
        x = X;
        y = Y;
    }

    ESDL_Vector operator+(ESDL_Vector other)
    {
        return ESDL_Vector(x+other.x,y+other.y);
    }

};

struct ESDL_Tri
{
    ESDL_Point p0;
    ESDL_Point p1;
    ESDL_Point p2;
    ESDL_Color color;

    ESDL_Tri(int x0,int y0,int x1,int y1,int x2,int y2)
    {
        p0 = ESDL_Point(x0,y0);
        p1 = ESDL_Point(x1,y1);
        p2 = ESDL_Point(x2,y2);
    }
    ESDL_Tri(ESDL_Point P0,ESDL_Point P1,ESDL_Point P2)
    {
        p0 = P0;
        p1 = P1;
        p2 = P2;
    }
    ESDL_Tri(ESDL_Point P0,ESDL_Point P1,ESDL_Point P2,ESDL_Color Color)
    {
        p0 = P0;
        p1 = P1;
        p2 = P2;
        color = Color;
    }
    ESDL_Tri(int x0,int y0,int x1,int y1,int x2,int y2,ESDL_Color Color)
    {
        p0 = ESDL_Point(x0,y0);
        p1 = ESDL_Point(x1,y1);
        p2 = ESDL_Point(x2,y2);
        color = Color;
    }
};

struct ESDL_Index_Tri
{
    Uint8 p0;
    Uint8 p1;
    Uint8 p2;
    ESDL_Color color;

    ESDL_Index_Tri(Uint8 P0,Uint8 P1,Uint8 P2)
    {
        p0 = P0;
        p1 = P1;
        p2 = P2;
        // FOR WIREFRAME MODE
        color.r = rand() % 255;
        color.g = rand() % 255;
        color.b = rand() % 255;
        color.a =  255;
    }
    ESDL_Index_Tri(Uint8 P0,Uint8 P1,Uint8 P2,ESDL_Color Color)
    {
        p0 = P0;
        p1 = P1;
        p2 = P2;
        color = Color;
    }
};

//POLY (Poly)
// Only Polygons without holes (or try to idc its your time)
struct ESDL_Poly
{
    public:
    // Constructor
    ESDL_Poly(std::vector<ESDL_Point> Points)
    {
        points = Points;
        for(int i = 0;i<points.size();i++)
        {
            points.at(i).y = -points.at(i).y;
        }
        SplitPoly();
        FillPolar();
    }

    // The Triangles of this poly these are ESDL_Index_Tri's they store the index of the each point in points
    //(for optimisation so you can rotate the poly without recalculating)
    std::vector<ESDL_Index_Tri> tris;

    // The Points of the poly (can be changed call Reset after!)
    std::vector<ESDL_Point> points;

    // The polar coordinates of points
    std::vector<ESDL_Polar_Point> polar;

    // The dirction the poly is facing
    float rot = 0;

    // Resets use these to reset the values
    int ResetTris();
    int ResetPolar();
    int Reset();

    // Use this to rotate the Polygon
    int Rotate(float deg);

    // Gets the normal Vector of this Polygon
    //(useful to move in a direction affected by rot)
    ESDL_Vector GetForward();

    private:
    int SplitPoly();
    int FillPolar();
    bool InsideTriangle(ESDL_Point A,ESDL_Point B,ESDL_Point C,ESDL_Point P);
    bool IsSmallDeg(ESDL_Point P, ESDL_Point A, ESDL_Point B);
};

//WINDOW (Window)
class ESDL_Window
{
    public:
        // Constructor
        ESDL_Window(int width,int height,std::string name,int SDL_renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC,SDL_BlendMode SDL_blend_flag = SDL_BLENDMODE_BLEND);

        // SDL Window Stuff
        SDL_Renderer* rend;
        SDL_Window* win;
        SDL_Event event;
        SDL_Surface* surf;

        // Inputs
        // keyboard inputs are in the SDLK format so keyboard[SDLK_w] for example
        std::map<int, bool> keyboard;
        std::map<int, bool> last_keyboard;
        ESDL_Point mouse_pos;

        // Time when Update is called
        std::chrono::time_point<std::chrono::system_clock> time = std::chrono::high_resolution_clock::now();
        // Delta Times (milliseconds(delta) and microsecond(delta_m))
        float delta;
        float delta_m;

        // Window height/width ...
        int window_height;
        int window_width;
        // ... and half
        int half_window_height;
        int half_window_width;

        // whether the window should quit (put your main function in a while loop and check for this)
        bool quit = false;
        // Internal, if true will show all debug information in ESDL. Can be activated with the b key
        bool debug = false;

        // Updates the Window
        int Update();

    private:
        float GetDeltaTime();
        int HandleSDLEvents();
        int GetKeys();
        int HandleKeys();
};

//DRAWING (Draw)
// Draw Line between point 0 and 1 with the in color
int ESDL_DrawLine(ESDL_Window* win,int x0,int y0,int x1,int y1,ESDL_Color color);

// Draw a Point at x, y with the in color
int ESDL_DrawPoint(ESDL_Window* win,int x,int y,ESDL_Color color);

// Draw a Filled Rectangle between the corner points 0 and 1 in the given color
int ESDL_DrawRectF(ESDL_Window* win,int x0,int y0,int x1,int y1,ESDL_Color color);

// Draw a Rectangle between the corner point 0 and 1 in the given color
int ESDL_DrawRect(ESDL_Window* win,int x0,int y0,int x1,int y1,ESDL_Color color);

// Draw a Filled Triangle with a ESDL_Tri at x, y in the given color
int ESDL_DrawTriF(ESDL_Window* win,ESDL_Tri tri,int x,int y,ESDL_Color color);

// Draw a Filled Triangle with a ESDL_Tri at an ESDL_Point in the given color
int ESDL_DrawTriF(ESDL_Window* win,ESDL_Tri tri,ESDL_Point pos,ESDL_Color color);

// Draw a Triangle with a ESDL_Tri at x, y in the given color
int ESDL_DrawTri(ESDL_Window* win, ESDL_Tri tri, int x, int y, ESDL_Color color);

// Draw a Filled with a ESDL_Tri at an ESDL_Point in the given color
int ESDL_DrawTri(ESDL_Window* win,ESDL_Tri tri,ESDL_Point pos,ESDL_Color color);

// Draw a Filled Polygon with a ESDL_Poly at x, y in the given color
int ESDL_DrawPolyF(ESDL_Window* win, ESDL_Poly *poly, int x, int y, ESDL_Color color);

// Draw a Filled Polygon with a ESDL_Poly at an ESDL_Point in the given color
int ESDL_DrawPolyF(ESDL_Window* win,ESDL_Poly* poly,ESDL_Point pos,ESDL_Color color);

// Draw a Polygon with a ESDL_Poly at x, y in the given color
int ESDL_DrawPoly(ESDL_Window* win,ESDL_Poly* poly,int x, int y,ESDL_Color color);

// Draw a Polygon with a ESDL_Poly at an ESDL_Point in the given color
int ESDL_DrawPoly(ESDL_Window* win,ESDL_Poly* poly,ESDL_Point pos,ESDL_Color color);


// CAMERA
// Useful for a moving Camera
// Currently you need to convert the position of everything you draw to the relative position to the camera
// Use the ToCamCords Function for this
class ESDL_Camera
{
    public:
        float x;
        float y;
        ESDL_Window *win;
        ESDL_Camera(int X,int Y, ESDL_Window* Win)
        {
            x = X;
            y = Y;
            win = Win;
        }

        ESDL_Point ToCamCords(int X, int Y)
        {
            return ESDL_Point(X-x+win->half_window_width,Y-y+win->half_window_height);
        }
};



#endif // EASYSDL_H
