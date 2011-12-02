/**
 * Filename: Missile.cpp
 * Author: Karshan Sharma <sharma34@illinois.edu>
 * Created: Fri Nov 25 10:12:39 CST 2011
 *
 * Description:
 * Implementation of the Missile class.
 */

#include "Missile.h"

// TODO function headers (comments)

Missile::Missile(int tankId, k3d::vec2 pos, k3d::vec2 velocity, float speed) :
    tankId(tankId), pos(pos), velocity(velocity), speed(speed), exploding(false),
    exploded(false), collisionBox(0.05, 0.01) {}

int Missile::getTankId() const
{
    return tankId;
}

const k3d::vec2 & Missile::getPos() const
{
    return pos;
}

const k3d::vec2 & Missile::getVelocity() const
{
    return velocity;
}

float Missile::getSpeed() const
{
    return speed;
}

bool Missile::getExploding() const
{
    return exploding;
}

bool Missile::getExploded() const
{
    return exploded;
}

k3d::vec2 Missile::getCollisionBox() const
{
    return collisionBox;
}

void Missile::setPos(const k3d::vec2 & pos)
{
    this->pos = pos;
}

void Missile::setExploding(bool exploding)
{
    this->exploding = exploding;
}

void Missile::setExploded(bool exploded)
{
    this->exploded = exploded;
}
