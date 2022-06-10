#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

void gameplay_start(struct game * game);
void gameplay_add_player_ships(struct game * game);
void gameplay_add_opponent_ships(struct game * game);
void gameplay_reset_player_aim(struct game * game);
void gameplay_place_ship(struct game * game);
void gameplay_rotate_ship(struct game * game);
void gameplay_shoot_at_component(struct game * game);
void gameplay_shoot_at_player(struct game * game);

#endif