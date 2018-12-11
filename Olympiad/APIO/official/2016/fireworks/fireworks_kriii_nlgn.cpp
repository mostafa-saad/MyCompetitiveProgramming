/*
 * Author: Gyeonggeun Kim(kriii)
 * Time Complexity: O(N lg N)
 */
#include <stdio.h>

const int Z = 1<<21;

int N,M,V,par[Z/2],dist[Z/2],child[Z/2],size[Z/2],st[Z/2],ed[Z/2];
long long my[Z/2];

struct node{
	node(){
		x = i = 0;
	}
	node(long long x_, int i_){
		x = x_; i = i_;
	}
	long long x; int i;

	bool operator <(const node &t)const{
		return x < t.x;
	};

	node operator +(const node &t)const{
		if (x < t.x) return t;
		return (*this);
	}
}I[Z*2];

void in(long long x, int i)
{
	I[i+Z] = node(x,i);
	i = (i + Z) >> 1;
	while (i){
		I[i] = I[i*2] + I[i*2+1];
		i >>= 1;
	}
}

node out(int i, int j)
{
	node res;
	i += Z; j += Z;
	while (i < j){
		if (i & 1){
			if (res < I[i]) res = I[i];
			i++;
		}
		if (~j & 1){
			if (res < I[j]) res = I[j];
			j--;
		}
		i >>= 1; j >>= 1;
	}
	if (i == j){
		if (res < I[i]) res = I[i];
	}
	return res;
}

long long remove(int s, int e)
{
	node t = out(s,e);
	in(0,t.i);
	return t.x;
}

int main()
{
	scanf ("%d %d",&N,&M); V = N + M;

	for (int i=2;i<=V;i++){
		scanf ("%d %d",&par[i],&dist[i]);
		child[par[i]]++;
	}

	for (int i=V;i>=1;i--){
		size[i]++;
		size[par[i]] += size[i];
	}

	ed[1] = 1;
	for (int i=2;i<=V;i++){
		st[i] = ed[par[i]] + 1;
		ed[i] = st[i] + 1;
		ed[par[i]] = st[i] + size[i] * 2 - 1;
	}

	for (int i=V;i>=2;i--){
		int s = st[i], e = ed[i];
		for (int k=1;k<child[i];k++) my[i] += remove(s,e);
		long long p = remove(s,e);
		long long q = remove(s,e);
		in(dist[i]+p,s);
		in(dist[i]+q,s+1);
		my[i] -= dist[i];
		my[par[i]] += my[i];
	}

	for (int k=0;k<child[1];k++) my[1] += remove(st[1],ed[1]);
	printf ("%lld\n",my[1]);

	return 0;
}