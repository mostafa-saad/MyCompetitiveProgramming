/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clo11.java                                                *
 *   Autor:    Adam Iwanicki                                             *
 *   Opis:     Rozwiazanie wzorcowe, przechodzace dwa razy przy uzyciu   *
 *             DFSa. Zlozonosc O(n+m). Zostalo ono specjalnie zapisane   *
 *             przez mozliwosc przekroczenia glebokosci stosu            *
 *                                                                       *
 *************************************************************************/
import java.io.*;
import java.util.*;

public class clo11 implements Runnable {

  clo11() {
  }

  public static void main(String[] args) {
    new Thread(new clo11()).start();
  }

  public static final int MAXN = 100000;
  public static final int MAXM = 200000;

  private class Vertex {
    private boolean visited;
    private int adj;
    private int prev;
  };

  Vertex[] vertices = new Vertex[MAXN];

  @SuppressWarnings("unchecked")
  ArrayList<Integer>[] vertEdges = new ArrayList[MAXN];

  void solve2(int v, int adj) {
    vertices[v].adj = adj;
    vertices[v].visited = true;
    for (int i=0; i < vertEdges[v].size(); ++i) {
      int edge = vertEdges[v].get(i);
      if (edge != adj ) {
        if (0 > vertices[edge].adj) {
          solve2(edge,v);
        }
      }
    }
  }

  boolean solve(int v) {
    vertices[v].visited = true;
    vertices[v].adj = -2;
    int prev = vertices[v].prev;
    for (int i=0; i < vertEdges[v].size(); ++i) {
      int adj = vertEdges[v].get(i);
      if (adj != prev) {
        if (-1 == vertices[adj].adj) {
          vertices[adj].prev = v;
          if (solve(adj)) {
            return true;
          }
        } else {
          solve2(adj,v);
          return true;
        }
      }
    }
    return false;
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
        if (!vertices[i].visited) {
          solve(i);
        }
      }
      boolean isPossibe = true;
      for (int i=0; i<n; ++i) {
        if (0 > vertices[i].adj) {
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
