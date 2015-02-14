#include <iostream>
//#include<conio.h>
#include <stdlib.h>
#include <math.h>
#include "cubic.h"

using namespace std;
//#define clrscr() system("CLS")

//let equation be y = a1*x^3 + b1*x^2 + c1*x^1 + d1*x^0
//The equations are of the form: ax+by+cz+dw=e fx+gy+hz+iw=j kx+ly+mz+nw=o px+qy+rz+sw=t

// float D = 0.0;
// float a1 = 0.0;
// float b1 = 0.0;
// float c1 = 0.0;
// float d1 = 0.0;

vector<float> co_effs(vector<point> points){
	vector<float> temp;temp.clear();
	vector<float> coefficients;

	float D, a1, b1, c1, d1;

	for (int i=0; i<4; i++){		//considering 4 points given in vector points
		temp.push_back(pow(points[i].x,3.0));
		temp.push_back(pow(points[i].x,2.0));
		temp.push_back(points[i].x);
		temp.push_back(points[i].y);
	}

	float a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t;

	a=temp[0];b=temp[1];c=temp[2];d=1;e=temp[3];
	f=temp[4];g=temp[5];h=temp[6];i=1;j=temp[7];
	k=temp[8];l=temp[9];m=temp[10];n=1;o=temp[11];
	p=temp[12];q=temp[13];r=temp[14];s=1;t=temp[15];
	// d=i=n=s=1 these are x^0 thing

	D = a*((g*m*s+h*n*q+i*l*r)-(g*n*r+h*l*s+i*m*q)) - b*((f*m*s+h*n*p+i*k*r)-(f*n*r+h*k*s+i*p*m)) + c*((f*l*s+g*n*p+i*k*q)-(f*n*q+g*k*s+i*l*p)) -d*((f*l*r+g*m*p+h*k*q)-(f*m*q+g*k*r+h*l*p));

	a1 = (e*((g*m*s+h*n*q+i*l*r)-(g*n*r+h*l*s+i*m*q)) - b*((j*m*s+h*n*t+i*o*r)-(j*n*r+h*o*s+i*t*m)) + c*((j*l*s+g*n*t+i*o*q)-(j*n*q+g*o*s+i*l*t)) -d*((j*l*r+g*m*t+h*o*q)-(j*m*q+g*o*r+h*l*t)))/D;

	b1 = (a*((j*m*s+h*n*t+i*o*r)-(j*n*r+h*o*s+i*m*t)) - e*((f*m*s+h*n*p+i*k*r)-(f*n*r+h*k*s+i*p*m)) + c*((f*o*s+j*n*p+i*k*t)-(f*n*t+j*k*s+i*o*p)) -d*((f*o*r+j*m*p+h*k*t)-(f*m*t+j*k*r+h*o*p)))/D;

	c1 = (a*((g*o*s+j*n*q+i*l*t)-(g*n*t+j*l*s+i*o*q)) - b*((f*o*s+j*n*p+i*k*t)-(f*n*t+j*k*s+i*p*o)) + e*((f*l*s+g*n*p+i*k*q)-(f*n*q+g*k*s+i*l*p)) -d*((f*l*t+g*o*p+j*k*q)-(f*o*q+g*k*t+j*l*p)))/D;

	d1 = (a*((g*m*t+h*o*q+j*l*r)-(g*o*r+h*l*t+j*m*q)) - b*((f*m*t+h*o*p+j*k*r)-(f*o*r+h*k*t+j*p*m)) + c*((f*l*t+g*o*p+j*k*q)-(f*o*q+g*k*t+j*l*p)) -e*((f*l*r+g*m*p+h*k*q)-(f*m*q+g*k*r+h*l*p)))/D;

	coefficients.push_back(a1);
	coefficients.push_back(b1);
	coefficients.push_back(c1);
	coefficients.push_back(d1);

	temp.clear();
	return coefficients;
}

vector<float> transform_coeffs(point pa, float tana, point pb, float tanb)
{
	float Det, ca, cb, cc, cd;
	vector<float> coffs;
	vector<float> constants;

	//making constants
	constants.push_back(pow(pa.x,3.0));
	constants.push_back(pow(pa.x,2.0));
	constants.push_back(pa.x);
	constants.push_back(pa.y);
	constants.push_back(pow(pb.x,3.0));
	constants.push_back(pow(pb.x,2.0));
	constants.push_back(pb.x);
	constants.push_back(pb.y);
	constants.push_back(3*(pow(pa.x,2.0)));
	constants.push_back(2*pa.x);
	constants.push_back(1);
	constants.push_back(tana);
	constants.push_back(3*(pow(pb.x,2.0)));
	constants.push_back(2*pb.x);
	constants.push_back(1);
	constants.push_back(tanb);

	float a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t;

	a=constants[0];b=constants[1];c=constants[2];d=1;e=constants[3];
	f=constants[4];g=constants[5];h=constants[6];i=1;j=constants[7];
	k=constants[8];l=constants[9];m=constants[10];n=0;o=constants[11];
	p=constants[12];q=constants[13];r=constants[14];s=0;t=constants[15];
	// d=i=1 n=s=0 these are x^0 thing

	Det = a*((g*m*s+h*n*q+i*l*r)-(g*n*r+h*l*s+i*m*q)) - b*((f*m*s+h*n*p+i*k*r)-(f*n*r+h*k*s+i*p*m)) + c*((f*l*s+g*n*p+i*k*q)-(f*n*q+g*k*s+i*l*p)) -d*((f*l*r+g*m*p+h*k*q)-(f*m*q+g*k*r+h*l*p));

	ca = (e*((g*m*s+h*n*q+i*l*r)-(g*n*r+h*l*s+i*m*q)) - b*((j*m*s+h*n*t+i*o*r)-(j*n*r+h*o*s+i*t*m)) + c*((j*l*s+g*n*t+i*o*q)-(j*n*q+g*o*s+i*l*t)) -d*((j*l*r+g*m*t+h*o*q)-(j*m*q+g*o*r+h*l*t)))/Det;

	cb = (a*((j*m*s+h*n*t+i*o*r)-(j*n*r+h*o*s+i*m*t)) - e*((f*m*s+h*n*p+i*k*r)-(f*n*r+h*k*s+i*p*m)) + c*((f*o*s+j*n*p+i*k*t)-(f*n*t+j*k*s+i*o*p)) -d*((f*o*r+j*m*p+h*k*t)-(f*m*t+j*k*r+h*o*p)))/Det;

	cc = (a*((g*o*s+j*n*q+i*l*t)-(g*n*t+j*l*s+i*o*q)) - b*((f*o*s+j*n*p+i*k*t)-(f*n*t+j*k*s+i*p*o)) + e*((f*l*s+g*n*p+i*k*q)-(f*n*q+g*k*s+i*l*p)) -d*((f*l*t+g*o*p+j*k*q)-(f*o*q+g*k*t+j*l*p)))/Det;

	cd = (a*((g*m*t+h*o*q+j*l*r)-(g*o*r+h*l*t+j*m*q)) - b*((f*m*t+h*o*p+j*k*r)-(f*o*r+h*k*t+j*p*m)) + c*((f*l*t+g*o*p+j*k*q)-(f*o*q+g*k*t+j*l*p)) -e*((f*l*r+g*m*p+h*k*q)-(f*m*q+g*k*r+h*l*p)))/Det;

	coffs.push_back(ca);
	coffs.push_back(cb);
	coffs.push_back(cc);
	coffs.push_back(cd);

	return coffs;
}
