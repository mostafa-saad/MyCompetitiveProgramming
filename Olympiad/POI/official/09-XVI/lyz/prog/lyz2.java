/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Lyzwy (LYZ)                                               *
 *   Plik:     lyz2.java                                                 *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Rozwiazanie wzorcowe O((n+m)*log(n))                      *
 *                                                                       *
 *************************************************************************/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class lyz2 {
	final static int MAX_N = 200000;
	final static int MAX_N2 = 262144;
	final static int KORZEN = 1;
	
	static class wezel {
		public long suma;
		public long mx_lewy, mx_prawy, mx;
	}
	static int rodzic(int v) { return v / 2; }
	static int lsyn(int v) { return 2 * v; }
	static int psyn(int v) { return 2 * v + 1; }
	
	static wezel[] drz;
	static int ile;
	
	/* Zmienia ilosc czlonkow o rozmiarze stopy x o w i uaktualnia drzewo */
	static void ustaw(int x, int w) {
		/* Ustawia wartosc w wierzcholku reprezentujacym przedzial jednoelementowy */
		int v = ile + x;
		drz[v].suma += w;
		drz[v].mx_lewy = drz[v].mx_prawy = drz[v].mx = Math.max(drz[v].suma, 0);
	
		/* Poprawia idac w gore drzewa */
		while (v != KORZEN)
		{
			v = rodzic(v);
			drz[v].suma = drz[lsyn(v)].suma + drz[psyn(v)].suma;
			drz[v].mx_lewy = Math.max(drz[lsyn(v)].mx_lewy, drz[lsyn(v)].suma + drz[psyn(v)].mx_lewy);
			drz[v].mx_prawy = Math.max(drz[psyn(v)].mx_prawy, drz[psyn(v)].suma + drz[lsyn(v)].mx_prawy);
	
			drz[v].mx = Math.max(drz[lsyn(v)].mx, drz[psyn(v)].mx);
			drz[v].mx = Math.max(drz[v].mx, drz[lsyn(v)].mx_prawy + drz[psyn(v)].mx_lewy);
		}
	}
	
	public static void main(String[] args) throws java.io.IOException {
		BufferedReader bufReader = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer tokenizer = new StringTokenizer(bufReader.readLine());
		int n = Integer.parseInt(tokenizer.nextToken());
		int m = Integer.parseInt(tokenizer.nextToken());
		int k = Integer.parseInt(tokenizer.nextToken());
		int d = Integer.parseInt(tokenizer.nextToken());
		
		drz = new wezel[2 * MAX_N2 + 1];
		for(int i = 0; i < drz.length; i++) drz[i] = new wezel();
		
		ile = 1;
		while (ile <= n-d)
			ile *= 2;
		for(int i = 1; i <= n-d; i++)
			ustaw(i, -k);
		/* Przetwarzanie zdarzen */
		for(int i = 0; i < m; i++) {
			tokenizer = new StringTokenizer(bufReader.readLine());
			int r = Integer.parseInt(tokenizer.nextToken());
			int x = Integer.parseInt(tokenizer.nextToken());
			ustaw(r, x);
			if (drz[KORZEN].mx <= (long)d * (long)k)
				System.out.println("TAK");
			else
				System.out.println("NIE");
		}
	}
}
