/**
 * Filename: TankGameView.cpp
 * Author: Karshan Sharma <sharma34@illinois.edu>
 * Created: Fri Nov 25 10:36:10 CST 2011
 *
 * Description:
 * Implementation of the TankGameView class.
 */

#include <vector>
#include <libk3d/k3d.h>

#include "TankGameView.h"

using std::vector;

using k3d::gl;

/**
 * TankGameView parameterized constructor
 * sets up a TankGameView associated with the TankGameModel passed in.
 */
TankGameView::TankGameView(TankGameModel * model) : model(model) {}

/**
 * loadModels()
 * ModelFname's are path's to wavefront obj files from which to load the respective
 * models. (remember k3d::model has limited support for wavefront obj's)
 */
bool TankGameView::loadModels(const char *floorModelFname,
                              const char *cubeModelFname,
                              const char *missileModelFname,
                              const char *tankHeadModelFname,
                              const char *tankTreadsModelFname)
{
    return floorModel.loadObj(floorModelFname) &&
    cubeModel.loadObj(cubeModelFname) &&
    missileModel.loadObj(missileModelFname) &&
    tankHeadModel.loadObj(tankHeadModelFname) &&
    tankTreadsModel.loadObj(tankTreadsModelFname);
}

/**
 * drawLevel()
 * helper function that actually renders a Level object to the screen.
 */
void TankGameView::drawLevel(const Level & level)
{
    // floorModel is a rect from (-1, -1, 0) to (1, 1, 0)
    // cubeModel is a cube from (0, 0, 0) to (1, 1, 1)

    const bool ** map = level.getMap();

    k3d::mat4 tMat = gl::mModelView;

    gl::mModelView.scalef(level.getWidth()/2.0, level.getHeight()/2.0, 1.0);
    gl::mModelView.translatef(1.0, 1.0, 0.0);
    gl::sendMatrices();

    gl::sendColor(0.431, 0.254, 0.254, 1.0); // Brown floor

    floorModel.draw();

    for (int x = 0; x < level.getWidth(); x++) {
        for (int y = 0; y < level.getHeight(); y++) {
            if (map[x][y]) {
                gl::mModelView = tMat;
                gl::mModelView.translatef((float)x, (float)y, 0.0);

                gl::sendMatrices();

                gl::sendColor(1.0, 0.0, 0.0, 1.0); // Red walls

                cubeModel.draw();
            }
        }
    }
    gl::mModelView = tMat;
}

/**
 * drawMissile()
 * helper function that actually renders a Missile object to the screen. Sets
 * the missile as exploded if it was exploding and the exploding animation is
 * complete.
 */
void TankGameView::drawMissile(Missile & missile)
{
    const k3d::vec2 aim(missile.getVelocity());
    float _aimRotation[4][4] = {
        { aim.x, aim.y, 0.0, 0.0 },
        { -aim.y, aim.x, 0.0, 0.0 },
        { 0.0, 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 0.0, 1.0 },
    };

    k3d::mat4 tMat = gl::mModelView;
    k3d::mat4 aimRotation(_aimRotation);
    const k3d::vec2 & pos = missile.getPos();

    gl::mModelView.translatef(pos.x + 0.5, pos.y + 0.5, 0.0);
    gl::mModelView = gl::mModelView * aimRotation;
    if (missile.getExploding() == true) {
        gl::mModelView.scalef(0.5, 1.0, 3.0);
        missile.setExploded(true); // will be pruned by TankGameModel
    } else {
        gl::mModelView.scalef(0.2, 0.3, 0.5);
    }
    gl::sendMatrices();

    gl::sendColor(1.0, 1.0, 0.8, 1.0);

    missileModel.draw();

    gl::mModelView = tMat;
}

/**
 * drawTank()
 * helper function that actually renders a Tank object to the screen.
 */
void TankGameView::drawTank(const Tank & tank)
{
    /**
     * Tank models draw a tank centred and on the xy plane
     * i.e. the tank lies in z > 0. It also is within the
     * canonical GL volume. It is aiming and facing in -Y
     */

    k3d::mat4 tMat = gl::mModelView;
    const k3d::vec2 & pos = tank.getPos();
    const k3d::vec2 & velocity = tank.getVelocity();
    const k3d::vec2 & aim = tank.getAim();

    float _velRotation[4][4] = {
        { -velocity.y,  velocity.x, 0.0, 0.0 },
        { -velocity.x, -velocity.y, 0.0, 0.0 },
        { 0.0, 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 0.0, 1.0 },
    };

    float _aimRotation[4][4] = {
        { -aim.y,  aim.x, 0.0, 0.0 },
        { -aim.x, -aim.y, 0.0, 0.0 },
        { 0.0, 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 0.0, 1.0 },
    };

    k3d::mat4 velRotation(_velRotation);
    k3d::mat4 aimRotation(_aimRotation);

    gl::sendColor(0.1, 0.8, 0.29, 1.0); // Some shade of green

    gl::mModelView.translatef(pos.x + 0.5, pos.y + 0.5, 0.0);
    gl::mModelView = gl::mModelView * velRotation;
    gl::mModelView.scalef(0.5, 0.5, 1.0);
    gl::sendMatrices();
    tankTreadsModel.draw();

    gl::mModelView = tMat;
    gl::mModelView.translatef(pos.x + 0.5, pos.y + 0.5, 0.0);
    gl::mModelView = gl::mModelView * aimRotation;
    gl::mModelView.scalef(0.5, 0.5, 1.0);
    gl::sendMatrices();
    tankHeadModel.draw();

    gl::mModelView = tMat;
}

/**
 * renderFrame()
 * render the model to the screen. It is expected that k3d::gl is
 * initialized before calling this function. It is also expected
 * that the screen is cleared before a call to render frame and
 * if double buffering, buffers are swapped after this call.
 */
void TankGameView::renderFrame()
{
    const Level & level = model->getLevel();
    const Tank & player = model->getPlayer();
    const k3d::vec2 & playerPos = player.getPos();
    vector<Missile> & missiles = model->getMissiles();
    const vector<Tank> & enemies = model->getEnemies();

    gl::mModelView.loadIdentity();
    // set the eye above the player looking down on him
    gl::mModelView.lookAt(k3d::vec3(playerPos.x, playerPos.y, 7.0),
        k3d::vec3(playerPos.x, playerPos.y, 0.0), k3d::vec3(0.0, 1.0, 0.0));

    gl::vLight0 = k3d::vec3(4.0, 3.0, 20.0);
    gl::sendLight0();

    drawLevel(level);

    if (player.getIsDead() == false) {
        drawTank(player);
    }
    for (unsigned i = 0; i < enemies.size(); i++) {
        if (enemies[i].getIsDead() == false) {
            drawTank(enemies[i]);
        }
    }

    for (unsigned i = 0; i < missiles.size(); i++) {
        if (missiles[i].getExploded() == false) { // technically over here no missiles will have exploded since they will be pruned... but since we should try to make no assumptions of the calling order of step() and renderFrame()
            drawMissile(missiles[i]);
        }
    }
}
