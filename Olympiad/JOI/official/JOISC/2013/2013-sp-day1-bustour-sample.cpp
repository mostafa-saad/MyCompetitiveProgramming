#include<cstdio>
#include<queue>
#include<algorithm>
#include<vector>
using namespace std;
#define INF 1000000000

struct qnode
{
	qnode *next;
	pair<int, int> val;
};

int W, H, N, Sx, Sy, Gx, Gy;
int X1i, Y1i, X2i, Y2i;
vector<pair<int, int> > ids[1000][1000];
int Ti[1000]; vector<pair<int, int> > buses[1000];

int dist[1000][4000]; bool vis[1000][4000];
bool used[1000][1000];

qnode *Q[4000001], pool[8000001]; int pTop=0;

void add(int bus, int x, int y, int id)
{
	ids[x][y].push_back(make_pair(bus, id));
	buses[bus].push_back(make_pair(x, y));
}

void qpush(int bus, int id, int t)
{
	if(dist[bus][id] > t){
		dist[bus][id] = t;
		qnode *tmp = &(pool[pTop++]);
		tmp->val = make_pair(bus, id);
		tmp->next = Q[t];
		Q[t] = tmp;
	}
}

int main()
{
	scanf("%d%d%d%d%d%d%d", &W, &H, &Sx, &Sy, &Gx, &Gy, &N);
	--Sx; --Sy; --Gx; --Gy;

	for(int i=0;i<W;i++)
		for(int j=0;j<H;j++) used[i][j] = false;
	for(int i=0;i<=4000000;i++) Q[i] = NULL;

	//input
	for(int i=0;i<N;i++){
		scanf("%d%d%d%d%d", &X1i, &Y1i, &X2i, &Y2i, Ti+i);
		X1i--; Y1i--; X2i--; Y2i--;

		int id = 0;
		for(int j=X1i;j<X2i;j++) add(i, j, Y1i, id++);
		for(int j=Y1i;j<Y2i;j++) add(i, X2i, j, id++);
		for(int j=X2i;j>X1i;j--) add(i, j, Y2i, id++);
		for(int j=Y2i;j>Y1i;j--) add(i, X1i, j, id++);

		for(int j=0;j<id;j++){
			dist[i][j] = INF;
			vis[i][j] = false;
		}
	}

	for(int i=0;i<ids[Sx][Sy].size();i++){
		int t2 = 0, id2 = ids[Sx][Sy][i].second, bus2 = ids[Sx][Sy][i].first;
		int wtime = (t2 + (id2 - Ti[bus2] + buses[bus2].size())) % buses[bus2].size();

		qpush(bus2, id2, t2+wtime);
	}

	for(int i=0;;i++){
		for(qnode *nd=Q[i]; nd!=NULL; nd=nd->next){
			if(vis[nd->val.first][nd->val.second]) continue;

			int bus=nd->val.first, id=nd->val.second;
			vis[bus][id] = true;

			qpush(bus, (id+1)%buses[bus].size(), dist[bus][id]+1);

			int x=buses[bus][id].first, y=buses[bus][id].second;
			if(x==Gx && y==Gy){
				printf("%d\n", dist[bus][id]);
				return 0;
			}

			if(used[x][y]) continue;
			used[x][y] = true;

			for(int j=0;j<ids[x][y].size();j++) if(ids[x][y][j].first != bus){
				int t2 = dist[bus][id]+1, id2 = ids[x][y][j].second, bus2 = ids[x][y][j].first;
				int wtime = (buses[bus2].size() - t2%buses[bus2].size() + (id2 - Ti[bus2] + buses[bus2].size())) % buses[bus2].size();

				qpush(bus2, id2, t2+wtime);
			}
		}
	}

	return 0;
}
