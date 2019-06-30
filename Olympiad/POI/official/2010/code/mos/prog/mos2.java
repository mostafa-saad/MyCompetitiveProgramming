/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Mosty (MOS)                                   *
 *   Plik:                 mos2.java                                     *
 *   Autor:                Tomasz Kulczynski                             *
 *   Opis:                 Rozwiazanie wzorcowe.                         *
 *   Zlozonosc czasowa:    O((n + m) * m * log MAX_WIATR)                *
 *   Zlozonosc pamieciowa: O(n + m)                                      *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;

public class mos2 implements Runnable 
{
    private static final int M = 2001;
    private static final int N = 1001;
    private static final int MAX_WIATR = 1000;

    int n,m;
    int[] a=new int[M];
    int[] b=new int[M];
    int[] l=new int[M];
    int[] p=new int[M];
    int[] stopien=new int[N];
    boolean[] bylem=new boolean[N+M];

    class kraw
    {
        int x,r,c;
    };

    Vector<kraw>[] v=(Vector<kraw>[])(new Vector[N+M]);

    int sciezka(int x,int kon) //znajduje jedna sciezke powiekszajaca przeplyw
    {                           //i powieksza wzdluz niej
        if(x==kon) return 1;
        if(bylem[x]) return 0;
        bylem[x]=true;
  //      System.out.println("    jestem w "+x+" (kon="+kon+") size="+v[x].size());
        for(int i=0;i<v[x].size();i++) 
        {
    //    	System.out.println(v[x].get(i).x+" "+v[x].get(i).c);
            int y=v[x].get(i).x;
            if((v[x].get(i).c!=0) && (sciezka(y,kon)!=0)) 
            {
                v[x].get(i).c--;
                v[y].get(v[x].get(i).r).c++;
                return 1;
            }
        }
        return 0;
    }

    int maxflow(int pocz,int kon)
    {
        int flow=0;
        while(true)
        {
            for(int i=0;i<=n+m+1;i++) 
                bylem[i]=false;
            if(0==sciezka(pocz,kon)) 
                break;
            flow++;
        }
        return flow;
    }

    void add_edge( int a, int b, int p ) //dodaje krawedz z a do b o przepustowosci p
    {
        kraw k=new kraw();
        k.x=b;
        k.r=v[b].size();
        k.c=p;
        v[a].add(k);

        k=new kraw();
        k.x=a;
        k.r=v[a].size()-1;
        k.c=0;
        v[b].add(k);
    }

    void tworz(int x) //stworzenie grafu dwudzielnego, w ktorym i (1<=i<=n)
                      // jest polaczone z n+j (1<=j<=m), gdy z wierzcholka
                      // i wejsciowego grafu mozna wyjsc krawedzia j
                      // nie przekraczajac kosztu x
                      // 0 jest super-zrodlem a n+m+1 super-ujsciem
    {
        for(int i=0;i<=n+m+1;i++) 
            v[i]=new Vector();
        for(int i=1;i<=n;i++) 
            add_edge( 0, i, stopien[i]/2 );
        for(int i=1;i<=m;i++)
        {
            if(l[i]<=x) 
                add_edge( a[i] , n+i, 1 );
            if(p[i]<=x)
                add_edge( b[i] , n+i, 1 );
            add_edge( n+i, n+m+1, 1 );
        }
  //      for(int i=0;i<=n+m+1;i++) System.out.println(" "+v[i].size());
    }

    Vector<Integer>[] kr=new Vector[N];

    void euler() //znajduje i wypisuje cykl eulera w grafie ktory jest
    {            //zapisany w listach krawedzi z kazdego wierzcholka kr[]
        if(kr[1].isEmpty()) return;
        int g=1;
        Vector<Integer> l=new Vector();
                
        int u=1,e;
        while(!kr[u].isEmpty())
        {
        	e=kr[u].lastElement();
            l.add(e);
            kr[u].remove(kr[u].size()-1);
            u=a[e]+b[e]-u;
        }

        int p=0,q;
        while(p<l.size())
        {
        	q=p;
            if(!kr[g].isEmpty())
            {
                u=g;
                while(!kr[u].isEmpty())
                {
                    l.add(q++,e=kr[u].lastElement());
                    kr[u].remove(kr[u].size()-1);
                    u=a[e]+b[e]-u;
                }
            }
            g=a[l.get(p)]+b[l.get(p)]-g;
            p++;
        }
        for(Integer r:l) 
        	System.out.print(r+" ");
        System.out.println();
    }

    public static void main(String[] args)
    {
        new Thread(new mos2()).start();
    }

    public void run()
    {
        Scanner sc = new Scanner( System.in );
        n=sc.nextInt();
        m=sc.nextInt();
        for(int i=1;i<=m;i++) 
        {
        	a[i]=sc.nextInt();
        	b[i]=sc.nextInt();
        	l[i]=sc.nextInt();
        	p[i]=sc.nextInt();
            stopien[a[i]]++;
            stopien[b[i]]++;
        }
    //    for(int i=1;i<=n;i++) System.out.print(stopien[i]+ " ");
      //  System.out.println();
        int L=1,P=MAX_WIATR+1,S;
        while(L<P)  //wyszukiwanie binarne wyniku
        {
            S=(L+P)/2;
            tworz(S);
       //     System.out.println(maxflow(0,n+m+1));
            if(maxflow(0,n+m+1)==m) P=S;
            else L=S+1;
        }
        if(L>MAX_WIATR) System.out.println("NIE");
        else
        {
        	System.out.println(L);
            tworz(L);
            maxflow(0,n+m+1);
            for(int i=1;i<=n;i++) kr[i]=new Vector();
            for(int i=1;i<=m;i++)
                for(int j=0;j<v[n+i].size();j++)
                    if(v[n+i].get(j).c!=0) kr[v[n+i].get(j).x].add(i);
            euler();
        }
    }
}
