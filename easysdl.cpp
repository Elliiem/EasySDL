#include "easysdl.h"
#include <SDL2/SDL.h>
#include <string.h>
#include <fmt/format.h>
#include <unistd.h>
#include <iostream>

ESDL_Color red(255,0,0,255);
ESDL_Color green(0,255,0,255);
ESDL_Color blue(0,0,255,255);
ESDL_Color white(255,255,255,255);
ESDL_Color black(0,0,0,255);

ESDL_Window::ESDL_Window(int width,int height,char* name,int SDL_renderer_flags,SDL_BlendMode SDL_blend_flag)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    win = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    rend = SDL_CreateRenderer(win, -1, SDL_renderer_flags);
    surf = SDL_GetWindowSurface(win);

    SDL_SetRenderDrawBlendMode(rend, SDL_blend_flag);
}


int ESDL_Window::GetKeys()
{
    if(event.type == SDL_KEYUP)
    {
        try
        {
            keyboard.at(event.key.keysym.sym) = false;
        }

        catch (const std::exception&)
        {
            keyboard.insert({event.key.keysym.sym,false});
        }
    }
    else
    {
        try
        {
            keyboard.at(event.key.keysym.sym) = true;
        }

        catch (const std::exception&)
        {
            keyboard.insert({event.key.keysym.sym,true});
        }
    }
    return 0;
}

int ESDL_Window::HandleSDLEvents()
{
    last_keyboard = keyboard;
    while (SDL_PollEvent(&event))
    {
        if(event.type == SDL_KEYDOWN | event.type == SDL_KEYUP)
        {
            GetKeys();
        }
        if(event.type == SDL_QUIT)
        {
            quit = true;
        }
    }
    return 0;
}

int ESDL_Window::HandleKeys()
{
    if (keyboard[SDLK_LCTRL] & keyboard[SDLK_z])
    {
        quit = true;
    }

    return 0;
}

int  ESDL_Window::Update()
{
    HandleSDLEvents();
    HandleKeys();

    SDL_RenderPresent(rend);
    SDL_SetRenderDrawColor(rend,0,0,0,255);
    SDL_RenderClear(rend);

    return 0;
}


int Sort_Tri(ESDL_Tri* tri)
{
    if(tri->p0.y <= tri->p1.y)
    {
        if(tri->p1.y > tri->p2.y)
        {
            ESDL_Point temp;
            temp = tri->p1;
            tri->p1 = tri->p2;
            tri->p2 = temp;
        }
    }
    else
    {
        ESDL_Point temp;
        temp = tri->p0;
        tri->p0 = tri->p1;
        tri->p1 = temp;
        if(tri->p1.y > tri->p2.y)
        {
            ESDL_Point temp;
            temp = tri->p1;
            tri->p1 = tri->p2;
            tri->p2 = temp;
        }
    }

    if(tri->p0.y <= tri->p1.y)
    {
        if(tri->p1.y > tri->p2.y)
        {
            Sort_Tri(tri);
        }
    }
    else
    {
        Sort_Tri(tri);
    }

    return 0;
}

int ESDL_DrawLine(ESDL_Window win,int x0,int y0,int x1,int y1,ESDL_Color color)
{
    SDL_SetRenderDrawColor(win.rend,color.r,color.g,color.b,color.a);
    SDL_RenderDrawLine(win.rend,x0,y0,x1,y1);
    return 0;
}

int ESDL_DrawPoint(ESDL_Window win,int x,int y,ESDL_Color color)
{
    SDL_SetRenderDrawColor(win.rend,color.r,color.g,color.b,color.a);
    SDL_RenderDrawPoint(win.rend,x,y);
    return 0;
}

int ESDL_DrawRect(ESDL_Window win,int x0,int y0,int x1,int y1,ESDL_Color color)
{
    SDL_SetRenderDrawColor(win.rend,color.r,color.g,color.b,color.a);
    SDL_Rect rect;
    rect.x = x0;
    rect.y = y0;
    rect.w = x1-x0;
    rect.h = y1-y0;
    SDL_RenderDrawRect(win.rend,&rect);
    return 0;
}

