#ifndef _COLLIDE_H
#define _COLLIDE_H

#include "libk3d/k3d.h"

k3d::vec2 collide(k3d::vec2 pos1, const k3d::vec2 & hw1, const k3d::vec2 & v1,
                  const k3d::vec2 & pos2, const k3d::vec2 & hw2, const k3d::vec2 & v2, bool & collided);

#endif // _COLLIDE_H
