#pragma once

#include <SDL.h>

#include "common.h"
#include "Maze.h"

namespace SDLMazeDrawer
{
    void DrawWalker(SDL_Renderer * renderer, int i, int j)
    {
        int posI = i * CELL_SIZE;
        int posJ = j * CELL_SIZE;
        int hm = (CELL_SIZE - PATH_WIDTH) / 2; //half margin

            SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
            SDL_Rect r { posJ + hm, posI + hm, CELL_SIZE - 2 * hm, CELL_SIZE - 2 * hm };
            SDL_RenderFillRect(renderer, &r);
    }
    void DrawCell(SDL_Renderer * renderer, int i, int j, int d)
    {
        int posI = i * CELL_SIZE;
        int posJ = j * CELL_SIZE;
        int hm = (CELL_SIZE - PATH_WIDTH) / 2; // half margin

        if (d == Maze::Direction::restricted)
        {
            //SDL_SetRenderDrawColor(gRenderer, 0x00, 0x55, 0x55, 0xFF);
            SDL_Rect r{ posJ + hm, posI + hm, CELL_SIZE - 2 * hm, CELL_SIZE - 2 * hm };
            SDL_RenderFillRect(renderer, &r);
            return;
        }

        if (d & Maze::Direction::right)
        {
            SDL_Rect r{ posJ + hm, posI + hm, CELL_SIZE - hm, CELL_SIZE - 2 * hm };
            SDL_RenderFillRect(renderer, &r);
        }
        if (d & Maze::Direction::up)
        {
            SDL_Rect r{ posJ + hm, posI, CELL_SIZE - 2 * hm, CELL_SIZE - hm };
            SDL_RenderFillRect(renderer, &r);
        }
        if (d & Maze::Direction::left)
        {
            SDL_Rect r{ posJ, posI + hm, CELL_SIZE - hm, CELL_SIZE - 2 * hm };
            SDL_RenderFillRect(renderer, &r);
        }
        if (d & Maze::Direction::down)
        {
            SDL_Rect r{ posJ + hm, posI + hm, CELL_SIZE - 2 * hm, CELL_SIZE - hm };
            SDL_RenderFillRect(renderer, &r);
        }
    }
    void DrawMaze(SDL_Renderer * renderer, const Maze::Maze& maze)
    {
        //Clear screen
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderClear(renderer);

        //Set Drawing Color
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

        int width = maze[0].size() - 2;
        int height = maze.size() - 2;

        for (int row = 1; row < maze.size() - 1; row++)
            for (int col = 1; col < maze[0].size() - 1; col++)
                DrawCell(renderer, row, col, maze[row][col]);
    }
}