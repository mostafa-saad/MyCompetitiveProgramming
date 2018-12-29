/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Pieczec                                            *
 *   Autor programu:       Karol Pokorski                                     *
 *   Zlozonosc czasowa:    O(n*m)                                             *
 *   Zlozonosc pamieciowa: O(n*m)                                             *
 *   Opis:                 rozwiazanie wzorcowe                               *
 *****************************************************************************/


#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 1005;

int n, m, a, b;
char T[MAXN][MAXN], M[MAXN][MAXN];
vector<pair<int,int> > P;

bool Mark(int x, int y) {
    for (int i = 0; i < (int)P.size(); i++) {
        int dx = P[i].first, dy = P[i].second;

        if ((x+dx < 0) || (x+dx >= n) || (y+dy < 0) || (y+dy >= m))
            return true;
        if (T[x+dx][y+dy] == 'x')
            T[x+dx][y+dy] = '#';
        else
            return true;
    }
    return false;
}

int main() {
    int q;

    scanf("%d", &q);

    while (q--) {
        bool ok = true;
        pair<int,int> pos = make_pair(-1, -1);

        P.clear();

	    scanf("%d%d%d%d", &n, &m, &a, &b);
	    for (int i = 0; i < n; i++)
	        scanf("%s", T[i]);
    	for (int i = 0; i < a; i++) {
	        scanf("%s", M[i]);
            for (int j = 0; j < b; j++) {
                if ((M[i][j] == 'x') && (pos == make_pair(-1, -1)))
                    pos = make_pair(i, j);
                if (M[i][j] == 'x')
                    P.push_back(make_pair(i, j));
            }
        }

    	for (int i = 0; i < n && ok; i++)
	        for (int j = 0; j < m && ok; j++)
    		    if (T[i][j] == 'x') {
        		    if (Mark(i-pos.first, j-pos.second)) {
		            	printf("NIE\n");
                        ok = false;
        		    }
                }

        if (ok)
            printf("TAK\n");
    }

    return 0;
}
