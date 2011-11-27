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

private:
    Level           level;
    Tank            player;
    vector<Tank>    enemies;
    vector<Missile> missiles;

public:
    TankGameModel();

    const Tank & getPlayer() const;
    const vector<Tank> & getEnemies() const;
    const vector<Missile> & getMissiles() const;
    const Level & getLevel() const;

    // Experimental
    bool loadTestLevel() __attribute__((warn_unused_result));

};

#endif // _TANKGAMEMODEL_H
