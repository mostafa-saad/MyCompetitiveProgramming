/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Pensje                                           *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n log n)                                       *
 *   Opis:              Rozwiazanie weryfikujace                         *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <queue>

#define MAXN 1000000

using namespace std;

int root;

vector <int> children[MAXN];
int zero_children[MAXN];
int zero_child[MAXN];
int tree_size[MAXN];
int uktree_size[MAXN];
int npc[MAXN];
int father[MAXN];

int s[MAXN];

struct fs{
    int f;
    int c;
    bool operator<(const fs& b) const{
        return s[f] < s[b.f];
    }
}_fs;

vector <int> values;
bool used[MAXN + 1];
vector <fs> to_proc;
int n;

int get_value(int v){
    vector <int>::iterator it = lower_bound(values.begin(), values.end(), v);
    --it;
    return (*it);
}

int count_lower(int v){
    vector <int>::iterator it = lower_bound(values.begin(), values.end(), v);
    return (int)(it - values.begin());
}

int main(){
    ios_base::sync_with_stdio(0);
    
    // input
    cin >> n;
    for(int i = 0; i < n; ++i){
        int a;
        cin >> a >> s[i];
        used[s[i]] = true;
        --a;
        if(a == i)root = a;
        else{
            children[a].push_back(i);
            father[i] = a;
            if(!s[i]){
                ++zero_children[a];
                zero_child[a] = i;
            }
        }
    }
    s[root] = n;

    // tree_size processing
    queue <int> leaves;
    for(int i = 0; i < n; ++i){
        npc[i] = children[i].size();
        if(!npc[i])leaves.push(i);
    }
    while(!leaves.empty()){
        int a = leaves.front();
#ifdef DEBUG
        cout << a + 1 << endl;
#endif
        leaves.pop();
        ++tree_size[a];
        if(a != root){
            --npc[father[a]];
            tree_size[father[a]] += tree_size[a];
            if(!npc[father[a]]){
                leaves.push(father[a]);
            }
        }
    }
#ifdef DEBUG
    cout << endl;
#endif

    // values processing
    for(int i = 1; i <= n; ++i){
        if(!used[i])values.push_back(i);
    }

    //uktree_size processing
    for(int i = 0; i < n; ++i){
        for(unsigned int j = 0; j < children[i].size(); ++j){
            if(!s[children[i][j]]){
                uktree_size[i] += tree_size[children[i][j]];
            }
        }
    }
    
    //to_proc
    for(int i = 0; i < n; ++i){
        if(s[i]){
            _fs.f = i;
            if(zero_children[i] == 1)_fs.c = zero_child[i];
            to_proc.push_back(_fs);
        }
    }
#ifdef DEBUG
    for(int i = 0; i < n; ++i){
        cout << i+1 << " : " << tree_size[i] << endl;
    }
#endif
    sort(to_proc.begin(), to_proc.end());
    int prev = -1;
    int sum = 0;
    int nprev;
    for(unsigned int i = 0; i < to_proc.size(); ++i){
        fs act = to_proc[i];
        int f = act.f;
        nprev = prev;
        if(zero_children[f])nprev = s[f];
        sum += uktree_size[f];
#ifdef DEBUG
        cout << f + 1 << " " << s[f] << " " << prev << " " << sum << endl;
#endif
        if(zero_children[f] == 1){
            int v = get_value(s[act.f]);
            int nr = count_lower(s[act.f]);
#ifdef DEBUG
            cout << "\t" << v << " " << nr << endl;
#endif
            if(v > prev && nr == sum){
#ifdef DEBUG
                cout << "\t\tOK" << endl;
#endif
                f = act.c;
                s[f] = v;
                act.f = f;
                act.c = zero_child[f];
                bool goon = true;
                while(goon){
                    if(zero_children[f] != 1){
                        goon = false;
                    }
                    else{
                        v = get_value(s[act.f]);
                        if(v > prev){
                            f = act.c;
                            s[f] = v;
                            act.f = f;
                            act.c = zero_child[f];
                        }
                        else{
                            goon = false;
                        }
                    }
                }
            }
        }
        prev = nprev;
    }
    for(int i = 0; i < n; ++i){
        cout << s[i] << "\n";
    }
    return 0;
}
