/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clo10.java                                                *
 *   Autor:    Adam Iwanicki                                             *
 *   Opis:     Alternatywne rozwiazanie wzorcowe. Zachlannie przegladamy *
 *             wierzcholki wkolejnosci nierosnacych stopni i             *
 *             przyporzadkowujemy im dowolne krawedzie. Zlozonosc O(n+m) *
 *                                                                       *
 *************************************************************************/
import java.io.*;
import java.util.*;

public class clo10 implements Runnable {

  clo10() {
  }

  public static void main(String[] args) {
    new Thread(new clo10()).start();
  }

  public static final int MAXN = 100000;
  public static final int MAXM = 200000;


  private class Edge {
    public int a;
    public int b;
    boolean isUsed;
  };

  Edge[] edges = new Edge[MAXM];

  int[] degrees = new int[MAXM];

  private class Vertex {
    public int degree;
    public int prev;
    public int next;
    public int adj;
    public int e;
  }

  Vertex[] vertices = new Vertex[MAXN];

  private class VertEdge {
    public int edge;
    public int next;
  };

  VertEdge[] vertEdges = new VertEdge[MAXM*2];
  int vertEdgesNum = 0;

  void dodaj(int degree, int v)
  {
    int prev = degrees[degree];
    vertices[v].next = prev;
    vertices[v].prev = -1;
    if( -1 != prev ) {
      vertices[prev].prev = v;
    }
    degrees[degree] = v;
  }

  void usun(int v)
  {
    int prev = vertices[v].prev;
    int next = vertices[v].next;
    if( -1 != prev ) vertices[prev].next = next;
    if( -1 != next ) vertices[next].prev = prev;
  }

  int findFree(int v)
  {
    int akt = vertices[v].e;
    while( -1 != akt ) {
      if( edges[vertEdges[akt].edge].isUsed ) {
        akt = vertEdges[akt].next;
      } else {
        return vertEdges[akt].edge;
      }
    }
    assert( "" != "Powinnismy byli znalezc wolna krawedz" );
    return -1;
  }

  public void run()
  {
    try {
      int n,m;
      BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
      String line = br.readLine();
      StringTokenizer st = new StringTokenizer(line);
      n = Integer.parseInt(st.nextToken());
      m = Integer.parseInt(st.nextToken());

      for(int i=0; i<n; ++i) {
        vertices[i] = new Vertex();
        vertices[i].e = -1;
        vertices[i].adj = -1;
      }
      for(int i=0; i<m; ++i) {
        int a, b;
        line = br.readLine();
        st = new StringTokenizer(line);
        a = Integer.parseInt(st.nextToken());
        b = Integer.parseInt(st.nextToken());
        --a; --b;

        edges[i] = new Edge();
        edges[i].a = a;
        edges[i].b = b;
        ++vertices[a].degree;
        ++vertices[b].degree;

        vertEdges[vertEdgesNum] = new VertEdge();
        VertEdge ve = vertEdges[vertEdgesNum];
        ve.next = vertices[a].e;
        ve.edge = i;
        vertices[a].e = vertEdgesNum;
        ++vertEdgesNum;

        vertEdges[vertEdgesNum] = new VertEdge();
        ve = vertEdges[vertEdgesNum];
        ve.next = vertices[b].e;
        ve.edge = i;
        vertices[b].e = vertEdgesNum;
        ++vertEdgesNum;
      }
      for(int i=0; i<m; ++i) {
        degrees[i] = -1;
      }
      int mindeg = m;
      boolean isPossibe = true;
      for(int i=0; i<n; ++i) {
        int degree = vertices[i].degree;
        if( degree < mindeg ) mindeg = degree;
        dodaj(degree,i);
      }
      for(int i=0; i<n; ++i) {
        if( -1 != degrees[0] ) {
          isPossibe = false;
          break;
        }
        assert(mindeg < n);
        int v = degrees[mindeg];
        degrees[mindeg] = vertices[degrees[mindeg]].next;
        usun(v);
        int k=findFree(v);
        assert(k >= 0);
        int adj = edges[k].a == v ? edges[k].b : edges[k].a;
        vertices[v].adj = adj;
        if( -1 == vertices[adj].adj ) {
          usun(adj);
          if (degrees[vertices[adj].degree] == adj) {
            degrees[vertices[adj].degree] = vertices[adj].next;
          }
          if( --vertices[adj].degree < mindeg ) mindeg = vertices[adj].degree;
          dodaj(vertices[adj].degree, adj);
        }
        edges[k].isUsed = true;
        while (mindeg < n && -1 == degrees[mindeg]) {
          ++mindeg;
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
