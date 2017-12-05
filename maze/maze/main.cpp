#include <SDL.h>

#include "common.h"
#include "Maze.h"
#include "MazeWalker.h"
#include "MazeDrawer.h"

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;
//The window renderer
SDL_Renderer* gRenderer = nullptr;
//Current displayed texture
SDL_Texture* gTexture;

//Starts up SDL and creates window
bool init()
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    //Create window
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    //Create renderer for window
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    //Initialize renderer color
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    return true;
}
//Close media and shut down SDL
void close()
{
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}


int main(int argc, char * argv[])
{
    //Start up SDL and create window
    if (!init()) { printf("Failed to initialize!\n"); }
    else
    {
        //Main loop flag
        bool quit = false;
        //Event handler
        SDL_Event e;

        auto maze = Maze::GenerateDFSMaze();
        auto * walker = new Maze::MazeWalker(maze, 5, 1);
        SDLMazeDrawer::DrawMaze(gRenderer, maze);

        //While application is running
        while (!quit)
        {
            //Handle events on queue
            while (SDL_PollEvent(&e) != 0)
            {
                //User requests quit
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
                else if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_n)
                    {
                        maze = Maze::GenerateDFSMaze();
                        delete walker;
                        walker = new Maze::MazeWalker(maze, 5, 1);
                    }
                    if (e.key.keysym.sym == SDLK_UP)
                        walker->Move(Maze::Direction::up);
                    if (e.key.keysym.sym == SDLK_DOWN)
                        walker->Move(Maze::Direction::down);
                    if (e.key.keysym.sym == SDLK_LEFT)
                        walker->Move(Maze::Direction::left);
                    if (e.key.keysym.sym == SDLK_RIGHT)
                        walker->Move(Maze::Direction::right);
                }
            }

            SDLMazeDrawer::DrawMaze(gRenderer, maze);
            SDLMazeDrawer::DrawWalker(gRenderer, walker->m_posI, walker->m_posJ);

            //Update screen
            SDL_RenderPresent(gRenderer);
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}