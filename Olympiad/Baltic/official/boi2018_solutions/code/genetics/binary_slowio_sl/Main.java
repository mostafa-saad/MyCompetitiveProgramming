import java.io.*;
import java.util.*;

public class Main {
	public static void main(String[] args) throws Exception {
		Scanner r = new Scanner(System.in);
		String[] line = r.nextLine().split(" ");
		int N = Integer.parseInt(line[0]);
		int M = Integer.parseInt(line[1]);
		int K = Integer.parseInt(line[2]);
		String[] mat = new String[N];
		boolean[] iscandidate = new boolean[N];
		boolean[] included = new boolean[N];
		int[] count = new int[M];
		for (int i = 0; i < N; i++) {
			mat[i] = r.nextLine();
			iscandidate[i] = true;
		}

		int ncand = N;
		while (ncand > 1) {
			int nincluded = 0;
			for (int i = 0; i < N; i++) {
				included[i] = Math.random() < 0.5;
				nincluded += included[i] ? 1 : 0;
			}
			for (int i = 0; i < M; i++) {
				count[i] = 0;
			}

			for (int i = 0; i < N; i++) {
				if (!included[i]) continue;
				for (int j = 0; j < M; j++) {
					count[j] += (mat[i].charAt(j) == 'A' ? 1 : 0);
				}
			}
			for (int i = 0; i < N; i++) {
				if (!iscandidate[i]) continue;
				int sumdif = 0;
				for (int j = 0; j < M; j++)
					sumdif += (mat[i].charAt(j) == 'A' ? nincluded - count[j] : count[j]);
				int expectedsumdif = nincluded * K - (included[i] ? K : 0);
				if (sumdif != expectedsumdif) {
					iscandidate[i] = false;
					ncand--;
				}
			}
		}
		for (int i = 0; i < N; i++) {
			if (iscandidate[i]) {
				System.out.println(i+1);
				return;
			}
		}
		System.exit(1);
	}
}
