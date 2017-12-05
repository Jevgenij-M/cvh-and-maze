#pragma once

#include <cmath>
#include <vector>
#include <algorithm>

#include "common.h"

struct Point
{
    int x, y;
    bool operator==(const Point & p) { return x == p.x && y == p.y; }
    bool operator!=(const Point & p) { return !operator==(p); }

    static double distance(const Point & p1, const Point & p2)
    {
        int dx = p1.x - p2.x;
        int dy = p1.y - p2.y;
        return std::sqrt(dx*dx + dy*dy);
    }
};

class ConvexHull
{
    std::vector<Point> m_points;
    std::vector<Point> m_convexHull;
    std::vector<Point> m_interior;

public:
    ConvexHull(int n);
    void reset(int n);
    bool toLeft(const Point & c1, const Point & c2, const Point & c3);
    void calculate();
    void clear();

    const std::vector<Point>& getPoints()     const;
    const std::vector<Point>& getConvexHull() const;
    const std::vector<Point>& getInterior()   const;

    Point * getPoint(int x, int y, int distance);
};