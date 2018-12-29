/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Patyczki                                         *
 *   Autor:             Alan Kutniewski                                  *
 *   Opis:              Program sprawdzajacy wyjscia                     *
 *                                                                       *
 *************************************************************************/

#include "weryfikator.h"
#include <cstring>

void my_error(const char* msg, int line, int pos)
{
    fprintf(stdout, "WRONG\n");    
    exit(0);
}

bool ansNIE = false;
char corrans[4];

bool nt(int x, int y, int z){ //sprawdza nierówność trójkąta dla x, y i z
	if(x < y + z && y < x + z && z < x + y)return true;
	return false;
}

int main(int argc, char **argv){
    Scanner out_zaw(argv[2], my_error);
    Scanner out_correct(argv[3]);
    out_correct.readString(corrans, 4);
    if(strcmp(corrans, "NIE") == 0)ansNIE = true;
    if(ansNIE){
        out_zaw.skipWhitespaces();
		out_zaw.readString(corrans, 4);
        if(strcmp(corrans, "NIE")){
			puts("WRONG\nOczekiwano NIE");
			return 0;
		}
	}
	else{
		int kol[3], dl[3]; //kolory i długości
		//zczytanie danych wypisanych
		for(int i = 0; i < 3; ++i){
			out_zaw.skipWhitespaces();
			kol[i] = out_zaw.readInt(1, 50);
			out_zaw.skipWhitespaces();
			dl[i] = out_zaw.readInt(0, 1000000000);
		}
		//sprawdzenie poprawności tych danych
		if(kol[0] == kol[1] || kol[0] == kol[2] || kol[1] == kol[2]){
			puts("WRONG\nWypisano patyczki o takich samych kolorach");
			return 0;
		}
		if(!nt(dl[0], dl[1], dl[2])){
			puts("WRONG\nZ wypisanych patyczkow nie da sie utworzyc trojkata");
			return 0;
		}
		//sprawdzenie, czy podane patyczki występują w wejściu
		Scanner in(argv[1]);
		int k, n, d;
		bool ok[3]; //czy dany patyczek występował w wejściu
		k = in.readInt();
		in.readEoln();
		for(int i = 1; i <= k; ++i){
			n = in.readInt();
			for(int j = 0; j < n; ++j){
				in.readSpace();
				d = in.readInt();
				for(int c = 0; c < 3; ++c){
					if(kol[c] == i && dl[c] == d)ok[c] = true;
				}
			}
			in.readEoln();
		}
		for(int i = 0; i < 3; ++i){
			if(!ok[i]){
				puts("WRONG\nKorzytsanie z nieistniejacych patyczkow");
			}
		}
	}
    puts("OK");
    return 0;
}

