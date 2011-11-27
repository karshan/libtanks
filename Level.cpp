/**
 * Filename: Level.cpp
 * Author: Karshan Sharma <sharma34@illinois.edu>
 * Created: Fri Nov 25 10:32:50 CST 2011
 *
 * Description:
 * Implementation of the Level class.
 */

#include <fstream>
#include <sstream>
#include <string>

#include "Level.h"

/**
 * Level default constructor
 * setup an invalid level
 */
Level::Level() : width(0), height(0), map(NULL) {}

/**
 * Level destructor
 * calls clear() to free memory
 */
Level::~Level()
{
    clear();
}

/**
 * clear()
 * free any memory allocated by to map (the bool[][] representation of the level)
 */
void Level::clear()
{
    if (map) {
        for (int i = 0; i < width; i++) {
            delete []map[i];
        }
        delete []map;
    }
    width = 0;
    height = 0;
}

/**
 * getWidth()
 * returns the width of the level in blocks (x direction)
 */
int Level::getWidth() const
{
    return width;
}

/**
 * getHeight()
 * returns the height of the level in blocks (y direction)
 */
int Level::getHeight() const
{
    return height;
}

/**
 * getMap()
 * returns a constant pointer to the map which tells you where walls are in
 * the level
 */
const bool ** Level::getMap() const
{
    return (const bool **)map;
}

/**
 * loadFromFile()
 * loads a level in from a file, the file format is described in levels/README
 * TODO: exceptions instead ? or atleast some way of knowing what the error was.
 */
bool Level::loadFromFile(const char *filename)
{
    std::ifstream in(filename);
    std::string line;
    char ch;

    if (!in.is_open()) {
        return false;
    }

    clear();

    std::getline(in, line);
    std::istringstream iss(line, std::istringstream::in);

    iss >> width;
    iss >> height;

    map = new bool*[width];
    for (int i = 0; i < width; i++)
        map[i] = new bool[height];

    int y = height - 1;
    while (!in.eof() && y >= 0) {
        std::getline(in, line);
        if (line.size() != width) {
            clear();
            return false;
        }

        for (int x = 0; x < width; x++) {
            ch = line[x];
            if (ch != '#' && ch != ' ') {
                clear();
                return false;
            }
            map[x][y] = ch == '#';
        }
        y--;
    }
    if (y != -1) {
        clear();
        return false;
    }

    return true;
}
