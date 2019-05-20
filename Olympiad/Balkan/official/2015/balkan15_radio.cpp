#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, k;

struct elem{
	int pos, val, add; // pos 위치에서 val을 (add > 0 ? 추가 : 삭제)
	bool operator<(const elem &v)const{
		return pos < v.pos;
	}
};

vector<elem> v1, v2, v3;
vector<int> cnd;

multiset<lint> act1, act2, act3;
multiset<lint> inact1, inact2, inact3;
lint sum;

lint tsolve(int x){
	lint ret = sum + 1ll * x * (act3.size() - act1.size());
	return ret;
}

void update(multiset<lint> &inact, multiset<lint> &act, elem e){
	if(e.add > 0){
		if(!act.empty() && *--act.end() >= e.val){
			act.insert(e.val);
			sum += e.val;
		}
		else inact.insert(e.val);
	}
	else{
		if(inact.find(e.val) != inact.end()){
			inact.erase(inact.find(e.val));
		}
		else{
			sum -= e.val;
			act.erase(act.find(e.val));
		}
	}
}

void move12(lint i){
	sum += *inact2.begin() - *--act1.end();
	inact1.insert(*--act1.end());
	act1.erase(--act1.end());
	act2.insert(*inact2.begin());
	inact2.erase(inact2.begin());
}

void move13(lint i){
		sum += *inact3.begin() - *--act1.end();
		inact1.insert(*--act1.end());
		act1.erase(--act1.end());
		act3.insert(*inact3.begin());
		inact3.erase(inact3.begin());
}

void move23(lint i){
		sum += *inact3.begin() - *--act2.end();
		inact2.insert(*--act2.end());
		act2.erase(--act2.end());
		act3.insert(*inact3.begin());
		inact3.erase(inact3.begin());
}

void move32(lint i){
		sum += *inact2.begin() - *--act3.end();
		inact3.insert(*--act3.end());
		act3.erase(--act3.end());
		act2.insert(*inact2.begin());
		inact2.erase(inact2.begin());
}

void move31(lint i){
		sum += *inact1.begin() - *--act3.end();
		inact3.insert(*--act3.end());
		act3.erase(--act3.end());
		act1.insert(*inact1.begin());
		inact1.erase(inact1.begin());
}

void move21(lint i){
		sum += *inact1.begin() - *--act2.end();
		inact2.insert(*--act2.end());
		act2.erase(--act2.end());
		act1.insert(*inact1.begin());
		inact1.erase(inact1.begin());
}

lint solve(){
	int p1 = 0, p2 = 0, p3 = 0;
	lint ret = 1e18;
	for(auto &i : cnd){
		while(p1 < v1.size() && v1[p1].pos <= i){
			update(inact1, act1, v1[p1]);
			p1++;
		}
		while(p2 < v2.size() && v2[p2].pos <= i){
			update(inact2, act2, v2[p2]);
			p2++;
		}
		while(p3 < v3.size() && v3[p3].pos <= i){
			update(inact3, act3, v3[p3]);
			p3++;
		}
		while(act1.size() + act2.size() + act3.size() < k){		
			lint p1 = 1e10, p2 = 1e10, p3 = 1e10;
			if(!inact1.empty()) p1 = *inact1.begin() - i;
			if(!inact2.empty()) p2 = *inact2.begin();
			if(!inact3.empty()) p3 = *inact3.begin() + i;
			if(min(p1, min(p2, p3)) == p1){
				sum += *inact1.begin();
				act1.insert(*inact1.begin());
				inact1.erase(inact1.begin());
			}
			else if(min(p1, min(p2, p3)) == p2){
				sum += *inact2.begin();
				act2.insert(*inact2.begin());
				inact2.erase(inact2.begin());
			}
			else{
				sum += *inact3.begin();
				act3.insert(*inact3.begin());
				inact3.erase(inact3.begin());
			}
		}
		while(act1.size() + act2.size() + act3.size() > k){
			lint p1 = -1e10, p2 = -1e10, p3 = -1e10;
			if(!act1.empty()) p1 = *--act1.end() - i;
			if(!act2.empty()) p2 = *--act2.end();
			if(!act3.empty()) p3 = *--act3.end() + i;
			if(max(p1, max(p2, p3)) == p1){
				sum -= *--act1.end();
				inact1.insert(*--act1.end());
				act1.erase(--act1.end());
			}
			else if(max(p1, max(p2, p3)) == p2){
				sum -= *--act2.end();
				inact2.insert(*--act2.end());
				act2.erase(--act2.end());
			}
			else{
				sum -= *--act3.end();
				inact3.insert(*--act3.end());
				act3.erase(--act3.end());
			}
		}
		while(1){
			lint p1 = 1e10, p2 = 1e10, p3 = 1e10;
			lint q1 = -1e10, q2 = -1e10, q3 = -1e10;
			if(!inact1.empty()) p1 = *inact1.begin() - i;
			if(!inact2.empty()) p2 = *inact2.begin();
			if(!inact3.empty()) p3 = *inact3.begin() + i;
			if(!act1.empty()) q1 = *--act1.end() - i;
			if(!act2.empty()) q2 = *--act2.end();
			if(!act3.empty()) q3 = *--act3.end() + i;
			if(max(q1, max(q2, q3)) <= min(p1, min(p2, p3))) break;
			if(min(p1, min(p2, p3)) == p1 && max(q1, max(q2, q3)) == q2){
				move21(i);
				continue;
			}
			if(min(p1, min(p2, p3)) == p1 && max(q1, max(q2, q3)) == q3){
				move31(i);
				continue;
			}
			if(min(p1, min(p2, p3)) == p2 && max(q1, max(q2, q3)) == q1){
				move12(i);
				continue;
			}
			if(min(p1, min(p2, p3)) == p2 && max(q1, max(q2, q3)) == q3){
				move32(i);
				continue;
			}
			if(min(p1, min(p2, p3)) == p3 && max(q1, max(q2, q3)) == q1){
				move13(i);
				continue;
			}
			if(min(p1, min(p2, p3)) == p3 && max(q1, max(q2, q3)) == q2){
				move23(i);
				continue;
			}
		}
		ret = min(ret, tsolve(i));
	}
	return ret;
}

int main(){
	scanf("%d %d",&n,&k);
	lint ret = 0;
	for(int i=0; i<n; i++){
		int x, p, s;
		scanf("%d %d %d",&x,&p,&s);
		ret += s;
		v1.push_back({-2000000001, x - p + s, 1});
		v1.push_back({x - p, x - p + s, -1});
		v2.push_back({x - p, s, 1});
		v2.push_back({x + p, s, -1});
		v3.push_back({x + p, s - x - p, 1});
		cnd.push_back(x - p);
		cnd.push_back(x + p);
	}
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	sort(v3.begin(), v3.end());
	sort(cnd.begin(), cnd.end());
	cnd.resize(unique(cnd.begin(), cnd.end()) - cnd.begin());
	ret -= solve();
	printf("%lld",-ret);
}