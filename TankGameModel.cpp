/**
 * Filename: TankGameModel.cpp
 * Author: Karshan Sharma <sharma34@illinois.edu>
 * Created: Fri Nov 25 08:34:30 CST 2011
 *
 * Description:
 * Implementation of the TankGameModel class
 */

#include "TankGameModel.h"

/**
 * TankGameModel default constructor
 * Sets up an empty TankGameModel with the player's tank at 0, 0 facing in +x
 */
TankGameModel::TankGameModel() : player(k3d::vec2(0.0, 0.0), k3d::vec2(1.0, 0.0), k3d::vec2(1.0, 0.0))
{
}

/**
 * getPlayer()
 * returns a constant reference to the Tank Object associated with the player's
 * tank in the game.
 */
const Tank & TankGameModel::getPlayer() const
{
    return player;
}

/**
 * getEnemies()
 * returns a constant reference to a vector of Tank objects that represent the
 * enemy tanks currently in the game.
 */
const vector<Tank> & TankGameModel::getEnemies() const
{
    return enemies;
}

/**
 * getMissiles()
 * returns a constant reference to a vector of Missile objects that represent
 * all the missiles currently in the game.
 */
const vector<Missile> & TankGameModel::getMissiles() const
{
    return missiles;
}

/**
 * getLevel()
 * returns a constant reference to the current Level object.
 */
const Level & TankGameModel::getLevel() const
{
    return level;
}

// Experimental
bool TankGameModel::loadTestLevel()
{
   return level.loadFromFile("/sdcard/tanks/simple.lvl");
}
