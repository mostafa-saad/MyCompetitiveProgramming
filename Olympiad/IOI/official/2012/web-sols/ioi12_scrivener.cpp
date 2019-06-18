char ops[1000005];
int prev[1000005][20], size[1000005], sz;
int go[1000005];
 
void Init(){
     
}
 
void TypeLetter(char L){
    int p = sz;
    go[p] = p;
    ops[p] = L;
    if(p) prev[p][0] = go[p-1];
    for (int i=1; prev[p][i-1]; i++) {
        prev[p][i] = prev[prev[p][i-1]][i-1];
    }
    size[p] = size[prev[p][0]]+1;
    sz++;
}
 
void UndoCommands(int U){
    go[sz] = go[sz-U-1];
    sz++;
}
 
char GetLetter(int P){
    int pos = go[sz-1];
    int obj = P+1;
    for (int i=19; i>=0; i--) {
        if(size[prev[pos][i]] >= obj){
            pos = prev[pos][i];
        }
    }
    return ops[pos];
}