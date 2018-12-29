/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Squarki                                          *
 *   Autor:             Alan Kutniewski                                  *
 *   Opis:              Weryfikator testow                               *
 *                                                                       *
 *************************************************************************/

#include "oi.h"
#include <vector>
#include <iostream>
#define MAXN 300
#define MINN 3
#define MAXS 100000000
#define MINS 0

using namespace std;

int main(int argc, char **args) {
    oi::Scanner in(args[1]);
    oi::Scanner zaw(args[2]);
    oi::Scanner wzr(args[3]);
  int n = in.readInt(MINN, MAXN);
    int ileodp = wzr.readInt(0, MAXN);
    zaw.skipWhitespaces();
    if(zaw.readInt(0, MAXN) != ileodp){
        cout << "WRONG\nBledna liczba wynikow";
        return 0;
    }
    vector <int> wzrodp[ileodp];
    vector <int> zawodp[ileodp];
    for(int i = 0; i < ileodp; ++i){
        wzrodp[i].clear();
        zawodp[i].clear();
        for(int j = 0; j < n; ++j){
            zaw.skipWhitespaces();
            zawodp[i].push_back(zaw.readInt(MINS, MAXS));
            wzr.skipWhitespaces();
            wzrodp[i].push_back(wzr.readInt(MINS, MAXS));
        }
        sort(wzrodp[i].begin(), wzrodp[i].end());
        sort(zawodp[i].begin(), zawodp[i].end());
    }
    for(int i = 0; i < ileodp; ++i){
        bool ok = false;
        for(int j = 0; j < ileodp; ++j){
            if(zawodp[i][0] == wzrodp[j][0]){
                ok = true;
                for(int k = 1; k < n; ++k){
                    if(zawodp[i][k] != wzrodp[j][k]){
                        cout << "WRONG\nWynik(" << i + 1 << ") jest nieprawidlowy";
                        return 0;
                    }
                }
                j = ileodp;
            }
        }
        if(!ok){
            cout << "WRONG\nWynik(" << i + 1 << ") jest nieprawidlowy";
            return 0;
        }
    }
    cout << "OK\n";
    return 0;

}

