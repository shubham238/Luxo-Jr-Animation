
#include "rotatepoint.h"

#define PI 3.14159

point rotate_point(point r, point p, double theta)
{
	point new_r;
	double t=theta*(PI/180);
	//double rad=sqrt((r.x-p.x)*(r.x-p.x)+(r.z-p.z)*(r.z-p.z));
	new_r.x=p.x+(cos(t)*(r.x-p.x)+sin(t)*(r.y-p.y));
	new_r.y=p.y+(cos(t)*(r.y-p.y)-sin(t)*(r.x-p.x));
	new_r.z=r.z;     ///counter clockwise rotation I have used rotation matrix to calculate new positions
	return new_r;
}

vector<point> rotate_keypoints(vector<point> oldlist, float sx, float sy, float sz, double theta)
{
	vector<point> newlist;
	newlist.clear();
	point p = point(sx,sy,sz);
	for(int i=0; i<oldlist.size(); i++)
	{
		point r = oldlist[i];
		point newr = rotate_point(r,p,theta);
		newlist.push_back (newr);
	}
	return newlist;
}


