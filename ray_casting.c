#include "import.h"

extern int TILE;

const double Fov = PI / 3.0f;
const double Half_fov = Fov / 2.0f;
const int Num_rays = 120;
const double Delta_angle = Fov / (float)Num_rays;

const int Depth = 800;

bool check_colision(Vector2 pos, const Vector2 *w)
{
    int pos_x = ((int)pos.x / TILE * TILE);
    int pos_y = ((int)pos.y / TILE * TILE);
    for (int i = 0; w[i].x >= 0; i++)
        if ((int)w[i].x == pos_x && (int)w[i].y == pos_y)
            return false;  
    return true;
}

void ray_casting(Vector2 plp, double pla, const Vector2 *walls)
{
    double cur_angel = pla - Half_fov;
    Vector2 ray_dst;
    
    for (int r = 0; r < Num_rays; r++)
    {
        double sin_a = sin(cur_angel);
        double cos_a = cos(cur_angel);
        for (int i = 0; i < Depth; i++)
        {          
            ray_dst.x = plp.x + (float)i * cos_a;
            ray_dst.y = plp.y + (float)i * sin_a;
            if (!check_colision(ray_dst, walls))
                break;
     
        }
        DrawLineV(plp, ray_dst, GRAY);
        cur_angel += Delta_angle;
    }
}