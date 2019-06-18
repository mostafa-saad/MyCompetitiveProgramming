#include "grader.h"
#include "cluedo.h"
 
void Solve(){
    int p1 = 1, p2 = 1, p3 = 1;
 
    while (1) {
        int t = Theory(p1,p2,p3);
        if(t == 1) p1++;
        if(t == 2) p2++;
        if(t == 3) p3++;
        if(t == 0) break;
    }
}