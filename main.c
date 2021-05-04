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
int placingShipIndex = 0;
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
void drawGridLines(SDL_Renderer * renderer);
void drawOpponentShips(SDL_Renderer * renderer, Ship * opponentShips);
void rotateShip(Ship * playerShips);
void placeShip(Ship * ships);
void drawPlacingShip(SDL_Renderer * renderer, Ship * ships);
void drawPlacedShips(SDL_Renderer * renderer, Ship * ships);


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

    addPlayerShips(playerShips);
    addOpponentShips(opponentShips);

    char * fontPath = "TheCaliforniaHustle.ttf";
    int quit = 0;

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED , &window, &renderer);
 
    font = TTF_OpenFont(fontPath, 80);
    setTextTextureAndRect(renderer, 760, 60, "Sea Battle", font, &titleTexture, &titleRect);

    while (!quit)
    {
        while (SDL_PollEvent(&event) == 1)
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    quit = 1;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_RETURN:
                            placeShip(playerShips);
                            break;

                        case SDLK_SPACE:
                            rotateShip(playerShips);
                            break;
                    
                        case SDLK_ESCAPE:
                            quit = 1;
                            break;

                        case SDLK_w:
                        case SDLK_UP:
                            if (playerShips[placingShipIndex].rect.y != gridOffsetY) {
                                playerShips[placingShipIndex].rect.y = playerShips[placingShipIndex].rect.y - cellSize;
                            }

                            break;

                        case SDLK_s:
                        case SDLK_DOWN:
                            if ((playerShips[placingShipIndex].rect.y + playerShips[placingShipIndex].rect.h) < gridOffsetY + (10 * cellSize)) {
                                playerShips[placingShipIndex].rect.y = playerShips[placingShipIndex].rect.y + cellSize;
                            }

                            break;

                        case SDLK_a:
                        case SDLK_LEFT:
                            if (playerShips[placingShipIndex].rect.x != playerGridOffsetX) {
                                playerShips[placingShipIndex].rect.x = playerShips[placingShipIndex].rect.x - cellSize;
                            }

                            break;

                        case SDLK_d:
                        case SDLK_RIGHT:
                            if ((playerShips[placingShipIndex].rect.x + playerShips[placingShipIndex].rect.w) < playerGridOffsetX + (10 * cellSize)) {
                                playerShips[placingShipIndex].rect.x = playerShips[placingShipIndex].rect.x + cellSize;
                                break;
                            }
                    }

                    break;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        // Draw the title text
        SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);

        drawOpponentShips(renderer, opponentShips);
        drawPlacingShip(renderer, playerShips);
        drawPlacedShips(renderer, playerShips);

        drawGridLines(renderer);

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
        ships[i].rect.x       = playerGridOffsetX;
        ships[i].rect.y       = gridOffsetY;
        ships[i].rect.w       = 1 * cellSize;
        ships[i].rect.h       = shipSizes[i] * cellSize;
        ships[i].isPlaced     = false;
        ships[i].orientation  = VERTICAL;
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

    // This needs to be initialized otherwise getting some garbage value.
    for (int i = 0; i < 10; i++) {
        ships[i].isPlaced = false;
    }
    
    for (int i = 0; i < 10; i++)
    {
        bool shipCanBePlaced = false;
        int  tries = 0;

        Orientation newShipOrientation;
        int newShipX;
        int newShipY;
        int newShipW;
        int newShipH;

        while (shipCanBePlaced == false || tries > 1000)
        {
            bool rndOrientation = rand() & 1;

            if (rndOrientation == 1) {
                newShipOrientation = HORIZONTAL;
            } else {
                newShipOrientation = VERTICAL;
            }
            
            newShipX = randomNumber(opponentGridOffsetX, opponentGridOffsetX + (10 * cellSize));
            newShipX = (newShipX / cellSize) * cellSize;
            newShipX = newShipX + 30;

            newShipY = randomNumber(gridOffsetY, gridOffsetY + (10 * cellSize));
            newShipY = (newShipY / cellSize) * cellSize;
            newShipY = newShipY + 40;

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
                tries++;
                continue;
            }


            /**
             * Loop through all placed ships and determine if the new
             * ship overlaps the placed ship's boundary.
             */
            shipCanBePlaced = true;

            for (int j = 0; j < 10; j++)
            {
                if (ships[j].isPlaced == true)
                {
                    int outerBoundaryXStart = ships[j].rect.x - cellSize;
                    int outerBoundaryXEnd   = ships[j].rect.x + ships[j].rect.w + cellSize;

                    int outerBoundaryYStart = ships[j].rect.y - cellSize;
                    int outerBoundaryYEnd   = ships[j].rect.y + ships[j].rect.h + cellSize;

                    bool shipsOverlap = rectanglesOverlap(
                        newShipX, newShipXEnd, newShipY, newShipYEnd,
                        outerBoundaryXStart, outerBoundaryXEnd, outerBoundaryYStart, outerBoundaryYEnd
                    );

                    if (shipsOverlap) {
                        shipCanBePlaced = false;
                        break;
                    }
                }
            }

            if (shipCanBePlaced == false) {
                tries++;
            }

            if (tries > 1000) {
                printf("Error: tries > 1000! \n");
                exit(1);
            }
        }

        ships[i].rect.x       = newShipX;
        ships[i].rect.y       = newShipY;
        ships[i].rect.w       = newShipW;
        ships[i].rect.h       = newShipH;
        ships[i].isPlaced     = true;
        ships[i].orientation  = newShipOrientation;
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

