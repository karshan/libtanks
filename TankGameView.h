#ifndef _TANKGAMEVIEW_H
#define _TANKGAMEVIEW_H

/**
 * Filename: TankGameView.h
 * Author: Karshan Sharma <sharma34@illinois.edu>
 * Created: Fri Nov 25 10:17:32 CST 2011
 *
 * Description:
 * The View for the game, this is the class that has functions to render
 * a TankGameModel (that it is associated with) to the screen. the V in
 * MVC.
 */

#include "TankGameModel.h"

class TankGameView {

private:
    k3d::model floorModel;
    k3d::model cubeModel;
    k3d::model missileModel;
    k3d::model tankHeadModel;
    k3d::model tankTreadsModel;

    TankGameModel * model;

    // Helpers
    void drawLevel(const Level & level);
    void drawTank(const Tank & tank);
    void drawMissile(const Missile & missile);

public:
    TankGameView(TankGameModel * model);

    bool loadModels(const char *floorModelFname, const char *cubeModelFname, const char *missileModelFname,
        const char *tankHeadModelFname, const char *tankTreadsModelFname)
            __attribute__((warn_unused_result));

    void renderFrame();
};

#endif //_TANKGAMEVIEW_H
