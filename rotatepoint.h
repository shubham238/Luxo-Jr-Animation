#ifndef _ROTATEPOINT_H_
#define _ROTATEPOINT_H_

#include <iostream>
#include <stdlib.h>
#include "math.h"
#include <vector>
#include "points.h"
using namespace std;

point rotate_point(point r, point p, double theta);
vector<point> rotate_keypoints(vector<point> oldlist, float sx, float sy, float sz, double theta);

#endif
