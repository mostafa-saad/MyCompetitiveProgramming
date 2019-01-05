/*************************************************************************}
{*                                                                       *}
{*                                  CEOI 2004                            *}
{*                                                                       *}
{*   Sample solution:     Clouds                                         *}
{*   File:                CLO.CPP                                        *}
{*   Author:              PIOTR STANCZYK                                 *}
 *************************************************************************/
#include <cstdio>
#include <algorithm>
#include <vector>
#define MAX_CLOUDS 1000
#define CLOUD_SIZE 1000

typedef long long int lli;
typedef unsigned long long int ulli;
const ulli low_part  = 2147483647;          /* 2^31 - 1 */
const ulli high_part = low_part * (low_part + 2); /* 2^62 - 1 */
using namespace std;

struct point {
	int x,y;
};

struct superlong {
	ulli high, low;
};

struct crossing {  /* Intersection point             */
	lli posh, posl;  /* Relative position of the point */
	short int cloud; /* Owner of the point             */
	char type;       /* Type of intersection           */
};

int vel_x, vel_y, clouds; /* Velocity vector and the number of clouds */
vector<crossing> cr;      /* Vector of intersection points          */


inline superlong multiply(ulli v1, ulli v2)
/* Multiplies two unsigned long long ints and returns the result as superlong. *
 * This function assumes that multiplied values are at most 62-bits long       */
{
	superlong val;
	ulli x = (v1 & low_part) * (v2 >> 31) + (v1 >> 31) * (v2 & low_part);
	val.low = (v1 & low_part) * (v2 & low_part);
	val.high = (v1 >> 31) * (v2 >> 31);
	val.low  += (x & low_part) << 31;
	val.high += (x >> 31) + (val.low >> 62);
	val.low  = val.low & high_part;
	return val;
}

inline int compare(const crossing& a, const crossing& b)
/* Compares a position of two given crossing points */
{
	superlong a1 = multiply(a.posh, b.posl);
	superlong b1 = multiply(a.posl, b.posh);
	if (a1.high == b1.high) {
		if (a1.low == b1.low) return 0;
		if (a1.low < b1.low) return -1;
		return 1;
	}
	if (a1.high < b1.high) return -1;
	return 1;  
}

inline bool cmp(const crossing& a, const crossing& b)
{
	return (compare(a, b) == -1);
}

int side(const point& a)
/* Determines the location of a given point against velocity vector */
{
	lli x = (lli)vel_x * (lli)a.y - (lli)vel_y * (lli)a.x;
	if (x == 0) return 0; else
	if (x > 0) return 1; else
	return -1;
}

void Add_intersection(const point& a, const point& b, short int cloud, char type)
/* Examines an intersection point between velocity vector and (a,b) segment */
{
	crossing c;
	/* The relative distance of the crossing point from the laser beam (point [0,0]) *
	 * is defined as c.posh/c.posl. In order to keep arithmetic precision we have    *
	 * to represent this value as a fraction                                         */
	c.posh = lli (b.y) * lli (a.x) - lli (b.x) * lli (a.y);
	c.posl = lli (vel_y) * lli (a.x - b.x) - lli (vel_x) * lli (a.y - b.y);
	if (c.posh < 0 && c.posl < 0) {
		c.posh = -c.posh;
		c.posl = -c.posl;
	} else 
	if (c.posh < 0 || c.posl < 0) return; /* Examined intersection is not important for as */
	c.cloud = cloud;
	c.type = type;
	cr.push_back(c);
}

void Read_Data()
/* Reads data and finds all intersection points */
{
	int size;
	point cloud[CLOUD_SIZE];
	scanf("%d %d %d", &clouds, &vel_x, &vel_y);
	vel_x = -vel_x;
	vel_y = -vel_y;
	
	for(int x = 0; x < clouds; ++x) {
		scanf("%d", &size);
		for(int y = 0; y < size; ++y) {
			scanf("%d %d", &cloud[y].x, &cloud[y].y);
		}
		int pos = 0, f_side, l_side;
		while ( (f_side = side(cloud[pos])) == 0) ++pos; /* Finds a vertex not located above velocity vector */
		
		int y = 1;
		while (y <= size) {
			l_side = f_side;
			f_side = side(cloud[(pos + y) % size]);
			switch (l_side * f_side) {
				
				case 1 : /* Vertices are located on the same side -> no intersection */
				++y;
				break;
				
				case -1 : /* Vertices are located on a different sides -> intersection found */
				Add_intersection(cloud[(pos + y - 1) % size], cloud[(pos + y) % size], x, 0);
				++y;
				break;
				
				case 0 : /* Vertex is located directly above velocity vector -> further verification */
				int beg = pos + y;
				while ( (f_side = side(cloud[(pos + y) % size])) == 0) ++y;
				if (pos + y != beg + 1) {
					Add_intersection(cloud[(pos + y) % size], cloud[(pos + y - 1) % size], x, (l_side == f_side) ? 1 : 2);
					Add_intersection(cloud[(beg - 1) % size], cloud[beg % size], x, 1);
				} else {
					Add_intersection(cloud[(pos + y) % size], cloud[(pos + y - 1) % size], x, (l_side == f_side) ? 3 : 0);
				}
				break;
			}
		}
	}
}

int Count_Result()
/* Searches the sorted list of intersection points and calculates the result */
{
	bool inside[MAX_CLOUDS];  /* is a cloud directly above the laser beam */
	bool on_edge[MAX_CLOUDS]; /* is an edge of a cloud directly above the laser beam */
	int am_edges = 0, am_inside = 0, result = 0;
	crossing location;
	location.posh = 0; /* Sets the actual location to the    */
	location.posl = 1; /* initial position of the laser beam */
	
	for(int x = 0; x < clouds; ++x)
	inside[x] = on_edge[x] = false;
	
	for(__typeof (cr.begin()) it = cr.begin(); it != cr.end(); ++it) {
		if (am_inside == 0 && am_edges == 0 && compare(location,*it) != 0)
		++result;
		
		location = *it;
		
		if (location.type == 1 || location.type == 2) /* Intersection changes the state of an edge */
		(on_edge[location.cloud] = !on_edge[location.cloud]) ? ++am_edges : --am_edges;
		
		if (location.type == 0 || location.type == 2) /* Intersection changes the state of a cloud */
		(inside[location.cloud] = !inside[location.cloud]) ? ++am_inside : --am_inside;
	}
	return result;
}

int main()
{
	Read_Data();
	for(int i=0;i<int(cr.size()); i++) {
		if (i>1) {
			int j=rand()/(RAND_MAX/i); 
			if (j>=i) j=i;
			if (j<0) j=0;
			swap(cr[i],cr[j]);
		}
	}
	sort(cr.begin(), cr.end(), cmp);
	printf("%d\n", Count_Result());
	return 0;
}
