#include <iostream>
#include "conio.h"
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "points.h"
#include "rotatepoint.h"
#include "centroid.h"
//#include "bezier.h"
#include "cubic.h"
#include "normal.h"
using namespace std;


void mapofffile(string name, string name2)
{
	
	string str;
	string line;
	int numfile;

	if(name == "StandingT01.off"){numfile = 16;}
	else if(name == "StandingT02.off"){numfile = 15;}	
	else if(name == "StandingT03.off"){numfile = 14;}
	else if(name == "StandingT04.off"){numfile = 13;}
	else if(name == "StandingT05.off"){numfile = 12;}
	else if(name == "StandingT06.off"){numfile = 11;}
	else if(name == "StandingT07.off"){numfile = 10;}
	else if(name == "StandingT08.off"){numfile = 9;}
	else if(name == "StandingT09.off"){numfile = 8;}
	else if(name == "StandingT10.off"){numfile = 7;}
	else if(name == "StandingT11.off"){numfile = 6;}
	else if(name == "StandingT12.off"){numfile = 5;}
	else if(name == "StandingL01.off"){numfile = 4;}
	else if(name == "StandingL02.off"){numfile = 3;}
	else if(name == "StandingL03.off"){numfile = 2;}
	else if(name == "StandingL04.off"){numfile = 1;}
	else if(name == "StandingL05.off"){numfile = 0;}
	cout<<"numfile "<<numfile<<endl;
	
	ifstream myfile;  
	myfile.open(name.c_str());  //reading file

	ofstream writefile;
	writefile.open(name2.c_str());

	getline(myfile,line);  //removing the first line
	cout<<line<<endl;
	writefile<< line<<endl;;

	getline(myfile,line);  //extracting no of vertices and faces from next line
	cout<<line<<endl;
	writefile<< line<<endl;
	str = line;
	istringstream iss(str);
	int num_vertices, num_faces, n;
	if(!(iss >> num_vertices >> num_faces >> n))
		{exit;}
	cout<<num_vertices<<endl;
	
	float ra, rb, rc;

	vector < vector<point> > temporary = calculate_centroid("standingcentroids.off");

	vector<point> final = temporary[2];
//	cout<<"test "<<test[15].x<<" "<<test[15].y<<" "<<test[15].z<<endl;
	vector<point> init = temporary[0];
//	cout<<"test1 "<<test1[15].x<<" "<<test1[15].y<<" "<<test1[15].z<<endl;


	vector<float> initangle;
	vector<point> initused;
	vector<float> finalangle;// 16 13 5 0 
	vector<point> finalused;

	vector<float> anglediff;

	initused.push_back(init[0]);
	initused.push_back(init[5]);
	initused.push_back(init[13]);
	initused.push_back(init[16]);

	finalused.push_back(final[0]);
	finalused.push_back(final[5]);
	finalused.push_back(final[13]);
	finalused.push_back(final[16]);

	// if (numfile<5){

			vector<float> coeff_init = co_effs(initused);

			for (int i=0;i<init.size();i++){
				float angle = normal(init[i].x,coeff_init[0],coeff_init[1],coeff_init[2],coeff_init[3]);
				initangle.push_back(angle);
			}

			vector<float> coeff_final = co_effs(finalused);

			for (int i1=0;i1<final.size();i1++){
				float angle = normal(final[i1].x,coeff_final[0],coeff_final[1],coeff_final[2],coeff_final[3]);
				finalangle.push_back(angle);
			}

			for(int j=0;j<initangle.size();j++){
				if (finalangle[j] <0 && initangle[j] >0){ float temp = initangle[j]; initangle[j] = -(temp);}
				if (finalangle[j] >0 && initangle[j] <0){ float temp = finalangle[j]; finalangle[j] = -(temp);}

				if (j == 0){
					anglediff.push_back(initangle[j]-finalangle[j]);
				}
				else {
					anglediff.push_back(initangle[j]-finalangle[j]);
				}
			}

		// }
			if (numfile == 1){
				for (int i = 0;i< init.size();i++){
					cout << initangle[i] <<"  "<<finalangle[i] << "  "<< anglediff[i]<<endl;
				}
			}


			cout<<"angle "<<numfile<<" "<< anglediff[numfile]<<endl;
	for(int i=0; i<num_vertices; i++)  //saving information of every points in vectors
	{
		getline(myfile,line);
		str = line;
		istringstream iss1(str);
		float a, b, c;
		if(!(iss1 >> a >> b >> c))
			{exit;}
		// vector<point> init = fillVectors();
		// vector<point> cv = calculate_centroid();
		

		point oc = init[numfile];
		point ct = final[numfile];
		float vx = ct.x - oc.x;
		float vy = ct.y - oc.y;

		float wx = a + vy;//......changed vx to vy as iv contains (y,x,z) and .off contains (x,y,z)
		float wy = b + vx;//......changed vy to vx
		float wz = c; 


		
		
		point beforeRot = point(wx,wy,wz);
		point about = point(ct.y,ct.x,ct.z);

		point afterRot = rotate_point(beforeRot,about,anglediff[numfile]);

		//writefile<<beforeRot.x<<" "<<beforeRot.y<<" "<<beforeRot.z<<endl;
		writefile<<afterRot.x<<" "<<afterRot.y<<" "<<afterRot.z<<endl;
	}
	
	while(!myfile.eof())  //saving the last information about how faces are formed from vertices
	{
		getline (myfile,line);
		writefile<< line<<endl;
		str = line;
		
	}
}

