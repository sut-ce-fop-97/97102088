
#ifndef FOP_PROJECT_LOGIC_H
#define FOP_PROJECT_LOGIC_H
int correct_mod(int a, int b);
int movement_collides_walls(Tank * tank, Map * map, char direction);
int bullet_tank_collision(Bullet * bullet, Map * map);

#define Primary_Bullets 8
#define collision 2
#define proceed_to_game 1
#define  no_collision 1
#define bullet_radius 4
#define Primary_Lifetime 180 // Multiplication of 30(FPS) and 6(Number of seconds of lifetime)
#define Exit 2
#define new_game_in_pause_menu 3
#define horizontal_margin_for_text 4
#define FPS 30

#endif