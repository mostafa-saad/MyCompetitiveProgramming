/*
 * 1.cpp
 * Another buggy code by mostafa_saad
 *
 *  Created on: Jul 27, 2009
 */

#include<string>
#include<memory.h>
#include<set>
#include<map>
#include<list>
#include<iomanip>
#include<cmath>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<complex>
#include<sstream>
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include <bits/stdc++.h>
using namespace std;

#define all(v)				((v).begin()), ((v).end())
#define sz(v)				((int)((v).size()))
#define clr(v, d)			memset(v, d, sizeof(v))
#define repi(i, j, n) 		for(int i=(j);i<(int)(n);++i)
#define repd(i, j, n) 		for(int i=(j);i>=(int)(n);--i)
#define repa(v)				repi(i, 0, sz(v)) repi(j, 0, sz(v[i]))
#define rep(i, v)			repi(i, 0, sz(v))
#define lp(i, cnt)			repi(i, 0, cnt)
#define lpi(i, s, cnt)		repi(i, s, cnt)
#define P(x)				cout<<#x<<" = { "<<x<<" }\n"
#define pb					push_back
#define MP					make_pair

typedef vector<int> vi;
typedef vector<double> vd;
typedef vector<vi> vvi;
typedef vector<vd> vvd;
typedef vector<string> vs;
typedef long long ll;
typedef long double ld;

const int OO = (int) 1e8; //Small -> WRONG, Large -> OVERFLOW

const double PI = acos(-1.0);
const double EPS = (1e-7);

int dcmp(double x, double y) {
	return fabs(x - y) <= EPS ? 0 : x < y ? -1 : 1;
}

const int MAX = 200;

int x1[MAX];
int Y1[MAX];
int z1[MAX];

int x2[MAX];
int y2[MAX];
int z2[MAX];

int grid[MAX][MAX][MAX];

int MX, MY, MZ;
int dx[] = { -1, 0, 0, 1, 0, 0 };
int dy[] = { 0, -1, 0, 0, 1, 0 };
int dz[] = { 0, 0, -1, 0, 0, 1 };

// Call it For X's, Y's and Z's
// When compressing a shape, and marking it in a 2D array,
// use sx, sy inclusive and ex, ey exclusive to express units
void intervalCompression(const vector<int>& axis, vector<int> &iToV, map<int,
		int> &vToI) {
	set<int> rank(axis.begin(), axis.end());

	iToV.resize(rank.size() + 4, -1); // s.size()+4 = the new frame boundary

	for (int i = 0; i < sz(axis); i++) {
		// using 1+distance is very important. It gives space such that flooding from 0, 0
		// can flood external faces of components
		int idx = 1 + distance(rank.begin(), rank.find(axis[i]));
		iToV[idx] = axis[i], vToI[axis[i]] = idx;
	}
}
/*
 int calArea(int color, vector<int> & x_iToV, vector<int> & y_iToV) {
 int area = 0;
 repa(grid) if (grid[i][j] && color == -1 || grid[i][j] == color)
 area += (x_iToV[i+1] - x_iToV[i]) * (y_iToV[j+1] - y_iToV[j]);	//cut rectangle
 return area;
 }
 */

void flood(int x, int y, int z) {
	if (grid[x][y][z] != 0)
		return; //cell not occupied by a box
	grid[x][y][z] = 2;

	lp(d, 6) {
		int nx = x + dx[d], ny = y + dy[d], nz = z + dz[d];
		if (nx >= 0 && ny >= 0 && nz >= 0 && nx < MX && ny < MY && nz < MZ)
			flood(nx, ny, nz);
	}
}

vector<int> x, y, z;
vector<int> ix, iy, iz;
map<int, int> xi, yi, zi;

struct point {
	int x, y, z;
};

int main() {
//	freopen("f.in", "rt", stdin);
//	freopen("f.txt", "wt", stdout);

	int cases;
	cin >> cases;

	while (cases--) {
		int n;
		cin >> n;

		x.clear(), y.clear(), z.clear();
		ix.clear(), iy.clear(), iz.clear();
		xi.clear(), yi.clear(), zi.clear();

		clr(grid, 0);

		//read & save
		lp(i, n) {
			cin >> x1[i] >> Y1[i] >> z1[i] >> x2[i] >> y2[i] >> z2[i];
			x2[i] += x1[i], y2[i] += Y1[i], z2[i] += z1[i];

			x.push_back(x1[i]), x.push_back(x2[i]);
			y.push_back(Y1[i]), y.push_back(y2[i]);
			z.push_back(z1[i]), z.push_back(z2[i]);
		}

		//compress
		intervalCompression(x, ix, xi);
		intervalCompression(y, iy, yi);
		intervalCompression(z, iz, zi);

		//mark
		lp(i, n) {
			x1[i] = xi[x1[i]], x2[i] = xi[x2[i]];
			Y1[i] = yi[Y1[i]], y2[i] = yi[y2[i]];
			z1[i] = zi[z1[i]], z2[i] = zi[z2[i]];

			//inclusive start, execlisve end
			for (int f = x1[i]; f < x2[i]; ++f) {
				for (int j = Y1[i]; j < y2[i]; ++j) {
					for (int k = z1[i]; k < z2[i]; ++k) {
						grid[f][j][k] = 1;
					}
				}
			}
		}
		//flood external area, not occupied by any body and ACCESSIBLE
		MX = sz(ix), MY = sz(iy), MZ = sz(iz);

		//flood(0, 0, 0);	//will MLE

		queue<point> q;
		point cur, nxt;
		cur.x = cur.y = cur.z = 0;
		q.push(cur);
		grid[cur.x][cur.y][cur.z] = 2;

		while (!q.empty()) {
			cur = q.front();
			q.pop();

			lp(d, 6) {
				int nx = cur.x + dx[d], ny = cur.y + dy[d], nz = cur.z + dz[d];
				if (nx >= 0 && ny >= 0 && nz >= 0 && nx < MX && ny < MY && nz
						< MZ && grid[nx][ny][nz] == 0) {
					grid[nx][ny][nz] = 2;
					nxt.x = nx, nxt.y = ny, nxt.z = nz;
					q.push(nxt);
				}
			}
		}

		// To find area of visible lengths in 3d shapes
		// Do floodfill (iterative) from 0, 0 to mark all space outside the cubes
		// A face is visible IFF cell x, y, z is marked as outside and a neighbor of it is not
		// The floodfill also help us in determining the space completely enclosed,
		// as cell marked with val != OUTSIDE is either INSIDE or INCUBE
		ll volume = 0, surfacesArea = 0;

		//inspect unit by unit and evaluate using real coordinates
		lp(i, MX)  lp(j, MY) lp(k, MZ) {
			ll x = ix[i + 1] - ix[i], y = iy[j + 1] - iy[j], z = iz[k+ 1] - iz[k];

			if (grid[i][j][k] != 2) // either 1 -> occupied or 0 -> space completely enclosed
				volume += x * y * z;

			lp(d, 6) {
				int nx = i + dx[d], ny = j + dy[d], nz = k + dz[d];
				if (nx >= 0 && ny >= 0 && nz >= 0 && nx < MX && ny < MY
						&& nz < MZ) {
					if (grid[i][j][k] == 2 && grid[nx][ny][nz] != 2) //one face outside and another inside
						surfacesArea += dx[d] ? y * z : dy[d] ? x * z : x * y;
				}
			}
		}

		cout << surfacesArea << " " << volume << "\n";

	}

	return 0;
}
