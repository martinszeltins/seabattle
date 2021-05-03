#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

int cellSize = 60;
int gridWidth = 10;
int gridHeight = 10;
int gridOffsetY = 280;
int playerGridOffsetX = 280;
int opponentGridOffsetX = 1050;

typedef struct {
  SDL_Rect rect;
  bool isPlaced;
} Ship;

void setTextTextureAndRect(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture **textTexture, SDL_Rect *textRect);
void addPlayerShips(Ship * ships);
void addOpponentShips(Ship * ships)


/**
 * A program to demonstrate text rendering
 * using the SDL2 library.
 */
int main()
{
    TTF_Font * font;
    SDL_Event event;
    SDL_Rect titleRect;
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Texture * titleTexture;

    Ship playerShips[10];
    Ship opponentShips[10];

    addPlayerShips(playerShips);
    addOpponentShips(opponentShips);

    return 0;

    char * fontPath = "TheCaliforniaHustle.ttf";
    int quit = 0;

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED , &window, &renderer);
 
    font = TTF_OpenFont(fontPath, 80);
    setTextTextureAndRect(renderer, 760, 60, "Sea Battle", font, &titleTexture, &titleRect);

    while (!quit)
    {
        while (SDL_PollEvent(&event) == 1) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);


        // Draw the player grid lines
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Horizontal 
        for (int y = gridOffsetY; y < 1 + gridHeight * cellSize + gridOffsetY; y += cellSize) {
            SDL_RenderDrawLine(renderer, playerGridOffsetX, y, playerGridOffsetX + (10 * cellSize), y);
        }

        // Vertical
        for (int x = playerGridOffsetX; x < 1 + gridWidth * cellSize + playerGridOffsetX; x += cellSize) {
            SDL_RenderDrawLine(renderer, x, gridOffsetY, x, gridOffsetY + (10 * cellSize));
        }


        // Draw the opponent grid lines
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Horizontal 
        for (int y = gridOffsetY; y < 1 + gridHeight * cellSize + gridOffsetY; y += cellSize) {
            SDL_RenderDrawLine(renderer, opponentGridOffsetX, y, opponentGridOffsetX + (10 * cellSize), y);
        }

        // Vertical
        for (int x = opponentGridOffsetX; x < 1 + gridWidth * cellSize + opponentGridOffsetX; x += cellSize) {
            SDL_RenderDrawLine(renderer, x, gridOffsetY, x, gridOffsetY + (10 * cellSize));
        }


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(titleTexture);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/**
 * Set the text's texture and rectangle
 */
void setTextTextureAndRect(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture **textTexture, SDL_Rect *textRect)
{
    int textWidth;
    int textHeight;

    SDL_Surface * surface;
    SDL_Color textColor = { 255, 255, 255, 0 };

    surface = TTF_RenderText_Blended(font, text, textColor);
    *textTexture = SDL_CreateTextureFromSurface(renderer, surface);

    textWidth = surface->w;
    textHeight = surface->h;

    SDL_FreeSurface(surface);

    textRect->x = x;
    textRect->y = y;
    textRect->w = textWidth;
    textRect->h = textHeight;
}

/**
 * Add all 10 ships for a player
 * 
 * Ship * ship is pointing to the address of the first
 * element of the ships array which is of type Ship.
 */
void addPlayerShips(Ship * ships)
{
    int shipSizes[] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

    for (int i = 0; i < 10; i++)
    {
        ships[i].rect.x    = 0;
        ships[i].rect.y    = 0;
        ships[i].rect.w    = 1 * cellSize;
        ships[i].rect.h    = shipSizes[i] * cellSize;
        ships[i].isPlaced  = true;
    }
}

/**
 * Add all 10 ships for the opponent in random order
 * 
 * Ship * ship is pointing to the address of the first
 * element of the ships array which is of type Ship.
 */
void addOpponentShips(Ship * ships)
{
    
}