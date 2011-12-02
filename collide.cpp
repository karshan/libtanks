#include <cmath>

#include "collide.h"

// returns true if a,b,c points are in counterclockwise order
static bool ccw(const k3d::vec2 & a, const k3d::vec2 & b, const k3d::vec2 & c)
{
    return (c.y - a.y)*(b.x - a.x) > (b.y - a.y)*(c.x - a.x);
}

// returns true if 2 line segments ab and cd intersect
static bool intersect(const k3d::vec2 & a, const k3d::vec2 & b,
    const k3d::vec2 & c, const k3d::vec2 & d)
{
    return ccw(a, c, d) != ccw(b, c, d) && ccw(a, b, c) != ccw(a, b, d);
}

static float dist_point_to_line(const k3d::vec2 & p, const k3d::vec2 & a, const k3d::vec2 & b)
{
    const float epsilon = 0.01;
    return (fabs(((b.x - a.x)*(a.y - p.y)) - ((a.x - p.x)*(b.y - a.y)))/
                sqrtf((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y))) + epsilon;
}

static float max(float a, float b)
{
    return a > b ? a : b;
}

// Collision detection for rotated rectangles
k3d::vec2 collide(k3d::vec2 pos1, const k3d::vec2 & hw1, const k3d::vec2 & v1,
                  const k3d::vec2 & pos2, const k3d::vec2 & hw2, const k3d::vec2 & v2, bool & collided)
{
    k3d::vec2 vn1(-v1.y, v1.x);
    k3d::vec2 a1((pos1 + (hw1.x*v1)) - (hw1.y*vn1));
    k3d::vec2 b1((pos1 + (hw1.x*v1)) + (hw1.y*vn1));
    k3d::vec2 c1((pos1 - (hw1.x*v1)) + (hw1.y*vn1));
    k3d::vec2 d1((pos1 - (hw1.x*v1)) - (hw1.y*vn1));

    k3d::vec2 vn2(-v2.y, v2.x);
    k3d::vec2 a2((pos2 + (hw2.x*v2)) - (hw2.y*vn2));
    k3d::vec2 b2((pos2 + (hw2.x*v2)) + (hw2.y*vn2));
    k3d::vec2 c2((pos2 - (hw2.x*v2)) + (hw2.y*vn2));
    k3d::vec2 d2((pos2 - (hw2.x*v2)) - (hw2.y*vn2));

    collided = true;

    if (intersect(a1, b1, a2, b2)) {
        // TODO check if it is enough to go back that distance for the 1st 2 cases (corners) here
        if (intersect(a1, b1, b2, c2)) { //corner
            return pos1 + dist_point_to_line(b2, a1, b1)*((v2 + vn2).normalize());
        }
        if (intersect(a1, b1, a2, d2)) { //corner
            return pos1 + dist_point_to_line(a2, a1, b1)*((v2 - vn2).normalize());
        }
        if (intersect(b1, c1, a2, b2)) {
            return pos1 + dist_point_to_line(b1, a2, b2)*v2;
        }
        if (intersect(a1, d1, a2, b2)) {
            return pos1 + dist_point_to_line(a1, a2, b2)*v2;
        }
        if (intersect(b1, c1, a2, d2)) {
            //return pos1 + a2 - b1; // MAYBE THIS IS BETTER ?
            // FIXME max is actually incorrect here, it should be a weighted sum based on where a2b2 intersects a1b1
            return pos1 - max(dist_point_to_line(a1, a2, d2), dist_point_to_line(b1, a2, d2))*vn2;
        }
        if (intersect(a1, d1, b2, c2)) {
            // FIXME max is actually incorrect here, it should be a weighted sum based on where a2b2 intersects a1b1
            return pos1 + max(dist_point_to_line(a1, b2, c2), dist_point_to_line(b1, b2, c2))*vn2;
        }
    }

    if (intersect(a1, b1, b2, c2)) {
        // a1,b1 and a2,b2 already covered
        // TODO check if it is enough to go back that distance for the 1st case here (corner)
        if (intersect(a1, b1, c2, d2)) { //corner
            return pos1 + dist_point_to_line(c2, a1, b1)*((vn2-v2).normalize());
        }
        if (intersect(b1, c1, b2, c2)) {
            return pos1 + dist_point_to_line(b1, b2, c2)*vn2;
        }
        if (intersect(a1, d1, b2, c2)) {
            return pos1 + dist_point_to_line(a1, b2, c2)*vn2;
        }
        if (intersect(b1, c1, a2, b2)) {
            // FIXME max is actually incorrect here, it should be a weighted sum based on where b2c2 intersects a1b1
            return pos1 + max(dist_point_to_line(b1, a2, b2), dist_point_to_line(a1, a2, b2))*v2;
        }
        if (intersect(a1, d1, c2, d2)) {
            // FIXME max is actually incorrect here, it should be a weighted sum based on where b2c2 intersects a1b1
            return pos1 - max(dist_point_to_line(b1, c2, d2), dist_point_to_line(a1, c2, d2))*v2;
        }
    }

    if (intersect(a1, b1, c2, d2)) {
        // a1,b1 and b2,c2 already covered
        // TODO check if it is enough to go back that distance for the 1st case here (corner)
        if (intersect(a1, b1, a2, d2)) {
            return pos1 + dist_point_to_line(d2, a1, b1)*((-1.0*v2)-vn2);
        }
        if (intersect(b1, c1, c2, d2)) {
            return pos1 - dist_point_to_line(b1, c2, d2)*v2;
        }
        if (intersect(a1, d1, c2, d2)) {
            return pos1 - dist_point_to_line(a1, c2, d2)*v2;
        }
        if (intersect(b1, c1, b2, c2)) {
            // FIXME see above fixme's
            return pos1 + max(dist_point_to_line(b1, b2, c2), dist_point_to_line(a1, b2, c2))*vn2;
        }
        if (intersect(a1, d1, a2, d2)) {
            // FIXME see above fixme's
            return pos1 - max(dist_point_to_line(a1, d2, a2), dist_point_to_line(b1, d2, a2))*vn2;
        }
    }

    if (intersect(a1, b1, d2, a2)) {
        // a1,b1 and c2,d2 already covered and a1,b1 and a2,b2 also already covered
        if (intersect(b1, c1, d2, a2)) {
            return pos1 - dist_point_to_line(b1, d2, a2)*vn2;
        }
        if (intersect(a1, d1, d2, a2)) {
            return pos1 - dist_point_to_line(a1, d2, a2)*vn2;
        }
        if (intersect(b1, c1, c2, d2)) {
            // FIXME see above fixme's
            return pos1 - max(dist_point_to_line(b1, c2, d2), dist_point_to_line(a1, c2, d2))*v2;
        }
        if (intersect(a1, d1, a2, b2)) {
            // FIXME see above fixme's
            return pos1 + max(dist_point_to_line(a1, a2, b2), dist_point_to_line(b1, a2, b2))*v2;
        }
    }

    if (intersect(b1, c1, a2, b2)) {
        return pos1 + dist_point_to_line(b1, a2, b2)*v2;
    }
    if (intersect(b1, c1, b2, c2)) {
        return pos1 + dist_point_to_line(b1, b2, c2)*vn2;
    }
    if (intersect(b1, c1, c2, d2)) {
        return pos1 - dist_point_to_line(b1, c2, d2)*v2;
    }
    if (intersect(b1, c1, d2, a2)) {
        return pos1 - dist_point_to_line(b1, d2, a2)*vn2;
    }

    if (intersect(a1, d1, a2, b2)) {
        return pos1 + dist_point_to_line(a1, a2, b2)*v2;
    }
    if (intersect(a1, d1, b2, c2)) {
        return pos1 + dist_point_to_line(a1, b2, c2)*vn2;
    }
    if (intersect(a1, d1, c2, d2)) {
        return pos1 - dist_point_to_line(a1, c2, d2)*v2;
    }
    if (intersect(a1, d1, d2, a2)) {
        return pos1 - dist_point_to_line(a1, d2, a2)*vn2;
    }

    collided = false;
    return pos1;
}
