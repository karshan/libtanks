#include "TouchController.h"


TouchController::TouchController(TankGameModel * model, TankGameView * view)
    : TankGameController(model, view) {}

void TouchController::setRes(int w, int h)
{
    width = w;
    height = h;
}

void TouchController::touch(int x, int y, bool down)
{
    if (down) {
        setPlayerSpeed(0.06);
        setPlayerVelocity(k3d::vec2(x-width/2, y - height/2));
    } else {
        setPlayerSpeed(0.0);
    }
}
