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
    bool isDead;

public:
    Tank();

    bool getIsDead() const;
    const k3d::vec2 & getPos() const;
    const k3d::vec2 & getVelocity() const;
    float getSpeed() const;
    const k3d::vec2 & getAim() const;
    int getId() const;

    void setPos(const k3d::vec2 & pos);
    void setVelocity(const k3d::vec2 & velocity);
    void setSpeed(float speed);
    void setAim(const k3d::vec2 & aim);
    void setIsDead(bool isDead);

};

#endif // _TANK_H
