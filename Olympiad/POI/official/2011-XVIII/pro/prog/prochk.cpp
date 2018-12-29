/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Konkurs programistyczny                          *
 *   Autor:             Pawel Parys                                      *
 *   Opis:              Program sprawdzajacy wyjscia                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>

#define REP(a,n) for (int a=0; a<(n); ++a)
#define FOR(a,b,c) for (int a=(b); a<=(c); ++a)

using namespace std;

template<class T>
int size(const T &t) { return t.size(); }

FILE *foutgr;
char buf[2000000];
int line = 0;

void error(const char *str, int line2 = line)
{
	printf("WRONG\nLine %d: %s\n", line2, str);
	exit(0);
}

void read_ints(int n)
{
	if (!n) // ma byc pusta linia - tak jakby jej mialo nie byc
		return;
	int len = 0;
	for (;;) // wczytuj a¿ dostaniesz niepust± liniê (pomijaj±c puste)
	{
		for (;;) // wczytuj a¿ wczytasz ca³± liniê
		{
			if (len>=(int)sizeof(buf)-1) // koniec bufora
				error("Line too long.", line+1);
			char *ok = fgets(buf+len, sizeof(buf)-len, foutgr);
			if (!ok && !len)
				error("To few lines.", line+1);
			if (!ok) // koniec pliku = koniec linii
				break;
			for (int a = len; buf[a]; ++a) // pomin zbedne spacje
				if (buf[a]!=' ' || (buf[a]==' ' && len && buf[len-1]!=' '))
					buf[len++] = buf[a];
			if (len && buf[len-1]=='\n')
			{ // koniec linii - usun znak konca i przerwij czytanie
				buf[--len] = 0;
				break;
			}
		}
		++line;
		if (len)
			break;
	}
	while (len && buf[len-1]==' ')
		--len; // usun spacje z konca linii
	int dl = 0;
	REP(a, len)
	{
		if (!isdigit(buf[a]) && buf[a]!=' ')
			error("Invalid character.");
		if (isdigit(buf[a]))
		{
			if (!dl)
				--n;
			++dl;
			if (dl>9 && (dl>10 || buf[a-9]!='1'))
				error("Number to big.");
		}
		else
		{
			if (!n)
				error("Garbage at the end of line.");
			dl = 0;
		}
	}
	if (n)
		error("Too few numbers in a line.");
}

void end_of_file()
{
	++line;
	for (;;) // wczytuj i pomijaj puste linie
	{
		char *ok = fgets(buf, sizeof(buf), foutgr);
		if (!ok) 
			break;
		int len = strlen(buf);
		REP(a, len)
			if (buf[a]!=' ' && buf[a]!='\n')
				error("Garbage at the end of file.");
		if (len && buf[len-1]=='\n')
		{
			++line;
			buf[--len] = 0;
		}
	}
}

int N, M, R, T, K;
bool moze[500][500];
vector<int> czasy[500];
bool bylo[500];

int main(int argc, char **argv)
{
	if (argc!=4)
	{
		fprintf(stderr, "Three arguments needed!!!\n");
		return -1;
	}
	FILE *fin = fopen(argv[1], "r");
	foutgr = fopen(argv[2], "r");
	FILE *foutok = fopen(argv[3], "r");
	if (fin==NULL || foutgr==NULL || foutok==NULL)
	{
		fprintf(stderr, "Error opening files!!!\n");
		return -2;
	}
	fscanf(fin, "%d%d%d%d%d", &N, &M, &R, &T, &K);
	REP(i, K)
	{
		int a, b;
		fscanf(fin, "%d%d", &a, &b);
		moze[a-1][b-1] = true;
	}
	int bestile, bestkara;
	fscanf(foutok, "%d%d", &bestile, &bestkara);
	int ile, kara;
	read_ints(2); 
	sscanf(buf, "%d%d", &ile, &kara);
	if (ile<bestile)
	{
		sprintf(buf, "It was possible to solve %d problems and you solved only %d.", bestile, ile);
		error(buf);
	}
	if (ile>bestile)
	{
		sprintf(buf, "Your program assigned %d problems but it was possible to solve only %d.", ile, bestile);
		error(buf);
	}
	if (kara>bestkara)
	{
		sprintf(buf, "It was possible to get penalty of %d points and you received %d.", bestkara, kara);
		error(buf);
	}
	if (kara<bestkara)
	{
		sprintf(buf, "Your program calculated penalty of %d points but it was possible to get no less than %d.", kara, bestkara);
		error(buf);
	}
	int karaj = 0;
	REP(p, ile)
	{
		read_ints(3);
		int a, b, c;
		sscanf(buf, "%d%d%d", &a, &b, &c);
		if (a<1 || a>N)
		{
			sprintf(buf, "Contestant number %d out of range.", a);
			error(buf);
		}
		if (b<1 || b>M)
		{
			sprintf(buf, "Problem number %d out of range.", b);
			error(buf);
		}
		if (c<0 || c>T-R)
		{
			sprintf(buf, "Start moment %d out of range.", c);
			error(buf);
		}
		if (!moze[a-1][b-1])
		{
			sprintf(buf, "Contestant %d does not know how to solve problem %d.", a, b);
			error(buf);
		}
		if (bylo[b-1])
		{
			sprintf(buf, "Problem %d solved more than once.", b);
			error(buf);
		}
		bylo[b-1] = true;
		czasy[a-1].push_back(c);
		karaj += c+R;
		sort(czasy[a-1].begin(), czasy[a-1].end());
		REP(x, size(czasy[a-1])-1)
			if (czasy[a-1][x]+R>czasy[a-1][x+1])
			{
				sprintf(buf, "Contestant %d in moment %d solves more than one problem.", a, czasy[a-1][x+1]);
				error(buf);
			}
	}
	if (karaj!=kara)
	{
		sprintf(buf, "You calculated the penalty of %d but in fact it is %d.", kara, karaj);
		error(buf);
	}
	end_of_file();
	printf("OK\n");
}
