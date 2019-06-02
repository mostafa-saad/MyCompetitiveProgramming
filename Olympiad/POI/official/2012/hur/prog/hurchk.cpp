/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Hurtownia                                        *
 *   Autor:             Alan Kutniewski                                  *
 *   Opis:              Weryfikator odpowiedzi                           *
 *                                                                       *
 *************************************************************************/

#include "oi.h"
#include <iostream>
#define MAXN 250000
#define MINN 1
#define MAXV 1000000000ll
#define MINV 0ll
#define MINR 0
#define MAXR MAXN

using namespace std;

int main(int argc, char **args) {
    oi::Scanner in(args[1]);
    oi::Scanner zaw(args[2]);
    oi::Scanner wzr(args[3]);
    int res_wzr = wzr.readInt(MINR, MAXR);
    zaw.skipWhitespaces();
    int res_zaw = zaw.readInt(MINR, MAXR);
    if(res_wzr != res_zaw){
        cout << "WRONG\nBledna liczba zrealizowanych zamowien\n";
        return 0;
    }

    int n = in.readInt(MINN, MAXN);
    in.readEoln();
    long long a[n], b[n];
    for(int i = 0; i < n; ++i){
        if(i)in.readSpace();
        a[i] = in.readLL(MINV, MAXV);
    }
    in.readEoln();
    for(int i = 0; i < n; ++i){
        if(i)in.readSpace();
        b[i] = in.readLL(MINV, MAXV);
    }
    long long sum = 0;
    int last_ans = -1;
    int it = 0;
    for(int i = 0; i < res_zaw; ++i){
        zaw.skipWhitespaces();
        int act_ans = zaw.readInt(1, n);
        if(act_ans <= last_ans){
            cout << "WRONG\nNumery zamowien nie sa posortowane\n";
            return 0;
        }
        last_ans = act_ans;
        while(it < act_ans){
            sum += a[it];
            ++it;
        }
        if(sum < b[act_ans - 1]){
            cout << "WRONG\nNie mozna zrealizowac wybranych zamowien\n";
            return 0;
        }
        sum -= b[act_ans - 1];
    }
    cout << "OK" << endl;
    return 0;
}

