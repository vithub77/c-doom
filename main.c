#include "import.h"
#include "map.h"

#define Len(x) (sizeof(x) / sizeof(x[0]))

const int scrWidth = 1200;
const int scrHeight = 800;
const int scrHalfWidth = scrWidth / 2;
const int scrHalfHeight = scrHeight / 2;
const int FPS = 60;
const int TILE = 100;

float PLAYER_ANGEL = 0.0f;
float PLAYER_SPEED = 3.0f;


void ray_casting(Vector2, float, const Walls *w);   // ray_casting.c

int cmpless(const void * lhs, const void * rhs)
{
    Vector2 *lr = (Vector2 *)lhs;
    Vector2 *rr = (Vector2 *)rhs;
    float ilr = lr->x * lr->x + lr->y * lr->y;
    float irr = rr->x * rr->x + rr->y * rr->y;
    if (ilr < irr)
        return -1;
    if (ilr > irr)
        return 1;
    else
        return 0;
}

int getMap(Walls *wals)
{   
    int w, i = 0;
    Vector2 map[(scrWidth / TILE)*(scrHeight / TILE)];
    for (int y = 0; y < Len(MYMAP); y++)
        for (int x = 0; x < Len(MYMAP[y]); x++)
        {
            if (MYMAP[y][x] == 'W'){
                map[i].x = (float)x * TILE;
                map[i].y = (float)y * TILE;
                i++;
            }
        }
    qsort(map, i, sizeof(Vector2), cmpless);

    wals->size = i;
    wals->walls = (Vector2 *)calloc(i, sizeof(Vector2));

    for (w = 0; w < i; w++)
    {
        wals->walls[w].x = map[w].x;
        wals->walls[w].y = map[w].y;
    }
    return 1;
}


void move_player(Vector2 *pp)
{   
    int flag_press = 0;
    float cos_a = cos(PLAYER_ANGEL);
    float sin_a = sin(PLAYER_ANGEL);
    if (IsKeyDown(KEY_W)) 
    {   
        flag_press = 1;
        pp->x += PLAYER_SPEED * cos_a;
        pp->y += PLAYER_SPEED * sin_a;
    }   
    if (IsKeyDown(KEY_S)) 
    {   
        flag_press = 1;
        pp->x -= PLAYER_SPEED * cos_a;
        pp->y -= PLAYER_SPEED * sin_a;
    }   
    if (IsKeyDown(KEY_A)) 
    {   
        float div = (flag_press) ? 2 : 1;
        pp->x += (PLAYER_SPEED/div) * sin_a;
        pp->y -= (PLAYER_SPEED/div) * cos_a;
    }
    if (IsKeyDown(KEY_D)) 
    {   
        float div = (flag_press) ? 2.0f : 1.0f;
        pp->x -= (PLAYER_SPEED/div) * sin_a;
        pp->y += (PLAYER_SPEED/div) * cos_a;
    }      
    if (IsKeyDown(KEY_LEFT))
        PLAYER_ANGEL -= 0.04f;
    if (IsKeyDown(KEY_RIGHT))
        PLAYER_ANGEL += 0.04f;
    PLAYER_ANGEL = fmod(PLAYER_ANGEL, 360.0);
}


int main(void)
{
    InitWindow(scrWidth, scrHeight, "C-DOOM");
    // DisableCursor();                
    SetTargetFPS(FPS);   
    //--------------------------------------------------------------------------------------
    Vector2 player_pos = {(float)scrHalfWidth, (float)scrHalfHeight + 30.0};


    Walls *walls = (Walls *)malloc(sizeof(Walls));
    int res = getMap(walls);
    assert (res == 1);

    // Main game loop
    while (!WindowShouldClose())
    {   
        move_player(&player_pos);
        Vector2 player_dst = {
            (float)player_pos.x + scrWidth * cos(PLAYER_ANGEL),
            (float)player_pos.y + scrWidth * sin(PLAYER_ANGEL)};
        // Update Screen
        BeginDrawing();
        ClearBackground(BLACK);
        ray_casting(player_pos, PLAYER_ANGEL, walls);
        for (int i = 0; i < walls->size; i++)
                DrawRectangleLines(
                (int)walls->walls[i].x, (int)walls->walls[i].y, TILE, TILE, DARKGRAY);
        DrawCircleV(player_pos, 10, GREEN);
        DrawLineV(player_pos, player_dst, GREEN);
        DrawFPS(200, 200);
        EndDrawing();
    }
    free(walls->walls);
    CloseWindow();
    return 0;
}