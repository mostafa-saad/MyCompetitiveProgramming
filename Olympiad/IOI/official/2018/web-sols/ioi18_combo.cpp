#include "combo.h"
#include <bits/stdc++.h>
using namespace std;

string guess_sequence(int N) {
	string p = "";
	if(press("AB") >= 1) p = press("A") ? "A" : "B";
	else p = press("X") ? "X" : "Y";
	vector<char> chr = {'A', 'B', 'X', 'Y'};
	chr.erase(find(chr.begin(), chr.end(), p[0]));
	while((int)p.size() <= N - 2){ 
		int query = press(p + chr[0] + chr[0] + p + chr[0] + chr[1] + p + chr[1] + chr[0]);
		if(query == p.size()){
			p.push_back(chr[2]);
		}
		else if(query == p.size() + 1){
			query = press(p + chr[1] + chr[2]);
			if(query == p.size()) p = p + chr[0] + chr[2];
			else if(query == p.size() + 1) p = p + chr[1] + chr[1];
			else p = p + chr[1] + chr[2];
		}
		else{
			query = press(p + chr[0] + chr[1]);
			if(query == p.size()) p = p + chr[1] + chr[0];
			else if(query == p.size() + 1) p = p + chr[0] + chr[0];
			else p = p + chr[0] + chr[1];
		}
	}
	while(p.size() != N){
		if(press(p + chr[0]) == p.size() + 1) p.push_back(chr[0]);
		else if(press(p + chr[1]) == p.size() + 1) p.push_back(chr[1]);
		else p.push_back(chr[2]);
	}
	return p;
}
