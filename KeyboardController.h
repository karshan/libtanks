#ifndef _KEYBOARDCONTROLLER_H
#define _KEYBOARDCONTROLLER_H

/**
 * Filename: KeyboardController.h
 * Author: Karshan Sharma <sharma34@illinois.edu>
 * Created: Mon Nov 28 07:16:14 CST 2011
 *
 * Description:
 * Keyboard Input for TankGame
 */

#include "TankGameController.h"

class KeyboardController : public TankGameController {

public:
    KeyboardController(TankGameModel * model, TankGameView * view);

    void keydown(unsigned char key);
    void keyup(unsigned char key);

};

#endif // _KEYBOARDCONTROLLER_H
