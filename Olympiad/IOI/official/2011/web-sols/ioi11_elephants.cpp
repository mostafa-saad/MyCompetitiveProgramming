#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
 
const int U = 400;
const int B = 500;
 
struct elem{
    int val;
    int next;
    int cnt;
};
 
bool operator<(elem a, elem b){ return a.val < b.val; }
 
elem bucket[305][905];
int size[305];
 
int sentinel;
 
int b[150005];
int a[150005], n, l;
int q_cnt;
 
void bucket_label(int bnum){
    int pt = size[bnum];
    for (int i=size[bnum]-1; i>=0; i--) {
        while (pt && bucket[bnum][pt-1].val > bucket[bnum][i].val + l) {
            pt--;
        }
        if(pt == size[bnum]){
            bucket[bnum][i].next = -1;
            bucket[bnum][i].cnt = 0;
        }
        else{
            if(bucket[bnum][pt].next == -1){
                bucket[bnum][i].next = pt;
            }
            else{
                bucket[bnum][i].next = bucket[bnum][pt].next;
            }
            bucket[bnum][i].cnt = bucket[bnum][pt].cnt + 1;
        }
    }
}
 
void bucket_clear(){
    int piv = 0;
    for (int i=0; i<sentinel; i++) {
        for (int j=0; j<size[i]; j++) {
            b[piv++] = bucket[i][j].val;
        }
    }
    for (int i=0; i<sentinel; i++) {
        size[i] = min(n-i*B,B);
        for (int j=0; j<size[i]; j++) {
            bucket[i][j].val = b[i*B + j];
        }
        bucket_label(i);
    }
}
 
void bucket_erase(int bnum, int pos){
    size[bnum]--;
    for (int i=pos; i<size[bnum]; i++) {
        bucket[bnum][i] = bucket[bnum][i+1];
    }
    bucket_label(bnum);
}
 
void bucket_update(int bnum, int pos, int val){
    size[bnum]++;
    for (int i=size[bnum]-1; i>pos; i--) {
        bucket[bnum][i] = bucket[bnum][i-1];
    }
    bucket[bnum][pos].val = val;
    bucket_label(bnum);
}
 
int query(){
    int pos = 0, ret = 0;
    for (int i=0; i<sentinel; ) {
        if(!size[i]){
            i++;
            continue;
        }
         
        ret += bucket[i][pos].cnt + 1;
        if(bucket[i][pos].next != -1) pos = bucket[i][pos].next;
         
        int new_buck = i+1;
        int new_pos = bucket[i][pos].val + l;
        while (1){
            if(new_buck == sentinel) break;
            if(lower_bound(bucket[new_buck],bucket[new_buck] + size[new_buck],(elem){new_pos+1,0,0})
               != bucket[new_buck] + size[new_buck]) break;
            new_buck++;
        }
         
        if(new_buck == sentinel) break;
        i = new_buck;
         
        pos = (int)(lower_bound(bucket[new_buck],bucket[new_buck] + size[new_buck],(elem){new_pos+1,0,0}) - bucket[new_buck]);
    }
    return ret;
}
 
void init(int N, int L, int* X){
    memcpy(a,X,sizeof(int) * N);
    memcpy(b,a,sizeof(int) * N);
    n = N;
    l = L;
    while (sentinel * B < n) sentinel++;
    bucket_clear();
}
 
int update(int i, int y){
    q_cnt = (q_cnt + 1) % U;
    int o = a[i];
    a[i] = y;
    for (int i=0; i<sentinel; i++) {
        if(!size[i]) continue;
        else if(bucket[i][0].val <= o && o <= bucket[i][size[i]-1].val){
            int pos = (int)(lower_bound(bucket[i],bucket[i] + size[i],(elem){o,0,0}) - bucket[i]);
            bucket_erase(i,pos);
            break;
        }
    }
    int low = -1;
    for (int i=0; i<sentinel; i++) {
        if(!size[i]) continue;
        if(bucket[i][0].val <= y) low = i;
    }
    if(low == -1){
        bucket_update(0,0,y);
    }
    else{
        int pos = (int)(lower_bound(bucket[low],bucket[low] + size[low],(elem){y,0,0}) - bucket[low]);
        bucket_update(low,pos,y);
    }
    if(q_cnt == 0){
        bucket_clear();
    }
    return query();
}