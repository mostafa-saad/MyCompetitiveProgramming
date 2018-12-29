// KONDUKTOR
// Weryfikator wej¶æ
// Autor: Pawel Parys


#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

#define REP(a,n) for (int a=0; a<(n); ++a)
#define FOR(a,l,h) for (int a=(l); a<=(h); ++a)

using namespace std;

#define INF 1000000000

char buf[9000000];
int line = 0;
bool no_newline = false;

void error(const char *str)
{
	printf("WRONG (line %d): %s\n", line, str);
	exit(1);
}

void read_ints(int n)
{
	++line;
	fgets(buf, sizeof(buf), stdin);
	int l = strlen(buf);
	if (!l || no_newline)
		error("Unexpected end of file");
	if (buf[l-1]!='\n')
		no_newline = true;
	else
		--l;
	buf[l] = 0;
	int dl = 0;
	REP(a, l)
	{
		if (!isdigit(buf[a]) && buf[a]!=' ')
			error("Illegal character");
		if (isdigit(buf[a]))
		{
			if (!dl)
				--n;
			++dl;
			if (dl>10 || (dl==10 && !(buf[a-9]=='1' || (buf[a-9]=='2' && buf[a-8]=='0'))))
				error("Integer too big");
		}
		else
		{
			if (!n)
				error("Unexpected characters at end of line");
			if (!a || buf[a-1]==' ')
				error("Too many spaces");
			dl = 0;
		}
	}
	if (n)
		error("Unexpected end of line");
}

void end_of_file()
{
	if (no_newline)
		error("No trailing endline");
	if (fgets(buf, sizeof(buf), stdin)!=NULL)
	{
		++line;
		error("Unexpected characters at end of file\n");
	}
}

int main()
{
	int N, K;
	read_ints(2);
	sscanf(buf, "%d%d", &N, &K);
	if (2>N || N>600)
		error("N out of range");
	if (1>K || K>N-1 || K>50)
		error("K out of range");
	long long suma = 0;
	REP(a, N-1)
	{
		read_ints(N-a-1);
		int pos = 0;
		char ch = 0;
		REP(b, N-a-1)
		{
			int x, prz;
			swap(buf[pos+12], ch);  // specjalna sztuczka, inaczej wolno dziala
			sscanf(buf+pos, "%d%n", &x, &prz);
			swap(buf[pos+12], ch);
			pos += prz;
			if (0>x)
				error("x_{i,j} out of range");
			suma += x;
		}
	}
	if (suma>2000000000)
		error("za duzo pasazerow");
	end_of_file();
	printf("OK %d %d %Ld\n", N, K, suma);
}
