import java.util.*;
import java.io.*;
public class mm19 {
    void solve(BufferedReader in) throws Exception {
        int[] xx = toInts(in.readLine());
        int N =xx[0], M=xx[1];
        FlowNetwork net = new FlowNetwork(N+1);
        int id = M;
        for(int i = 1; i<N+1; i++) {
            net.add_edge(i, i-1, 2, id++);
        }
        for(int i = 0; i<M; i++) {
            xx = toInts(in.readLine());
            net.add_edge(xx[0] - 1, xx[1], 1, i);
        }
        int v = net.max_flow(0, N);
        if(v!=2) {
            System.out.println("impossible");
            return;
        }
        int[] MS = new int[M];
        for(Edge e: net.path) {
            if(e.id2 >= 0 && e.id2 < M) MS[e.id2] = 1;
        }
        StringBuilder sb = new StringBuilder();
        for(int i : MS) sb.append(i);
        System.out.println(sb);
    }
    int toInt(String s) {return Integer.parseInt(s);}
    int[] toInts(String s) {
        String[] a = s.split(" ");
        int[] o = new int[a.length];
        for(int i = 0; i<a.length; i++) o[i] = toInt(a[i]);
        return o;
    }
    void e(Object o) {
        System.err.println(o);
    }
    public static void main(String[] args) throws Exception{
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        (new mm19()).solve(in);
    }
}
class Node {
    LinkedList<Edge> edges = new LinkedList<>();
    int id;
    boolean visited = false;
    Edge last = null;
    public Node(int id) {
        this.id = id;
    }
    public void append(Edge e) {
        edges.add(e);
    }
}
class Edge {
    Node source, sink;
    int cap;
    int id, id2;
    Edge redge;
    public Edge(Node u, Node v, int w, int id, int id2){
        source = u; sink = v;
        cap = w;
        this.id = id;
        this.id2 = id2;
    }
    public Edge(Node u, Node v, int w, int id){
        source = u; sink = v;
        cap = w;
        this.id = id;
        id2 = -1;
    }
}
class FlowNetwork {
    Node[] adj;
    int edgec = 0;
    HashMap<Integer,Integer> flow = new HashMap<>();
    ArrayList<Edge> real = new ArrayList<Edge>();
    public FlowNetwork(int size) {
        adj = new Node[size];
        for(int i = 0; i<size; i++) {
            adj[i] = new Node(i);
        }
    }
    void add_edge(int u, int v, int w, int id){
        Node Nu = adj[u], Nv = adj[v];
        Edge edge = new Edge(Nu, Nv, w, edgec++, id);
        Edge redge = new Edge(Nv, Nu, 0, edgec++);
        edge.redge = redge;
        redge.redge = edge;
        real.add(edge);
        adj[u].append(edge);
        adj[v].append(redge);
        flow.put(edge.id, 0);
        flow.put(redge.id, 0);
    }

    void reset() {
        for(int i = 0; i<adj.length; i++) {
            adj[i].visited = false; adj[i].last = null;
        }
    }

    boolean real_path(Node s, Node t) {
        LinkedList<Node> active = new LinkedList<>();
        active.add(s);
        s.visited = true;
        while(!active.isEmpty() && !t.visited) {
            Node now = active.pollFirst();
            for(Edge e: now.edges) {
                if(flow.get(e.id) != 0 && e.id2 >= 0 && !e.sink.visited) {
                    e.sink.visited = true;
                    e.sink.last = e;
                    active.addLast(e.sink);
                }
            }
        }
        return t.visited;
    }

    LinkedList<Edge> find_path(Node s, Node t, 
            List<Edge> path){
        reset();
        LinkedList<Node> active = new LinkedList<>();
        active.add(s);
        while(!active.isEmpty() && !t.visited) {
            Node now = active.pollFirst();
            for(Edge e: now.edges) {
                int residual = e.cap - flow.get(e.id);
                if(residual>0 && !e.sink.visited) {
                    e.sink.visited = true;
                    e.sink.last = e;
                    active.addLast(e.sink);
                }
            }
        }
        if(t.visited) {
            LinkedList<Edge> res = new LinkedList<>();
            Node curr = t;
            while(curr != s) {
                res.addFirst(curr.last);
                curr = curr.last.source;
            }
            return res;
        } else return null;
    }
    LinkedList<Edge> path;
    int max_flow(int s, int t) {
        Node source = adj[s];
        Node sink = adj[t];
        path = new LinkedList<Edge>();
        int sum = 0;
        while (path != null && sum < 2) {
            path = find_path(source, sink, 
                    new LinkedList<Edge>());
            if(path == null) break;
            int min = Integer.MAX_VALUE;
            for(Edge e : path) {
                min = Math.min(min, e.cap - flow.get(e.id));
            }
            for (Edge e : path) {
                flow.put(e.id, flow.get(e.id) + min);
                Edge r = e.redge;
                flow.put(r.id, flow.get(r.id) - min);
            }
            sum += min;

        }
        if(sum == 2) {
            reset();
            if(real_path(source, sink)) {
                LinkedList<Edge> res = new LinkedList<>();
                Node curr = sink;
                while(curr != source) {
                    res.addFirst(curr.last);
                    curr = curr.last.source;
                }
                path=res;
                return sum;

            }
            System.exit(1);
        }
        return sum;
    }
}
