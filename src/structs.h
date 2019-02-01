#ifndef FOP_PROJECT_STRUCTS_H
#define FOP_PROJECT_STRUCTS_H

typedef struct {
    int x1, y1, x2, y2;
} Wall;

typedef struct {
    int x, y;
    double angle, radius;
    int lifetime;
    int previous_collided_wall_index;
} Bullet;

typedef struct {
    int x, y;
    int index;
    double angle, thickness, radius;
    Bullet * bullets;
    int remaining_bullets;
    int score;
    int mine_index;
} Tank;

typedef struct {
    int x, y;
    double radius;
    int interval_between_appear_and_pick, countdown_before_next_mine, lifetime_after_plant;
    int picker_tank, is_planted, explosion_countdown;
    int index;
} Mine;

typedef struct {
    Tank * tanks;
    Wall * walls;
    Mine * mines;
    int number_of_walls;
    int width, height;
    int index_of_last_assigned_mine;
} Map;

typedef struct {
    int x, y;
} Button;

#endif