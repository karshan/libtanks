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
 * Tank default constructor
 * sets up a dead Tank with a unique id
 */
Tank::Tank() : pos(0.0, 0.0), velocity(1.0, 0.0), speed(0.0), aim(1.0, 0.0),
    isDead(true)
{
    id = Tank::nextId++;
}

/**
 * getIsDead()
 * returns the isDead variable (its up to you to set it and clear it appropriately
 */
bool Tank::getIsDead() const
{
    return isDead;
}

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
 * getVelocity()
 * returns a reference to a vec2 that tells you in which direction this Tank
 * is facing (magnitude of this vec2 is irrelevant, but ALWAYS = 1.0)
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

void Tank::setPos(const k3d::vec2 & pos)
{
    this->pos = pos;
}

void Tank::setVelocity(const k3d::vec2 & velocity)
{
    this->velocity = velocity;
    this->velocity.normalize();
}

void Tank::setSpeed(float speed)
{
    this->speed = speed;
}

void Tank::setAim(const k3d::vec2 & aim)
{
    this->aim = aim;
    this->aim.normalize();
}

void Tank::setIsDead(bool isDead)
{
    this->isDead = isDead;
}
