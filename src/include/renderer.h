#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SDL2/SDL.h>

void renderer_draw(struct game * game);
void renderer_clear_screen(SDL_Renderer * renderer);
void renderer_draw_title(struct game * game);
void renderer_draw_grid_lines(struct game * game);
void renderer_draw_placed_ships(struct game * game);
void renderer_draw_placing_ship(struct game * game);
void renderer_draw_player_aim(struct game * game);
void renderer_draw_player_shots(struct game * game);
void renderer_draw_opponent_shots(struct game *game);

#endif
