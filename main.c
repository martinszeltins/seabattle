#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
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

typedef enum { 
    HORIZONTAL, 
    VERTICAL
} Orientation;

typedef struct {
    SDL_Rect rect;
    bool isPlaced;
    Orientation orientation;
} Ship;

void setTextTextureAndRect(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font, SDL_Texture **textTexture, SDL_Rect *textRect);
void addPlayerShips(Ship * ships);
void addOpponentShips(Ship * ships);
bool rectanglesOverlap(int rect1StartX, int rect1EndX, int  rect1StartY, int rect1EndY, int rect2StartX, int rect2EndX, int rect2StartY, int rect2EndY);
int randomNumber(int min, int max);


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

    srand(time(NULL));

    Ship playerShips[10];
    Ship opponentShips[10];

    return 0;

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
    int shipSizes[] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };
    
    for (int i = 0; i < 10; i++)
    {
        bool shipCanBePlaced = false;
        int  tries = 0;

        Orientation newShipOrientation;
        int newShipX;
        int newShipY;
        int newShipW;
        int newShipH;

        while (shipCanBePlaced == false || tries > 10)
        {
            bool rndOrientation = rand() & 1;

            if (rndOrientation == 1) {
                newShipOrientation = HORIZONTAL;
            } else {
                newShipOrientation = VERTICAL;
            }

            newShipX = randomNumber(opponentGridOffsetX, opponentGridOffsetX + (10 * cellSize));
            newShipX = (newShipX / cellSize) * cellSize;

            newShipY = randomNumber(gridOffsetY, gridOffsetY + (10 * cellSize));
            newShipY = (newShipY / cellSize) * cellSize;

            if (newShipOrientation == HORIZONTAL) {
                newShipW = shipSizes[i] * cellSize;
                newShipH = cellSize;
            } else {
                newShipW = cellSize;
                newShipH = shipSizes[i] * cellSize;
            }

            /**
             * Check if the new ship is out of bounds and if it is
             * then generate a new random ship.
             */
            int newShipXEnd = newShipX + newShipW;
            int newShipYEnd = newShipY + newShipH;

            if (newShipXEnd > opponentGridOffsetX + (10 * cellSize) || newShipYEnd > gridOffsetY + (10 * cellSize)) {
                continue;
            }


            /**
             * Loop through all placed ships and determine if the new
             * ship overlaps the placed ship's boundary.
             */
            for (int j = 0; j < 10; j++)
            {
                if (ships[j].isPlaced) {
                    int outerBoundaryXStart = ships[i].rect.x - cellSize;
                    int outerBoundaryXEnd   = ships[i].rect.x + ships[i].rect.w + cellSize;

                    int outerBoundaryYStart = ships[i].rect.y - cellSize;
                    int outerBoundaryYEnd   = ships[i].rect.y + ships[i].rect.h + cellSize;

                    // bool shipsOverlap = rectanglesOverlap()

                    
                }
            }

            tries++;

            if (tries > 8) {
                printf("Tries > 8 already!! \n");
            }
        }
    }
}

/**
 * Determine if two rectangles overlap each other
 */
bool rectanglesOverlap(int rect1StartX, int rect1EndX, int  rect1StartY, int rect1EndY,
                       int rect2StartX, int rect2EndX, int rect2StartY, int rect2EndY)
{
    if (rect1StartX >= rect2EndX || rect1EndX <= rect2StartX) {
        return false;
    }

    if (rect1StartY >= rect2EndY || rect1EndY <= rect2StartY) {
        return false;
    }

    return true;
}

/**
 * Generate a random number
 */
int randomNumber(int min, int max)
{
    return rand() % ((max+1) - min) + min;
}