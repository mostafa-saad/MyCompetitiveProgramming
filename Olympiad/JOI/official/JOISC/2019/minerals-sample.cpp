#include <cstdio>
#include <vector>
#include<algorithm>
#include<cmath>
#include "minerals.h"
using namespace std;

int used[110000];
vector<int>gr[2];
void rec(vector<int>A,vector<int>B,int c){
	if(A.size()==0)return;
	if(A.size()==1){
		used[A[0]]=B[0];
		used[B[0]]=A[0];
		return;
	}
	int rac=0;
	int SZ= (3 - sqrt(5)) / 2*A.size();
	if(c==0){
		SZ= (1-(3 - sqrt(5)) / 2 )*A.size();
	}
	if(SZ==0)SZ++;
	if(SZ==A.size())SZ--;
	vector<int>X1;
	vector<int>X2;
	vector<int>Y1;
	vector<int>Y2;
	if(c==1){
		for(int i=0;i<SZ;i++){
			rac=Query(A[i]+1);
		}
		for(int i=0;i<A.size();i++){
			if(i<SZ)X1.push_back(A[i]);
			else X2.push_back(A[i]);
		}
		for(int i=0;i<B.size();i++){
			if(Y1.size()==X1.size()){
				Y2.push_back(B[i]);
			}else if(X2.size()==Y2.size()){
				Y1.push_back(B[i]);
			}else{
				int tmp=Query(B[i]+1);
				if(rac!=tmp){
					Y1.push_back(B[i]);
				}else Y2.push_back(B[i]);
				rac=tmp;
			}
		}
	}else{
		for(int i=SZ;i<A.size();i++){
			rac=Query(A[i]+1);
		}
		for(int i=0;i<A.size();i++){
			if(i<SZ)X1.push_back(A[i]);
			else X2.push_back(A[i]);
		}
		for(int i=0;i<B.size();i++){
			if(Y1.size()==X1.size()){
				Y2.push_back(B[i]);
			}else if(X2.size()==Y2.size()){
				Y1.push_back(B[i]);
			}else{
				int tmp=Query(B[i]+1);
				if(rac!=tmp){
					Y1.push_back(B[i]);
				}else Y2.push_back(B[i]);
				rac=tmp;
			}
		}
	}
	rec(X1,Y1,0);
	rec(X2,Y2,1);
}
void Solve(int N){
	int cur=0;
	for(int i=0;i<N*2;i++){
		int tmp=Query(i+1);
		if(cur<tmp){
			gr[0].push_back(i);
		}else gr[1].push_back(i);
		cur=tmp;
	}
	random_shuffle(gr[0].begin(),gr[0].end());
	random_shuffle(gr[1].begin(),gr[1].end());
	rec(gr[0],gr[1],1);

	for(int i=0;i<N;i++){
		Answer(gr[0][i]+1,used[gr[0][i]]+1);
	}
}