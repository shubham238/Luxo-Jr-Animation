#include <iostream>
#include "conio.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include "bezier.h"

using namespace std;

vector< vector<point> > bezier(string name)
{

	//float theta = 0.32; //for standing to seated
	//float theta = 2.37275; //for manual standing to seated
	//float theta = 1.1433; //for manual standing to seated 2
	//float theta = -7.32716; //for manual standing to supine
	float theta = -8.563917; //for manual standing to supine 2
	//float theta = 3.81919; //for standing to supine

	vector< vector<point> > temporary = calculate_centroid(name);

	vector<point> after_cubic_all = temporary[2];
	vector<point> after_cubic_thor;

	for (int i = 5;i<after_cubic_all.size();i++){
		after_cubic_thor.push_back(after_cubic_all[i]);
	}

	vector< vector<point> > bef_aft_thor;
	bef_aft_thor.push_back(after_cubic_thor);

	vector<float> t_val;   // contains values from t12 to t1
	t_val.push_back(0);    //12	0
	t_val.push_back(0.089);//11	1
	t_val.push_back(0.179);//10	2
	t_val.push_back(0.274);//9 	3
	t_val.push_back(0.363);//8  4
	t_val.push_back(0.455);//7  5
	t_val.push_back(0.545);//6  6
	t_val.push_back(0.636);//5  7
	t_val.push_back(0.726);//4  8
	t_val.push_back(0.813);//3  9
	t_val.push_back(0.91); //2  10
	t_val.push_back(1);    //1  11

	vector<float> t_valueUsed;
	t_valueUsed.push_back(0);
	t_valueUsed.push_back(0.274);
	t_valueUsed.push_back(0.726);
	t_valueUsed.push_back(1);


	point t12 = after_cubic_all[5];
	point t11 = after_cubic_all[6];
	point t10 = after_cubic_all[7];
	point t9 = after_cubic_all[8];
	point t8 = after_cubic_all[9];
	point t7 = after_cubic_all[10];
	point t6 = after_cubic_all[11];
	point t5 = after_cubic_all[12];
	point t4 = after_cubic_all[13];
	point t3 = after_cubic_all[14];
	point t2 = after_cubic_all[15];
	point t1 = after_cubic_all[16];

	vector<float> keysx; 
	keysx.clear();
	keysx.push_back(t12.x);
	keysx.push_back(t9.x);
	keysx.push_back(t4.x);
	keysx.push_back(t1.x);
	
	vector<float> temp = co_ord(keysx,t_valueUsed);
	
	vector<float> keysy; keysy.clear();
	keysy.push_back(t12.y);
	keysy.push_back(t9.y);
	keysy.push_back(t4.y);
	keysy.push_back(t1.y);

	vector<float> temp1 = co_ord(keysy,t_valueUsed);

	vector<point> control;

	point c0 = point(temp[0],temp1[0],t12.z);
	control.push_back(c0);
	point c1 = point(temp[1],temp1[1],t9.z);
	control.push_back(c1);
	point c2 = point(temp[2],temp1[2],t4.z);
	control.push_back(c2);
	point c3 = point(temp[3],temp1[3],t1.z);
	control.push_back(c3);
	//control = t12->t9'->t4'->t1(order of control points)

	vector<point> rotated_control =  rotate_keypoints(control,t12.x,t12.y,t12.z,theta);

	vector<point> newControl;
	newControl.push_back(c0);
	newControl.push_back(c1);
	newControl.push_back(rotated_control[2]);
	newControl.push_back(rotated_control[3]);

	vector<float> VerX;
	vector<float> VerY;

	for (int i=0;i<t_val.size();i++){
		float x1 = pow((1-t_val[i]),3.0)*newControl[0].x + 3*pow((1-t_val[i]),2.0)*t_val[i]*newControl[1].x + 3*pow((t_val[i]),2.0)*(1-t_val[i])*newControl[2].x + pow((t_val[i]),3.0)*newControl[3].x;
		VerX.push_back(x1);
		float y1 = pow((1-t_val[i]),3.0)*newControl[0].y + 3*pow((1-t_val[i]),2.0)*t_val[i]*newControl[1].y + 3*pow((t_val[i]),2.0)*(1-t_val[i])*newControl[2].y + pow((t_val[i]),3.0)*newControl[3].y;
		VerY.push_back(y1);
	}

	vector<point> newThorVert;
	point t12n = point(VerX[0],VerY[0],t12.z);newThorVert.push_back(t12n);
	point t11n = point(VerX[1],VerY[1],t11.z);newThorVert.push_back(t11n);
	point t10n = point(VerX[2],VerY[2],t10.z);newThorVert.push_back(t10n);
	point t9n = point(VerX[3],VerY[3],t9.z);newThorVert.push_back(t9n);
	point t8n = point(VerX[4],VerY[4],t8.z);newThorVert.push_back(t8n);
	point t7n = point(VerX[5],VerY[5],t7.z);newThorVert.push_back(t7n);
	point t6n = point(VerX[6],VerY[6],t6.z);newThorVert.push_back(t6n);
	point t5n = point(VerX[7],VerY[7],t5.z);newThorVert.push_back(t5n);
	point t4n = point(VerX[8],VerY[8],t4.z);newThorVert.push_back(t4n);
	point t3n = point(VerX[9],VerY[9],t3.z);newThorVert.push_back(t3n);
	point t2n = point(VerX[10],VerY[10],t2.z);newThorVert.push_back(t2n);
	point t1n = point(VerX[11],VerY[11],t1.z);newThorVert.push_back(t1n);

	bef_aft_thor.push_back(newThorVert);

	return bef_aft_thor;	// has t12 @ newThorVert[0] and t1 @ newThorVert[11]

	}

// int main()
// {
// 	vector< vector<point> > result = bezier("standingcentroids.off");
// 	vector<point> cent = result[1];

// 	ofstream writefile;
// 	writefile.open("G:/Acads/Project/integrated/standing to supine repositioned/standing_to_supineafterthorax2.off");

// 	writefile<<"OFF"<<endl;
// 	writefile<<"12 0 0"<<endl;

// 	for (int i=11;i>=0;i--){
// 		writefile<<cent[i].y << " "<< cent[i].x  << " " << cent[i].z << endl; 
// 		cout<< cent[i].y << " "<< cent[i].x  << " " << cent[i].z << endl;
// 	}
	
// 	return 0;

// }