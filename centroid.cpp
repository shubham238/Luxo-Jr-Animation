
#include <iostream>
#include "conio.h"
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "centroid.h"
#include <math.h>
#include <vector>
#include "points.h"
#include "rotatepoint.h"
#include "cubic.h"

using namespace std;

#define PI 3.14159

vector< vector<point> > calculate_centroid(string name){

	//x and y axis are to be interchanged
	//point lsj = point(134.271,397.84,175.306);
	//point lsj = point(84.068, 400.455, 175.306); //for standing
	point lsj = point(127.196, 411.800, 175.306);
	//double theta = -7.32954; //for manual standing to seated
	double theta = 4.33437; //for manual standing to supine

	//double theta = 1.58784; //for standing to supine
	//double theta = -9.03056;//.........

	vector< vector<point> > useful;

	vector<point> init;
	vector<point> initUsed;
	vector<point> temp;

	string str;
	string line;

	ifstream myfile;  
	myfile.open(name.c_str());  //reading file

	getline(myfile,line);  //removing the first line
	cout<<line<<endl;

	getline(myfile,line);  //extracting no of vertices and faces from next line
	cout<<line<<endl;
	//writefile<< line<<endl;
	str = line;
	istringstream iss(str);
	int num_vertices, num_faces, n;
	if(!(iss >> num_vertices >> num_faces >> n))
		{exit;}
	cout<<num_vertices<<endl;

	for(int i=0; i<num_vertices; i++)  //saving information of every points in vectors
	{
		getline(myfile,line);
		str = line;
		istringstream iss1(str);
		float a, b, c;
		if(!(iss1 >> a >> b >> c))
			{exit;}
		
		point p = point(b,a,0.0);
		temp.push_back(p);

	}

	for (int i = 16; i>=0; i--)
	{
		init.push_back(temp[i]);
	}

	initUsed.push_back(init[0]);
	initUsed.push_back(init[5]);
	initUsed.push_back(init[13]);
	initUsed.push_back(init[16]);

	useful.push_back(init);
	useful.push_back(initUsed);
	
	vector<float> ratiolumbar;
	vector<float> ratiothoracic;
	vector<point> finalUsed;// has l5' , t12' , t4' , t1'
	vector<point> tempnewlist;

	vector<point> final;

	for (int i=1;i<5;i++){
		float u = (init[i].x - initUsed[0].x)/(initUsed[1].x- initUsed[0].x);//first for l4 then l3,l2,l1
		ratiolumbar.push_back(u);// ratiolumbar has first for l4, then l3,l2,l1
	}

	// for (int i=6;i<16;i++){
	// 	float u = (init[i].x - init[5].x)/(init[16].x - init[5].x);
	// 	ratiothoracic.push_back(u);// ratiothoracic has first for t11, then t10, t9.....upto t2
	// }

	int sumx=0;
	for (int i=5;i<16;i++){
		sumx = sumx + sqrt(pow((init[i+1].x - init[i].x),2.0) + pow((init[i+1].y - init[i].y),2.0));
	}

	float length = 0;
	for (int i=6;i<16;i++){
		length = length + (sqrt(pow((init[i].x - init[i-1].x),2.0) + pow((init[i].y - init[i-1].y),2.0)));
		float u = length/sumx;
		ratiothoracic.push_back(u);
	}


	vector<point> t12t4t1;

	for (int k = 1;k<initUsed.size();k++){
		t12t4t1.push_back(initUsed[k]);//.....has t12 @ 0, t4 @ 1, t1 @ 2
	}

	tempnewlist = rotate_keypoints(t12t4t1,lsj.x,lsj.y,lsj.z,theta);

	finalUsed.push_back(init[0]);

	for (int j=0;j<3;j++){
		finalUsed.push_back(tempnewlist[j]);//..finalused has now rotated positions of l5,t12,t4,t1
	}

	vector<float> coeffs = co_effs(finalUsed);// &&&&&&&&&&---------this gives new coeffs[0],coeffs[1],coeffs[2],coeffs[3]

	final.push_back(init[0]);

	for (int newV=0; newV<ratiolumbar.size(); newV++)
	{
		float x1 = finalUsed[0].x + ratiolumbar[newV]*(finalUsed[1].x - finalUsed[0].x);
		float y1 = coeffs[0]*(pow(x1,3.0)) + coeffs[1]*(pow(x1,2.0)) + coeffs[2]*(x1) + coeffs[3];//natSpline(x1,finalUsed); 
		point newp = point(x1,y1,0.0);
		final.push_back(newp);
	}//final now has l5',l4',l3',l2',l1'

	final.push_back(tempnewlist[0]);//...now t12

	for (int newV=0; newV<7; newV++)
	{
		float x1 = finalUsed[1].x + ratiothoracic[newV]*(finalUsed[3].x - finalUsed[1].x);
		float y1 = coeffs[0]*(pow(x1,3.0)) + coeffs[1]*(pow(x1,2.0)) + coeffs[2]*(x1) + coeffs[3];//natSpline(x1,finalUsed);
		point newp = point(x1,y1,0.0);
		final.push_back(newp);
	}//.....t11 to t5

	final.push_back(tempnewlist[1]);//...now t4

	for (int newV=8; newV<10; newV++)
	{
		float x1 = finalUsed[1].x + ratiothoracic[newV]*(finalUsed[3].x - finalUsed[1].x);
		float y1 = coeffs[0]*(pow(x1,3.0)) + coeffs[1]*(pow(x1,2.0)) + coeffs[2]*(x1) + coeffs[3];//natSpline(x1,finalUsed);
		point newp = point(x1,y1,0.0);
		final.push_back(newp);
	}//....t3 to t2

	final.push_back(tempnewlist[2]);//.....now t1

	useful.push_back(final);


	return useful;//.......useful has init, initused and final
	// return 0;
}


