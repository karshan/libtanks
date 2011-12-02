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

void TankGameController::setPlayerAim(const k3d::vec2 & aim)
{
    model->player.setAim(aim);
}

void TankGameController::setPlayerSpeed(float speed)
{
    model->player.setSpeed(speed);
}

const k3d::vec2 & TankGameController::getPlayerPos() const
{
    return model->player.getPos();
}

const k3d::vec2 & TankGameController::getPlayerVelocity() const
{
    return model->player.getVelocity();
}

const k3d::vec2 & TankGameController::getPlayerAim() const
{
    return model->player.getAim();
}

void TankGameController::firePlayerMissile()
{
    model->fireMissile(model->player);
}
