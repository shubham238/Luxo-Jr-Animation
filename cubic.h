/*
 * cubic.h
 *
 *  Created on: Jun 1, 2014
 *      Author: cs1120254
 */

#ifndef _CUBIC_H_
#define _CUBIC_H_

#include <vector>
#include "points.h"
using namespace std;

//extern float D, a1, b1, c1, d1;

vector<float> co_effs(vector<point> points);

vector<float> transform_coeffs(point pa, float tana, point pb, float tanb);

#endif 
