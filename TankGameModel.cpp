/**
 * Filename: TankGameModel.cpp
 * Author: Karshan Sharma <sharma34@illinois.edu>
 * Created: Fri Nov 25 08:34:30 CST 2011
 *
 * Description:
 * Implementation of the TankGameModel class
 */

#include <iostream> // TODO remove

#include <cstdlib>
#include <cmath>

#include "TankGameModel.h"
#include "collide.h"

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

bool TankGameModel::collideWithLevel(k3d::vec2 & pos, const k3d::vec2 & velocity, const k3d::vec2 & box)
{
    const bool ** map = level.getMap();
    int x = int(pos.x + 0.5);
    int y = int(pos.y + 0.5);
    bool collided = false;
    bool check; // temporary...

    k3d::vec2 wallbox(0.5, 0.5);
    k3d::vec2 wallvelocity(1.0, 0.0);
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (x + i < 0 || x + i >= level.getWidth() ||
                y + j < 0 || y + j >= level.getHeight()) {
                continue;
            }
            if (map[x + i][y + j]) {
                pos = collide(pos, box, velocity, k3d::vec2(x + i, y + j), wallbox, wallvelocity, check);
                collided |= check;
            }
        }
    }
    return collided;
}

void TankGameModel::moveTank(Tank & tank)
{
    const k3d::vec2 & pos = tank.getPos();
    float speed = tank.getSpeed();
    const k3d::vec2 & velocity = tank.getVelocity();

    k3d::vec2 tankbox(0.3, 0.15); // width/2 by height/2 of collision box for tank
    k3d::vec2 tmpPos(pos);
    collideWithLevel(tmpPos, velocity, tankbox);  // get into a consistent state
    tank.setPos(tmpPos);

    k3d::vec2 newPos[3];
    newPos[0] = pos + speed * velocity;
    newPos[1] = pos + speed * k3d::vec2(velocity.x, 0.0);
    newPos[2] = pos + speed * k3d::vec2(0.0, velocity.y);

    for (int ind = 0; ind < 3; ind++) {
        tmpPos = newPos[ind];
        if (!collideWithLevel(tmpPos, velocity, tankbox)) {
            tank.setPos(newPos[ind]);
            return;
        }
    }
}

void TankGameModel::moveMissile(Missile & missile)
{
    const k3d::vec2 & pos = missile.getPos();
    missile.setPos(pos + missile.getSpeed()*missile.getVelocity());
}

void TankGameModel::fireMissile()
{
    missiles.push_back(Missile(player.getId(), player.getPos() + 0.3*player.getAim(), player.getAim(), 0.1));
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
    for (unsigned i = 0; i < missiles.size(); i++)
        moveMissile(missiles[i]);
}
