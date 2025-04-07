#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "map.h"

#define Len(x) (sizeof(x) / sizeof(x[0]))

const int scrWidth = 1200;
const int scrHeight = 800;
const int scrHalfWidth = scrWidth / 2;
const int scrHalfHeight = scrHeight / 2;
const int FPS = 60;
const int TILE = 100;

float PLAYER_ANGEL = 0.0f;
float PLAYER_SPEED = 4.0f;

double FOV = 3.14159265 / 3.0; 


Vector2 *getWall(void)
{   
    int i = 0;
    Vector2 *wall = (Vector2 *)calloc(
        (scrWidth / TILE)*(scrHalfHeight / TILE), sizeof(Vector2));
    
    for (int y = 0; y < Len(MAP); y++)
        for (int x = 0; x < Len(MAP[y]); x++)
        {
            if (MAP[y][x] == 'W'){
                wall[i].x = (float)x * TILE;
                wall[i].y = (float)y * TILE;
                i++;
            }
        }
    return wall;
}


void move_player(Vector2 *pp)
{   
    float cos_a = cos(PLAYER_ANGEL);
    float sin_a = sin(PLAYER_ANGEL);
    if (IsKeyDown(KEY_W)) 
    {   
        pp->x += PLAYER_SPEED * cos_a;
        pp->y += PLAYER_SPEED * sin_a;
    }   
    if (IsKeyDown(KEY_S)) 
    {   
        pp->x -= PLAYER_SPEED * cos_a;
        pp->y -=PLAYER_SPEED * sin_a;
    }   
    if (IsKeyDown(KEY_A)) 
    {   
        pp->x += PLAYER_SPEED * sin_a;
        pp->y -= PLAYER_SPEED * cos_a;
    }
    if (IsKeyDown(KEY_D)) 
    {   
        pp->x -= PLAYER_SPEED * sin_a;
        pp->y += PLAYER_SPEED * cos_a;
    } 
         
    if (IsKeyDown(KEY_LEFT)) PLAYER_ANGEL -= 0.02f;
    if (IsKeyDown(KEY_RIGHT)) PLAYER_ANGEL += 0.02f;
    PLAYER_ANGEL = fmod(PLAYER_ANGEL, 360.0);
}

int main(void)
{
    InitWindow(scrWidth, scrHeight, "C-DOOM");
    // DisableCursor();                
    SetTargetFPS(FPS);   
    //--------------------------------------------------------------------------------------
    Vector2 player_pos = {(float)scrHalfWidth, (float)scrHalfHeight};

    Vector2 *walls = getWall();
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
        for (int i = 0; i < (scrWidth / TILE)*(scrHalfHeight / TILE); i++)
            DrawRectangleLines((int)walls[i].x, (int)walls[i].y, TILE, TILE, DARKGRAY);
        DrawCircleV(player_pos, 10, GREEN);
        DrawLineV(player_pos, player_dst, GREEN);
        DrawFPS(200, 200);
        EndDrawing();
    }
    free(walls);
    CloseWindow();
    return 0;
}