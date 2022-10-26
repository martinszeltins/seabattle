#ifndef __GAME_H__
#define __GAME_H__

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    SDL_Rect rect;
    SDL_Texture * texture;
} text;

typedef enum {
    HORIZONTAL,
    VERTICAL
} orientation;

typedef struct {
    SDL_Rect rect;
    bool is_placed;
    orientation orientation;
} ship;

typedef struct {
    SDL_Rect rect;
    bool is_hit;
} shot;

struct game {
    text title;
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Rect player_aim;
    shot player_shots[100];
    shot opponent_shots[100];
    ship player_ships[10];
    ship opponent_ships[10];
    bool is_running;
    int cell_size;
    int grid_width;
    int grid_height;
    int grid_offset_y;
    int placing_ship_index;
    int player_grid_offset_x;
    int opponent_grid_offset_x;
    int placed_ships;
    int player_hits;
    int opponent_hits;
    int player_shots_count;
    int opponent_shots_count;
    bool is_shooting;
};

struct game * game_create();
void game_run(struct game * game);
void game_init(struct game * game);
int game_terminate(struct game * game);
void game_quit(struct game *game);
text game_get_title(struct game *game);

#endif
