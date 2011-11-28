/**
 * Filename: KeyboardController.cpp
 * Author: Karshan Sharma <sharma34@illinois.edu>
 * Created: Mon Nov 28 07:20:12 CST 2011
 *
 * Description:
 * Implementation of KeyboardController
 */

#include <libk3d/k3d.h>

#include "KeyboardController.h"

KeyboardController::KeyboardController(TankGameModel * model, TankGameView * view)
    : TankGameController(model, view) {}

void KeyboardController::keydown(unsigned char key)
{
    setPlayerSpeed(0.1);
    if (key == 'w') {
        setPlayerVelocity(k3d::vec2(0.0, 1.0));
    }
    else if (key == 'a') {
        setPlayerVelocity(k3d::vec2(-1.0, 0.0));
    }
    else if (key == 's') {
        setPlayerVelocity(k3d::vec2(0.0, -1.0));
    }
    else if (key == 'd') {
        setPlayerVelocity(k3d::vec2(1.0, 0.0));
    }
}

void KeyboardController::keyup(unsigned char key)
{
    setPlayerSpeed(0.0);
}
