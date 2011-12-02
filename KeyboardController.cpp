/**
 * Filename: KeyboardController.cpp
 * Author: Karshan Sharma <sharma34@illinois.edu>
 * Created: Mon Nov 28 07:20:12 CST 2011
 *
 * Description:
 * Implementation of KeyboardController
 */

#include <iostream> // TODO remove
#include <libk3d/k3d.h>

#include "KeyboardController.h"

KeyboardController::KeyboardController(TankGameModel * model, TankGameView * view)
    : TankGameController(model, view) {}

void KeyboardController::keydown(unsigned char key)
{
    if (key == 'w') {
        setPlayerSpeed(0.06);
    }
    else if (key == 's') {
        setPlayerVelocity(-1.0 * getPlayerVelocity());
    }
    else if (key == 'a') {
        k3d::mat4 m;
        m.rotatef(k3d::vec3(0.0, 0.0, 1.0), 5.0);
        k3d::vec3 t(m * k3d::vec3(getPlayerVelocity(), 0.0));
        setPlayerVelocity(k3d::vec2(t.x, t.y));
    }
    else if (key == 'd') {
        k3d::mat4 m;
        m.rotatef(k3d::vec3(0.0, 0.0, 1.0), -5.0);
        k3d::vec3 t(m * k3d::vec3(getPlayerVelocity(), 0.0));
        setPlayerVelocity(k3d::vec2(t.x, t.y));
    }
    else if (key == 'h') {
        std::cout << "pos: " << k3d::vec3(getPlayerPos(), 0.0) << " vel: " << k3d::vec3(getPlayerVelocity(), 0.0) << '\n';
        fireMissile();
    }
}

void KeyboardController::keyup(unsigned char key)
{
    if (key == 'w') {
        setPlayerSpeed(0.0);
    }
}
