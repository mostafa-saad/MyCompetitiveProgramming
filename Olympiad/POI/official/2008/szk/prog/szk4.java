/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Szklana pulapka (SZK)                                     *
 *   Plik:     szk4.java                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Implementacja w Javie, zlozonosc O(l log l).              *
 *                                                                       *
 *************************************************************************/
import java.util.*;
import java.io.*;

public class szk4 {

    static private int m;

    private static int pp(int x){ return (x+m)%m; }

    private static class point{
        public int x;
        public int y;        /* wspolrzedne */
        public int ver;        /* rodzaj wierzcholka */
        public int num;        /* numer wierzcholka */

        point(int a,int b,int nn){
            x=a; y=b; ver=-1; num=nn;
        }
    }

    private static int[][] next;        /* next[x][c] to sasiedni wezel wedlug porzadku c */

    private static class Side{

        public int n;

        public point[] sd;

        Side(){
            n = 0;
            sd = new point[310000];
        }

        private class comp0 implements Comparator{
            public int compare(Object a,Object b){
                if (((point)a).x!=((point)b).x) return (((point)a).x-((point)b).x); else return (((point)a).y-((point)b).y);
            }
        }
        /* Comparator porzadku 0 */

        private class comp1 implements Comparator{
            public int compare(Object a,Object b){
                if (((point)a).y!=((point)b).y) return (((point)a).y-((point)b).y); else return (((point)a).x-((point)b).x);
            }
        }
        /* Comparator porzadku 1 */

        private void sort(int which){
            if (which==0) Arrays.sort(sd,0,n,new comp0()); else Arrays.sort(sd,0,n,new comp1());
        }
        /* sortowanie wedlug porzadku which */

        private void insert(int a,int b){
            sd[n]=new point(a-b,a+b,n); n++;
        }
        /* dorzucenie nowego punktu */

        public void getInput(BufferedReader bufReader) throws IOException{
            StringTokenizer Line;
            int[] len = new int[m];
            for(int i=0;i<m;i++){
                Line = new StringTokenizer(bufReader.readLine());
                len[i] = Integer.parseInt(Line.nextToken()) + Integer.parseInt(Line.nextToken());
            }
            int c = len[m-1];
            for(int i=m-1;i>0;i--) len[i]-=len[i-1];
            len[0]-=c;
            /* mamy dlugosci kolejnych bokow */
            int a=0; int b=0;
            for(int i=0;i<m;i++){
                if (i%2==1){
                    if (len[i]>0){
                        for(int j=0;j<len[i];j++){insert(a,b); a++;}
                        sd[n-len[i]].ver=((len[pp(i-1)]>0)?(2*i+1):(2*i));
                    } else {
                        for(int j=0;j<-len[i];j++){insert(a,b); a--;}
                        sd[n+len[i]].ver=((len[pp(i-1)]<0)?(2*i+1):(2*i));
                    }
                } else {
                    if (len[i]>0){
                        for(int j=0;j<len[i];j++){insert(a,b); b++;}
                        sd[n-len[i]].ver=((len[pp(i-1)]>0)?(2*i+1):(2*i));
                    } else {
                        for(int j=0;j<-len[i];j++){insert(a,b); b--;}
                        sd[n+len[i]].ver=((len[pp(i-1)]<0)?(2*i+1):(2*i));
                    }
                }
            }
        }
        /* wczytywanie wejscia */

        public void mk_next(int wh){
            sort(wh);
            int akt=-1;
            for(int i=0;i<n;i++){
                if ((sd[i].ver>=0)&&((sd[i].ver%2)!=wh))
                    {next[sd[i].num][wh]=((-sd[i].ver)/2-1); continue;}
                if (akt<0) akt=i; else {
                    next[sd[akt].num][wh]=sd[i].num;
                    next[sd[i].num][wh]=sd[akt].num;
                    akt=-1;
                }
            }
        }
        /* wypelnianie tablicy next dla porzadku wh */

    }
    /* klasa reprezentujaca odwod wielokata z mozliwoscia jego sortowania, wczytania z wejscia oraz wypelniania next */


    private static int find(int f){
        int akt=((next[f][0]>=0)?0:1);
        for(;;)
            if (next[f][akt]<0) break; else {f=next[f][akt]; akt^=1;}
        return (next[f][akt]*=-1);
    }
    /* znajdowanie sparowanego wierzcholka */

    public static void main(String[] args) throws IOException {

        BufferedReader bufReader = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer Line = new StringTokenizer(bufReader.readLine());

        m = Integer.parseInt(Line.nextToken());
        System.out.print(m/2);
        System.out.println();
        Side side = new Side();
        side.getInput(bufReader);
        next = new int[side.n][2];

        side.mk_next(0); side.mk_next(1);

        for(int i=0;i<side.n;i++){
            if ((next[i][0]<0)||(next[i][1]<0)){
                int p=find(i);
                int out1=pp(((next[i][0]<0)?(next[i][0]*(-1)):(next[i][1]*(-1)))-2)+1;
                int out2=pp(p-2)+1;
                System.out.print( out1 + " " + out2);
                System.out.println();
            }
        }
    }
}
