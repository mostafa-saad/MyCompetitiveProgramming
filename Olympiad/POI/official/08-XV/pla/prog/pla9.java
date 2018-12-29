/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Plakatowanie (PLA)                                        *
 *   Plik:     pla9.java                                                 *
 *   Autor:    Marcin Pilipczuk, Michal Pilipczuk                        *
 *   Opis:     Rozwiazanie wzorcowe O(n*log n) - listy wskaznikowe       *
 *             wedlug pomyslu Marcina Kubicy.                            *
 *                                                                       *
 *************************************************************************/
import java.io.*;
import java.util.*;

public class pla9 implements Runnable{
    public static void main(String[] args){
        new Thread(new pla9()).start();
    }
    
    static class Element{
        public int val;
        public int next;
        public int prev;
    }

    static class Blok implements Comparable<Blok>{
        public int num;
        public int h;

        public int compareTo(Blok b){
            if (h == b.h) return num - b.num;
            else return b.h - h;
        }
    }

    final static int MAX=270000;

    Element[] list;
    Blok[] input;
    int n,result,dump,k;
    Blok p1,p2;

    void reset(){
        for (int i = 0; i <= n+1; ++i)
            list[i] = new Element();
        list[0].prev=0;
        list[0].next=1;
        list[0].val=(-1);
        for (int i = 1; i <= n; ++i){
            list[i].prev=i-1;
            list[i].next=i+1;
            list[i].val=input[i-1].h;
        }
        list[n+1].prev=n;
        list[n+1].next=n+1;
        list[n+1].val=(-1);
    }

    int nx_val(int g){return list[list[g].next].val;}

    void del(int g){
        list[list[g].next].prev=list[g].prev;
        list[list[g].prev].next=list[g].next;
    }
    
    public void run(){
        try{
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            String linia = br.readLine();
            StringTokenizer st = new StringTokenizer(linia);
            n = Integer.parseInt(st.nextToken());
            input = new Blok[n];
            list = new Element[n+2];
            for (int i = 0; i < n; ++i){
                linia = br.readLine();
                st = new StringTokenizer(linia);
                st.nextToken();
                input[i] = new Blok();
                input[i].h = Integer.parseInt(st.nextToken());
                input[i].num = i+1;
            }
            reset();
            Arrays.sort(input);
            for (int i = 0; i < n; ++i){
                k = input[i].num;
                if (list[k].val != nx_val(k)) result++;
                del(k);
            }
            System.out.println(result);
        }catch(Exception e){
            throw new RuntimeException(e);
        }
    }
};
