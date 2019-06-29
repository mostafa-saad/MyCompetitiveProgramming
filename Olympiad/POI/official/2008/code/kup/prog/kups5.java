/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kupno gruntu (KUP)                                        *
 *   Plik:     kups5.java                                                *
 *   Autor:    Jakub Pawlewicz                                           *
 *   Opis:     Rozwiazanie za wolne, zlozonosc O(n^4).                   *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;

public class kups5 implements Runnable {
	public static void main(String[] args) {
		(new kups5()).run();
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

	long v[][];

	public long getS(int x1, int y1, int x2, int y2) {
		return v[x2][y2] - v[x1 - 1][y2] - v[x2][y1 - 1] + v[x1 - 1][y1 - 1];
	}

	public void run() {
		try {
			int k, n;
			BufferedReader br = new BufferedReader(new InputStreamReader(
					System.in));
			StringTokenizer st = new StringTokenizer(br.readLine());
			k = Integer.parseInt(st.nextToken());
			n = Integer.parseInt(st.nextToken());
			v = new long[n + 1][n + 1];
			for (int y = 0; y <= n; y++) {
				if (y != 0)
					st = new StringTokenizer(br.readLine());
				for (int x = 0; x <= n; x++)
					v[x][y] = x == 0 || y == 0 ? 0 : Integer.parseInt(st.nextToken());
			}
			for (int y = 1; y <= n; y++)
				for (int x = 2; x <= n; x++)
					v[x][y] += v[x - 1][y];
			for (int x = 1; x <= n; x++)
				for (int y = 2; y <= n; y++)
					v[x][y] += v[x][y - 1];
			for (int x1 = 1; x1 <= n; x1++)
				for (int x2 = x1; x2 <= n; x2++)
					for (int y1 = 1; y1 <= n; y1++)
						for (int y2 = y1; y2 <= n; y2++) {
							long s = getS(x1, y1, x2, y2);
							if (k <= s && s <= 2 * k) {
								printResult(x1, y1, x2, y2);
								return;
							}
						}
			System.out.println("NIE");
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}
};
