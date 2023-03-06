#include "ESDL.h"


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


int ESDL_DrawLine(ESDL_Window* win,int x0,int y0,int x1,int y1,ESDL_Color color)
{
    SDL_SetRenderDrawColor(win->rend,color.r,color.g,color.b,color.a);
    SDL_RenderDrawLine(win->rend,x0,y0,x1,y1);
    return 0;
}

int ESDL_DrawPoint(ESDL_Window* win,int x,int y,ESDL_Color color)
{
    SDL_SetRenderDrawColor(win->rend,color.r,color.g,color.b,color.a);
    SDL_RenderDrawPoint(win->rend,x,y);
    return 0;
}

int ESDL_DrawRectF(ESDL_Window* win,int x0,int y0,int x1,int y1,ESDL_Color color)
{
    int height = y1-y0;
    for(int i = 0;i<=height;i++)
    {
        SDL_RenderDrawLine(win->rend,x0,y0+i,x1,y0+i);
    }
    return 0;
}

int ESDL_DrawRect(ESDL_Window* win,int x0,int y0,int x1,int y1,ESDL_Color color)
{
    SDL_SetRenderDrawColor(win->rend,color.r,color.g,color.b,color.a);
    SDL_Rect rect;
    rect.x = x0;
    rect.y = y0;
    rect.w = x1-x0;
    rect.h = y1-y0;
    SDL_RenderDrawRect(win->rend,&rect);
    return 0;
}

int ESDL_DrawTriF(ESDL_Window* win,ESDL_Tri tri,int x,int y,ESDL_Color color)
{
    Sort_Tri(&tri);
    SDL_SetRenderDrawColor(win->rend,color.r,color.g,color.b,color.a);

    float delta_a,delta_b;
    float line_a = 0;
    float line_b = 0;
    int Y = 0;

    delta_a = (float)(tri.p1.x-tri.p0.x)/(float)(tri.p1.y-tri.p0.y);
    delta_b = (float)(tri.p2.x-tri.p0.x)/(float)(tri.p2.y-tri.p0.y);

    while(Y != tri.p1.y-tri.p0.y)
    {
        line_a += delta_a;
        line_b += delta_b;

        SDL_RenderDrawLineF(win->rend,x+tri.p0.x+line_a,y+tri.p0.y+Y,x+tri.p0.x+line_b,y+tri.p0.y+Y);

        Y++;
    }

    delta_a = (float)(tri.p2.x-tri.p1.x)/(float)(tri.p2.y-tri.p1.y);

    line_a = tri.p1.x - tri.p0.x;

    while (Y != tri.p2.y-tri.p0.y)
    {
        line_a += delta_a;
        line_b += delta_b;
        SDL_RenderDrawLineF(win->rend,x+tri.p0.x+line_a,y+tri.p0.y+Y,x+tri.p0.x+line_b,y+tri.p0.y+Y);
        Y++;
    }

    return 0;
}

int ESDL_DrawTri(ESDL_Window* win,ESDL_Tri tri,int x,int y,ESDL_Color color)
{
    SDL_SetRenderDrawColor(win->rend,color.r,color.g,color.b,color.a);
    SDL_RenderDrawLine(win->rend,x+tri.p0.x,y+tri.p0.y,x+tri.p1.x,y+tri.p1.y);
    SDL_RenderDrawLine(win->rend,x+tri.p1.x,y+tri.p1.y,x+tri.p2.x,y+tri.p2.y);
    SDL_RenderDrawLine(win->rend,x+tri.p2.x,y+tri.p2.y,x+tri.p0.x,y+tri.p0.y);
    return 0;
}

int ESDL_DrawPolyF(ESDL_Window* win,ESDL_Poly* poly,int x,int y,ESDL_Color color)
{
    std::vector<ESDL_Index_Tri>::iterator trisP = poly->tris.begin();
    std::vector<ESDL_Point>::iterator pointsP = poly->points.begin();

    for(int i = 0;i<poly->tris.size();i++)
    {
        // FIX
        if(win->debug)
        ESDL_DrawTriF(win,ESDL_Tri(*(pointsP+((trisP+i)->p0)),*(pointsP+((trisP+i)->p1)),*(pointsP+((trisP+i)->p2))),x,y,poly->tris.at(i).color);
        else
        ESDL_DrawTriF(win,ESDL_Tri(*(pointsP+((trisP+i)->p0)),*(pointsP+((trisP+i)->p1)),*(pointsP+((trisP+i)->p2))),x,y,color);
        // FIX
    }
    return 0;
}

int ESDL_DrawPoly(ESDL_Window* win,ESDL_Poly poly,int x,int y,ESDL_Color color)
{
    SDL_SetRenderDrawColor(win->rend,color.r,color.g,color.b,color.a);
    for(int i=0;i<poly.points.size()-1;i++)
    {
        SDL_RenderDrawLine(win->rend,x+poly.points.at(i).x,y+poly.points.at(i).y,x+poly.points.at(i+1).x,y+poly.points.at(i+1).y);
    }
    SDL_RenderDrawLine(win->rend,x+poly.points.at(0).x,y+poly.points.at(0).y,x+poly.points.back().x,y+poly.points.back().y);
    return 0;
}
