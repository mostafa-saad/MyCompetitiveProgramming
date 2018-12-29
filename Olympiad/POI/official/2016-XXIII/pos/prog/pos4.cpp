/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Poslaniec                                          *
 *   Autor:                Michal Glapa                                       *
 *   Zlozonosc czasowa:    O(n^3 * d + q*d^2)                                 *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/


#include<iostream>
#include<vector>
#include<algorithm>
#include<array>
using namespace std;
typedef vector<vector<int>> matrix;

const int MaxD = 51;

int n, MOD;
matrix GG,R;
vector<array<int,3>> queries;
vector<vector<int>> max_used_d;

matrix empty_matrix() {
    vector<vector<int> > res (n, vector<int>(n,0));
    return res;
}
matrix id_matrix() {
    vector<vector<int> > res (n, vector<int>(n,0));
    for(int i = 0; i < n; i++)
        res[i][i]=1;
    return res;
}
matrix mult(matrix &a, matrix &b) {
    auto res = empty_matrix();
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++)
                res[i][j] = ((long long) (res[i][j]) + (long long) a[i][k]*b[k][j]) %MOD;
    return res;
}
matrix reverse_edges(matrix &a) {
    auto res = empty_matrix();
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            res[j][i] = a[i][j];
    return res;
}
vector<matrix> make_paths(matrix &a,int max_length) {
    auto tmp = id_matrix();
    vector<matrix> res;
    for(int i = 0; i <= max_length; i++) {
        res.push_back(tmp);
        tmp = mult(tmp,a);
    }
    return res;
}

vector<vector<int>> make_paths_without_revisiting_start(matrix & G, int start, int max_length) {
    vector<vector<int>> res;
    auto dp = vector<int>(n);
    dp[start]=1;
    res.push_back(dp);
    for(int i=1;i<=max_length;i++)
    {
        vector<int> tmp(n);
        for(int from = 0; from < n; from++)
            for(int to = 0; to < n; to++) {
                if(to == start)
                    continue;
                tmp[to] += G[from][to] * dp[from];
                tmp[to] %= MOD;
            }
        dp = tmp;
        res.push_back(dp);
    }
    return res;
}
vector<matrix> make_paths_without_revisiting_start_for_all_starts(matrix &G, int max_length) {
    vector<matrix> res(max_length+1,empty_matrix());
    for(int i = 0; i < n; i++) {
        auto tmp = make_paths_without_revisiting_start(G,i,max_length);
        for(int d = 0; d <= max_length; d++)
            for(int q = 0; q < n; q++)
                res[d][i][q] = tmp[d][q];
    }
    return res;
}

vector<matrix>  paths,
                paths_without_revisiting_start,
                reversed_graph_paths_without_revisiting_start;

void preprocessing() {
    int needed_d = -1;
    for(auto &i : queries)
        needed_d = max(needed_d,i[2]+1);
    paths = make_paths(GG,needed_d);
    paths_without_revisiting_start = make_paths_without_revisiting_start_for_all_starts(GG,needed_d);
    R = reverse_edges(GG);
    reversed_graph_paths_without_revisiting_start = make_paths_without_revisiting_start_for_all_starts(R,needed_d);
}
vector<int> all_answers_query(int p, int q) {
    //int p = query[0],
    //    q = query[1],
    //    length = query[2];
    int length = max_used_d[p][q];//MaxD-1;

    vector<int> good_paths_of_length(length+1),
                cycles_ommitting_p_of_length(length+1);
    good_paths_of_length[0] = 0;
    cycles_ommitting_p_of_length[0]=0;
    for(int d = 1; d <= length; d++) {
        good_paths_of_length[d] = paths_without_revisiting_start[d][p][q];
        for(int i = 1; i < d; i++) {
            good_paths_of_length[d] -=
                ((long long)good_paths_of_length[i]*cycles_ommitting_p_of_length[d-i]) % MOD;
            good_paths_of_length[d] %= MOD;
        }
        cycles_ommitting_p_of_length[d] = paths[d][q][q];
        for(int i = 1; i < d; i++) {
            cycles_ommitting_p_of_length[d] -=
                ((long long) reversed_graph_paths_without_revisiting_start[i][p][q] * paths[d-i][p][q])%MOD;
            cycles_ommitting_p_of_length[d] %= MOD;
        }
    }
    //cout << (good_paths_of_length[length] + MOD) % MOD << endl;
    for(int& res: good_paths_of_length)
		res = (res+MOD) % MOD;
	return good_paths_of_length;
}


//using threed_vector = vector<vector<vector<int>>>;

//vector<vector<vector<int>>> answers;

vector<vector<vector<int>>> make_all_answers(){
	vector<int> empty(MaxD, 0);
	vector<vector<int>> empty_pack(n+1, empty);
	vector<vector<vector<int>>> answers(n+1, empty_pack);

	for(int p = 0; p < n; p++) {
		for(int q = 0; q < n; q++) {
			answers[p][q] = all_answers_query(p, q);
		}
	}
	return answers;
}

void read() {
	ios_base::sync_with_stdio(false);
    int m;
    cin >> n >> m >> MOD;
    GG = empty_matrix();
    while(m--) {
        int a,b;
        cin >> a >> b;
        a--;
        b--;
        GG[a][b] = 1;
    }
    int q;
    cin >> q;
    queries.resize(q);
    for(int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        queries[i][0] = a;
        queries[i][1] = b;
        cin >> queries[i][2];
    }

	max_used_d = vector<vector<int>>(n, vector<int>(n,0));

	for(int i = 0; i < q; i++) {
		max_used_d[queries[i][0]][queries[i][1]] =
			max(max_used_d[queries[i][0]][queries[i][1]], queries[i][2]);
	}
}
int main() {
    read();
    preprocessing();
    vector<vector<vector<int>>> answers = make_all_answers();
    for(auto &i : queries)
		cout << answers[i[0]][i[1]][i[2]] << endl;
}
