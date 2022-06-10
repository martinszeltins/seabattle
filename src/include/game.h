#ifndef __GAME_H__
#define __GAME_H__

#include <SDL2/SDL.h>
#include <stdbool.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

typedef struct {
    SDL_Rect rect;
    SDL_Texture * texture;
} text;

struct game {
    text title;
    SDL_Window * window;
    SDL_Renderer * renderer;
    bool is_running;
};

struct game * game_create();
void game_run(struct game * game);
void game_init(struct game * game);
int game_terminate(struct game * game);
void game_quit(struct game *game);
text game_get_title(struct game *game);

#endif
