/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Stacja (STA)                                              *
 *   Plik:     sta1.java                                                 *
 *   Autor:    Marek Cygan (oryginal Jakub Radoszewski)                  *
 *   Opis:     Rozwiazanie o zlozonosci czasowej O(n), wykonuje          *
 *             dwuprzebiegowe programowanie dynamiczne w drzewie.        *
 *                                                                       *
 *************************************************************************/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class sta1 {
	public static int n;
	public static ArrayList<Integer>[] graf;
	public static int[] wezly;
	public static boolean[] odw;
	/* Uwaga: Trzeba zastosowac typ 64-bitowy! */
	public static long[] drogi;
	public static long[] wynik;

	/* Liczenie liczb wezlow i sum odleglosci w poddrzewach */
	public static void faza1(int v)
	{
		odw[v] = true;
		wezly[v] = 1;
		drogi[v] = 0;
		for (int w : graf[v])
		{
			if (!odw[w])
			{
				faza1(w);
				wezly[v] += wezly[w];
				drogi[v] += drogi[w] + wezly[w];
			}
		}
	}

	/* Liczenie wlasciwych wynikow, par to ojciec danego wezla */
	public static void faza2(int v, int par)
	{
		wynik[v] = wynik[par] - wezly[v] + (n - wezly[v]);
		for (int x : graf[v])
			if (x != par)
				faza2(x, v);
	}

	@SuppressWarnings("unchecked")
	public static void main(String[] args) 
	{
		new Thread(){ 
			public void run(){
				try{
					/* Odczyt */
					BufferedReader bufReader = new BufferedReader(new InputStreamReader(System.in));
					StringTokenizer tokenizer = new StringTokenizer(bufReader.readLine());
					n = Integer.parseInt(tokenizer.nextToken());
					graf = new ArrayList[n];
					wezly = new int[n];
					odw = new boolean[n];
					drogi = new long[n];
					wynik = new long[n];
					for (int i = 0; i < n; ++i) 
						graf[i] = new ArrayList<Integer>();
					
					for (int i = 0; i < n - 1; i++)
					{
						int a, b;
						tokenizer = new StringTokenizer(bufReader.readLine());
						a = Integer.parseInt(tokenizer.nextToken());
						b = Integer.parseInt(tokenizer.nextToken());
						a--; b--;
						graf[a].add(b);
						graf[b].add(a);
					}
					
					/* Dwukrotne programowanie dynamiczne */
					faza1(0);
					wynik[0] = drogi[0];
					for (int x : graf[0])
						faza2(x, 0);
					
					/* Wyznaczanie i wypisywanie wyniku */
					long wyn = wynik[0];
					for (int i = 1; i < n; ++i)
						wyn = Math.max(wyn, wynik[i]);
					
					for (int i = 0; i < n; i++)
						if (wynik[i] == wyn)
						{
							System.out.println(i + 1);
							break;
						}
				} catch (IOException e){
				}
			}
		}.start();
	}
}
