#ifndef _TANK_H
#define _TANK_H

/**
 * Filename: Tank.h
 * Author: Karshan Sharma <sharma34@illinois.edu>
 * Created: Fri Nov 25 08:45:22 CST 2011
 *
 * Description:
 * The representation of a Tank in the game, part of the Model (MVC).
 */

#include <libk3d/k3d.h>

class Tank {

private:
    static int nextId;

    int  id;
    k3d::vec2 pos;      // position within the level
    k3d::vec2 velocity; // facing direction
    float     speed;    // (magnitude)
    k3d::vec2 aim;      // turret direction

public:
    Tank(k3d::vec2 pos, k3d::vec2 velocity, k3d::vec2 aim);

    const k3d::vec2 & getPos() const;
    const k3d::vec2 & getVelocity() const;
    float getSpeed() const;
    const k3d::vec2 & getAim() const;

};

#endif // _TANK_H
