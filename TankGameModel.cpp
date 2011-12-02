/**
 * Filename: TankGameModel.cpp
 * Author: Karshan Sharma <sharma34@illinois.edu>
 * Created: Fri Nov 25 08:34:30 CST 2011
 *
 * Description:
 * Implementation of the TankGameModel class
 */

#include <iostream> // TODO remove

#include <cstdlib>
#include <cmath>

#include "TankGameModel.h"

/**
 * TankGameModel default constructor
 * Sets up an empty TankGameModel
 */
TankGameModel::TankGameModel()
{
}

/**
 * getPlayer()
 * returns a constant reference to the Tank Object associated with the player's
 * tank in the game.
 */
const Tank & TankGameModel::getPlayer() const
{
    return player;
}

/**
 * getEnemies()
 * returns a constant reference to a vector of Tank objects that represent the
 * enemy tanks currently in the game.
 */
const vector<Tank> & TankGameModel::getEnemies() const
{
    return enemies;
}

/**
 * getMissiles()
 * returns a constant reference to a vector of Missile objects that represent
 * all the missiles currently in the game.
 */
const vector<Missile> & TankGameModel::getMissiles() const
{
    return missiles;
}

/**
 * getLevel()
 * returns a constant reference to the current Level object.
 */
const Level & TankGameModel::getLevel() const
{
    return level;
}

// expects stdlib's PNRG to be called before
// aka call srand() sometime before (once)
bool TankGameModel::loadLevel(const char *levelFname)
{
    if (level.loadFromFile(levelFname) == false)
        return false;

    player.setSpeed(0.0);
    player.setVelocity(k3d::vec2(1.0, 0.0));
    player.setAim(k3d::vec2(1.0, 0.0));
    // Pick player start position
    // XXX theres probably a better way to do this
    const bool ** map = level.getMap();
    while (1) {
        int x = rand() % level.getWidth();
        int y = rand() % level.getHeight();
        if (map[x][y] == false) {
            player.setPos(k3d::vec2(x, y));
            player.setIsDead(false);
            return true;
        }
    }
}

// returns true if a,b,c points are in counterclockwise order
bool ccw(const k3d::vec2 & a, const k3d::vec2 & b, const k3d::vec2 & c)
{
    return (c.y - a.y)*(b.x - a.x) > (b.y - a.y)*(c.x - a.x);
}

// returns true if 2 line segments ab and cd intersect
bool intersect(const k3d::vec2 & a, const k3d::vec2 & b,
    const k3d::vec2 & c, const k3d::vec2 & d)
{
    return ccw(a, c, d) != ccw(b, c, d) && ccw(a, b, c) != ccw(a, b, d);
}

float dist_point_to_line(const k3d::vec2 & p, const k3d::vec2 & a, const k3d::vec2 & b)
{
    const float epsilon = 0.01;
    return (fabs(((b.x - a.x)*(a.y - p.y)) - ((a.x - p.x)*(b.y - a.y)))/
                sqrtf((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y))) + epsilon;
}

float max(float a, float b)
{
    return (a+b)/2.0;
//    return a > b ? a : b;
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

bool TankGameModel::collideWithLevel(k3d::vec2 & pos, const k3d::vec2 & velocity, const k3d::vec2 & box)
{
    const bool ** map = level.getMap();
    int x = int(pos.x + 0.5);
    int y = int(pos.y + 0.5);
    bool collided = false;
    bool check; // temporary...

    k3d::vec2 wallbox(0.5, 0.5);
    k3d::vec2 wallvelocity(1.0, 0.0);
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (x + i < 0 || x + i >= level.getWidth() ||
                y + j < 0 || y + j >= level.getHeight()) {
                continue;
            }
            if (map[x + i][y + j]) {
                pos = collide(pos, box, velocity, k3d::vec2(x + i, y + j), wallbox, wallvelocity, check);
                collided |= check;
            }
        }
    }
    return collided;
}

void TankGameModel::moveTank(Tank & tank)
{
    const k3d::vec2 & pos = tank.getPos();
    float speed = tank.getSpeed();
    const k3d::vec2 & velocity = tank.getVelocity();

    k3d::vec2 tankbox(0.3, 0.15); // width/2 by height/2 of collision box for tank
    k3d::vec2 tmpPos(pos);
    collideWithLevel(tmpPos, velocity, tankbox);  // get into a consistent state
    tank.setPos(tmpPos);

    k3d::vec2 newPos[3];
    newPos[0] = pos + speed * velocity;
    newPos[1] = pos + speed * k3d::vec2(velocity.x, 0.0);
    newPos[2] = pos + speed * k3d::vec2(0.0, velocity.y);

    for (int ind = 0; ind < 3; ind++) {
        tmpPos = newPos[ind];
        if (!collideWithLevel(tmpPos, velocity, tankbox)) {
            tank.setPos(newPos[ind]);
            return;
        }
    }
}

/**
 * step()
 * move everything one step
 */
void TankGameModel::step()
{
    if (player.getIsDead() == false) {
        moveTank(player);
    }
}
