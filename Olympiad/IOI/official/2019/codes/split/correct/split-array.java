import java.util.ArrayList;
import java.util.Collections;

//IOI 2019
//Split
//Current Version: 31 May 2019
//Mahdi Safarnejad Boroujeni

class Pair implements Comparable<Pair> {
  final int first, second;
  Pair(int first, int second) {
  	this.first=first;
  	this.second=second;
  }
  @Override
	public int compareTo(Pair b) {
		if (first!=b.first)
			return first - b.first;
		return second - b.second;
	}
}

public class split {
	int n;
	int[][] a;
	int[][] b;
	int[] result, mark, size, startingtime, mintime;
	int[] deg, ahead;
	int counter = 1;
	boolean finishedPhase1 = false;

	int dfs2(int v, int goal, int comp, boolean ignore_st) {
		int sum=1;
		mark[v]=2;
		result[v]=comp;
		goal -= 1;
		for (int i = 0; i < a[v].length; i++)
			if (goal > 0 && mark[a[v][i]] < 2 && (ignore_st || (startingtime[a[v][i]] > startingtime[v]))) {
				int thisSize = dfs2(a[v][i], goal, comp, ignore_st);
				sum += thisSize;
				goal -= thisSize;
			}
		return sum;
	}
	void dfs(int v, int par) {
		mark[v]=1;
		size[v]=1;
		startingtime[v] = counter++;
		mintime[v] = startingtime[v];
		int removablesSum=0;
		for (int i = 0; i < a[v].length; i++)
			if (mark[a[v][i]] == 0){
				dfs(a[v][i], v);
				if (finishedPhase1)
					return;
				size[v]+=size[a[v][i]];
				mintime[v] = Math.min(mintime[v], mintime[a[v][i]]);
				if (mintime[a[v][i]] < startingtime[v])
					removablesSum += size[a[v][i]];
			} else if (a[v][i]!=par) {
				mintime[v] = Math.min(mintime[v], mintime[a[v][i]]);				
			}
		if (size[v] >= b[0][0]) {
			finishedPhase1 = true;
			if (n - size[v] + removablesSum < b[0][0])
				return; //No Solution
			int element = 0;
			if (n - size[v] + removablesSum < b[1][0])
				element = 1;
			result[v] = b[element][1];
			mark[v]=2;
			int goal = b[element][0] - 1;
			for (int i = 0; i < a[v].length; i++) {
				if (mark[a[v][i]] < 2 && goal > 0 && mintime[a[v][i]] >= startingtime[v] && startingtime[a[v][i]] > startingtime[v])
					goal -= dfs2(a[v][i], goal, b[element][1], false);
			}
			for (int i = 0; i < a[v].length; i++) {
				if (mark[a[v][i]] < 2 && goal > 0 && mintime[a[v][i]] < startingtime[v] && startingtime[a[v][i]] > startingtime[v])
					goal -= dfs2(a[v][i], goal, b[element][1], false);
			}
			dfs2(0, b[1-element][0], b[1-element][1], true);
			for (int i = 0; i < n; i++)
				if (result[i]==0)
					result[i]=b[2][1];
		}
	}

	public int[] find_split(int n, int a_, int b_, int c_, int[] p, int[] q) {
		this.n = n;
		result = new int[n];
		mark = new int[n];
		size = new int[n];
		startingtime = new int[n];
		mintime = new int[n];
		deg = new int[n];
		ArrayList<Pair> bAList;
		bAList = new ArrayList<Pair>();
		bAList.add(new Pair(a_, 1));
		bAList.add(new Pair(b_, 2));
		bAList.add(new Pair(c_, 3));
		Collections.sort(bAList);
		b = new int[3][2];
		for (int i = 0; i < 3; ++i) {
			b[i][0] = bAList.get(i).first;
			b[i][1] = bAList.get(i).second;
		}
		for (int i = 0; i < p.length; i++) {
			deg[p[i]]++;
			deg[q[i]]++;
		}
		a = new int[n][];
		for (int i = 0; i < n; i++)
			a[i] = new int[deg[i]];
		ahead = new int[n];
		for (int i = 0; i < p.length; i++) {
			a[p[i]][ ahead[p[i]] ] = q[i];
			ahead[p[i]]++;
			a[q[i]][ ahead[q[i]] ] = p[i];
			ahead[q[i]]++;
		}
		dfs(0, -1);
		return result;
	}
//	public static void main(String[] args) {
//		split test = new split();
//		int[] p = {0, 0, 0};
//		int[] q = {1, 2, 3};
//		int[] result = test.do_split(4, 2, 1, 1, p, q);
//		for (int i = 0; i < 4; i++)
//			System.out.print(result[i]+" ");
//		System.out.println();
//	}
}
