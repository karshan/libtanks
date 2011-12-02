#ifndef _TANKGAMECONTROLLER_H
#define _TANKGAMECONTROLLER_H

/**
 * Filename: TankGameController.h
 * Author: Karshan Sharma <sharma34@illinois.edu>
 * Created: Mon Nov 28 06:10:24 CST 2011
 *
 * Description:
 * C in MVC
 */

#include "TankGameModel.h"
#include "TankGameView.h"

class TankGameController {

protected:
    TankGameModel * model;
    TankGameView * view;

public:
    TankGameController(TankGameModel * model, TankGameView * view);

    const k3d::vec2 & getPlayerPos() const;
    const k3d::vec2 & getPlayerVelocity() const;
    const k3d::vec2 & getPlayerAim() const;

    void setPlayerVelocity(const k3d::vec2 & velocity);
    void setPlayerAim(const k3d::vec2 & aim);
    void setPlayerSpeed(float speed);

    void firePlayerMissile();

};

#endif // _TANKGAMECONTROLLER_H
