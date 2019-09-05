import java.util.*;

class walk {

    class triple implements Comparable<triple>{
        public int a, b, c;
        public triple(int a, int b, int c){
            this.a = a;
            this.b = b;
            this.c = c;
        }

        @Override
        public int compareTo(triple cur){
            if(this.a < cur.a)return -1;
            if(this.a > cur.a)return 1;
            if(this.b < cur.b)return -1;
            if(this.b > cur.b)return 1;
            if(this.c < cur.c)return -1;
            if(this.c > cur.c)return 1;
            return 0;
        }

        @Override
        public boolean equals(Object o){
            if (o == this) {
                return true;
            }
            if (!(o instanceof triple)) {
                return false;
            }
            triple cur = (triple) o;
            return (this.a == cur.a && this.b == cur.b && this.c == cur.c);
        }
        @Override
        public int hashCode() {
            int p = 1000000007;
            return p * p * this.a + p * this.b + this.c;
        }
    }

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


    public static final int MAXN = 600000 + 10;
    public static final long INF = 1000000000000000000L;
    public int n, m, node;
    public int[] a = new int[MAXN];
    public int[] b = new int[MAXN];
    public int[] y_map = new int[MAXN];
    public int[] X, Y, H, L, R;
    public pair[] adj = new pair[MAXN * 15];
    public int adj_size[] = new int[MAXN * 12];
    public ArrayList<Integer>[] neiL = new ArrayList[MAXN];
    public ArrayList<Integer>[] neiR = new ArrayList[MAXN];
    public long[] dis = new long[MAXN];
    public HashMap<pair, Integer> nodes = new HashMap<pair, Integer>();
    public HashMap<pair, Boolean> mrk = new HashMap<pair, Boolean>();
    public Integer[] all_y;

    public void devide(int idx){
        Arrays.fill(a, -1);
        Arrays.fill(b, -1);
        ArrayList<triple> sky = new ArrayList<triple>();
        ArrayList<pair> st = new ArrayList<pair>();
        st.add(new pair(H[idx], idx));
        for(int i = idx - 1; i >= 0; i--){
            if(H[i] > st.get(st.size() - 1).a)
                st.add(new pair(H[i], i));
            for(int j = 0; j < neiL[i].size(); j++){
                int cur = neiL[i].get(j);
                if(R[cur] > idx){
                    int pos = -1 * Collections.binarySearch(st, new pair(Y[cur], -1)) - 1;
                    a[cur] = (int)st.get(pos).b;
                }
            }
        }
        st.clear();
        st.add(new pair(H[idx], idx));
        for(int i = idx + 1; i < n; i++){
            if(H[i] > st.get(st.size() - 1).a)
                st.add(new pair(H[i], i));
            for(int j = 0; j < neiR[i].size(); j++){
                int cur = neiR[i].get(j);
                if(L[cur] < idx){
                    int pos = -1 * Collections.binarySearch(st, new pair(Y[cur], -1)) - 1;
                    b[cur] = (int)st.get(pos).b;
                }
            }
        }
        for(int i = 0; i < m; i++){
            if(a[i] != -1){
                if(a[i] != L[i])
                    sky.add(new triple(L[i], a[i], Y[i]));
                if(a[i] != b[i])
                    sky.add(new triple(a[i], b[i], Y[i]));
                if(b[i] != R[i])
                    sky.add(new triple(b[i], R[i], Y[i]));
            }
            else
                sky.add(new triple(L[i], R[i], Y[i]));
        }
        for(int i = 0; i < n; i++){
            neiL[i].clear();
            neiR[i].clear();
        }
        m = sky.size();
        L = new int[m];
        R = new int[m];
        Y = new int[m];
        for(int i = 0; i < m; i++){
            L[i] = sky.get(i).a;
            R[i] = sky.get(i).b;
            Y[i] = sky.get(i).c;
            neiL[L[i]].add(i);
            neiR[R[i]].add(i);
        }
    }

    public long dijkstra(int source, int sink){
        TreeSet<pair> S = new TreeSet<pair>();
        for(int i = 0; i <= node; i++)
            dis[i] = INF;
        dis[source] = 0;
        S.add(new pair(0, source));
        while(S.size() > 0){
            pair cur = S.first();
            long dist = cur.a;
            int v = (int)cur.b;
            S.remove(cur);
            for(int i = v * 12; i < v * 12 + adj_size[v]; i++){
                int u = (int)adj[i].a;
                long w = adj[i].b;
                if(dist + w < dis[u]){
                    S.remove(new pair(dis[u], u));
                    dis[u] = dist + w;
                    S.add(new pair(dis[u], u));
                }
            }
        }
        if(dis[sink] == INF)
            return -1;
        return dis[sink];
    }

    public int add_map(int x, int y){
        if(nodes.get(new pair(x, y)) == null)
            nodes.put(new pair(x, y), ++node);
        return nodes.get(new pair(x, y));
    }

