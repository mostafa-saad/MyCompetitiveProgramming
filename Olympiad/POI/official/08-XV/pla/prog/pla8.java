/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Plakatowanie (PLA)                                        *
 *   Plik:     pla8.java                                                 *
 *   Autor:    Marcin Pilipczuk, Michal Pilipczuk                        *
 *   Opis:     Rozwiazanie wzorcowe O(n*log n) - prostsza wersja: drzewo *
 *             licznikowe.                                               *
 *                                                                       *
 *************************************************************************/
import java.io.*;
import java.util.*;

public class pla8 implements Runnable{
    public static void main(String[] args){
        new Thread(new pla8()).start();
    }

    static final int zz=262200;
    static final int MAX=270000;
    static final int MAX2=700000;
    static final int inf=200000000;

    static class Blok implements Comparable<Blok> {
        public int x;
        public int num;

        public int compareTo(Blok b){
            if (x != b.x)
                return x - b.x;
            else
                return num - b.num;
        }
    }

    int[] tree;
    Blok[] dosor;
    int p,q,h,n,k,dump,result,c,j;
    Blok p1,p2;

    void reset(){
        for (int i = 0; i < 2*MAX; ++i)
            tree[i] = 0;
    }

    void insert(int gdzie){
        p=gdzie+zz;
        while (p>0){tree[p]++; p=(p>>1);}
    }

    void count(int a,int b){
        p=zz+a-1;
        q=zz+b+1;
        c=0;
        while ((p>>1)!=(q>>1)){
            if (p%2==0){c+=tree[p+1];}
            if (q%2==1){c+=tree[q-1];}
            p=(p>>1); q=(q>>1);
        }
    }

    public void run(){
        try{
            tree = new int[MAX2];
            reset();
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            String linia = br.readLine();
            StringTokenizer st = new StringTokenizer(linia);
            n = Integer.parseInt(st.nextToken());
            dosor = new Blok[n];
            for (int i = 0; i < n; ++i){
                dosor[i] = new Blok();
                linia = br.readLine();
                st = new StringTokenizer(linia);
                st.nextToken();
                dosor[i].x = Integer.parseInt(st.nextToken());
                dosor[i].num = i;
            }
                
            Arrays.sort(dosor);

            for(j=0;j<n;j++){
                result++;
                insert(dosor[j].num);
                while((j<(n-1))&&(dosor[j].x==dosor[j+1].x)){
                    insert(dosor[j+1].num);
                    count(dosor[j].num+1,dosor[j+1].num-1);
                    if (c>0){result++;}
                    j++;
                }
            }    
            System.out.println(result);
        }catch(Exception e){
            throw new RuntimeException(e);
        }
    }
};
