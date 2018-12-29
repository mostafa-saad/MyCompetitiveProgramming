/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clo9.java                                                 *
 *   Autor:    Adam Iwanicki                                             *
 *   Opis:     Rozwiazanie wzorcowe, przechodzace dwa razy przy uzyciu   *
 *             BFSa. Zlozonosc O(n+m).                                   *
 *                                                                       *
 *************************************************************************/
import java.io.*;
import java.util.*;

public class clo9 implements Runnable {

  clo9() {
  }

  public static void main(String[] args) {
    new Thread(new clo9()).start();
  }

  public static final int MAXN = 100000;
  public static final int MAXM = 200000;

  private class Vertex {
    public boolean visited;
    public int adj;
    public int prev;
  }

  Vertex[] vertices = new Vertex[MAXN];
  @SuppressWarnings("unchecked")
  ArrayList<Integer>[] vertEdges = new ArrayList[MAXN];

  Queue<Integer> queue = new LinkedList<Integer>();

  void solve2(int v, int adj) {
    vertices[v].adj = adj;
    queue.clear();
    int rozm = vertEdges[v].size();
    for (int i = 0; i < rozm; ++i) {
      int w = vertEdges[v].get(i);
      if( w != adj ) {
        queue.add(w);
        vertices[w].adj = v;
      }
    }
    vertices[v].visited = true;
    while (!queue.isEmpty()) {
      int w = queue.remove();
      vertices[w].visited = true;
      rozm = vertEdges[w].size();
      for (int i = 0; i < rozm; ++i) {
        int pom = vertEdges[w].get(i);
        if (0 > vertices[pom].adj) {
          queue.add(pom);
          vertices[pom].adj = w;
        }
      }
    }
  }

  void solve(int v) {
    queue.clear();
    queue.add(v);
    while( !queue.isEmpty() ) {
      int w = queue.remove();
      vertices[w].visited = true;
      ArrayList<Integer> adj = vertEdges[w];
      int rozm = adj.size();
      for (int i = 0; i < rozm; ++i) {
        int akt = adj.get(i);
        if (akt != vertices[w].prev) {
          if( -1 == vertices[akt].adj ) {
            vertices[akt].adj = -2;
            queue.add(akt);
            vertices[akt].prev = w;
          } else {
            solve2(akt, w);
            return;
          }
        }
      }
    }
  }

  public void run() {
    try {
      int n,m;
      BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
      String line = br.readLine();
      StringTokenizer st = new StringTokenizer(line);
      n = Integer.parseInt(st.nextToken());
      m = Integer.parseInt(st.nextToken());

      for(int i=0; i<n; ++i) {
        vertices[i] = new Vertex();
        vertices[i].adj = -1;
        vertices[i].visited = false;
        vertices[i].prev = -1;
        vertEdges[i] = new ArrayList<Integer>();
      }
      for(int i=0; i<m; ++i) {
        int a, b;
        line = br.readLine();
        st = new StringTokenizer(line);
        a = Integer.parseInt(st.nextToken());
        b = Integer.parseInt(st.nextToken());
        --a; --b;

        vertEdges[a].add(b);
        vertEdges[b].add(a);
      }
      for(int i=0; i<n; ++i) {
        if( ! vertices[i].visited ) {
          solve(i);
        }
      }
      boolean isPossibe = true;
      for (int i=0; i<n; ++i) {
        if ( 0 > vertices[i].adj ) {
          isPossibe = false;
          break;
        }
      }
      if( isPossibe ) {
        System.out.println("TAK");
        for(int i=0; i<n; ++i) {
          System.out.println(vertices[i].adj + 1);
        }
      } else {
        System.out.println("NIE");
      }
    } catch (Exception e) {
      throw new RuntimeException(e);
    }
  }
}
