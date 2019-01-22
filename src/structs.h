#ifndef FOP_PROJECT_STRUCTS_H
#define FOP_PROJECT_STRUCTS_H

typedef struct {
    int x1, y1, x2, y2;
} Wall;

typedef struct {
    int x, y;
    double angle, radius;
    int lifetime;
} Bullet;

typedef struct {
    int x, y, radius;
    int tank_index;
    double angle, thickness;
    Bullet * bullets;
    int remaining_bullets;
    int score;
} Tank;

typedef struct {
    Tank * tanks;
    Wall * walls;
    int number_of_walls;
    int width;
    int height;
} Map;

typedef struct {
    int x, y;
} Button;

#endif