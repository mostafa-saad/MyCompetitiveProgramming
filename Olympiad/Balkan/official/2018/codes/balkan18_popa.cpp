#include <bits/stdc++.h>
#include "popa.h"
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;

int solve(int N, int *l, int *r){
	for(int i=0; i<N; i++) l[i] = r[i] = -1;
	stack<int> stk;
	stk.push(0);
	for(int i=1; i<N; i++){
		int son = -1;
		while(!stk.empty()){
			int pos = stk.top();
			while(l[pos] != -1) pos = l[pos];
			if(query(pos, i, stk.top(), stk.top()) == 1){
				break;
			}
			else{
				son = stk.top();
				stk.pop();
			}
		}
		if(!stk.empty()) r[stk.top()] = i;
		l[i] = son;
		stk.push(i);
	}
	while(stk.size() > 1) stk.pop();
	return stk.top();
}
