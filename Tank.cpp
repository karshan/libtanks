/**
 * Filename: Tank.cpp
 * Author: Karshan Sharma <sharma34@illinois.edu>
 * Created: Fri Nov 25 08:59:22 CST 2011
 *
 * Description:
 * Implementation of the Tank class. see Tank.h for more information on the
 * class as a whole.
 */

#include "Tank.h"

int Tank::nextId = 0; // This is used to figure out the next id to give a tank

/**
 * Tank parametrized constructor
 * sets up the Tank from the params you passed in and gives it a unique id
 */
Tank::Tank(k3d::vec2 pos, k3d::vec2 velocity, k3d::vec2 aim) :
    pos(pos), velocity(velocity), aim(aim), speed(0.0) { id = Tank::nextId++; }

/**
 * getPos()
 * returns a reference to a vec2 that tells you where this Tank is within
 * the level.
 */
const k3d::vec2 & Tank::getPos() const
{
    return pos;
}

/**
 * getPos()
 * returns a reference to a vec2 that tells you in which direction this Tank
 * is facing (magnitude of this vec2 is irrelevant), it is illegal for this
 * vec2 to be (0.0, 0.0).
 */
const k3d::vec2 & Tank::getVelocity() const
{
    return velocity;
}

/**
 * getSpeed()
 * returns a the current speed of the Tank
 */
float Tank::getSpeed() const
{
    return speed;
}

/**
 * getAim()
 * returns a reference to a vec2 that tells you where this Tank's turret is
 * facing (magnitude of this vec2 is irrelevant), it is illegal for this vec2
 * to be (0.0, 0.0)
 */
const k3d::vec2 & Tank::getAim() const
{
    return aim;
}
