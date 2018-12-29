/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Licytacja                                        *
 *   Autor:             Alan Kutniewski                                  *
 *   Opis:              Weryfikator odpowiedzi                           *
 *                                                                       *
 *************************************************************************/

#include "oi.h"
#include <iostream>
#define MAXN 2000
#define MAGIC_IN_SUM 7496
#define MAGIC_OUT 756396726
#define OK 1
#define ERR 0

using namespace std;

int main(int argc, char **args){
    oi::Scanner in(args[1]);
    oi::Scanner zaw(args[2]);
    oi::Scanner wzr(args[3]);

    int magic = zaw.readInt(0, MAGIC_OUT + 10);
    if(magic != MAGIC_OUT){
        cout << "WRONG\nBledne uzycie biblioteki";
        return 0;
    }
    zaw.readEoln();
    int result = zaw.readInt(0, 1);
    if(result == OK){
        cout << "OK\n";
        return 0;
    }
    zaw.readEoln();
    char msg[64];
    zaw.readLine(msg, 63);
    cout << "WRONG\n" << msg;
    return 0;
}
