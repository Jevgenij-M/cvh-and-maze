#pragma once

namespace Maze
{
    enum Direction
    { 
        none       = 0,
        right      = 1,
        up         = 2,
        left       = 4,
        down       = 8,
        restricted = 16 
    };

    Direction FirstDirection(const int d)
    {
        if (d == 0)                     return Direction::none;
        if (d & Direction::restricted)  return Direction::restricted;

        if (d & Direction::right)        return Direction::right;
        if (d & Direction::up)           return Direction::up;
        if (d & Direction::left)         return Direction::left;
        if (d & Direction::down)         return Direction::down;
    }

    Direction NextDirection(const Direction d)
    {
        if (d == Direction::restricted)  return Direction::restricted;
        if (d == Direction::none)        return Direction::right;
        if (d == Direction::right)       return Direction::up;
        if (d == Direction::up)          return Direction::left;
        if (d == Direction::left)        return Direction::down;
        if (d == Direction::down)        return Direction::restricted;
    }
}