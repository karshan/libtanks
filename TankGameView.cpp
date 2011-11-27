/**
 * Filename: TankGameView.cpp
 * Author: Karshan Sharma <sharma34@illinois.edu>
 * Created: Fri Nov 25 10:36:10 CST 2011
 *
 * Description:
 * Implementation of the TankGameView class.
 */

#include <libk3d/k3d.h>

#include "TankGameView.h"

using k3d::gl;

k3d::model TankGameView::floorModel("models/floor.obj");
k3d::model TankGameView::cubeModel("models/wall.obj");

/**
 * TankGameView parameterized constructor
 * sets up a TankGameView associated with the TankGameModel passed in
 */
TankGameView::TankGameView(TankGameModel * model) : model(model) {}

/**
 * drawLevel()
 * helper function that actually renders a Level object to the screen.
 */
void TankGameView::drawLevel()
{
    // floorModel is a rect from (-1, -1, 0) to (1, 1, 0)
    // cubeModel is a cube from (0, 0, 0) to (1, 1, 1)

    const Level & level = model->getLevel();
    const bool ** map = level.getMap();

    k3d::mat4 tMat = gl::mModelView;

    gl::mModelView.scalef(level.getWidth()/2.0, level.getHeight()/2.0, 1.0);
    gl::mModelView.translatef(1.0, 1.0, 0.0);
    gl::sendMatrices();

    gl::sendColor(0.431, 0.254, 0.254, 1.0); // Brown

    TankGameView::floorModel.draw();

    for (int x = 0; x < level.getWidth(); x++) {
        for (int y = 0; y < level.getHeight(); y++) {
            if (map[x][y]) {
                gl::mModelView = tMat;
                gl::mModelView.translatef((float)x, (float)y, 0.0);
                gl::sendMatrices();

                gl::sendColor(1.0, 0.0, 0.0, 1.0);

                TankGameView::cubeModel.draw();
            }
        }
    }
}

/**
 * drawTank()
 * helper function that actually renders a Tank object to the screen.
 */
void TankGameView::drawTank(const Tank & tank)
{
}

/**
 * drawMissile()
 * helper function that actually renders a Missile object to the screen.
 */
void TankGameView::drawMissile(const Missile & missile)
{
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
    k3d::mat4 tMat;
    const Tank & player = model->getPlayer();
    //const k3d::vec2 & myPos = player.getPos();
    k3d::vec2 myPos(model->getLevel().getWidth()/2.0, model->getLevel().getHeight()/2.0);

    gl::mModelView.loadIdentity();
    gl::mModelView.lookAt(k3d::vec3(myPos.x, myPos.y - 1.5, 7.0),
        k3d::vec3(myPos.x, myPos.y, 0.0), k3d::vec3(0.0, 1.0, 0.0));

    gl::vLight0 = k3d::vec3(4.0, 3.0, 20.0);
    gl::sendLight0();

    tMat = gl::mModelView;
    drawLevel();
}
