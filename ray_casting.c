#include "import.h"

extern int TILE;
extern int scrWidth;
extern int scrHalfHeight;

bool check_colision(Vector2 dst, const Walls *w)
{
    int dst_x = ((int)dst.x / TILE * TILE);
    int dst_y = ((int)dst.y / TILE * TILE);
    for (int i = 0; i < w->size; i++)
        if ((int)w->walls[i].x == dst_x && (int)w->walls[i].y == dst_y)
            return true;  
    return false;
}

void ray_casting(Vector2 plp, float pla, const Walls *walls)
{   
    const float Fov = PI / 3.0;  // 60
    const float Half_fov = Fov / 2.0;
    const int Num_rays = 120;
    const int Depth = 800;
    const float Delta_angle = Fov / (float)Num_rays;
    const float Dist = (float)Num_rays / (float)(2 * tan(Half_fov));
    const int Scale = scrWidth / Num_rays;
    const float Proj_coef = 3 * Dist * (float)TILE; 

    float cur_angel = pla - Half_fov;
    Vector2 ray_dst, rect_coord, rect_size;

    for (int r = 0; r < Num_rays; r++)
    {
        float sin_a = sin(cur_angel);
        float cos_a = cos(cur_angel);
        for (int i = 0; i < Depth; i++)
        {          
            ray_dst.x = plp.x + (float)i * cos_a;
            ray_dst.y = plp.y + (float)i * sin_a;
            if (check_colision(ray_dst, walls) && i != 0)
            {   
                float proj_height = Proj_coef / (float)i;
                rect_coord.x = (float)r * (float)Scale;
                rect_coord.y = (float)scrHalfHeight - (proj_height / 2.0);
                rect_size.x = (float)Scale;
                rect_size.y = proj_height;
                DrawRectangleV(rect_coord, rect_size, RAYWHITE);
                break;
            }
        }
        // DrawLineV(plp, ray_dst, GRAY);
        cur_angel += Delta_angle;
    }
}