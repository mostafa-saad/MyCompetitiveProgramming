/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Slonie (SLO)                                              *
 *   Plik:     slo1.java                                                 *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Rozwiazanie wzorcowe O(n)                                 *
 *                                                                       *
 *************************************************************************/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.io.IOException;

class slo1 {

	static final int INF = 1000000000;

	static final int MAXN = 1000000;

	static int[] wagi = new int[MAXN];
	static int[] orig = new int[MAXN]; // orig[i] = kto stal na pozycji i
	static int[] perm = new int[MAXN]; // slon i ma wyladowac na pozycji slonia perm[i]
	static boolean[] vis = new boolean[MAXN]; // nalezy do juz zbadanego cyklu
	
	static int minw = INF; // minimalna waga
	
	public static void main(String[] args)
	{
        	BufferedReader rd = new BufferedReader(new InputStreamReader(System.in));
        	int N = 0;
       		try 
       		{
	                StringTokenizer input = new StringTokenizer(rd.readLine());
       			N = Integer.parseInt(input.nextToken());
	                input = new StringTokenizer(rd.readLine());
			for (int a = 0; a<N; ++a)
			{
				wagi[a] = Integer.parseInt(input.nextToken());
				minw = Math.min(minw, wagi[a]);
			}
			input = new StringTokenizer(rd.readLine());
			for (int a = 0; a<N; ++a)
				orig[a] = Integer.parseInt(input.nextToken())-1;
			input = new StringTokenizer(rd.readLine());
			for (int a = 0; a<N; ++a)
				perm[Integer.parseInt(input.nextToken())-1] = orig[a];
		}
		catch (IOException e) {}
		long wynik = 0;
		for (int pocz = 0; pocz<N; ++pocz) 
			if (!vis[pocz])
			{
				int minc = INF; // minimalna waga w cyklu
				long suma = 0; // suma wag w cyklu
				int cur = pocz;
				int dl = 0; // dlugosc cyklu
				for (;;)
				{
					minc = Math.min(minc, wagi[cur]);
					suma += wagi[cur];
					cur = perm[cur];
					vis[cur] = true;
					++dl;
					if (cur==pocz)
						break;
				}
				wynik += Math.min(suma+(dl-2)*(long)minc, suma+minc+(dl+1)*(long)minw);
			}
		System.out.println(wynik);
	}
}
	
