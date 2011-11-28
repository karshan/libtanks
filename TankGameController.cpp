/**
 * Filename: TankGameController.h
 * Author: Karshan Sharma <sharma34@illinois.edu>
 * Created: Mon Nov 28 07:08:28 CST 2011
 *
 * Description:
 * Implementation of TankGameController
 */

#include "TankGameController.h"

TankGameController::TankGameController(TankGameModel * model, TankGameView * view)
    : model(model), view(view) {}

void TankGameController::setPlayerVelocity(const k3d::vec2 & velocity)
{
    model->player.setVelocity(velocity);
}

void TankGameController::setPlayerSpeed(float speed)
{
    model->player.setSpeed(speed);
}
