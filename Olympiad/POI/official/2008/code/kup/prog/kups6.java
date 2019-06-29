/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kupno gruntu (KUP)                                        *
 *   Plik:     kups6.java                                                *
 *   Autor:    Jakub Pawlewicz                                           *
 *   Opis:     Rozwiazanie za wolne, zlozonosc O(n^6).                   *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;

public class kups6 implements Runnable {
	public static void main(String[] args) {
		(new kups6()).run();
	}

	public void printResult(int x1, int y1, int x2, int y2) {
		System.out.print(x1);
		System.out.print(' ');
		System.out.print(y1);
		System.out.print(' ');
		System.out.print(x2);
		System.out.print(' ');
		System.out.println(y2);
	}

	int v[][];

	public void run() {
		try {
			int k, n;
			BufferedReader br = new BufferedReader(new InputStreamReader(
					System.in));
			StringTokenizer st = new StringTokenizer(br.readLine());
			k = Integer.parseInt(st.nextToken());
			n = Integer.parseInt(st.nextToken());
			v = new int[n][n];
			for (int y = 0; y < n; y++) {
				st = new StringTokenizer(br.readLine());
				for (int x = 0; x < n; x++)
					v[x][y] = Integer.parseInt(st.nextToken());
			}
			for (int x1 = 0; x1 < n; x1++)
				for (int x2 = x1; x2 < n; x2++)
					for (int y1 = 0; y1 < n; y1++)
						for (int y2 = y1; y2 < n; y2++) {
							long s = 0;
							for (int x = x1; x <= x2; x++)
								for (int y = y1; y <= y2; y++)
									s += v[x][y];
							if (k <= s && s <= 2 * k) {
								printResult(x1 + 1, y1 + 1, x2 + 1, y2 + 1);
								return;
							}
						}
			System.out.println("NIE");
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}
};
