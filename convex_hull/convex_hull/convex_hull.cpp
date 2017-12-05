#include "convex_hull.h"

ConvexHull::ConvexHull(int n)
{
    reset(n);
}

void ConvexHull::reset(int n)
{
    m_points.clear();
    m_convexHull.clear();

    for (int i = 0; i < n; i++)
    {
        double a = 2 * pi * rand() / RAND_MAX;
        int r = rand() % (int)(SCREEN_HEIGHT / 4) + (SCREEN_HEIGHT / 5);
        int x = r*std::cos(a) + SCREEN_WIDTH / 2;
        int y = r*std::sin(a) + SCREEN_HEIGHT / 2;

        bool found = false;
        for (const auto & p : m_points)
        {
            if (p.x == x && p.y == y)
            {
                i--;
                found = true;
            }
        }

        if (!found) m_points.push_back(Point{ x, y });
    }

    std::sort(m_points.begin(), m_points.end(),
        [](const Point & c1, const Point & c2) { return c1.x < c2.x; });
}

bool ConvexHull::toLeft(const Point & c1, const Point & c2, const Point & c3)
{
    // [ c1.x, c1.y, 1;
    //   c2.x, c2.y, 1;
    //   c3.x, c3.y, 1 ]

    return (c1.x*c2.y + c1.y*c3.x + c2.x*c3.y - (c2.y*c3.x + c1.y*c2.x + c1.x*c3.y)) > 0;
}

void ConvexHull::calculate()
{
    m_convexHull.clear();
    m_interior.clear();
    std::vector<Point> P = m_points;
    std::vector<Point> H;

    auto refMin = std::min_element(P.begin(), P.end(), [](Point & c1, Point & c2) { return c1.x < c2.x; });
    Point min = *refMin;
    P.erase(refMin);
    std::sort(P.begin(), P.end(), [this, min](Point & c1, Point & c2) { return toLeft(min, c1, c2); });
    auto refMin2 = P.begin();
    Point min2 = *refMin2;
    P.erase(refMin2);
    std::reverse(P.begin(), P.end());

    H.push_back(min);
    H.push_back(min2);

    while (!P.empty())
    {
        if ((H.size() < 2) || toLeft(H[H.size() - 2], H[H.size() - 1], P.back()))
        {
            H.push_back(P.back());
            P.pop_back();
        }
        else
        {
            m_interior.push_back(H.back());
            H.pop_back();
        }
    }

    H.push_back(min);
    m_convexHull = H;
}

void ConvexHull::clear()
{
    m_points.clear();
}

const std::vector<Point>& ConvexHull::getPoints() const 
{ 
    return m_points; 
}

const std::vector<Point>& ConvexHull::getConvexHull() const
{
    return m_convexHull; 
}

const std::vector<Point>& ConvexHull::getInterior() const 
{ 
    return m_interior; 
}

Point * ConvexHull::getPoint(int x, int y, int distance)
{
    for (auto & point : m_points)
        if (Point::distance(Point{ x, y }, point) <= distance)
        {
            return &point;
        }

    return nullptr;
}