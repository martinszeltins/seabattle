#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

void gameplay_start(struct game * game);
void gameplay_add_player_ships(struct game * game);
void gameplay_add_opponent_ships(struct game *game);
void gameplay_reset_player_cursor(struct game *game);

#endif