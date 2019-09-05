//IOI 2019
//Split - Version 1.1 - First Solution
//Current Version: 9 May 2019
//Older version: 31 March 2019
//Mahdi Safarnejad Boroujeni

#define forn(i, n) for (int i = 0; i < int(n); i++)

#include "split.h"

#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 1000000+110;
typedef pair<int,int> intpair;

int n;
vector<int> a[maxn];
vector<int> result(maxn);
intpair b[3];

bool finishedPhase1 = false;

int mark[maxn], size[maxn];
int counter=1, startingtime[maxn], mintime[maxn];

int dfs2(int v, int goal, int comp, bool ignore_st=false) {
	int sum=1;
	mark[v]=2;
	result[v]=comp;
	goal -= 1;
	forn(i, a[v].size())
    if (goal > 0 && mark[a[v][i]] < 2 && (ignore_st || (startingtime[a[v][i]] > startingtime[v]))) {
        int thisSize = dfs2(a[v][i], goal, comp, ignore_st);
        sum += thisSize;
        goal -= thisSize;
    }
    return sum;
}

void dfs(int v, int par) {
    mark[v]=1;
    size[v]=1;
    startingtime[v] = counter++;
    mintime[v] = startingtime[v];
    int removablesSum=0;
    forn(i, a[v].size())
        if (!mark[a[v][i]]) {
            dfs(a[v][i], v);
            if (finishedPhase1)
            	return;
            size[v]+=size[a[v][i]];
            mintime[v] = min(mintime[v], mintime[a[v][i]]);
            if (mintime[a[v][i]] < startingtime[v])
                removablesSum += size[a[v][i]];
        } else if (a[v][i]!=par) {
            mintime[v] = min(mintime[v], mintime[a[v][i]]);
        }
    if (size[v] >= b[0].first) {
    	finishedPhase1 = true;
    	if (n - size[v] + removablesSum < b[0].first)
    		return; //No Solution
    	int element = 0;
    	if (n - size[v] + removablesSum < b[1].first)
    		element = 1;
    	result[v] = b[element].second;
        mark[v] = 2;
    	int goal = b[element].first - 1;
    	forn(i, a[v].size()) {
    		if (mark[a[v][i]] < 2 && goal > 0 && mintime[a[v][i]] >= startingtime[v] && startingtime[a[v][i]] > startingtime[v])
    			goal -= dfs2(a[v][i], goal, b[element].second);
    	}
    	forn(i, a[v].size()) {
    		if (mark[a[v][i]] < 2 && goal > 0 && mintime[a[v][i]] < startingtime[v] && startingtime[a[v][i]] > startingtime[v])
    			goal -= dfs2(a[v][i], goal, b[element].second);
    	}
    	dfs2(0, b[1-element].first, b[1-element].second, true);
    	forn(i, n)
    		if (result[i]==0)
    			result[i]=b[2].second;
    }
}

vector <int> find_split(int n_, int a_, int b_, int c_, vector <int> p, vector <int> q) {
	n = n_;
    b[0]=intpair(a_, 1); b[1]=intpair(b_, 2); b[2]=intpair(c_, 3);
	sort(b, b+3);
	forn(i, p.size()) {
		a[p[i]].push_back(q[i]);
		a[q[i]].push_back(p[i]);
	}
    dfs(0, -1);
		result.resize(n);
    return result;
}
