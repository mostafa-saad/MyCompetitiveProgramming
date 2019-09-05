import java.util.*;

class walk {

	public static final int MAXN = 200 * 1000 + 10;
	public static final int MAXM = 200 * 1000 + 10;
	public static final int MAXRM = 5 * MAXM;
	public static final int MAXV = 2 * 2 * MAXRM;
	public static final long INF = 1000l * 1000 * 1000 * 1000 * 1000 * 1000;

	class pair implements Comparable<pair>{
		public long a, b;
		public pair(long a, long b){
			this.a = a;
			this.b = b;
		}

		@Override
			public int compareTo(pair cur){
				if(this.a < cur.a)return -1;
				if(this.a > cur.a)return 1;
				if(this.b < cur.b)return -1;
				if(this.b > cur.b)return 1;
				return 0;
			}
		@Override
			public boolean equals(Object o){
				if (o == this) {
					return true;
				}
				if (!(o instanceof pair)) {
					return false;
				}
				pair cur = (pair) o;
				return (this.a == cur.a && this.b == cur.b);
			}
		@Override
			public int hashCode() {
				int p = 1000000007;
				return p * (int)this.a + (int)this.b;
			}
	}

	public long[] dist = new long[MAXV];
	public int vcnt = 0;
	public ArrayList<ArrayList<pair>> edges = new ArrayList<>();
 	public TreeSet<pair> dij = new TreeSet<>();
	public int[] last_x = new int[MAXRM];
	public int[] last_vertex = new int[MAXRM];
	public int[] last_height = new int[MAXN];
	public int[] first_height = new int[MAXN];
	public ArrayList<ArrayList<pair>> adds = new ArrayList<>();
	public ArrayList<ArrayList<pair>> removes = new ArrayList<>();
	public TreeSet<pair> walks = new TreeSet<pair>();

	long dijkstra(int start, int dest)
	{
		for (int i = 0; i < vcnt; i++)
			dist[i] = INF;
		dist[start] = 0;
		dij.add(new pair(dist[start], start));
		while (!dij.isEmpty())
		{
			int v =	(int)dij.pollFirst().b;
			if (v == dest)
				return dist[v];
			for (int i = 0; i < edges.get(v).size(); i++)
			{
				int u = (int)edges.get(v).get(i).a;
				int w = (int)edges.get(v).get(i).b;
				if (dist[u] > dist[v] + w)
				{
					dij.remove(new pair(dist[u], u));
					dist[u] = dist[v] + w;
					dij.add(new pair(dist[u], u));
				}
			}
		}
		return -1;
	}

	void add_edge(int u, int v, int w)
	{
		edges.get(u).add(new pair(v, w));
		edges.get(v).add(new pair(u, w));
	}

	int make_vertex(int walk, int x)
	{
		if (last_x[walk] == x)
			return last_vertex[walk];
		int cur = vcnt++;
		edges.add(new ArrayList<>());
		if (last_vertex[walk] != -1)
			add_edge(last_vertex[walk], cur, x - last_x[walk]);
		last_x[walk] = x;
		last_vertex[walk] = cur;
		return cur;
	}

	void break_segments(ArrayList<Integer> l, ArrayList<Integer> r, ArrayList<Integer> y, int s, int[] h)
	{
		TreeSet<Integer> ts = new TreeSet<Integer>();
		for (int i = 0; i < h.length; i++)
			ts.add(h[i]);
		List<Integer> heights = new ArrayList<Integer>();
		for (Integer x: ts)
			heights.add(x);
		for (int i = 0; i < heights.size(); i++)
		{
			last_height[i] = -1;
			first_height[i] = h.length + 1;
		}
		for (int i = 0; i < h.length; i++)
		{
			int idx = Collections.binarySearch(heights, h[i]);
			if (i <= s)
				last_height[idx] = Math.max(last_height[idx], i);
			if (i >= s)
				first_height[idx] = Math.min(first_height[idx], i);
		}
		for (int i = heights.size() - 2; i >= 0; i--)
		{
			last_height[i] = Math.max(last_height[i], last_height[i + 1]);
			first_height[i] = Math.min(first_height[i], first_height[i + 1]);
		}
		for (int i = 0; i < l.size(); i++)
			if (l.get(i) < s && r.get(i) > s)
			{
				int idx = Collections.binarySearch(heights, y.get(i));
				if (idx < 0)
					idx = -(idx + 1);
				int x = l.get(i);
				int a = last_height[idx];
				int b = first_height[idx];
				int q = r.get(i);

				if (x < a)
				{
					r.set(i, a);
					if (a < b)
					{
						l.add(a);
						r.add(b);
						y.add(y.get(i));
					}
				}
				else
				{
					r.set(i, b);
				}
				if (q > b)
				{
					l.add(b);
					r.add(q);
					y.add(y.get(i));
				}
				else
				{
				}
			}
	}

	long min_distance(int[] x, int[] h, int[] orig_l, int[] orig_r, int[] orig_y, int s, int g)
	{
		if (s == g)
			return 0;
		int n = x.length;

		ArrayList<Integer> l = new ArrayList<Integer>();
		for (int ttt: orig_l)
			l.add(ttt);
		ArrayList<Integer> r = new ArrayList<Integer>();
		for (int ttt: orig_r)
			r.add(ttt);
		ArrayList<Integer> y = new ArrayList<Integer>();
		for (int ttt: orig_y)
			y.add(ttt);
		for (int i = 0; i < n; i++)
		{
			adds.add(new ArrayList<>());
			removes.add(new ArrayList<>());
		}
		break_segments(l, r, y, s, h);
		break_segments(l, r, y, g, h);
		int m = l.size();

		for (int i = 0; i < m; i++)
		{
			last_x[i] = last_vertex[i] = -1;
			adds.get(l.get(i)).add(new pair(y.get(i), i));
			removes.get(r.get(i)).add(new pair(y.get(i), i));
		}
		int sv = -1, gv = -1;
		long res = 0;
		walks = new TreeSet<>();
		for (int i = 0; i < n; i++)
		{
			Collections.sort(adds.get(i));
			for (int j = 0; j < adds.get(i).size(); j++)
			{
				int v = make_vertex((int)adds.get(i).get(j).b, x[i]);
				pair it = walks.lower(adds.get(i).get(j));
				if (it != null)
				{
					int u = make_vertex((int)it.b, x[i]);
					add_edge(u, v, (int)(adds.get(i).get(j).a - it.a));
				}
				walks.add(adds.get(i).get(j));
			}
			if (i == s)
			{
				if (walks.isEmpty() || walks.first().a > h[i])
					return -1;
				sv = make_vertex((int)walks.first().b, x[i]);
				res += walks.first().a;
			}
			if (i == g)
			{
				if (walks.isEmpty() || walks.first().a > h[i])
					return -1;
				gv = make_vertex((int)walks.first().b, x[i]);
				res += walks.first().a;
			}
			Collections.sort(removes.get(i));
			Collections.reverse(removes.get(i));
			for (int j = 0; j < removes.get(i).size(); j++)
			{
				int v = make_vertex((int)removes.get(i).get(j).b, x[i]);
				pair it = walks.lower(removes.get(i).get(j));
				if (it != null)
				{
					int u = make_vertex((int)it.b, x[i]);
					add_edge(u, v, (int)(removes.get(i).get(j).a - it.a));
				}
				walks.remove(removes.get(i).get(j));
			}
		}
		long dij_res = dijkstra(sv, gv);
		if(dij_res == -1)
			return -1;
		return res + dij_res;
	}
}
