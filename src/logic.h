
#ifndef FOP_PROJECT_LOGIC_H
#define FOP_PROJECT_LOGIC_H
int correct_int_casting(double a);
int correct_mod(int a, int b);
int movement_collides_walls(Tank * tank, Map * map, char direction);
void bullet_wall_collision(Bullet * bullet, Map * map);
int bullet_tank_collision(Bullet * bullet, Map * map);

int index_of_last_assigned_mine;

#define Primary_Bullets 8
#define no_of_allowed_mines 20

#define inactive_mine -2
#define no_collision 1
#define collision 2

#define proceed_to_game 1
#define Exit 2
#define new_game_in_pause_menu 3
#define new_game_in_start_menu 4

#define bullet_radius 4.0
#define mine_radius 10.0

// All of the next constant times are multiplication of FPS and number of seconds
#define Bullet_Primary_Lifetime 300
#define time_between_appear_and_pick 600
#define time_between_consecutive_mines 150
#define mine_lifetime_after_plant 900
#define explosion_delay 30

#define horizontal_margin_for_text 4
#define FPS 30

#endif