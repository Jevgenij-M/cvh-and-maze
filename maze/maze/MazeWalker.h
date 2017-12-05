#pragma once

#include "Maze.h"

namespace Maze
{
    class MazeWalker
    {
    public:
        MazeWalker(const Maze & maze, int i, int j)
            : m_maze(maze)
            , m_posI(i)
            , m_posJ(j)
        { }

        bool Move(const Direction d)
        {
            if (d & m_maze[m_posI][m_posJ])
            {
                Point offset = DirectionToOffset(d);
                m_posI += offset.i;
                m_posJ += offset.j;

                return true;
            }
            else
            {
                return false;
            }
        }

        const Maze & m_maze;
        int m_posI, m_posJ;
    };
}