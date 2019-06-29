/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Plakatowanie (PLA)                                        *
 *   Plik:     pla6.java                                                 *
 *   Autor:    Marcin Pilipczuk, Michal Pilipczuk                        *
 *   Opis:     Rozwiazanie wzorcowe O(n) (na stosie).                    *
 *                                                                       *
 *************************************************************************/
import java.io.*;
import java.util.*;

public class pla6 implements Runnable{
    public static void main(String[] args){
        new Thread(new pla6()).start();
    }

    int n;
    int[] s;
    int sn;

    public void run(){
        try{
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            String linia = br.readLine();
            StringTokenizer st = new StringTokenizer(linia);
            n = Integer.parseInt(st.nextToken());
            s = new int[n];
            sn = 0;
            int wyn = 0;
            for (int i = 0; i < n; ++i){
                linia = br.readLine();
                st = new StringTokenizer(linia);
                st.nextToken();
                int w = Integer.parseInt(st.nextToken());
                while (sn > 0 && s[sn-1] > w) {
                    wyn++;
                    sn--;
                }
                if (sn == 0 || s[sn-1] < w) 
                    s[sn++] = w;
            }
            System.out.println(sn+wyn);
        }catch(Exception e){
            throw new RuntimeException(e);
        }
    }
};
