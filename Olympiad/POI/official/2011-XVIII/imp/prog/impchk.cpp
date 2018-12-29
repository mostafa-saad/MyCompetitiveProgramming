/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Impreza                                          *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Program sprawdzajacy wyjscia                     *
 *                                                                       *
 *************************************************************************/

#include "weryfikator.h"
#include <cstring>
#include <vector>
#define MAXN 3000

void my_error(const char* msg, int line, int pos)
{
    fprintf(stdout, "WRONG\n");    
    exit(0);
}

bool kmatrix[MAXN][MAXN];
bool choosen[MAXN];
vector <int> ans;
int n, m, a, b;

int main(int argc, char **argv){
    Scanner out_zaw(argv[2], my_error);
	Scanner in(argv[1]);
	n = in.readInt();
	in.readSpace();
	m = in.readInt();
	in.readEoln();
	for(int i = 0; i < m; ++i){
		a = in.readInt();
		in.readSpace();
		b = in.readInt();
		in.readEoln();
		kmatrix[a-1][b-1] = kmatrix[b-1][a-1] = true;
	}
	while(!out_zaw.isEOF()){
		out_zaw.skipWhitespaces();
		a = out_zaw.readInt();
		if(a < 1 || a > n) {
			puts("WRONG\nWypisano numer osoby spoza zakresu [1;n]");
			return 0;
		}
		--a;
		if(choosen[a]){
			puts("WRONG\nWypisano jedna osobê kilka razy");
			return 0;
		}
		ans.push_back(a);
		choosen[a] = true;
		if((int)ans.size() > (n/3)){
			puts("WRONG\nWypisano za du¿o osób");
			return 0;
		}
		out_zaw.skipWhitespaces();
	}
	if((int)ans.size() < (n/3)){
		puts("WRONG\nWypisano za ma³o osób");
		return 0;
	}
	for(int i = 0; i < (int)ans.size(); ++i){
		for(int j = 0; j < i; ++j){
			if(!kmatrix[ans[i]][ans[j]]){
				puts("WRONG\nNie wszystkie wypisane osoby siê znaja");
				return 0;
			}
		}
	}
    puts("OK");
    return 0;
}
