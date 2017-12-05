#include <string>
#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>

#include <SDL.h>

#include "common.h"
#include "convex_hull.h"

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;
//The window renderer
SDL_Renderer* gRenderer = nullptr;

//Starts up SDL and creates window
bool init()
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    //Create window
    gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    //Create renderer for window
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
    if( gRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    //Initialize renderer color
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

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


void drawCircle(SDL_Renderer * renderer, int posX, int posY, int radius)
{
    int points = 24;
    int x0, y0, x1, y1;
    for (int i = 0; i < points; i++)
    {
        x0 = posX + radius * std::cos(2 * pi * i / points);
        y0 = posY + radius * std::sin(2 * pi * i / points);
        x1 = posX + radius * std::cos(2 * pi * (i+1) / points);
        y1 = posY + radius * std::sin(2 * pi * (i+1) / points);
        SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
    }
}
void drawConvexHull(SDL_Renderer * renderer, const ConvexHull& convexHull)
{
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
    for (auto & p : convexHull.getInterior())   drawCircle(renderer, p.x, p.y, RADIUS);
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
    for (auto & p : convexHull.getConvexHull()) drawCircle(renderer, p.x, p.y, RADIUS);
    
    int size = convexHull.getConvexHull().size() - 1;
    const auto & points = convexHull.getConvexHull();
    for (int i = 0; i < size; i++) SDL_RenderDrawLine(renderer,
        points[i].x,
        points[i].y,
        points[i + 1].x,
        points[i + 1].y);
}

int main (int argc, char * argv[])
{
    //Start up SDL and create window
    if( !init() ) { printf( "Failed to initialize!\n" ); }
    else        
    {
        //Main loop flag
        bool quit = false;
        //Event handler
        SDL_Event e;

        const int COUNT = 13;
        ConvexHull ch(COUNT);
        ch.calculate();
        Point * selectedPoint = nullptr;

        //While application is running
        while( !quit )
        {
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
                else if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_n)
                    {
                        ch.reset(COUNT);
                        ch.calculate();
                    }
                }
                else if (e.type == SDL_MOUSEBUTTONDOWN)
                {
                    int x,y;
                    SDL_GetMouseState(&x, &y);
                    selectedPoint = ch.getPoint(x, y, RADIUS);
                }
                else if (e.type == SDL_MOUSEBUTTONUP)
                {
                    selectedPoint = nullptr;
                }
                else if (e.type == SDL_MOUSEMOTION)
                {
                    int dx, dy;
                    SDL_GetRelativeMouseState(&dx, &dy);
                    if (selectedPoint)
                    {
                        selectedPoint->x += dx;
                        selectedPoint->y += dy;
                    }
                }
            }

            //Clear screen
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);

            //Draw 
            ch.calculate();
            drawConvexHull(gRenderer, ch);

            //Update screen
            SDL_RenderPresent(gRenderer);
        }
    }
    //Free resources and close SDL
    close();

    return 0;
}