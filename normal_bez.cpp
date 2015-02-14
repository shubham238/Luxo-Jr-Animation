#include<iostream>
//#include<conio.h>
#include <stdlib.h>
#define clrscr() system("CLS")
#include <cmath>
#include <stdio.h>
#include "bez_control_pts.h"
using namespace std;

//#define PI = 3.14159265;

//float a,b,c,d;//,f,g,h,i,k,l,m,n,p,q,r,s;
//float	a=1.0; float b=-2.7; float c=4.5; float d=-6;

float normal_bez(float t,float x0 , float x1, float x2, float x3){ 	// xi's are x co-ordinates of control points



	float derivative;float m_noraml;float theta;
	derivative = 3*(1-t)*(1-t)*(x1-x0) + 6*(1-t)*t*(x2-x1) + 3*t*t*(x3-x2);

	m_noraml = (-(1/derivative));

	theta = atan (m_noraml) * 180 / 3.14159265 ;

	//cout<<" the angle is"<< theta<< endl;
	return theta;
}
