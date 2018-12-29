/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Podzial krolestwa (POD)                                   *
 *   Plik:     pod6.java                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Algorytm wzorcowy O(sqrt(|V|)2^|V|).                      *
 *                                                                       *
 *************************************************************************/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class pod6 {
  public static int[] present;       /* reprezentacja aktualnego stanu polowek (zerojedynkowo) */
  public static int[][] sasiedzi;    /* tablica list sasiedztwa */
  public static int[] degree;        /* liczba sasiadow kolejnych wierzcholkow */

  public static int n,m;
  public static int opt,opt_subset;  /* zapamientane optymalne rozwiazanie (koszt i podzial) */
  public static int akt;             /* aktualny koszt */
  public static int subset;          /* present zapamietany jako maska bitowa */

  /* wymiana miast a i b miedzy polowkami */
  public static void xch(int a,int b){
    subset^=(1<<a);
    present[a]^=1;
    int k=0;    /* licznik zliczajacy sasiadow a nalezacych do drugiej polowki */
    for (int i=0;i<degree[a];i++){k+=present[sasiedzi[a][i]];}
    if (present[a]!=0) akt+=(degree[a]-(k<<1)); else akt-=(degree[a]-(k<<1));      /* naniesienie zmian w koszcie */
    /* a jest juz w przeciwnej polowce */
    subset^=(1<<b);
    present[b]^=1;
    k=0;
    for (int i=0;i<degree[b];i++){k+=present[sasiedzi[b][i]];}
    if (present[b]!=0) akt+=(degree[b]-(k<<1)); else akt-=(degree[b]-(k<<1));
    /* b jest juz w przeciwnej polowce */
    if (akt<opt) {opt=akt; opt_subset=subset;}  /* poprawa optymalnego rozwiazania */
  }

  /* funkcja rekurencyjna przegladajaca ciagi k zer i l jedynek na pierwszych k+l miastach */
  public static void perf(int k,int l){
    if ((k==0)||(l==0)) return;
    int seeked=present[k+l-1]^1;        /* seeked - cyferka przeciwna do ostatniej w
    rozwazanym fragmencie tablicy present, poszukiwana potem */
    if (seeked==1) perf(k-1,l); else perf(k,l-1);
    int found;
    for (found=0;found<k+l;found++){if (present[found]==seeked) break;}
    xch(found,k+l-1);
    if (seeked==0) perf(k-1,l); else perf(k,l-1);
  }

  public static void main(String[] args) {
    new Thread(){
      public void run(){
        try{
          BufferedReader bufReader = new BufferedReader(new InputStreamReader(System.in));
          StringTokenizer tokenizer = new StringTokenizer(bufReader.readLine());
          n=Integer.parseInt(tokenizer.nextToken());
          m=Integer.parseInt(tokenizer.nextToken());
          present=new int[n];
          degree=new int[n];
          sasiedzi=new int[n][n];

          for (int i=0;i<m;i++){
            tokenizer = new StringTokenizer(bufReader.readLine());
            int a=Integer.parseInt(tokenizer.nextToken());
            int b=Integer.parseInt(tokenizer.nextToken());
            a--; b--;
            sasiedzi[a][degree[a]++]=b;
            sasiedzi[b][degree[b]++]=a;
          }   /* wczytywanie wejscia */

          akt = 0;
          subset=(1<<(n/2))-1;
          for (int i=0;i<n;i++){present[i]=((i<n/2)?1:0);}
          /* ustawienie podzbiorow */
          for (int i=0;i<n;i++){
            for (int j=0;j<degree[i];j++){
              if ((present[i]^present[sasiedzi[i][j]])!=0) akt++;
            }
          }
          /* ustawienie kosztu */
          akt>>=1;
          opt=akt;
          opt_subset=subset;
          perf(n/2-1,n/2);
          int v=(opt_subset&1); /* zmienna trzymajaca przynaleznosc miasta 1 do polowki oznaczonej jako 1 */
          for(int i=0;i<n;i++){
            if (((opt_subset&(1<<i))!=0 ? 1 : 0)==v){
              System.out.print(i+1);
              System.out.print(" ");
            }
          }
          System.out.println();
        } catch (IOException e){
        }
      }
    }.start();
  }
}
