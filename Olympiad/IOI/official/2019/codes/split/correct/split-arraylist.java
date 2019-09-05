import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

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
	List<Integer>[] a;
	ArrayList<Pair> b;
	int[] result, mark, size, startingtime, mintime;
	int counter = 1;
	boolean finishedPhase1 = false;

	int dfs2(int v, int goal, int comp, boolean ignore_st) {
		int sum=1;
		mark[v]=2;
		result[v]=comp;
		goal -= 1;
		for (int i = 0; i < a[v].size(); i++)
			if (goal > 0 && mark[a[v].get(i)] < 2 && (ignore_st || (startingtime[a[v].get(i)] > startingtime[v]))) {
				int thisSize = dfs2(a[v].get(i), goal, comp, ignore_st);
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
		for (int i = 0; i < a[v].size(); i++)
			if (mark[a[v].get(i)] == 0){
				dfs(a[v].get(i), v);
				if (finishedPhase1)
					return;
				size[v]+=size[a[v].get(i)];
				mintime[v] = Math.min(mintime[v], mintime[a[v].get(i)]);
				if (mintime[a[v].get(i)] < startingtime[v])
					removablesSum += size[a[v].get(i)];
			} else if (a[v].get(i)!=par) {
				mintime[v] = Math.min(mintime[v], mintime[a[v].get(i)]);
            }
		if (size[v] >= b.get(0).first) {
			finishedPhase1 = true;
			if (n - size[v] + removablesSum < b.get(0).first)
				return; //No Solution
			int element = 0;
			if (n - size[v] + removablesSum < b.get(1).first)
				element = 1;
			result[v] = b.get(element).second;
			mark[v]=2;
			int goal = b.get(element).first - 1;
			for (int i = 0; i < a[v].size(); i++) {
				if (mark[a[v].get(i)] < 2 && goal > 0 && mintime[a[v].get(i)] >= startingtime[v] && startingtime[a[v].get(i)] > startingtime[v])
					goal -= dfs2(a[v].get(i), goal, b.get(element).second, false);
			}
			for (int i = 0; i < a[v].size(); i++) {
				if (mark[a[v].get(i)] < 2 && goal > 0 && mintime[a[v].get(i)] < startingtime[v] && startingtime[a[v].get(i)] > startingtime[v])
					goal -= dfs2(a[v].get(i), goal, b.get(element).second, false);
			}
			dfs2(0, b.get(1-element).first, b.get(1-element).second, true);
			for (int i = 0; i < n; i++)
				if (result[i]==0)
					result[i]=b.get(2).second;
		}
	}

	public int[] find_split(int n, int a_, int b_, int c_, int[] p, int[] q) {
		this.n = n;
		result = new int[n];
		mark = new int[n];
		size = new int[n];
		startingtime = new int[n];
		mintime = new int[n];
		a = new ArrayList[n];
		for (int i = 0; i < n; i++)
			a[i] = new ArrayList<Integer>();
		b = new ArrayList<Pair>();
		b.add(new Pair(a_, 1));
		b.add(new Pair(b_, 2));
		b.add(new Pair(c_, 3));
		Collections.sort(b);
		for (int i = 0; i < p.length; i++) {
			a[p[i]].add(q[i]);
			a[q[i]].add(p[i]);
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
