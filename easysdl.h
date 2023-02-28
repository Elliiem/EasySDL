#ifndef EASYSDL_H
#define EASYSDL_H

#include <SDL2/SDL.h>
#include <map>
#include <unistd.h>
#include <string>
#include <vector>


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

};

struct ESDL_Point
{
    int x;
    int y;
    ESDL_Point(int X,int Y)
    {
        x = X;
        y = Y;
    }

    ESDL_Point()
    {

    }
};

struct ESDL_Polar_Point
{
    int deg;
    int r;
    ESDL_Polar_Point(int Deg,int R)
    {
        deg = Deg;
        r = R;
    }
};

struct ESDL_Tri
{
    ESDL_Point p0;
    ESDL_Point p1;
    ESDL_Point p2;

    ESDL_Tri(int x0,int y0,int x1,int y1,int x2,int y2)
    {
        p0 = ESDL_Point(x0,y0);
        p1 = ESDL_Point(x1,y1);
        p2 = ESDL_Point(x2,y2);
    }
};

struct ESDL_PTri
{
    ESDL_Point* p0;
    ESDL_Point* p1;
    ESDL_Point* p2;

    ESDL_PTri(ESDL_Point* P0,ESDL_Point* P1,ESDL_Point* P2)
    {
        p0 = P0;
        p1 = P1;
        p2 = P2;
    }
};

struct ESDL_Poly
{
    std::vector<ESDL_PTri> tris;
    std::vector<ESDL_Point> points;

    ESDL_Poly(std::vector<ESDL_Point> Points)
    {
        points = Points;
        tris = SplitPoly(Points);
    }

    std::vector<ESDL_PTri> SplitPoly(std::vector<ESDL_Point> points);
};

extern ESDL_Color red;
extern ESDL_Color green;
extern ESDL_Color blue;
extern ESDL_Color white;
extern ESDL_Color black;

class ESDL_Window
{
    public:
        SDL_Renderer* rend;
        SDL_Window* win;
        SDL_Event event;
        SDL_Surface* surf;

        std::map<int, bool> keyboard;
        std::map<int, bool> last_keyboard;

        bool quit = false;

        ESDL_Window(int width,int height,char* name,int SDL_renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC,SDL_BlendMode SDL_blend_flag = SDL_BLENDMODE_BLEND);

        int Update();

    private:
        int HandleSDLEvents();
        int GetKeys();
        int HandleKeys();
};

int ESDL_DrawLine(ESDL_Window win,int x0,int y0,int x1,int y1,ESDL_Color color);
int ESDL_DrawPoint(ESDL_Window win,int x,int y,ESDL_Color color);
int ESDL_DrawRect(ESDL_Window win,int x0,int y0,int x1,int y1,ESDL_Color color);
int ESDL_DrawTriF(ESDL_Window win,ESDL_Tri tri,ESDL_Color color);

#endif // EASYSDL_H
