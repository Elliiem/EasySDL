#include "ESDL.h"

// Color
ESDL_Color red(255,0,0,255);
ESDL_Color green(0,255,0,255);
ESDL_Color blue(0,0,255,255);
ESDL_Color white(255,255,255,255);
ESDL_Color black(0,0,0,255);
ESDL_Color gray(125,125,125,255);

// Draw
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

    int X = x+tri.p0.x;
    int Y = y+tri.p0.y;

    delta_a = (float)(tri.p1.x-tri.p0.x)/(float)(tri.p1.y-tri.p0.y);
    delta_b = (float)(tri.p2.x-tri.p0.x)/(float)(tri.p2.y-tri.p0.y);

    while(Y != y+tri.p1.y)
    {
        line_a += delta_a;
        line_b += delta_b;
        // I prolly should draw lines like this but I cant find a better way
        SDL_RenderDrawLine(win->rend,X+line_a,Y,X+line_b,Y);

        Y++;
    }

    delta_a = (float)(tri.p2.x-tri.p1.x)/(float)(tri.p2.y-tri.p1.y);

    line_a = tri.p1.x - tri.p0.x;

    while(Y != y+tri.p2.y)
    {
        line_a += delta_a;
        line_b += delta_b;

        SDL_RenderDrawLine(win->rend,X+line_a,Y,X+line_b,Y);

        Y++;
    }

    return 0;
}

