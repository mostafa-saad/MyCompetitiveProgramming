/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kolej (KOL)                                               *
 *   Plik:     kols5.cpp                                                 *
 *   Autor:    Miroslaw Michalski                                        *
 *   Opis:     Rozwiazanie powolne.
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <queue>
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;


const int MAXN=100057;
const int INF=1000000000;
int poc[MAXN],rev[MAXN],mini[MAXN],c[MAXN];
int n;
vector<int> tab[MAXN];
bool niet=false;


bool checkOut() {
	stack<int> st[2];
	for(int i=0;i<2;i++) st[i].push(-1);
	int passed = 1;
	for(int i=1;i<=n;i++) {
		if (c[i]!=0) st[c[i]-1].push(poc[i]); else return false;
		bool change = true;
		while (change) {
			change = false;
			for(int j=0;j<2;j++) {
				while (st[j].top()==passed) {
					passed++;
					st[j].pop();
					change = true;
				}
			}
		}
	}
	return (passed==n+1);
}


void paint(int p,int colour) {
	c[p]=colour;
	for(int i=0;i<(int)tab[p].size();i++) {
		if (c[tab[p][i]]==0) paint(tab[p][i],colour%2+1); else
		if (c[tab[p][i]]!=(colour%2+1)) niet=true;
	}
}

int main() {
	stack<vector<int> > stos;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%d",&poc[i]);
		rev[poc[i]]=i;
	}
	int prev=INF;
	for(int i=n;i>=1;i--) {
		mini[i]=prev;
		prev=min(prev,poc[i]);
	}
	vector<int> v;
	for(int i=1;i<=n;i++) {
		int d=poc[i], e=mini[i];
		vector<int> tmp; 
		tmp.push_back(poc[i]);
		while (!stos.empty()) {
			v=stos.top();
			int val=v[v.size()-1];
			if (val<d) {
				tab[i].push_back(rev[val]);
				tab[rev[val]].push_back(i);
				if (tmp.size()<v.size()) swap(v,tmp);
				for(int i=0;i<(int)v.size();i++) tmp.push_back(v[i]);
				stos.pop();
			} else break;
		}
		sort(tmp.begin(),tmp.end());
		reverse(tmp.begin(),tmp.end());
		stos.push(tmp);
		while (!stos.empty()) {
			tmp=stos.top(); stos.pop();
			while (!tmp.empty() && tmp[tmp.size()-1]<e)	tmp.pop_back();
			
			if (!tmp.empty()) {
				stos.push(tmp);
				break;
			}
		}
	}
	for(int i=1;i<=n;i++) c[i]=0;
	for(int i=1;i<=n;i++) if (c[i]==0)  paint(i,1);
	niet=checkOut();
	if (!niet) printf("NIE\n"); else {
		printf("TAK\n");
		for(int i=1;i<=n;i++) printf("%d ",c[i]);
		printf("\n");
	}
	return 0;
}

