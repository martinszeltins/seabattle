#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

void setTextTextureAndRect(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture **textTexture, SDL_Rect *textRect);


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

    int gridCellSize = 60;
    int gridWidth = 10;
    int gridHeight = 10;
    int gridYFrom = 280;
    int playerGridXFrom = 280;
    int opponentGridXFrom = 1050;

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
        for (int y = gridYFrom; y < 1 + gridHeight * gridCellSize + gridYFrom; y += gridCellSize) {
            SDL_RenderDrawLine(renderer, playerGridXFrom, y, playerGridXFrom + (10 * gridCellSize), y);
        }

        // Vertical
        for (int x = playerGridXFrom; x < 1 + gridWidth * gridCellSize + playerGridXFrom; x += gridCellSize) {
            SDL_RenderDrawLine(renderer, x, gridYFrom, x, gridYFrom + (10 * gridCellSize));
        }


        // Draw the opponent grid lines
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Horizontal 
        for (int y = gridYFrom; y < 1 + gridHeight * gridCellSize + gridYFrom; y += gridCellSize) {
            SDL_RenderDrawLine(renderer, opponentGridXFrom, y, opponentGridXFrom + (10 * gridCellSize), y);
        }

        // Vertical
        for (int x = opponentGridXFrom; x < 1 + gridWidth * gridCellSize + opponentGridXFrom; x += gridCellSize) {
            SDL_RenderDrawLine(renderer, x, gridYFrom, x, gridYFrom + (10 * gridCellSize));
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