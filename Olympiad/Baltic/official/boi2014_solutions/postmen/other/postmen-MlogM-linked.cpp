#include <cstdio>
#include <set>
#include <cstring>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;
const int MaxN = 500010,
	  	  MaxM = 2*500010;

typedef pair<int,int> pii;
struct node {
	int next, edge;
};

pii mpair (int a, int b) {
	return pair<int, int> (min(a,b), max(a,b));
}

set<pii> SS;
int LN = 1;
node L[MaxM];
int E[MaxM][3];
int pr[MaxN] = {0}, C[MaxN];
int N, M, a, b;
bool visited[MaxN] = {0};
vector<int> path;
int newv = -1, u;

int getU (int i, int v) {
	return (v == E[i][0]) ? E[i][1] : E[i][0];
}

const int Maxl = 7000005;
char S[Maxl];

void printInt (int t) {
    int pnt = 0;

        int d = 100000;
        while (d > 1 && t / d == 0) d /= 10;
        for ( ; d > 0; d /= 10) 
           S[pnt++] = '0' + t / d % 10;
        S[pnt++] = ' ';

        S[pnt] = '\0';
        printf("%s", S);
}   



void dfs(int v) {
	path.clear();
	path.push_back(v);	
	while (v != -1) {
		visited[v] = true;
		newv = -1;
		while (pr[v] != -1) {
			int i = L[pr[v]].edge;
			pr[v] = L[pr[v]].next;
            u = getU(i, v);
			if (SS.find(mpair(u, v)) == SS.end()) {
				SS.insert(mpair(u, v));
				if (visited[u]) {
                    bool ar = false;
					newv = u;
                    int pnt = 0;
					while (!ar) {
						//printf("%d ", path.back());
                        if (path.back() == u) ar = true;
                        int d = 100000, t = path.back();
                        while (d > 1 && t / d == 0) d /= 10;
                        for ( ; d > 0; d /= 10)  S[pnt++] = '0' + t / d % 10;
                        S[pnt++] = ' ';
                        visited[path.back()] = false;
						path.pop_back();
					}
                    S[pnt] = '\0';
                    printf("%s\n", S);
                    path.push_back(u);
					//printf("%d\n", path.back());
				}else {
					newv = u;
					path.push_back(u);
				}
				break;
			}
		}
		if (newv == -1 and path.size() > 1) {
			newv = path.back();
			path.pop_back();
		}
		v =newv;
	}
	//visited[path[0]] = false;
}

void Parse(char lin[], int &a, int &b)
{
    int slen = strlen(lin);
    int pnt = 0;
    a = 0; b = 0;
    while (isdigit(lin[pnt])) {
        a = 10 * a + lin[pnt] - '0';
        pnt++;
    }
    while (!isdigit(lin[pnt])) pnt++;
    while (pnt < slen && isdigit(lin[pnt])) {
        b = 10 * b + lin[pnt] - '0';
        pnt++;
    }
}

int main() {
	path.reserve(MaxN);	
	scanf("%d%d\n", &N, &M);
	
	for (int i = 0; i < M; i++) {
		int a, b; 
		gets(S);
        Parse (S, a, b);
		E[i][0] = a;
		E[i][1] = b;

		if (pr[a] == 0) 
			pr[a] = LN;
		else  
			L[C[a]].next = LN;
		if (pr[b] == 0) 
			pr[b] = LN+1;
		else 
			L[C[b]].next = LN+1;
	
		C[a] = LN;
		C[b] = LN+1;
		L[LN].next = -1;
		L[LN].edge = i;
		L[LN+1].next = -1;
		L[LN+1].edge = i;
		LN += 2;			
	}
	
	for (int i = 1; i <= N; i++) 
		dfs(i);
		
	return 0;
}