// float u(float x)					//...........for seated
// {
// 	float uval = (x-312.208)/(235.678);
// 	return uval;
// }

// float u(float x)					//...........for supine
// {
// 	float uval = (x-315.499)/(230.16);
// 	return uval;
// }

float herm_basis(float p1, float p2, float p1deriv, float p2deriv, float x)
{
	float f1 = ((2*pow(x,3))-(3*(pow(x,2)))+1);
	float f2 = ((3*(pow(x,2)))-(2*pow(x,3)));
	float f3 = ((pow(x,3))-(2*pow(x,2))+x);
	float f4 = ((pow(x,3))-(pow(x,2)));

	float val = ((f1*p1)+(f2*p2)+(f3*p1deriv)+(f4*p2deriv));

	return val;
}

vector<point> spline_transformation(vector< vector<point> > newpoints)
{
	vector<point> initialspine = newpoints[0];
	vector<point> finalspine = newpoints[2];

	//calculating ratios for thoracic vertebrae
	vector<float> ratiothorax;
	int sumx=0;
	for (int i=5;i<16;i++){
		sumx = sumx + sqrt(pow((initialspine[i+1].x - initialspine[i].x),2.0) + pow((initialspine[i+1].y - initialspine[i].y),2.0));
	}
	//cout<< "sum="<< " "<<sumx<< endl;
	// for (int i=6;i<16;i++){

	// 	float length = 0;
	// 	for (int j=6;j<=i;j++){
	// 		length  += sqrt(pow((init[j].x - init[j-1]),2.0) + pow((init[j].y - init[j-1].y),2.0));
	// 	}

	// 	float u = length/sumx;
	// 	ratiothorax.push_back(u);
	// }

	float length = 0;
	for (int i=6;i<16;i++){
		length = length + (sqrt(pow((initialspine[i].x - initialspine[i-1].x),2.0) + pow((initialspine[i].y - initialspine[i-1].y),2.0)));
		float u = length/sumx;
		//cout<< "uvalues"<<" " <<u<< " ";

		ratiothorax.push_back(u);
	}

	// cout<<"ratios"<<" ";

	// for (int i=0;i<ratiothorax.size();i++){
	// 	cout << ratiothorax[i]<<" ";
	// }
	

	//calculating coefficients of the new cubic equation
	//point t1target = point(559.898, 431.674, 0.0);//.....for seated
	point t1target = point(562.053, 392.715, 0.0);//.....for supine
	point t12r = finalspine[5];
	cout<<"t1target "<<t1target.x<<" "<<t1target.y<<endl;
	cout<<"t12r"<<t12r.x<<" "<<t12r.y<<endl;
	
	vector<point> finalkeypoints;
	finalkeypoints.push_back(finalspine[0]);
	finalkeypoints.push_back(finalspine[5]);
	finalkeypoints.push_back(finalspine[13]);
	finalkeypoints.push_back(finalspine[16]);
	vector<float> obtainedcoeffs = co_effs(finalkeypoints);

	point t1r = finalspine[16];
	cout<<"t1r"<<t1r.x<<" "<<t1r.y<<endl;

	// float slope_t1ry = (3*obtainedcoeffs[0]*(t1r.x)*(t1r.x) + 2*obtainedcoeffs[1]*(t1r.x) + obtainedcoeffs[2])*235.678;		//for seated
	// float slope_t12ry = (3*obtainedcoeffs[0]*(t12r.x)*(t12r.x)  + 2*obtainedcoeffs[1]*(t12r.x) + obtainedcoeffs[2])*235.678;	//for seated

	float slope_t1ry = (3*obtainedcoeffs[0]*(t1r.x)*(t1r.x) + 2*obtainedcoeffs[1]*(t1r.x) + obtainedcoeffs[2])*230.16 + 60.58;			//for supine
	float slope_t12ry = (3*obtainedcoeffs[0]*(t12r.x)*(t12r.x)  + 2*obtainedcoeffs[1]*(t12r.x) + obtainedcoeffs[2])*230.16 - 24.19;		//for supine

	cout<< "slope_t1ry" << " " << slope_t1ry<< endl;
	cout<< "slope_t12ry" << " " << slope_t12ry<< endl;


	vector<point> transformed;

	transformed.push_back(t12r);
	for (int i=6; i<16; i++)
	{
	//	cout<<"ratiothorax" <<" "<<ratiothorax[i-6]<<endl;
	//	point oldpt = finalspine[i];
	//	float x = herm_basis(t12r.x, t1target.x, 235.678, 235.678, u(oldpt.x));		//....for seated
	//	float x = herm_basis(t12r.x, t1target.x, 230.16, 230.16, u(oldpt.x));		//....for supine
	//	float y = herm_basis(t12r.y, t1target.y, slope_t12ry, slope_t1ry, u(oldpt.x));
		float x = herm_basis(t12r.x, t1target.x, 230.16, 230.16, ratiothorax[i-6]);		//....for supine
		float y = herm_basis(t12r.y, t1target.y, slope_t12ry, slope_t1ry, ratiothorax[i-6]);
		point p = point(x, y, 0.0);
		transformed.push_back(p);
	}
	transformed.push_back(t1target);

	return transformed;
}

