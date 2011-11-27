#ifndef _MISSILE_H
#define _MISSILE_H

/**
 * Filename: Missile.h
 * Author: Karshan Sharma <sharma34@illinois.edu>
 * Created: Fri Nov 25 09:15:12 CST 2011
 *
 * Description:
 * The representation of a Missile in the game, part of the Model (MVC).
 */

#include <libk3d/k3d.h>

class Missile {

private:
    uint32_t  tankId;   // the Id of the tank who fired this missile
    k3d::vec2 pos;      // position within the level
    k3d::vec2 velocity; // direction travelling in
    float     speed;    // magnitude

public:
    Missile(uint32_t tankId, k3d::vec2 pos, k3d::vec2 velocity, float speed);

    uint32_t getTankId() const;
    const k3d::vec2 & getPos() const;
    const k3d::vec2 & getVelocity() const;
    float getSpeed() const;

};

#endif // _MISSILE_H