int ESDL_DrawTriF(ESDL_Window win,ESDL_Tri tri,ESDL_Color color)
{
    Sort_Tri(&tri);
    SDL_SetRenderDrawColor(win.rend,color.r,color.g,color.b,color.a);

    float delta_a,delta_b;
    float line_a = 0;
    float line_b = 0;
    int y = 0;

    delta_a = (float)(tri.p1.x-tri.p0.x)/(float)(tri.p1.y-tri.p0.y);
    delta_b = (float)(tri.p2.x-tri.p0.x)/(float)(tri.p2.y-tri.p0.y);

    while(y != tri.p1.y-tri.p0.y)
    {
        line_a += delta_a;
        line_b += delta_b;
        SDL_RenderDrawLine(win.rend,tri.p0.x+line_a,tri.p0.y+y,tri.p0.x+line_b,tri.p0.y+y);
        y++;
    }

    delta_a = (float)(tri.p2.x-tri.p1.x)/(float)(tri.p2.y-tri.p1.y);

    line_a = tri.p1.x - tri.p0.x;

    while (y != tri.p2.y-tri.p0.y)
    {
        line_a += delta_a;
        line_b += delta_b;
        SDL_RenderDrawLine(win.rend,tri.p0.x+line_a,tri.p0.y+y,tri.p0.x+line_b,tri.p0.y+y);
        y++;
    }

    return 0;
}

int ESDL_DrawPolyF(ESDL_Window win,ESDL_Poly poly,ESDL_Color color, int x, int y)
{
    for(int i = 0;i<poly.tris.size();i++)
    {
        ESDL_DrawTriF(win,ESDL_Tri(poly.points.at(poly.tris.at(i).p0)+ESDL_Point(x,y),poly.points.at(poly.tris.at(i).p1)+ESDL_Point(x,y),poly.points.at(poly.tris.at(i).p2)+ESDL_Point(x,y)),white);
    }
    return 0;
}

int ESDL_Poly::SplitPoly()
{
    std::vector<int> indexes;

    for(int i = 0;i<points.size();i++)
    {
        indexes.push_back(i);
    }
    Uint8 indexes_size = indexes.size();
    Uint8 index = 0;
    Sint8 index_a,index_b;

    while(indexes_size > 3)
    {
        index_a = index + 1;
        index_b = index - 1;

        if(index_a >= indexes.size())
            index_a = 0;
        if(index_b < 0)
            index_b = indexes.size()-1;

        if(IsSmallDeg(points.at(indexes.at(index)),points.at(indexes.at(index_a)),points.at(indexes.at(index_b)),center))
        {
            for(int i = 0;i<indexes_size;i++)
                if(InsideTriangle(points.at(indexes.at(index)),points.at(indexes.at(index_a)),points.at(indexes.at(index_b)),points.at(indexes.at(i))))
                {
                    break;
                }
                else if(i==indexes_size-1)
                {
                    tris.push_back(ESDL_PTri(indexes.at(index_b),indexes.at(index),indexes.at(index_a)));
                    indexes.erase(indexes.begin()+index);
                    index = -1;
                    indexes_size--;
                    break;
                }
        }
        index++;
    }

    tris.push_back(ESDL_PTri(indexes.at(2),indexes.at(0),indexes.at(1)));

    return 0;
}

bool ESDL_Poly::InsideTriangle(ESDL_Point A,ESDL_Point B,ESDL_Point C,ESDL_Point P)
{
  float ax, ay, bx, by, cx, cy, apx, apy, bpx, bpy, cpx, cpy;
  float cCROSSap, bCROSScp, aCROSSbp;

  ax = C.x - B.x;  ay = C.y - B.y;
  bx = A.x - C.x;  by = A.y - C.y;
  cx = B.x - A.x;  cy = B.y - A.y;
  apx= P.x - A.x;  apy= P.y - A.y;
  bpx= P.x - B.x;  bpy= P.y - B.y;
  cpx= P.x - C.x;  cpy= P.y - C.y;

  aCROSSbp = ax*bpy - ay*bpx;
  cCROSSap = cx*apy - cy*apx;
  bCROSScp = bx*cpy - by*cpx;

  return ((aCROSSbp > 0.0f) && (bCROSScp > 0.0f) && (cCROSSap > 0));
}

bool ESDL_Poly::IsSmallDeg(ESDL_Point P, ESDL_Point A, ESDL_Point B,ESDL_Point C)
{
    int ad,bd,pd;

    ESDL_Point av = C-A;
    ESDL_Point bv = C-B;
    ESDL_Point pv = C-P;

    ad = sqrt(pow(av.x,2)+pow(av.y,2));
    bd = sqrt(pow(bv.x,2)+pow(bv.y,2));
    pd = sqrt(pow(pv.x,2)+pow(pv.y,2));

    if(pd > ad | pd > bd)
    {
        return true;
    }

    return false;
}
