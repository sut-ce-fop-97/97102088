#ifndef FOP_PROJECT_STRUCTS_H
#define FOP_PROJECT_STRUCTS_H

typedef struct {
    int x1, y1, x2, y2;
} Wall;

typedef struct {
    int x, y;
    double angle;
    int lifetime;
} Bullet;

typedef struct {
    int x, y, radius;
    //int right_corner_x, right_corner_y;
    //int left_corner_x, left_corner_y;
    double angle, thickness;
    Bullet * bullets;
    int remaining_bullets;
} Tank;

typedef struct {
    Tank * tanks;
    Wall * walls;
    int number_of_walls;
} Map;

#endif