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

Missile::Missile(uint32_t tankId, k3d::vec2 pos, k3d::vec2 velocity, float speed) :
    tankId(tankId), pos(pos), velocity(velocity), speed(speed) {}

uint32_t Missile::getTankId() const
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

void Missile::setPos(const k3d::vec2 & pos)
{
    this->pos = pos;
}
