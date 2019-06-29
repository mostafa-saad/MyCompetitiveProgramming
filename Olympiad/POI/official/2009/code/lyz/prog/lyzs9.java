/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Lyzwy (LYZ)                                               *
 *   Plik:     lyzs9.cpp                                                 *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Rozwiazanie wolniejsze O(n*m). Zapamietuje aktualnie      *
 *             najmniejszy rozmiar wolnych lyzew.                        *
 *                                                                       *
 *************************************************************************/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class lyzs9 {
	final static int MAX_N = 200001;
	
	static int n, m, k, d;
	static long t[] = new long[MAX_N];
	
	static boolean spr() {
		int i;
		long max=0, cur=0;
		/* Szukanie spojnego podciagu o najwiekszej sumie */
		for(i = 1; i <= n-d; i++) {
			cur += t[i];
			if(cur > max) max = cur;
			if(cur < 0) cur = 0;
		}
		if(max > (long) k * (long) d) return false; else return true;
	}
	
	public static void main(String[] args) throws java.io.IOException {
		BufferedReader bufReader = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer tokenizer = new StringTokenizer(bufReader.readLine());
		n = Integer.parseInt(tokenizer.nextToken());
		m = Integer.parseInt(tokenizer.nextToken());
		k = Integer.parseInt(tokenizer.nextToken());
		d = Integer.parseInt(tokenizer.nextToken());
		
		for(int i = 1; i <= n-d; i++) t[i] = -k;
		
		for(int i = 0; i < m; i++) {
			tokenizer = new StringTokenizer(bufReader.readLine());
			int r = Integer.parseInt(tokenizer.nextToken());
			int x = Integer.parseInt(tokenizer.nextToken());
			t[r] += x;
			if (spr())
				System.out.println("TAK");
			else
				System.out.println("NIE");
		}
	}
}
