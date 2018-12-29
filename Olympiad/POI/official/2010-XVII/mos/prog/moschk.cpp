/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Mosty (MOS)                                               *
 *   Plik:     moschk.cpp                                                *
 *   Autor:    Miroslaw Michalski                                        *
 *   Opis:     Weryfikator wyjsc.                                        *
 *                                                                       *
 *************************************************************************/

#include "weryfikator.h"

#include <cstdio>
#include <cstdlib>
#include <string.h>
using namespace std;

const int MAXM = 2013;
const int MAXB = 1024;

void wrong_answer(const char *msg, int line=0, int position=0){
	printf("WRONG\n%s\n",msg);
    exit(0);
}

int main(int argc, char **argv) {
    int n, m, ans;
    int a[MAXM], b[MAXM], l[MAXM], p[MAXM];
    bool used[MAXM];
    char buff[MAXB];
    char ret_buffer[MAXB];
    assert(argc==4);
    
    for(int i=0; i<MAXM; i++) used[i] = false;
    freopen(argv[1], "r", stdin);
    scanf("%d%d",&n, &m);
    for(int i=1; i<=m; i++)
        scanf("%d%d%d%d",&a[i], &b[i], &l[i], &p[i]);
    
    
    freopen(argv[3], "r", stdin);
    scanf("%s", buff);
    if (buff[0]=='N') ans = -1; else sscanf(buff,"%d",&ans);

 	Scanner* scanner=new Scanner(argv[2], wrong_answer, Lang(PL));
    if (ans == -1) {
        scanner->readString(buff, 7);
        if (strcmp(buff,"NIE")) {
            sprintf(ret_buffer, "chcialem wczytac 'NIE' a tu '%s'",buff);
            wrong_answer(ret_buffer);
        }
        scanner->skipWhitespaces();
        scanner->readEof();
        puts("OK");
        return 0;
    } else {
        int r;
        r = scanner->readInt(1, 1000);
        if (r != ans) {
            sprintf(ret_buffer, "ojoj, proponujesz %d, a powinno byc %d",r, ans);
            wrong_answer(ret_buffer);
        }
        scanner->skipWhitespaces();
        int start = 1;
        for(int i=0; i<m; i++) {
            int x = scanner->readInt(1, m);
            if (used[x]) {
                sprintf(ret_buffer, "powtorzona krawedz %d",x);
                wrong_answer(ret_buffer);
            }
            used[x] = true;
            if (a[x]!=start && b[x]!=start) {
                sprintf(ret_buffer, "krawedz %d nie jest incydentna z wierzcholkiem %d",x, start);
                wrong_answer(ret_buffer);
            }
            if (a[x]==start) {
                r=l[x];
                start=b[x];
            } else {
                r=p[x];
                start=a[x];
            }
            if (r>ans) {
                sprintf(ret_buffer,"ojoj, krawedz %d przechodzona w te strone ma koszt wiekszy od wyniku",x);
                wrong_answer(ret_buffer);
            }
            scanner->skipWhitespaces();
        }
        scanner->readEof();
    }
    delete scanner;
    puts("OK");
    return 0;
}
