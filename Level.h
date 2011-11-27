#ifndef _LEVEL_H
#define _LEVEL_H

/**
 * Filename: Level.h
 * Author: Karshan Sharma <sharma34@illinois.edu>
 * Created: Fri Nov 25 10:26:28 CST 2011
 *
 * Description:
 * The representation of a level in the game, i.e. the floor and walls. This
 * is part of the model description (MVC).
 */

class Level {

private:
    int     width;  // in blocks
    int     height; // in blocks
    bool ** map;    // map[x][y] == true iff the (x, y) block is impassable

    void clear();
public:
    Level();
    ~Level();

    int getWidth() const;
    int getHeight() const;
    const bool ** getMap() const;

    bool loadFromFile(const char *filename) __attribute__((warn_unused_result));

};

#endif // _LEVEL_H
