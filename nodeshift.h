#ifndef _NODESHIFT_H_
#define _NODESHIFT_H_

#include <vector>
#include "points.h"
using namespace std;

float derivative(vector<float> cubiceqn, float x);

vector<float> normal(vector<float> cubic, float x);

vector<float> construct_curve();

float anglesign(float px, float py, float cx, float cy, vector<float> polycoeffs);

vector<float> bin_search(float x, float y, vector<float> coffs, point ul, point ur);

#endif /*_NODESHIFT_H_*/