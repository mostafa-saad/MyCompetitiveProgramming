/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Konduktor (KON)                                           *
 *   Plik:     kon4.java                                                 *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Rozwiazanie wzorcowe O(n^2*k)                             *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;


public class kon4 {

static int N, K;
static int pas[][] = new int[1010][1010]; // tablica z wejscia
static int prost[][] = new int[1010][1010]; // ilu wsiadlo na >=a i wysiadlo <=b
static int best[][] = new int[1010][1010]; // best[o][k] = ilu pasazerow co najmniej trzeba pominac
    // na pierszych o stacjach przy k kontrolach, ostatnia kontrola po stacji o
static int poprz[][] = new int[1010][1010]; // oraz kiedy poprzednia kontrola
static int wyn[] = new int [1010];

public static void main(String[] args)
{
  BufferedReader rd = new BufferedReader(new InputStreamReader(System.in));
  try {
    String buf = rd.readLine();
    StringTokenizer input = new StringTokenizer(buf);
    N = Integer.parseInt(input.nextToken());
    K = Integer.parseInt(input.nextToken());
    for (int a = 0; a<N-1; ++a) {
      buf = rd.readLine();
      input = new StringTokenizer(buf);
      for (int b = a+1; b<N; ++b)
        pas[a][b] = Integer.parseInt(input.nextToken());
    }
  } catch (IOException e) { e.printStackTrace(); } 
  /// preprocesing - liczenie tablicy prost
  for (int b = 0; b<N; ++b)
    for (int a = b-1; a>=0; --a)
      prost[a][b] = pas[a][b]+prost[a][b-1]+prost[a+1][b]-prost[a+1][b-1];
  /// liczenie najlepszych zarobkow
  for (int k = 1; k<=K; ++k)
    for (int o = k-1; o<=N-K+k-2; ++o)
      if (k==1)
        best[o][k] = prost[0][o];
      else
      {
        best[o][k] = 2000000001;
        for (int op = k-2; op<o; ++op)
          if (best[op][k-1]+prost[op+1][o]<best[o][k])
          {
              best[o][k] = best[op][k-1]+prost[op+1][o];
              poprz[o][k] = op;
          }
      }
  // liczenie ogolnego wyniku
  int best_gl = 2000000001;
  int ost = -1;
  for (int o = K-1; o<=N-2; ++o)
    if (best[o][K]+prost[o+1][N-1]<best_gl)
    {
      best_gl = best[o][K]+prost[o+1][N-1];
      ost = o;
    }
  // gdzie trzeba sprawdzac
  for (int k = K-1; k>=0; --k)
  {
    wyn[k] = ost;
    ost = poprz[ost][k+1];
  }
  for (int k = 0; k<K; ++k)
  {
    System.out.print((wyn[k]+1));
    if (k<K-1)
      System.out.print(" ");
  }
  System.out.println();
//  System.err.println(best_gl);
}
}
