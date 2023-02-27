#ifndef EASYSDL_H
#define EASYSDL_H

#include <SDL2/SDL.h>
#include <map>
#include <unistd.h>
#include <string>


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

struct ESDL_KPoint
{
    int x;
    int y;
    ESDL_KPoint(int X,int Y)
    {
        x = X;
        y = Y;
    }

    ESDL_KPoint()
    {

    }
};

struct ESDL_PPoint
{
    int deg;
    int r;
    ESDL_PPoint(int Deg,int R)
    {
        deg = Deg;
        r = R;
    }
};

struct ESDL_Tri
{
    ESDL_KPoint p0;
    ESDL_KPoint p1;
    ESDL_KPoint p2;

    ESDL_Tri(int x0,int y0,int x1,int y1,int x2,int y2)
    {
        p0 = ESDL_KPoint(x0,y0);
        p1 = ESDL_KPoint(x1,y1);
        p2 = ESDL_KPoint(x2,y2);
    }
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
