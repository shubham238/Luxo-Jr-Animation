#ifndef _CENTROID_H_
#define _CENTROID_H_

#include <math.h>
#include <vector>
#include "points.h"
#include "rotatepoint.h"
#include "cubic.h"
//#include "spline.h"
using namespace std;

//vector<point> fillVectors();
//vector<point> fillkeyvector();
vector< vector<point> > calculate_centroid(string name);

vector<point> spline_transformation(vector< vector<point> > newpoints);

#endif
// 147.098 397.509 327.032 436.764 505.366 438.614 540.348 404.585

