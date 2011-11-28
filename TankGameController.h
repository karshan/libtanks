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

    void setPlayerVelocity(const k3d::vec2 & velocity);
    void setPlayerSpeed(float speed);

};

#endif // _TANKGAMECONTROLLER_H
