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
    int  tankId;       // the Id of the tank who fired this missile
    k3d::vec2 pos;          // position within the level
    k3d::vec2 velocity;     // direction travelling in
    float     speed;        // magnitude
    bool      exploding;    // set by model
    bool      exploded;     // set by view
    k3d::vec2 collisionBox;

public:
    Missile(int tankId, k3d::vec2 pos, k3d::vec2 velocity, float speed);

    int getTankId() const;
    const k3d::vec2 & getPos() const;
    const k3d::vec2 & getVelocity() const;
    float getSpeed() const;
    bool getExploding() const;
    bool getExploded() const;
    k3d::vec2 getCollisionBox() const;

    void setPos(const k3d::vec2 & pos);
    void setExploding(bool exploding);
    void setExploded(bool exploded);
};

#endif // _MISSILE_H
