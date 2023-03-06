#include "ESDL.h"


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
            fmt::print("coudnt find a tri!");
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

ESDL_Vector ESDL_Poly::GetForward()
{
    float x = cosf((rot+90)*0.017453292519943295);
    float y = -sinf((rot+90)*0.017453292519943295);
    return ESDL_Vector(x,y);
}
