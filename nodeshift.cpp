#include <iostream>
#include "conio.h"
#include <stdlib.h>
#include <vector>
#include <math.h>
#include "cubic.h"
#include "points.h"
#include "nodeshift.h"
#define PI 3.14159625

float derivative(vector<float> cubiceqn, float x)
{
	float m = 3*(cubiceqn[0])*x*x + 2*(cubiceqn[1])*x + cubiceqn[2];
	return m;
}

//changed axes
vector<float> normal(vector<float> cubiceqn, float x)
{
	float m = 3*(cubiceqn[0])*x*x + 2*(cubiceqn[1])*x + cubiceqn[2];
	//float vx = -m/((sqrt(1 + (pow (m, 2))))*m);
	//float vy =  1/((sqrt(1 + (pow (m, 2))))*m);

	float one_by_m = (-1)/m;

	float vx, vy;
	
	vx = m;
	vy = -1;
	
	vector<float> norm;
	norm.push_back(vx);
	norm.push_back(vy);

	return norm;  
}

vector<float> construct_curve()
{
	point l5 = point(145.098,388.937,179.384);		//curve using standing centroids
	point t12 = point(315.184,423.088,177.731);
	point t4 = point(501.428,428.385,169.079);
	point t1 = point(548.571,389.219,171.919);

	vector<point> vertecenters;
	vertecenters.push_back(l5);
	vertecenters.push_back(t12);
	vertecenters.push_back(t4);
	vertecenters.push_back(t1);

	vector<float> coefficients = co_effs(vertecenters);

	return coefficients;
}

float anglesign(float px, float py, float cx, float cy, vector<float> polycoeffs)
{
	float pcx = cx - px;
	float pcy = cy - py;

	float slope = derivative(polycoeffs, cx);
	float tx = 1.00;
	float ty = slope;

	float dotproduct = (pcx*tx)+(pcy*ty);
	
	return dotproduct;
}

vector<float> bin_search(float x, float y, vector<float> coffs, point ul, point ur)
{ 
	vector<float> answers;

	float sign;

	// float xl = 145.098;
	// float yl = 388.937;
	// float xr = 548.571;
	// float yr = 389.219;

	float xl = ul.x;
	float yl = ul.y;
	float xr = ur.x;
	float yr = ur.y;
	float xval;
	float yval;
	
	while((xr-xl)>0.05)
	{
		xval = (xl+xr)/2;
		yval = coffs[0]*(pow(xval,3.0)) + coffs[1]*(pow(xval,2.0)) + coffs[2]*(xval) + coffs[3];
		
		float sign = anglesign(x, y, xval, yval, coffs);
		//cout<<"sign "<<sign<<endl;
		
		if (sign > 0)
		{
			xr = xval;
			yr = yval;
			
		}
		else 
		{
			xl = xval;
			yl = yval; 
			
		}

	//	cout<< "the difference among the points is" << xl <<"  "<< xr <<"  "<<(xl-xr)<< " " <<sign<<"  "<<xval<<endl;
		//exit(0); 
 	}	
	
	float u = (xval-145.089)/403.473;
	float vx = x - xval;
	float vy = y - yval;

	answers.push_back(u);
	answers.push_back(vx);
	answers.push_back(vy);
	answers.push_back(xval);
	answers.push_back(yval);
	answers.push_back(x);
	answers.push_back(y);

	return answers;
}

// int main()
// {
// 	vector<float> poly = construct_curve();
	
// 	// float xl = 145.098;
// 	// float yl = 388.937;
// 	// float xr = 548.571;
// 	// float yr = 389.219;
// 	point pl = point(145.098, 388.937, 179.385);

// 	point pr = point(548.871, 389.219, 171.919);
	
// 	//vector<float> result = bin_search(-0.244,445.13,poly, pl, pr);
	
// 	vector<float> result = bin_search(456.466, 306.527, poly, pl, pr);
	
// 	cout<<result[0]<<endl;
// 	cout<<result[1]<<endl;
// 	cout<<result[2]<<endl;
// 	// bin_search(497.491,416.321);
// 	// bin_search(228.977,449.407);
// 	return 0;
// }

