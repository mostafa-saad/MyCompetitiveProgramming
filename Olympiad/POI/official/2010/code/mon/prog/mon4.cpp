/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Monotonicznosc (MON)                             *
 *   Plik:              mon4.cpp                                         *
 *   Autor:             Miroslaw Michalski                               *
 *   Opis:              Rozwiazanie weryfikujace.                        *
 *   Zlozonosc czasowa: O(n * k * log n)                                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>

const int MAX_M = 103;
const int MAX_N = 20003;
const int MAX_W = 1000023;
const int INF = 1000000000;
class Tree {
    private:
        int* t;
        int* pr;
        int BASE;
        int MAX_S;
    
    public:
        Tree(int sz) {
            BASE = 1;
            while (sz >= BASE) {
                BASE*=2;
            }
            MAX_S = 2*BASE + 7;
            t = new int[MAX_S];
            pr = new int[MAX_S];
            for(int i=0; i<MAX_S; i++) {
                t[i] = 0;
                pr[i] = 0;
            }
        }

        ::std::pair<int, int> getResult(int val, int type) {
            /** type == SMALLER 0;; GREATER 1;; EQUAL 2 **/
            int st = 1, size = BASE, res = 0, prv = 0;
            if (type == 0) {
                while (val>0) {
                    if (val>=size/2) {
                        if (res < t[2*st]) {
                            res = t[2*st];
                            prv = pr[2*st];
                        }
                        st = st*2 + 1;
                        val-=size/2;
                    } else {
                        st=st*2;
                    }
                    size/=2;
                }
            } else if (type == 1) {
                val = BASE - val - 1;
                while (val>0) {
                    if (val<size/2) {
                        st=st*2+1;
                    } else {
                        if (res < t[2*st+1]) {
                            res = t[2*st+1];
                            prv = pr[2*st+1];
                        }
                        st=st*2;
                        val-=size/2;
                    }
                    size/=2;
                }
            } else {
                res = t[BASE + val];
                prv = pr[BASE + val];
            }
            if (res==0) res=-2;
            return ::std::make_pair(res, prv);
        }

        void update(int position, int value, int p) {
            int st = BASE + position;
            while (st!=1 && t[st]<value) {
                t[st] = value;
                pr[st] = p;
                st/=2;
            }
        }
};

int n,m;
char dummy, sign[MAX_M];
int t[MAX_N], t_[MAX_N], rr[MAX_N], rev[MAX_N];
int result[MAX_N][MAX_M], prev[MAX_N][MAX_M];
int res = 0, rt;
int mapper[MAX_W];
::std::pair<int, int> st;


int main() {
    scanf("%d%d",&n, &m);
    for(int i=0; i<n; i++) {
        scanf("%d",&t_[i]);
        t[i] = t_[i];
    }

    ::std::sort(t_, t_+n);
    mapper[t_[0]] = 0;
    rev[0] = t_[0];
    int pos = 0;
    for(int i=1; i<n; i++) if (t_[i] != t_[i-1]) {
            pos++;
            mapper[t_[i]] = pos;
            rev[pos] = t_[i];
    }
    
    for(int i=0; i<n; i++) 
        t[i] = mapper[t[i]];

    for(int i=0; i<m; i++) {
        scanf("%c%c",&dummy, &sign[i]);
    }

    ::std::vector<Tree> tree;
    for(int i=0; i<m; i++) 
        tree.push_back(Tree(pos));

    for(int i=0; i<MAX_N; i++) {
        for(int j=0; j<MAX_M; j++) {
            result[i][j] = -1;
            prev[i][j] = -1;
        }
        result[i][0] = 1;
    }
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            int poprz = (j==0?m-1:j-1);
            if (sign[poprz]=='<') rt = 0; else
                if (sign[poprz]=='>') rt = 1; else
                    rt = 2;
            ::std::pair<int,int> tmp = tree[poprz].getResult(t[i], rt);

            if (result[i][j] < 1+ tmp.first) {
                result[i][j] = 1 + tmp.first;
                prev[i][j] = tmp.second;
            }
        }
        for(int j=0; j<m; j++) {
            tree[j].update(t[i], result[i][j], i);
            if (res < result[i][j]) {
                res = result[i][j];
                st = ::std::make_pair(i, j);
            }
        }
    }
    printf("%d\n",res);
    for(int i=0; i<res; i++) {
        rr[res-i-1] = rev[t[st.first]];
        st.first = prev[st.first][st.second]; 
        st.second = (st.second==0?m-1:st.second-1);
    }
    for(int i=0; i<res; i++) printf("%d ",rr[i]);
    printf("\n");
    return 0;
}
