#pragma once

#include <vector>
#include <queue>
#include <utility>

namespace Maze
{
    using  Maze      = std::vector<std::vector<int>>;
    struct Point     { int i; int j;  };
    struct Cell      { int i; int j; int d;  };
    enum   Direction { none = 0, right = 1, up = 2, left = 4, down = 8, restricted = 16 };

    namespace
    {
        Maze BlankMaze(const Point & size)
        {
            Maze maze;
            maze.resize(size.i);
            for (auto & row : maze) row.resize(size.j);

            for (int c = 0; c < size.j; c++)
            {
                maze[0][c]        = Direction::restricted;
                maze[size.i-1][c] = Direction::restricted;
            }

            for (int r = 0; r < maze[0].size(); r++)
            {
                maze[r][0]        = Direction::restricted;
                maze[r][size.j-1] = Direction::restricted;
            }

            return maze;
        }
        std::vector<Direction> AvailableDirections(const Maze & maze, const Cell & cell)
        {
            std::vector<Direction> result;

            if (maze[cell.i - 1][cell.j] == Direction::none)    result.push_back(Direction::up);
            if (maze[cell.i][cell.j - 1] == Direction::none)    result.push_back(Direction::left);
            if (maze[cell.i + 1][cell.j] == Direction::none)    result.push_back(Direction::down);
            if (maze[cell.i][cell.j + 1] == Direction::none)    result.push_back(Direction::right);

            return result;
        }
        Direction RandomDirection(const Maze & maze, const Cell & cell)
        {
            const auto & directions = AvailableDirections(maze, cell);

            if (directions.size())    return directions[rand() % directions.size()];
            else                      return Direction::restricted;
        }
        Cell NextCell(const Cell & cell, Direction dir)
        {
            if (dir == Direction::left)    return Cell{ cell.i, cell.j - 1, Direction::right };
            if (dir == Direction::right)   return Cell{ cell.i, cell.j + 1, Direction::left };
            if (dir == Direction::up)      return Cell{ cell.i - 1, cell.j, Direction::down };
            if (dir == Direction::down)    return Cell{ cell.i + 1, cell.j, Direction::up };

            throw std::logic_error("this place should not be reached");
        }
    }

    Point DirectionToOffset(const Direction d)
    {
        if (d & Direction::right)    return Point {  0,  1 };
        if (d & Direction::up)       return Point { -1,  0 };
        if (d & Direction::left)     return Point {  0, -1 };
        if (d & Direction::down)     return Point {  1,  0 };

        return Point{ 0, 0 };
    }

    Maze GenerateDFSMaze()
    {
        Cell  start {  5,  1, Direction::left  };
        Cell  end   { 18, 23, Direction::right };
        Point size  { 25, 25 };

        Maze maze = BlankMaze(size);
        
        std::vector<Cell> path;
        path.push_back(start);

        while (path.size())
        {
            Cell c = path.back();
            maze[c.i][c.j] |= c.d;

            auto newDirection = RandomDirection(maze, c);
            if (newDirection != Direction::restricted)
            {
                maze[c.i][c.j] |= newDirection;
                path.push_back(NextCell(c, newDirection));
            }
            else
                path.pop_back();
        }

        maze[end.i][end.j] |= end.d;
        return maze;
    }
}
