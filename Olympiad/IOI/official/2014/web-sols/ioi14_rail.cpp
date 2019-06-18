#include "rail.h"
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;
  
int dist0[5005], distmin[5005];
bool setCheck[5005];
vector<pi> v;
  
void make(int location[], int stype[], int x, int st){
    vector<pi> tmp;
    for(auto &i : v){
        if(tmp.empty()){
            stype[i.second] = x;
            location[i.second] = location[st];
            if(stype[i.second] == 1){
                location[i.second] -= i.first;
            }
            else{
                location[i.second] += i.first;
            }
            tmp.push_back(i);
            continue;
        }
        int found = 0;
        int longDist = getDistance(tmp.back().second, i.second);
        for(auto &j : tmp){
            int p = longDist;
            if(x == 2){
                p -= location[tmp.back().second] - location[j.second];
            }
            else{
                p += location[tmp.back().second] - location[j.second];
            }
            if(j.first + p == i.first){
                stype[i.second] = 3 - x;
                location[i.second] = location[j.second];
                if(stype[i.second] == 1){
                    location[i.second] -= p;
                }
                else{
                    location[i.second] += p;
                }
                found = 1;
                break;
            }
        }
        if(!found){
            stype[i.second] = x;
            location[i.second] = location[st];
            if(stype[i.second] == 1){
                location[i.second] -= i.first;
            }
            else{
                location[i.second] += i.first;
            }
            tmp.push_back(i);
        }
    }
}
  
void findLocation(int N, int first, int location[], int stype[])
{
    location[0] = first;
    stype[0] = 1;
    int minv = 1e9, minp = -1;
    for(int i=1; i<N; i++){
        dist0[i] = getDistance(0,i);
        if(minv > dist0[i]){
            minv = dist0[i];
            minp = i;
        }
    }
    location[minp] = first + minv;
    stype[minp] = 2;
    for(int i=1; i<N; i++){
        if(i == minp) continue;
        distmin[i] = getDistance(minp, i);
        if(dist0[i] == dist0[minp] + distmin[i]){
            setCheck[i] = 1;
        }
    }
    for(int i=1; i<N; i++){
        if(setCheck[i]){
            v.push_back(pi(distmin[i], i));
        }
    }
    sort(v.begin(), v.end());
    make(location, stype, 1, minp);
    v.clear();
    for(int i=1; i<N; i++){
        if(i != minp && !setCheck[i]){
            v.push_back(pi(dist0[i] - dist0[minp], i));
        }
    }
    sort(v.begin(), v.end());
    make(location, stype, 2, minp);
    v.clear();
}