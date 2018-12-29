/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  BBB (BBB)                                                 *
 *   Plik:     bbb2.java                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie wzorcowe, zlozonosc O(n), implementacja       *
 *             w Javie.                                                  *
 *                                                                       *
 *************************************************************************/

import java.util.*;
import java.io.*;

public class bbb2 {

    public static void main(String[] args) throws IOException {

        int inf=2*1000*1000*1000+100;

        int n,p,q,x,y;

        BufferedReader bufReader = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer Line = new StringTokenizer(bufReader.readLine());
        n = Integer.parseInt(Line.nextToken());
        p = Integer.parseInt(Line.nextToken());
        q = Integer.parseInt(Line.nextToken());
        x = Integer.parseInt(Line.nextToken());
        y = Integer.parseInt(Line.nextToken());

        int h=0,min=inf;                // wysokosc w trakcie przetwarzania i aktualne minimum
        int l_pre,l_suf;                // minima w prefixie i sufixie
        int opt=inf;                        // znalezione optimum
        int k,r;

        int[] height=new int[n+1];                // wysokosci
        int[] min_prefix=new int[n+1];                // minima w prefixach
        int[] min_sufix=new int[n+1];                // minima w sufixach

        height[0]=0;
        Line =         new StringTokenizer(bufReader.readLine());
        char[] input = (Line.nextToken()).toCharArray();                // slowo na wejsciu +-

        for(int i=0;i<n;i++){
            if (input[i]=='+') h++; else h--;
            height[i+1] = h;
        }
        /* wypelnianie wysokosci */

        for (int i=0;i<=n;i++){
            if (min>height[i]) min=height[i];
            min_prefix[i]=min;
        }
        min=inf;
        for (int i=n;i>=0;i--){
            if (min>height[i]) min=height[i];
            min_sufix[i]=min;
        }
        /* minima w prefixach i sufiksach */

        for(int i=1;i<=n;i++){
            l_suf = height[i]-min_sufix[i]-p;
            if (l_suf<0) l_suf=0;

            l_pre = (-min_prefix[i])+(height[i]-height[n])-p;
            if (l_pre<0) l_pre=0;
            /* wyznaczanie l_suf i l_pre - minimow w prefiksie i sufiksie */

            if (l_suf<l_pre) l_suf=l_pre;
            l_suf+=(l_suf%2);

            if (q-p>height[n]+l_suf)
                k = ((q-p-height[n])/2);
            else
                k = l_suf+(height[n]-(q-p))/2;
            /* obliczenie minimalnej potrzebnej liczby zmian znakow */

            r = (n-i)*y+k*x;
            if (r<opt) opt=r;
        }
        System.out.print(opt);
        System.out.println();
    }

}