/**
 * The the grid lines for both players
 */
void drawGridLines(SDL_Renderer * renderer)
{
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
}

/**
 * Draw the opponent ships
 */
void drawOpponentShips(SDL_Renderer * renderer, Ship * opponentShips)
{
    for (int i = 0; i < 10; i++) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderFillRect(renderer, &opponentShips[i].rect);
    }
}

/**
 * Rotate ship
 */
void rotateShip(Ship * ships)
{
    if (ships[placingShipIndex].orientation == VERTICAL)
    {
        if ((ships[placingShipIndex].rect.x + ships[placingShipIndex].rect.h) > playerGridOffsetX + (10 * cellSize)) {
            ships[placingShipIndex].rect.x = ships[placingShipIndex].rect.x - ships[placingShipIndex].rect.h + cellSize;

            int h = ships[placingShipIndex].rect.h;
            ships[placingShipIndex].rect.h = ships[placingShipIndex].rect.w;
            ships[placingShipIndex].rect.w = h;
            ships[placingShipIndex].orientation = HORIZONTAL;
        } else {
            int h = ships[placingShipIndex].rect.h;
            ships[placingShipIndex].rect.h = ships[placingShipIndex].rect.w;
            ships[placingShipIndex].rect.w = h;
            ships[placingShipIndex].orientation = HORIZONTAL;
        }
    }
    else if (ships[placingShipIndex].orientation == HORIZONTAL)
    {
        if ((ships[placingShipIndex].rect.y + ships[placingShipIndex].rect.w) > gridOffsetY + (10 * cellSize)) {
            ships[placingShipIndex].rect.y = ships[placingShipIndex].rect.y - ships[placingShipIndex].rect.w + cellSize;

            int h = ships[placingShipIndex].rect.h;
            ships[placingShipIndex].rect.h = ships[placingShipIndex].rect.w;
            ships[placingShipIndex].rect.w = h;
            ships[placingShipIndex].orientation = VERTICAL;
        } else {
            int h = ships[placingShipIndex].rect.h;
            ships[placingShipIndex].rect.h = ships[placingShipIndex].rect.w;
            ships[placingShipIndex].rect.w = h;
            ships[placingShipIndex].orientation = VERTICAL;
        }
    }
}

/**
 * Place current ship in position
 */
void placeShip(Ship * ships)
{
    ships[placingShipIndex].isPlaced = true;
    placingShipIndex++;
}

/**
 * Draw the currently placing ship
 */
void drawPlacingShip(SDL_Renderer * renderer, Ship * ships)
{
    if (ships[placingShipIndex].isPlaced) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    } else {
        SDL_SetRenderDrawColor(renderer, 75, 75, 75, 0);
    }

    SDL_RenderFillRect(renderer, &ships[placingShipIndex].rect);
}

/**
 * Draw the player's placed ships
 */
void drawPlacedShips(SDL_Renderer * renderer, Ship * ships)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

    for (int i = 0; i < 10; i++) {
        if (ships[i].isPlaced) {
            SDL_RenderFillRect(renderer, &ships[i].rect);
        }
    }
}