// int main()
// {
// 	vector< vector<point> > cent  = calculate_centroid("standingcentroids.off");
	
// 	vector<point> temp = cent[2];
// 	ofstream writefile;
// 	writefile.open("G:/Acads/Project/integrated/debug/obtained_seatedlumbarcentroids.off");

// 	writefile << "OFF"<<endl;
// 	writefile << "17 0 0"<<endl;
// 	for (int i = 16;i>=0;i--){
// 		writefile<< temp[i].y <<" "<<temp[i].x<<" "<<temp[i].z<<endl;
// 		cout<< temp[i].y <<" "<<temp[i].x << " " << temp[i].z << endl;
// 	}

// 	vector<point> newtemp = spline_transformation(cent);
// 	ofstream writefile1;
// 	writefile1.open("G:/Acads/Project/integrated/debug/obtained_seatedthorax1.off");
// 	writefile1 << "OFF" <<endl;
// 	writefile1 << "12 0 0"<<endl;
// 	for(int i = 11; i>=0; i--)
// 	{
// 		writefile1 <<newtemp[i].y << " "<<newtemp[i].x<<" "<<newtemp[i].z<<endl;
// 		cout <<newtemp[i].y << " "<<newtemp[i].x<<" "<<newtemp[i].z<<endl;
// 	}

// 	return 0;
// }




