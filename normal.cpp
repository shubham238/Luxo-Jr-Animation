#include<iostream>
//#include<conio.h>
#include <stdlib.h>
#define clrscr() system("CLS")
#include <cmath>
#include <stdio.h>
using namespace std;

//#define PI = 3.14159265;

//float a,b,c,d;//,f,g,h,i,k,l,m,n,p,q,r,s;
//float	a=1.0; float b=-2.7; float c=4.5; float d=-6;

float normal(float x,float a , float b, float c, float d){



	float derivative;float m_noraml;float theta;
	derivative=  (((a*pow((x + 0.0000001),3.0) + b*pow((x + 0.0000001),2.0) + c*(x + 0.0000001)) - (a*(x*x*x) + b*(x*x) + c*(x)))/0.0000001);

	m_noraml = (-(1/derivative));

	theta = atan (m_noraml) * 180 / 3.14159265 ;

	//cout<<" the angle is"<< theta<< endl;
	return theta;
}
