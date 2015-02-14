#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "conio.h"
#include "nodeshift.h"
#include "cubic.h"
#include "points.h"
#include "centroid.h"
//#include "bezier.h"
#include <fstream>
#include <sstream>
//#include "normal.h"
#include "rotatepoint.h"

using namespace std;


void insertion_sort (vector<float> arr, int length){
	 	int j;float temp;
		
	for (int i = 1; i < length; i++){
		j = i;
		
		while ((j > 0) && (arr[j] < arr[j-1])){
			  
			  temp = arr[j];
			  arr[j] = arr[j-1];
			  arr[j-1] = temp;
			  j--;
		}
		
	}
	
}


void rewrite(string readname, string writename)
{
	
	vector< vector<point> > lumbarcentroids = calculate_centroid("standingcentroids.off");
	//vector<point> spine = fillVectors();
	vector<point> spine = lumbarcentroids[0];

	//storing coefficients for intial curve
	vector<float> initcurve = construct_curve();

	//storing coefficients for final curve	
	vector<point> thorax = spline_transformation(lumbarcentroids);
	vector<point> lumbar = lumbarcentroids[2];

	vector<point> newspine;
	point ln5 = lumbar[0]; newspine.push_back(ln5);
	point tn12 = thorax[0]; newspine.push_back(tn12);
	point tn4 = thorax[8]; newspine.push_back(tn4);
	point tn1 = thorax[11]; newspine.push_back(tn1);
	vector<float> fincurve = co_effs(newspine);

	string line;
	string str;

	ifstream readfile;
	readfile.open(readname.c_str());

	ofstream writefile;
	writefile.open(writename.c_str());

	ofstream sffile;
	sffile.open("shortening factor.txt");

	getline(readfile,line);  //removing the first line
	cout<<line<<endl;
	writefile<< line<<endl;;

	getline(readfile,line);  //extracting no of vertices and faces from next line
	cout<<line<<endl;
	writefile<< line<<endl;
	str = line;
	istringstream iss(str);
	int num_vertices, num_faces, n;
	if(!(iss >> num_vertices >> num_faces >> n))
		{exit;}
	cout<<num_vertices<<endl;
	
	//defining limits for binary search
	point il = spine[0];
	point ir = spine[16];
	point fl = lumbar[0];
	point fr = thorax[11];

	//cout << il.x;

	// point center = point(548.571, 389.219, 171.919);
	// vector<float> t1normal = normal(fincurve, center.x);

	vector<float> normal_il_init = normal(initcurve, il.x);	//.......l5 standing
	float const_il = il.y + (il.x/normal_il_init[0]);
	float norslope_il_init = normal_il_init[1]/normal_il_init[0];
	float init_angle_il = atan (norslope_il_init) * 180 / 3.14159265 ;

	vector<float> normal_ir_init = normal(initcurve,ir.x);	//.......t1 standing
	float const_ir = ir.y + (ir.x/normal_ir_init[0]);
	// float norslope_ir_init = normal_ir_init[1]/normal_ir_init[0];
	// float init_angle_ir = atan (norslope_ir_init) * 180 / 3.14159265 ;

	vector<float> normal_il_final = normal(fincurve,il.x);	//.......l5 standing
	float norslope_il_final = normal_il_final[1]/normal_il_final[0];
	float final_angle_il = atan (norslope_il_final) * 180 / 3.14159265 ;

	float anglediff_il =  init_angle_il - final_angle_il ;

	//**************************************** shortening factor algo******************************


	vector<point> keyptInit;
	vector<point> keyptFinal;
	vector<float> uvalinit;
	vector<float> uvalfinal;
	vector<float> initdist;
	vector<float> finaldist;
	vector<float> shortFact;

	keyptInit.push_back(point(357.789,403.0,113.878));
	keyptInit.push_back(point(350.356,405.121,252.383));
	keyptInit.push_back(point(202.384,270.433,179.88));
	keyptInit.push_back(point(-5.747,454.565,169.940));
	keyptInit.push_back(point(146.836,364.747,276.348));
	keyptInit.push_back(point(154.933,375.13,78.769));

	keyptFinal.push_back(point(356.043,230.274,246.295));
	keyptFinal.push_back(point(361.875,235.685,100.811));
	keyptFinal.push_back(point(200.819,132.205,169.024));
	keyptFinal.push_back(point(8.258,295.674,163.014));
	keyptFinal.push_back(point(144.659,218.046,268.744));
	keyptFinal.push_back(point(143.257,203.95,80.894));
	



	for (int i=0;i<6;i++){
		vector<float> temp = bin_search(keyptInit[i].x,keyptInit[i].y,initcurve,il,ir);
		uvalinit.push_back(temp[0]);
		float dist = sqrt(temp[1]*temp[1] + temp[2]*temp[2]);
		initdist.push_back(dist);
	}

	for (int i=0;i<6;i++){
		vector<float> temp = bin_search(keyptFinal[i].x,keyptFinal[i].y,fincurve,il,ir);
		uvalfinal.push_back(temp[0]);
		float dist = sqrt(temp[1]*temp[1] + temp[2]*temp[2]);
		finaldist.push_back(dist);
	}

	for (int i=0;i<6;i++){
		float sf = finaldist[i]/initdist[i];
		shortFact.push_back(sf);
	}

	insertion_sort(uvalinit,6);
	insertion_sort(uvalfinal,6);
	insertion_sort(shortFact,6);



//*******************************************************************************************************

	float ra, rb, rc;
	for(int i=0; i<num_vertices; i++)  //saving information of every points in vectors
	{
		getline(readfile,line);
		str = line;
		//cout<<str<<endl;
		istringstream iss1(str);
		float a, b, c;
		if(!(iss1 >> a >> b >> c))
			{exit;}
		
		// float checksign_il = (a + (b/normal_il_init[0]) - const_il)*(il.y + ((il.x - 5)/normal_il_init[0]) - const_il);
		// float checksign_ir = (a + (b/normal_ir_init[0]) - const_ir)*(ir.y + ((ir.x + 5)/normal_ir_init[0]) - const_ir);

		


		// if (checksign_il >= 0){

		// //	cout << "check lag gaya"<<endl;
		// //	cout<< anglediff_il<< endl;
		// //***********************************************************************************
		// 	point beforeRot = point(a,b,c);
		// 	point about = point(spine[0].y,spine[0].x,spine[0].z);

		// 	point afterRot = rotate_point(beforeRot,about,(180.0-anglediff_il));

		// 	writefile<<afterRot.x<<" "<<afterRot.y<<" "<<afterRot.z<<endl;
		// //writefile << a + ()

		// }		

		// else if (checksign_ir >= 0){
		// 	point beforeRot = point(a,b,c);
		// 	point about = point(spine[16].y,spine[16].x,spine[16].z);

		// 	point afterRot = rotate_point(beforeRot,about,(180.0-anglediff_il));

		// 	writefile<<afterRot.x<<" "<<afterRot.y<<" "<<afterRot.z<<endl;
		
		// }
		
		
		// else 
		// {

		//	cout<< "else me gayaaa"<< endl;

			vector<float> ud = bin_search(b, a, initcurve, il, ir);
			 float newcurvepoint = (ud[0]*(newspine[3].x- newspine[0].x)) + newspine[0].x;
			 float wx,wy;

			
			// float wy = newcurvepoint + ud[1]; 
			// float yy = fincurve[0]*(pow(newcurvepoint,3.0)) + fincurve[1]*(pow(newcurvepoint,2.0)) + fincurve[2]*(newcurvepoint) + fincurve[3];

			// float wx = yy + ud[2];
			 float tempsf;

			if (ud[0] < uvalinit[0]){

				//cout<<"case 1"<<endl;

				tempsf = shortFact[0] + ((shortFact[1]-shortFact[0])/(uvalinit[1]-uvalinit[0]))* (ud[0]-uvalinit[0]);

				wy = newcurvepoint + ud[1]*tempsf; 
				float yy = fincurve[0]*(pow(newcurvepoint,3.0)) + fincurve[1]*(pow(newcurvepoint,2.0)) + fincurve[2]*(newcurvepoint) + fincurve[3];

				wx = yy + ud[2]*tempsf;

			}

			else if (ud[0] > uvalinit[5]){
				//cout<<"case 2"<<endl;

				tempsf = shortFact[4] + ((shortFact[5]-shortFact[4])/(uvalinit[5]-uvalinit[4]))*(ud[0]-uvalinit[4]);
				
				wy = newcurvepoint + ud[1]*tempsf; 
				float yy = fincurve[0]*(pow(newcurvepoint,3.0)) + fincurve[1]*(pow(newcurvepoint,2.0)) + fincurve[2]*(newcurvepoint) + fincurve[3];

				wx = yy + ud[2]*tempsf;

			}

			else {
				//cout<<"case 3"<<endl;
				//int bef = 1;
				int ii=1;
				while (ud[0]>uvalinit[ii] && ii<5){
					ii++;
				}

				tempsf = shortFact[ii-1] + ((shortFact[ii]-shortFact[ii-1])/(uvalinit[ii]-uvalinit[ii-1]))*(ud[0]-uvalinit[ii-1]);
				
				wy = newcurvepoint + ud[1]*tempsf; 
				float yy = fincurve[0]*(pow(newcurvepoint,3.0)) + fincurve[1]*(pow(newcurvepoint,2.0)) + fincurve[2]*(newcurvepoint) + fincurve[3];

				wx = yy + ud[2]*tempsf;

			}



			//writefile<<" "<< newcurvepoint<<"___"<<ud[3]<<"___"<< yy<< "___"<< ud[4] <<  "___" << (ud[2]) <<"___"<<(ud[6])<<"___" <<wx <<endl;

			writefile << wx<<" "<<wy<<" "<< (c-8.0) <<endl;
			sffile << wx<<" "<<wy<<" "<<(c-8.0)<<" "<<tempsf<<endl;
		// }
	}


	while(!readfile.eof())
	{
		getline (readfile, line);
		writefile<< line<<endl;

	}

}

