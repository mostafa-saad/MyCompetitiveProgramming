#include "grader.h"
#include "memory.h"
 
void play(){
    int fst[100] = {}, snd[100]= {};
    for (int i=1; i<=50; i+=2) {
        int t1 = faceup(i);
        int t2 = faceup(i+1);
        if(fst[t1]) snd[t1] = i;
        else fst[t1] = i;
        if(fst[t2]) snd[t2] = i+1;
        else fst[t2] = i+1;
    }
    for (int i='A'; i<='Y'; i++) {
        faceup(fst[i]); faceup(snd[i]);
    }
}