#ifndef MAP_H
#define MAP_H


struct Walls{
    int size;
    Vector2 *walls;
}

char MAP[8][12] = {
    {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
    {'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
    {'W', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
    {'W', ' ', ' ', ' ', 'W', 'W', ' ', ' ', ' ', 'W', ' ', 'W'},
    {'W', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
    {'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
    {'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W'},
    {'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W'},
};
#endif