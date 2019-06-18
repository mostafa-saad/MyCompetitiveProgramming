#include <cstdio>
 
int n,l;
char str[3000005],dtr[3005];
 
int getN(char t){
    if(t <= 'Z' && t >= 'A') return t - 'A';
    return t + 26 - 'a';
}
 
int main(){
    int cnt = 0, chash[52], dhash = 0, ehash = 0;
    chash[0] = 1;
    for (int i=1; i<52; i++) {
        chash[i] = chash[i-1] * 3109;
    }
    scanf("%d %d",&n,&l);
    scanf("%s %s",dtr,str);
    for(int i=0; i<n; i++) {
        dhash += chash[getN(dtr[i])];
        ehash += chash[getN(str[i])];
    }
    if(dhash == ehash) cnt++;
    for (int i=n; i<l; i++) {
        ehash += chash[getN(str[i])] - chash[getN(str[i-n])];
        if(dhash == ehash) cnt++;
    }
    printf("%d",cnt);
}
