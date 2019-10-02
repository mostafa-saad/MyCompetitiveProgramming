// By fegla

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <sstream>
#include <bitset>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <complex>
using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) ((int)(x).size())

#define MXSZ 100010

void computePrefixFunction(const char* p, vector<int>& pf) {
	int m = strlen(p);
	pf.resize(m+1);
	pf[0] = 0;
	int k = 0;
	for (int q = 1; q <= m - 1; ++q) {
		while (k > 0 && p[k] != p[q])
			k = pf[k - 1];
		if (p[k] == p[q])
			k++;
		pf[q] = k;
	}
}
int kmpMatch(const char *t, const char *p, int isOdd, int i, vector<int> & pf) {
	int n = strlen(t);
	int m = strlen(p);


	int q = 0;

	for (; i < n; ++i) {
		while (q > 0 && p[q] != t[i])
			q = pf[q - 1];
		if (p[q] == t[i])
			q++;
		if (q == m && (i - m + 1)%2 == isOdd )
			return i + 1;
	}
	return -1;
}

char pattern[MXSZ]; //the one that has # and *
char toMatch[MXSZ];



int main()
{
	int ii = 1;
	while(scanf("%s",pattern)!= EOF)
	{
		vector <string> segments;
		// build kmp for the pattern segment (not including * or #)
		int len = strlen(pattern);
		int cur = -1;
		if( !isdigit(pattern[0]) )
			segments.push_back("");
		for(int i = 0 ; i < len ; ++i )
		{
			if( cur == isdigit(pattern[i]) )
			{
				segments.back() += pattern[i];

			}else{
				cur = isdigit(pattern[i]);
				segments.push_back("");
				segments.back() += pattern[i];

			}
		}
		if(!isdigit(segments.back()[0]))
			segments.push_back("");
		vector<int>  wc(segments.size()); //wild cards
		for(int i = 1; i < segments.size() ; i+= 2)
			wc[i] = count(segments[i].begin(),segments[i].end(),'#');
		vector<vector <int> > pre(segments.size());
		for (int i = 0; i < segments.size(); i += 2)
			computePrefixFunction(segments[i].c_str(),pre[i]);

		int jj = 1;
		int lastI;
		while(scanf("%s",toMatch)!=EOF){
			if( strcmp(toMatch,"END") == 0 )
				break;
			else if( strcmp(toMatch,"QUIT") == 0 )
				return 0;
			printf("%d.%d. ",ii,jj);
			jj++;

			if( segments.size() == 1 ){
				if( strcmp(segments[0].c_str(),toMatch) )
					goto nomatch;
				printf("match\n");
				continue;
			}
			cur = segments[0].size();
			if( memcmp(segments[0].c_str(),toMatch,cur) )
				goto nomatch;
			for(int i = 1 ; i < segments.size()-1 ; ++i )
			{
				if(i%2) //wc
					cur += wc[i];
				else{
					cur = kmpMatch(toMatch,segments[i].c_str(),cur%2,cur,pre[i]);
					if( cur == -1 )
						goto nomatch;
				}
			}
			lastI = strlen(toMatch)-segments.back().size();

			if( cur%2 != lastI%2 )
				goto nomatch;
			if( memcmp(segments.back().c_str(),toMatch+lastI,segments.back().size()))
				goto nomatch;
			printf("match\n");
			continue;
			nomatch:
			printf("not\n");
		}
		ii++;
	}
	return 0;
}
