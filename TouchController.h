#ifndef _TOUCHCONTROLLER_H
#define _TOUCHCONTROLLER_H

#include "TankGameController.h"

class TouchController : public TankGameController {
    int width;
    int height;
public:
    TouchController(TankGameModel * model, TankGameView * view);

    void setRes(int w, int h);
    void touch(int x, int y, bool down);

};

#endif // _TOUCHCONTROLLER_H
