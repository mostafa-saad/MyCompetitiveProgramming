#include "boblib.h"
#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;

void Bob( int V, int U, int C[], int D[] ){
	static int N = V-12;
	static int cnt[1020] = {};
	static bool edge[1020][1020];
	static bool used[1020];
	for(int i = 0 ; i < V ; i ++){
		used[i] = false;
		for(int j = 0 ; j < V ; j ++){
			edge[i][j] = false;
		}
	}
	for(int i = 0 ; i < U ; i ++){
		cnt[C[i]] ++;
		cnt[D[i]] ++;
		edge[C[i]][D[i]] = true;
		edge[D[i]][C[i]] = true;
	}
	static int a = -1;
	for(int i = 0 ; i < V ; i ++){
		if(cnt[i] == N+10){
			a = i;
			break;
		}
	}
	used[a] = true;
	static int b = -1;
	for(int i = 0 ; i < V ; i ++){
		if(a != i && !edge[i][a]){
			b = i;
			break;
		}
	}
	used[b] = true;
	static int c[10];
	for(int i = 0 ; i < V ; i ++){
		if(edge[i][b]){
			int cnt_c = 0;
			for(int j = 0 ; j < V ; j ++){
				if(edge[j][b] && edge[i][j])cnt_c ++;
			}
			if(cnt_c == 1){
				c[0] = i;
				int k = 1;
				while(k < 10){
					for(int j = 0 ; j < V ; j ++){
						if(edge[j][b] && edge[c[k-1]][j] && !(k >= 2 && j == c[k-2])){
							c[k] = j;
							break;
						}
					}
					k ++;
				}
				if(cnt[c[0]] < cnt[c[9]]){
					for(int j = 0 ; j < 5 ; j ++)swap(c[j],c[9-j]);
				}
				break;
			}
		}
	}
	for(int i = 0 ; i < 10 ; i ++){
		used[c[i]] = true;
	}
	static int id[1002] = {};
	for(int i = 0 ; i < V ; i ++){
		if(used[i])continue;
		for(int j = 0 ; j < 10 ; j ++){
			if(edge[i][c[j]])id[i] += 1<<j;
		}
	}
	vector<pair<int,int>> Map;
	for(int i = 0 ; i < V ; i ++){
		if(used[i])continue;
		for(int j = i+1 ; j < V ; j ++){
			if(used[j])continue;
			if(edge[i][j]){
				Map.push_back(pair<int,int>(id[i],id[j]));
			}
		}
	}
	InitMap( N, Map.size() );
	for(int i = 0 ; i < Map.size() ; i ++){
		MakeMap( Map[i].first, Map[i].second );
	}
}
