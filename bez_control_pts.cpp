#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "bez_control_pts.h"
using namespace std;

vector<float> co_ord(vector<float> key,vector<float> t_value){		//.....given the co-ordinates( x or y at a time) of key vertebraes, this gives x(or y) co-ordinates of control points
	float p0,p1,p2,p3,Det;      // x (or y ) co-ordinate of control points

	vector<float> req_coord;

	float a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t;	//key contains x(or y) co-ordinates in the order of t12, t9, t4, t1

	a=1 ;
	b=0 ; 
	c=0;
	d=0; 
	e = key[0];

	f = (-1)*pow(t_value[1],3.0) + (3)*pow(t_value[1],2.0) + (-3)*t_value[1] + 1;
	g = (3)*pow(t_value[1],3.0) + (-6)*pow(t_value[1],2.0) + (3)*t_value[1];
	h = (-3)*pow(t_value[1],3.0) + (3)*pow(t_value[1],2.0) ;
	i = pow(t_value[1],3.0);
	j = key[1];

	k = (-1)*pow(t_value[2],3.0) + (3)*pow(t_value[2],2.0) + (-3)*t_value[2] + 1;
	l = (3)*pow(t_value[2],3.0) + (-6)*pow(t_value[2],2.0) + (3)*t_value[2];
	m = (-3)*pow(t_value[2],3.0) + (3)*pow(t_value[2],2.0) ;
	n = pow(t_value[2],3.0);
	o = key[2];

	p = (-1) + (3) + (-3) + 1;
	q = (3) + (-6) + (3);
	r = (-3) + (3) ;
	s = 1;
	t = key[3];

	Det = a*((g*m*s+h*n*q+i*l*r)-(g*n*r+h*l*s+i*m*q)) - b*((f*m*s+h*n*p+i*k*r)-(f*n*r+h*k*s+i*p*m)) + c*((f*l*s+g*n*p+i*k*q)-(f*n*q+g*k*s+i*l*p)) -d*((f*l*r+g*m*p+h*k*q)-(f*m*q+g*k*r+h*l*p));

	p0 = (e*((g*m*s+h*n*q+i*l*r)-(g*n*r+h*l*s+i*m*q)) - b*((j*m*s+h*n*t+i*o*r)-(j*n*r+h*o*s+i*t*m)) + c*((j*l*s+g*n*t+i*o*q)-(j*n*q+g*o*s+i*l*t)) -d*((j*l*r+g*m*t+h*o*q)-(j*m*q+g*o*r+h*l*t)))/Det;

	p1 = (a*((j*m*s+h*n*t+i*o*r)-(j*n*r+h*o*s+i*m*t)) - e*((f*m*s+h*n*p+i*k*r)-(f*n*r+h*k*s+i*p*m)) + c*((f*o*s+j*n*p+i*k*t)-(f*n*t+j*k*s+i*o*p)) -d*((f*o*r+j*m*p+h*k*t)-(f*m*t+j*k*r+h*o*p)))/Det;

	p2 = (a*((g*o*s+j*n*q+i*l*t)-(g*n*t+j*l*s+i*o*q)) - b*((f*o*s+j*n*p+i*k*t)-(f*n*t+j*k*s+i*p*o)) + e*((f*l*s+g*n*p+i*k*q)-(f*n*q+g*k*s+i*l*p)) -d*((f*l*t+g*o*p+j*k*q)-(f*o*q+g*k*t+j*l*p)))/Det;

	p3 = (a*((g*m*t+h*o*q+j*l*r)-(g*o*r+h*l*t+j*m*q)) - b*((f*m*t+h*o*p+j*k*r)-(f*o*r+h*k*t+j*p*m)) + c*((f*l*t+g*o*p+j*k*q)-(f*o*q+g*k*t+j*l*p)) -e*((f*l*r+g*m*p+h*k*q)-(f*m*q+g*k*r+h*l*p)))/Det;

	req_coord.push_back(p0);
	req_coord.push_back(p1);
	req_coord.push_back(p2);
	req_coord.push_back(p3);

	return req_coord;
}

