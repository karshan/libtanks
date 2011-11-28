/**
 * Filename: TankGameModel.cpp
 * Author: Karshan Sharma <sharma34@illinois.edu>
 * Created: Fri Nov 25 08:34:30 CST 2011
 *
 * Description:
 * Implementation of the TankGameModel class
 */

#include <cstdlib>

#include "TankGameModel.h"

/**
 * TankGameModel default constructor
 * Sets up an empty TankGameModel
 */
TankGameModel::TankGameModel()
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

// expects stdlib's PNRG to be called before
// aka call srand() sometime before (once)
bool TankGameModel::loadLevel(const char *levelFname)
{
    if (level.loadFromFile(levelFname) == false)
        return false;

    player.setSpeed(0.0);
    player.setVelocity(k3d::vec2(1.0, 0.0));
    player.setAim(k3d::vec2(1.0, 0.0));
    // Pick player start position
    // XXX theres probably a better way to do this
    const bool ** map = level.getMap();
    while (1) {
        int x = rand() % level.getWidth();
        int y = rand() % level.getHeight();
        if (map[x][y] == false) {
            player.setPos(k3d::vec2(x, y));
            player.setIsDead(false);
            return true;
        }
    }
}

void TankGameModel::moveTank(Tank & tank)
{
    const k3d::vec2 & pos = tank.getPos();
    float speed = tank.getSpeed();
    const k3d::vec2 & velocity = tank.getVelocity();
    const bool ** map = level.getMap();

    k3d::vec2 newPos = pos + speed * velocity;
    if (map[int(newPos.x + 0.5)][int(newPos.y + 0.5)] == false) {
        tank.setPos(newPos);
    }
}

/**
 * step()
 * move everything one step
 */
void TankGameModel::step()
{
    if (player.getIsDead() == false) {
        moveTank(player);
    }
}
