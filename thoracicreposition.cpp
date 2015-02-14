#include <iostream>
#include "conio.h"
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "points.h"
#include "rotatepoint.h"
//#include "bezier.h"
//#include "normal_bez.h"
#include "centroid.h"
//#include "bez_control_pts.h"

#include "cubic.h"

using namespace std;

void buildvertebrae(string name, string name2)
{
	
	string str;
	string line;
	int numfile;

	if(name == "StandingT01.off"){numfile = 11;}
	else if(name == "StandingT02.off"){numfile = 10;}
	else if(name == "StandingT03.off"){numfile = 9;}
	else if(name == "StandingT04.off"){numfile = 8;}
	else if(name == "StandingT05.off"){numfile = 7;}
	else if(name == "StandingT06.off"){numfile = 6;}
	else if(name == "StandingT07.off"){numfile = 5;}
	else if(name == "StandingT08.off"){numfile = 4;}
	else if(name == "StandingT09.off"){numfile = 3;}
	else if(name == "StandingT10.off"){numfile = 2;}
	else if(name == "StandingT11.off"){numfile = 1;}
	else if(name == "StandingT12.off"){numfile = 0;}
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

	vector< vector<point> > temporary1new = calculate_centroid("standingcentroids.off");
	vector<point> temporary1 = spline_transformation(temporary1new);

	vector<point> iv = temporary1new[0];
	vector<point> lumb = temporary1new[2];

	vector<point> bv = temporary1;

	if (numfile==0){

		cout<< "bv"<< endl;

		for (int i=(temporary1.size()-1);i>-1;i--){
			cout << bv[i].y << " "<< bv[i].x <<" "<< "0.0" <<endl; 
		}
		cout<< "iv"<<endl;

		for (int i=(lumb.size()-1);i>-1;i--){
			cout << lumb[i].y << " "<< lumb[i].x <<" "<< "0.0" <<endl; 
		}
	}


	

	
	float ra, rb, rc;
	for(int i=0; i<num_vertices; i++)  //saving information of every points in vectors
	{
		getline(myfile,line);
		str = line;
		istringstream iss1(str);
		float a, b, c;
		if(!(iss1 >> a >> b >> c))
			{exit;}
		
		
		point oc = iv[numfile+5];
		point bt = bv[numfile];
		
		float dx = bt.x - oc.x;
		float dy = bt.y - oc.y;

		float wx = a + dy;
		float wy = b + dx;
		float wz = c; 

		// point beforeRot = point(wx,wy,wz);
		// point about = point(bt.y,bt.x,bt.z);

		// point afterRot = rotate_point(beforeRot,about,anglediff[numfile]);
		

		//writefile<<afterRot.x <<" "<<afterRot.y <<" "<<afterRot.z<<endl; 
		writefile << wx << " " << wy << " " << wz << endl;
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
	buildvertebrae("StandingT01.off","E:/Study/Project/integrated/integrated/Shivam/slope supine/Su_T01.off");
	buildvertebrae("StandingT02.off","E:/Study/Project/integrated/integrated/Shivam/slope supine/Su_T02.off");
    buildvertebrae("StandingT03.off","E:/Study/Project/integrated/integrated/Shivam/slope supine/Su_T03.off");
	buildvertebrae("StandingT04.off","E:/Study/Project/integrated/integrated/Shivam/slope supine/Su_T04.off");
	buildvertebrae("StandingT05.off","E:/Study/Project/integrated/integrated/Shivam/slope supine/Su_T05.off");
	buildvertebrae("StandingT06.off","E:/Study/Project/integrated/integrated/Shivam/slope supine/Su_T06.off");
	buildvertebrae("StandingT07.off","E:/Study/Project/integrated/integrated/Shivam/slope supine/Su_T07.off");
	buildvertebrae("StandingT08.off","E:/Study/Project/integrated/integrated/Shivam/slope supine/Su_T08.off");
	buildvertebrae("StandingT09.off","E:/Study/Project/integrated/integrated/Shivam/slope supine/Su_T09.off");
	buildvertebrae("StandingT10.off","E:/Study/Project/integrated/integrated/Shivam/slope supine/Su_T10.off");
	buildvertebrae("StandingT11.off","E:/Study/Project/integrated/integrated/Shivam/slope supine/Su_T11.off");
	buildvertebrae("StandingT12.off","E:/Study/Project/integrated/integrated/Shivam/slope supine/Su_T12.off");
	
	getch();
	return 0;
}