int main()
{

		// rewrite("M05_STANDI_liver.off","E:/Study/Project/integrated/integrated/Shivam/organs/AF_M05_SUPINE_liver.off");
		// rewrite("M05_STANDI_kidney-L.off","E:/Study/Project/integrated/integrated/Shivam/organs/AF_M05_SUPINE_kidney-L.off");
	 //    rewrite("M05_STANDI_kidney-R.off","E:/Study/Project/integrated/integrated/Shivam/organs/AF_M05_SUPINE_kidney-R.off");

	    rewrite("M05_STANDI_abdominal_bag.off", "AF_M05_SUPINE_abdominal_bag.off");
	  // rewrite("M05_STANDI_bagskel.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_bagskel.off");
	  // rewrite("M05_STANDI_bagsldm.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_bagsldm.off");
	  // rewrite("M05_STANDI_fem-L.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_fem-L.off");
	  // rewrite("M05_STANDI_fem-R.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_fem-R.off");
	  // rewrite("M05_STANDI_kidpos.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_kidpos.off");
	  // rewrite("M05_STANDI_landmarks_pelvis.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_landmarks_pelvis.off");
	  // rewrite("M05_STANDI_landmarks_spine.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_landmarks_spine.off");
	  // rewrite("M05_STANDI_landmarks_sternum.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_landmarks_sternum.off");
	  // rewrite("M05_STANDI_liver.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_liver.off");
	// rewrite("M05_STANDI_livpos.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_livpos.off");
	// rewrite("M05_STANDI_pelvis.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_pelvis.off");
	// rewrite("M05_STANDI_skel.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_skel.off");
	// rewrite("M05_STANDI_skeleton.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_skeleton.off");
	// rewrite("M05_STANDI_skin.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_skin.off");
	// rewrite("M05_STANDI_solidland.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_solidland.off");
	// rewrite("M05_STANDI_solidskel.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_solidskel.off");
	// rewrite("M05_STANDI_solidspst.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_solidspst.off");
	// rewrite("M05_STANDI_spleen.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_spleen.off");
	// rewrite("M05_STANDI_spleenpos.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_spleenpos.off");
	// rewrite("M05_STANDI_sternum.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_sternum.off");
	// rewrite("M05_STANDI_thoracic_bag.off","E:/Study/Project/integrated/integrated/Shivam/organs/new/AF_M05_STANDI_thoracic_bag.off");





	getch();
	return 0;
}










