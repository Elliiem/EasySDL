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

std::vector<ESDL_PTri> ESDL_Poly::SplitPoly(std::vector<ESDL_Point> points)
{

}
