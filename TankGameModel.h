#ifndef _TANKGAMEMODEL_H
#define _TANKGAMEMODEL_H

/**
 * Filename: TankGameModel.h
 * Author: Karshan Sharma <sharma34@illinois.edu>
 * Created: Fri Nov 25 08:24:41 CST 2011
 *
 * Description:
 * This class has all the game state. It is the Model as is in the MVC design
 * pattern.
 */

#include <vector>

#include "Level.h"
#include "Tank.h"
#include "Missile.h"

using std::vector;

class TankGameModel {

    friend class TankGameController;

private:
    Level           level;
    Tank            player;
    vector<Tank>    enemies;
    vector<Missile> missiles;

    void fireMissile();

    // helpers
    void moveTank(Tank & tank);
    void moveMissile(Missile & missile);
    bool collideWithLevel(k3d::vec2 & pos, const k3d::vec2 & velocity, const k3d::vec2 & box);

public:
    TankGameModel();

    void step();

    const Tank & getPlayer() const;
    const vector<Tank> & getEnemies() const;
    vector<Missile> & getMissiles(); // this is not const since views read missiles and change them based on exploding animation
    const Level & getLevel() const;

    bool loadLevel(const char *levelFname) __attribute__((warn_unused_result));

};

#endif // _TANKGAMEMODEL_H
