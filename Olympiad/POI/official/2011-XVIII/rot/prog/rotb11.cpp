/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Adam Karczmarz                                   *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Rozwiazanie "oszukancze" O(n*lg^2(n))            *
 *                      Zlozonosc pamieciowa O(n log n), zastosowane     *
 *                      statyczne drzewo przedzialowe, ale rozwijane     *
 *                      dynamicznie, patrz was.zaa.mimuw.edu.pl          *
 *                      Mocno zylowane wykorzystanie pamieci             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define REP(AA,BB) for(int AA=0; AA<(BB); ++AA)
#define FOR(AA,BB,CC) for(int AA=(BB); AA<(CC); ++AA)
#define FC(AA,BB) for(__typeof((AA).begin()) BB=(AA).begin(); BB!=(AA).end(); ++BB)
#define SZ(AA) ((int)((AA).size()))
#define ALL(AA) (AA).begin(), (AA).end()
#define PB push_back
#define MP make_pair

using namespace std;

typedef vector<int> VI;
typedef pair<int, int> PII;
typedef long long LL;
typedef long double LD;

int N, BASE;

struct dyn_node {
	int sum;
	dyn_node *left, *right;
	dyn_node() : sum(0), left(0), right(0) {}
};

void insert(dyn_node *tr, int v) {
	int x=0, y=BASE-1;
	while(1) {
		++tr->sum;
		if(x==y)
			break;
		int mid=(x+y)/2;
		if(v<=mid) {
			if(tr->left==0)
				tr->left = new dyn_node;
			tr=tr->left;
			y=mid;
		}
		else {
			if(tr->right==0)
				tr->right = new dyn_node;
			tr=tr->right;
			x=mid+1;
		}
	}
}

int cnt_greater(dyn_node *tr, int v) {
	int x=0, y=BASE-1, res=0;
	while(tr!=0 && x<y) {
		int mid=(x+y)/2;
		if(v<=mid) {
			if(tr->right!=0)
				res+=tr->right->sum;
			tr=tr->left;
			y=mid;
		}
		else {
			tr=tr->right;
			x=mid+1;
		}
	}
	return res;
}

VI buf;

void erase(dyn_node *tr, int x, int y) {
	if(x==y)
		buf.PB(x);
	if(tr->left!=0)
		erase(tr->left, x, (x+y)/2);
	if(tr->right!=0)
		erase(tr->right, (x+y)/2+1, y);
	delete tr;
}

struct node;
struct node {
	node *left, *right;
	dyn_node *st;
	node() : left(0), right(0), st(0) {}
};

int f;

// wczytywanie danych
void read_input(node *tr) {
	int c; f=scanf("%d", &c);
	if(c!=0) {
		tr->st = new dyn_node;
		insert(tr->st, c);
	}	
	else {
		tr->left=new node; tr->right=new node;
		read_input(tr->left); read_input(tr->right);
	}
}

node *root;

// obliczenie wyniku
long long compute(node *tr) {
	if(tr->left==0)
		return 0LL;
	long long res=compute(tr->left)+compute(tr->right), inv=0LL;
	long long all=(long long)tr->left->st->sum * tr->right->st->sum;
	buf.clear();
	if(tr->left->st->sum < tr->right->st->sum) {
		tr->st = tr->right->st;
		erase(tr->left->st, 0, BASE-1);
	}
	else {
		tr->st = tr->left->st;
		erase(tr->right->st, 0, BASE-1);
	}
	REP(i,SZ(buf))
		inv+=cnt_greater(tr->st, buf[i]);
	if(tr!=root) {
		REP(i,SZ(buf))
			insert(tr->st, buf[i]);
	}
	delete tr->left; delete tr->right;
	return res+min(inv, all-inv);
}
	
int main(void) {
	root=new node;
	f=scanf("%d", &N);
	for(BASE=1; BASE<N+1; BASE<<=1); 
	read_input(root);
	printf("%lld\n", compute(root));
	return 0;
}