int main()
{
	mapofffile("StandingT01.off","E:/Study/Project/integrated/integrated/Shivam/new_supine/newRatios/TSu_T01.off");
	mapofffile("StandingT02.off","E:/Study/Project/integrated/integrated/Shivam/new_supine/newRatios/TSu_T02.off");
	mapofffile("StandingT03.off","E:/Study/Project/integrated/integrated/Shivam/new_supine/newRatios/TSu_T03.off");
	mapofffile("StandingT04.off","E:/Study/Project/integrated/integrated/Shivam/new_supine/newRatios/TSu_T04.off");
	mapofffile("StandingT05.off","E:/Study/Project/integrated/integrated/Shivam/new_supine/newRatios/TSu_T05.off");
	mapofffile("StandingT06.off","E:/Study/Project/integrated/integrated/Shivam/new_supine/newRatios/TSu_T06.off");
	mapofffile("StandingT07.off","E:/Study/Project/integrated/integrated/Shivam/new_supine/newRatios/TSu_T07.off");
	mapofffile("StandingT08.off","E:/Study/Project/integrated/integrated/Shivam/new_supine/newRatios/TSu_T08.off");
	mapofffile("StandingT09.off","E:/Study/Project/integrated/integrated/Shivam/new_supine/newRatios/TSu_T09.off");
	mapofffile("StandingT10.off","E:/Study/Project/integrated/integrated/Shivam/new_supine/newRatios/TSu_T10.off");
	mapofffile("StandingT11.off","E:/Study/Project/integrated/integrated/Shivam/new_supine/newRatios/TSu_T11.off");
	mapofffile("StandingT12.off","E:/Study/Project/integrated/integrated/Shivam/new_supine/newRatios/TSu_T12.off");
	mapofffile("StandingL01.off","E:/Study/Project/integrated/integrated/Shivam/new_supine/newRatios/TSu_L01.off");
	mapofffile("StandingL02.off","E:/Study/Project/integrated/integrated/Shivam/new_supine/newRatios/TSu_L02.off");
	mapofffile("StandingL03.off","E:/Study/Project/integrated/integrated/Shivam/new_supine/newRatios/TSu_L03.off");
	mapofffile("StandingL04.off","E:/Study/Project/integrated/integrated/Shivam/new_supine/newRatios/TSu_L04.off");
	mapofffile("StandingL05.off","E:/Study/Project/integrated/integrated/Shivam/new_supine/newRatios/TSu_L05.off");

	getch();
	return 0;
}