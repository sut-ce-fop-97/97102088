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
    int x, y, length;
    double angle, thickness;
    Bullet * bullets;
    int remaining_bullets;
} Tank;

typedef struct {
    Tank * tanks;
    Wall * walls;
} Map;

#endif