    public void add_edge(int x1, int y1, int x2, int y2){
        int u = add_map(x1, y1);
        int v = add_map(x2, y2);
        if(x1 == x2){
            adj[12 * u + adj_size[u]++] = new pair(v, Math.abs(y2 - y1));
            adj[12 * v + adj_size[v]++] = new pair(u, Math.abs(y2 - y1));
        }
        else{
            adj[12 * u + adj_size[u]++] = new pair(v, Math.abs(x2 - x1));
            adj[12 * v + adj_size[v]++] = new pair(u, Math.abs(x2 - x1));
        }
    }

    public void build_graph(){
        TreeSet<Integer> line = new TreeSet<Integer>();
        line.add(0);
        ArrayList<Integer> set_res = new ArrayList<Integer>();
        Arrays.fill(y_map, -1);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < neiL[i].size(); j++){
                int cur = neiL[i].get(j);
                line.add(-Y[cur]);
            }
            for(int j = 0; j < neiL[i].size(); j++){
                int cur = neiL[i].get(j);
                int y2 = Y[cur];
                int y1 = -1 * line.higher(-y2);
                int y2_id = Arrays.binarySearch(all_y, y2) + 1;
                int y1_id = Arrays.binarySearch(all_y, y1) + 1;
                set_res.add(y1_id);
                set_res.add(y2_id);
                add_edge(X[i], y1, X[i], y2);
                if(y_map[y1_id] != -1 && y1 != 0)
                    add_edge(X[i], y1, y_map[y1_id], y1);
            }
            for(int j = 0; j < neiR[i].size(); j++){
                int cur = neiR[i].get(j);
                int y2 = Y[cur];
                int y1 = -1 * line.higher(-y2);
                int y2_id = Arrays.binarySearch(all_y, y2) + 1;
                int y1_id = Arrays.binarySearch(all_y, y1) + 1;
                set_res.add(y1_id);
                set_res.add(y2_id);
                add_edge(X[i], y1, X[i], y2);
                add_edge(X[i], y2, y_map[y2_id], y2);
                if(y_map[y1_id] != -1 && y1 != 0)
                    add_edge(X[i], y1, y_map[y1_id], y1);
            }
            for(int j = 0; j < set_res.size(); j++)
                y_map[set_res.get(j)] = X[i];
            set_res.clear();
            for(int j = 0; j < neiR[i].size(); j++){
                int cur = neiR[i].get(j);
                int y2 = Arrays.binarySearch(all_y, Y[cur]) + 1;
                y_map[y2] = -1;
                line.remove(-Y[cur]);
            }
            for(int j = 0; j < neiL[i].size(); j++){
                int cur = neiL[i].get(j);
                int y2 = Arrays.binarySearch(all_y, Y[cur]) + 1;
                y_map[y2] = X[i];
                line.add(-Y[cur]);
            }
        }
    }

    public void init(){
        ArrayList<triple> tmp = new ArrayList<triple>();
        ArrayList<triple> nw = new ArrayList<triple>();
        for(int i = 0; i < MAXN; i++){
            neiL[i] = new ArrayList<Integer>();
            neiR[i] = new ArrayList<Integer>();
        }
        for(int i = 0; i < m; i++) tmp.add(new triple(Y[i], L[i], R[i]));
        Collections.sort(tmp);
        for(int i = 0; i < m; i++){
            if(tmp.get(i).b == tmp.get(i).c)continue;
            int j = i;
            int hei = tmp.get(i).a;
            int lo = tmp.get(i).b;
            int hi = tmp.get(i).c;
            while(j < m && tmp.get(j).a == hei && tmp.get(j).b <= hi && tmp.get(j).b >= lo){
                hi = Math.max(hi, tmp.get(j).c);
                j++;
            }
            nw.add(new triple(hei, lo, hi));
            i = j - 1;
        }
        m = nw.size();
        for(int i = 0; i < m; i++){
            L[i] = nw.get(i).b;
            R[i] = nw.get(i).c;
            Y[i] = nw.get(i).a;
            neiL[L[i]].add(i);
            neiR[R[i]].add(i);
        }
    }

    public long min_distance(int[] XX, int[] HH, int[] LL, int[] RR, int[] YY, int S, int G) {
        X = XX; H = HH; L = LL; R = RR; Y = YY;
        n = X.length;
        m = L.length;
        all_y = new Integer[m + 1];
        all_y[0] = 0;
        for(int i = 0; i < m; i++) all_y[i + 1] = Y[i];
        Set<Integer> uniq = new HashSet<>(Arrays.asList(all_y));
        all_y = uniq.toArray(new Integer[uniq.size()]);
        Arrays.sort(all_y);
        init();
        devide(S);
        devide(G);
        build_graph();
        return dijkstra(add_map(X[S], 0), add_map(X[G], 0));
    }
}
