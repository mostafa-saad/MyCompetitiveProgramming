/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Konkurs programistyczny                          *
 *   Autor:             Pawel Parys                                      *
 *   Zlozonosc czasowa: O(mk^2) = O(m^5)                                 *
 *   Opis:              Rozwiazanie bledne                               *
 *                      zachlannie przestawiamy krawedzie jak najlepiej, *
 *                      zeby kazde zadanie bylo rozwiazywane przez       *
 *                      najmniej obciazona osobe                         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>

#define REP(a,n) for (int a=0; a<(n); ++a)

using namespace std;

template<class T>
int size(const T &t) { return t.size(); }

typedef vector<int> vi;

#define PB push_back

/////////////////////////////////////////

int No, Nz, maxZ;

vi zad2os_nu[500];
int zad_uzyte[500], os_ile[500];

int main()
{
	int R, T, K;
	scanf("%d%d%d%d%d", &No, &Nz, &R, &T, &K);
	maxZ = T/R;
	REP(z, Nz)
		zad_uzyte[z] = -1;
	// wczytywanie + wstêpny przydzia³
	REP(a, K)
	{
		int o, z;
		scanf("%d%d", &o, &z);
		--o; --z;
		if (zad_uzyte[z]<0)
		{
			zad_uzyte[z] = o;
			++os_ile[o];
		}
		else
			zad2os_nu[z].PB(o);
	}
	// zach³anne poprawianie: dla ka¿dego zadania bierzemy najlepsz± osobê, 
	// która mo¿e je rozwi±zaæ
	bool ch = true; // czy nast±pi³a poprawa
	while (ch)
	{
		ch = false;
		REP(z, Nz)
		{
			if (zad_uzyte[z]<0)
				continue; // nikt nie umie rozwi±zaæ
			int bvi = os_ile[zad_uzyte[z]]-1;
			int bestval = bvi, best = 0;
			REP(nr, size(zad2os_nu[z]))
			{
				int o = zad2os_nu[z][nr];
				if (os_ile[o]<bestval)
				{
					bestval = os_ile[o];
					best = nr;
				}
			}
			if (bestval==bvi)
				continue; // nic nie mozna poprawic
			ch = true;
			--os_ile[zad_uzyte[z]];
			swap(zad2os_nu[z][best], zad_uzyte[z]);
			++os_ile[zad_uzyte[z]];
		}
	}
	// wypisywanie wyniku
	int ile = 0, res = 0;
	REP(o, No)
	{
		int x = os_ile[o] = min(os_ile[o], maxZ);
		ile += x;
		res += x*(x+1)/2;
	}
	printf("%d %d\n", ile, res*R);
	REP(z, Nz)
		if (zad_uzyte[z]>=0 && os_ile[zad_uzyte[z]]>0)
			printf("%d %d %d\n", zad_uzyte[z]+1, z+1, (--os_ile[zad_uzyte[z]])*R);
}