int ESDL_DrawTriF(ESDL_Window* win,ESDL_Tri tri,ESDL_Point pos,ESDL_Color color)
{
    int x = pos.x;
    int y = pos.y;

    Sort_Tri(&tri);
    SDL_SetRenderDrawColor(win->rend,color.r,color.g,color.b,color.a);

    float delta_a,delta_b;
    float line_a = 0;
    float line_b = 0;

    int X = x+tri.p0.x;
    int Y = y+tri.p0.y;

    delta_a = (float)(tri.p1.x-tri.p0.x)/(float)(tri.p1.y-tri.p0.y);
    delta_b = (float)(tri.p2.x-tri.p0.x)/(float)(tri.p2.y-tri.p0.y);

    while(Y != y+tri.p1.y)
    {
        line_a += delta_a;
        line_b += delta_b;
        // I prolly should draw lines like this but I cant find a better way
        SDL_RenderDrawLine(win->rend,X+line_a,Y,X+line_b,Y);

        Y++;
    }

    delta_a = (float)(tri.p2.x-tri.p1.x)/(float)(tri.p2.y-tri.p1.y);

    line_a = tri.p1.x - tri.p0.x;

    while(Y != y+tri.p2.y)
    {
        line_a += delta_a;
        line_b += delta_b;

        SDL_RenderDrawLine(win->rend,X+line_a,Y,X+line_b,Y);

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

int ESDL_DrawTri(ESDL_Window* win,ESDL_Tri tri,ESDL_Point pos,ESDL_Color color)
{
    int x = pos.x;
    int y = pos.y;
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

int ESDL_DrawPolyF(ESDL_Window* win,ESDL_Poly* poly,ESDL_Point pos,ESDL_Color color)
{
    std::vector<ESDL_Index_Tri>::iterator trisP = poly->tris.begin();
    std::vector<ESDL_Point>::iterator pointsP = poly->points.begin();

    for(int i = 0;i<poly->tris.size();i++)
    {
        // FIX
        if(win->debug)
        ESDL_DrawTriF(win,ESDL_Tri(*(pointsP+((trisP+i)->p0)),*(pointsP+((trisP+i)->p1)),*(pointsP+((trisP+i)->p2))),pos.x,pos.y,poly->tris.at(i).color);
        else
        ESDL_DrawTriF(win,ESDL_Tri(*(pointsP+((trisP+i)->p0)),*(pointsP+((trisP+i)->p1)),*(pointsP+((trisP+i)->p2))),pos.x,pos.y,color);
        // FIX
    }
    return 0;
}

int ESDL_DrawPoly(ESDL_Window* win,ESDL_Poly* poly,int x,int y,ESDL_Color color)
{
    SDL_SetRenderDrawColor(win->rend,color.r,color.g,color.b,color.a);
    for(int i=0;i<poly->points.size()-1;i++)
    {
        SDL_RenderDrawLine(win->rend,x+poly->points.at(i).x,y+poly->points.at(i).y,x+poly->points.at(i+1).x,y+poly->points.at(i+1).y);
    }
    SDL_RenderDrawLine(win->rend,x+poly->points.at(0).x,y+poly->points.at(0).y,x+poly->points.back().x,y+poly->points.back().y);
    return 0;
}

int ESDL_DrawPoly(ESDL_Window* win,ESDL_Poly* poly,ESDL_Point pos,ESDL_Color color)
{
    int x = pos.x;
    int y = pos.y;
    SDL_SetRenderDrawColor(win->rend,color.r,color.g,color.b,color.a);
    for(int i=0;i<poly->points.size()-1;i++)
    {
        SDL_RenderDrawLine(win->rend,x+poly->points.at(i).x,y+poly->points.at(i).y,x+poly->points.at(i+1).x,y+poly->points.at(i+1).y);
    }
    SDL_RenderDrawLine(win->rend,x+poly->points.at(0).x,y+poly->points.at(0).y,x+poly->points.back().x,y+poly->points.back().y);
    return 0;
}

// Poly
ESDL_Point ToKartesian(float len,float deg,float rot)
{
    deg += rot;
    if(deg>=360)
    {
        deg -= 360;
    }
    else if(rot<0)
    {
        deg += 360;
    }

    int x,y;

    if(deg <= 180)
    {
        if(deg<=90)
        {
            x = round(cos((deg)*0.017453292519943295)*len);
            y = -round(sin((deg)*0.017453292519943295)*len);
        }
        else
        {
            x = -round(sin((deg-90)*0.017453292519943295)*len);
            y = -round(cos((deg-90)*0.017453292519943295)*len);
        }
    }
    else
    {
        if(deg<=270)
        {
            x = -round(cos((deg-180)*0.017453292519943295)*len);
            y = round(sin((deg-180)*0.017453292519943295)*len);
        }
        else
        {
            x = round(sin((deg-270)*0.017453292519943295)*len);
            y = round(cos((deg-270)*0.017453292519943295)*len);
        }
    }
    return ESDL_Point(x,y);
}

ESDL_Polar_Point ToPolar(float x,float y)
{
    int add=0;

    if(x==0 & y==0)
    {
        return ESDL_Polar_Point(0,0);
    }
    else if (x == 0)
    {
        if(y<0)
        {
            return ESDL_Polar_Point(fabs(y),270);
        }
        else if (y > 0)
        {
            return ESDL_Polar_Point(fabs(y),90);
        }
    }
    else if(y == 0)
    {
        if(x<0)
        {
            return ESDL_Polar_Point(fabs(x),180);
        }
        else if (x>0)
        {
            return ESDL_Polar_Point(fabs(x),0);
        }
    }

    if(x < 0 & y > 0)
    {
        x = fabs(x);
        y = fabs(y);
        return ESDL_Polar_Point(sqrt(powf(x,2)+powf(y,2)),fabs(180-(atan((y/x))*57.29577951308232)));
    }
    else if (x < 0 & y < 0)
    {
        x = fabs(x);
        y = fabs(y);
        return ESDL_Polar_Point(sqrt(powf(x,2)+powf(y,2)),(atan((y/x))*57.29577951308232)+180);
    }
    else if (x > 0 & y < 0)
    {
        x = fabs(x);
        y = fabs(y);
        return ESDL_Polar_Point(sqrt(powf(x,2)+powf(y,2)),(atan((y/x))*57.29577951308232)+270);
    }
    return ESDL_Polar_Point(sqrt(powf(x,2)+powf(y,2)),(atan((y/x))*57.29577951308232));
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

    ESDL_Color randCol;

    std::vector<ESDL_Point>::iterator pointsP;

    pointsP = points.begin();

    while(indexes_size > 3)
    {
        index_a = index + 1;
        index_b = index - 1;

        if(index_a >= indexes.size())
            index_a = 0;
        if(index_b < 0)
            index_b = indexes.size()-1;

        if(IsSmallDeg(*(pointsP+indexes.at(index)),*(pointsP+indexes.at(index_a)),*(pointsP+indexes.at(index_b))))
        {
            for(int i = 0;i<indexes_size;i++)
                if(InsideTriangle(*(pointsP+indexes.at(index)),*(pointsP+indexes.at(index_a)),*(pointsP+indexes.at(index_b)),*(pointsP+indexes.at(i))))
                {
                    break;
                }
                else if(i == indexes_size-1)
                {
                    tris.push_back(ESDL_Index_Tri(indexes.at(index_b),indexes.at(index),indexes.at(index_a)));
                    indexes.erase(indexes.begin()+index);
                    index = -1;
                    indexes_size--;
                    break;
                }
        }
        index++;
        if(index == indexes_size)
        {
            std::cerr << "ESLD ERROR: coudnt find a tri!" << std::endl;
            return 1;
        }
    }

    tris.push_back(ESDL_Index_Tri(indexes.at(2),indexes.at(0),indexes.at(1)));

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

bool ESDL_Poly::IsSmallDeg(ESDL_Point P, ESDL_Point A, ESDL_Point B)
{
    int ad,bd,pd;

    ad = sqrt(pow(A.x,2)+pow(A.y,2));
    bd = sqrt(pow(B.x,2)+pow(B.y,2));
    pd = sqrt(pow(P.x,2)+pow(P.y,2));

    if(pd > ad | pd > bd)
    {
        return true;
    }
    if(pd == bd & pd == ad)
    {
        return true;
    }

    return false;
}

int ESDL_Poly::ResetTris()
{
    SplitPoly();
    return 0;
}

int ESDL_Poly::Rotate(float deg)
{
    rot += deg;
    for(int i = 0;i<polar.size();i++)
    {
        points.at(i) = ToKartesian(polar.at(i).r,polar.at(i).deg,rot);
    }
    if(rot > 360)
    {
        rot = 0;
    }
    if(rot < 0)
    {
        rot = 360;
    }
    return 0;
}

int ESDL_Poly::FillPolar()
{
    ESDL_Polar_Point polarpoint;
    for(int i = 0;i<points.size();i++)
    {
        polarpoint = ToPolar(points.at(i).x,-points.at(i).y);
        polar.push_back(polarpoint);
    }
    return 0;
}

int ESDL_Poly::ResetPolar()
{
    polar.clear();
    FillPolar();
    return 0;
}

int ESDL_Poly::Reset()
{
    ResetPolar();
    ResetTris();
    return 0;
}

ESDL_Vector ESDL_Poly::GetForward()
{
    float x = cosf((rot+90)*0.017453292519943295);
    float y = -sinf((rot+90)*0.017453292519943295);
    return ESDL_Vector(x,y);
}

//Window
ESDL_Window::ESDL_Window(int width,int height,std::string name,int SDL_renderer_flags,SDL_BlendMode SDL_blend_flag)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    win = SDL_CreateWindow(name.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    rend = SDL_CreateRenderer(win, -1, SDL_renderer_flags);
    surf = SDL_GetWindowSurface(win);

    time = std::chrono::high_resolution_clock::now();

    SDL_SetRenderDrawBlendMode(rend, SDL_blend_flag);

    SDL_GetWindowSize(win,&window_width,&window_height);

    half_window_height = window_height/2;
    half_window_width = window_width/2;
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
        switch(event.type)
        {
            case(SDL_KEYDOWN):
                GetKeys();
            break;

            case(SDL_KEYUP):
                GetKeys();
            break;

            case(SDL_QUIT):
                quit = true;
            break;

            case(SDL_MOUSEMOTION):
                mouse_pos.x = event.motion.x;
                mouse_pos.y = event.motion.y;
            break;
        }
    }
    return 0;
}

int ESDL_Window::HandleKeys()
{
    if (keyboard[SDLK_LCTRL] & keyboard[SDLK_z])
        quit = true;
    if(keyboard[SDLK_b] & !last_keyboard[SDLK_b])
        debug = !debug;

    return 0;
}

int ESDL_Window::Update()
{
    HandleSDLEvents();
    HandleKeys();

    SDL_RenderPresent(rend);
    SDL_SetRenderDrawColor(rend,30,30,60,255);
    SDL_RenderClear(rend);

    delta_m = GetDeltaTime();
    delta = delta_m/1000;

    return 0;
}

float ESDL_Window::GetDeltaTime()
{
    std::chrono::time_point<std::chrono::system_clock> last_time = time;
    time = std::chrono::high_resolution_clock::now();

    float delta = std::chrono::duration_cast<std::chrono::microseconds>(time - last_time).count();

    return delta;
}