/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kupno gruntu (KUP)                                        *
 *   Plik:     kup1.java                                                 *
 *   Autor:    Jakub Pawlewicz                                           *
 *   Opis:     Rozwiazanie wzorcowe, zlozonosc O(n^2).                   *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;

public class kup1 implements Runnable {
	public static void main(String[] args) {
		(new kup1()).run();
	}

	private class Point {
		public int x;
		public int y;

		Point(int nx, int ny) {
			x = nx;
			y = ny;
		}
	}

	int v[][];
	
	public int getS(int x1, int y1, int x2, int y2) {
		return v[x2][y2] - v[x1 - 1][y2] - v[x2][y1 - 1] + v[x1 - 1][y1 - 1];
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

	public void run() {
		try {
			int k, n;
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
			StringTokenizer st = new StringTokenizer(br.readLine());
			k = Integer.parseInt(st.nextToken());
			n = Integer.parseInt(st.nextToken());
			v = new int[n + 1][n + 1];
			for (int x = 0; x <= n; x++)
				v[x][0] = 0;
			int[] min_allowed_y = new int[n + 1];
			for (int x = 0; x <= n; x++)
				min_allowed_y[x] = 1;
			for (int y = 1; y <= n; y++) {
				st = new StringTokenizer(br.readLine());
				int sx = 0;
				int rowsum = 0;
				int rowsum_x1 = 1;
				Stack<Point> stack = new Stack<Point>();
				stack.push(new Point(0, y + 1));
				for (int x = 0; x <= n; x++) {
					v[x][y] = sx + v[x][y - 1];
					int a = x < n ? Integer.parseInt(st.nextToken()) : 2 * k + 1;
					sx += a;
					if (a > 2 * k) {
						min_allowed_y[x] = y + 1;
						rowsum = 0;
						rowsum_x1 = x + 2;
					} else if (a >= k) {
						printResult(x + 1, y, x + 1, y);
						return;
					} else {
						rowsum += a;
						if (rowsum >= k) {
							printResult(rowsum_x1, y, x + 1, y);
							return;
						}
					}
					int yp = min_allowed_y[x];
					int xp = x + 1;
					while (yp > stack.peek().y) {
						Point p = stack.pop();
						xp = p.x;
						if (getS(p.x, p.y, x, y) >= k) {
							printResult(p.x, p.y, x, y);
							return;
						}
					}
					if (stack.peek().y > yp)
						stack.push(new Point(xp, yp));
				}
			}
			System.out.println("NIE");
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}
}
