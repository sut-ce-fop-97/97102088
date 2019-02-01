
#ifndef FOP_PROJECT_LOGIC_H
#define FOP_PROJECT_LOGIC_H
int correct_int_casting(double inp);
int correct_mod(int a, int b);
int movement_collides_walls(Tank * tank, Map * map, char direction);
void bullet_wall_collision(Bullet * bullet, Map * map);
int bullet_tank_collision(Bullet * bullet, Map * map);
void save_game(Map * map, char * file_path);
void load_game(Map * map, char * file_path);

#define Primary_Bullets 8
#define no_of_allowed_mines 3

#define not_activated_mine_yet -2
#define no_collision 1
#define collision 2

#define proceed_to_game 1
#define Exit 2
#define new_game_in_pause_menu 3
#define new_game_in_start_menu 4
#define load_game_in_menu 5

// All of the next constant times are multiplication of FPS(= 30) and number of seconds
#define Bullet_Primary_Lifetime 300
#define time_between_appear_and_pick 450
#define time_between_consecutive_mines 300
#define mine_lifetime_after_plant 450
#define explosion_delay 15

#define horizontal_margin_for_text 4
#define FPS 30
#define map_scale 80
#define window_width 1400
#define window_height 800
#endif