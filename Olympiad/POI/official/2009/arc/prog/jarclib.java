/*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    carclib.c                                                  *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Biblioteka do wczytywania danych wejsciowych i wypisywania *}
{*            wyniku                                                     *}
{*   Ujavowienie: Marcin Pilipczuk                                       *}
{*                                                                       *}
{*************************************************************************/

import java.io.*;
import java.util.*;

public class jarclib {
  private final static int MAGIC_BEGIN = -435634223;
  private final static int MAGIC_END = -324556462;

  private final static int MIN_K = 1;
  private final static int MAX_K = 1000000;
  private final static int MAX_N = 15000000;
  private final static int MIN_A = 1;
  private final static int MAX_A = 1000000000;
  private final static int MIN_TYP = 1;
  private final static int MAX_TYP = 3;
  private final static int MIN_PAR = 0;
  private final static int MAX_PAR = 1000000000;

  private final static int ERROR = 0;
  private final static int CORRECT = 1;

  private static int init = 0; // czy zostala juz wywolana funkcja inicjuj()
  private static int lib_n; // ile biblioteka podala juz liczb
  private static int con_k; // ile zawodnik podal liczb

  private static int N, K, A, TYP, PAR; // parametry testu wczytywane z pliku
  private static int bre, len_sub, bou, is_end; // zmienne pomocnicze

  private static int rand2_status = 198402041;
  private static Scanner scanner;

  private static int rand2(int a, int b){
    rand2_status = rand2_status * 1103515245 + 12345;
    int x = rand2_status;
    if (x < 0) x = -x; // -2^31 sie nie zdarza :D
    x >>= 1;
    return a + x % (b - a + 1);
  }

  /* test losowy */
  private static int random_test(){
    return rand2(1, A);
  }

  /* test z dlugim podciagiem nierosnacym */
  private static int decreasing_test(){
    int tmp;
    if(bre == 0) {
      bre = rand2(0, (N - lib_n + 1 - len_sub));
      tmp = A;
      A -= rand2(0, (A - 1) / len_sub);
      len_sub--;
    } else {
      bre--;
      tmp = rand2(1, A);
    }
    return tmp;
  }

  /* test z dlugim podciagiem niemalejacym */
  private static int increasing_test(){
    return bou - decreasing_test();
  }

  private static void finish(int res, String com){
    if(res == ERROR)
      System.out.println(com);
    System.exit(0);
  }

  /* Inicjuje dane wejsciowe i zwraca liczbe projektow */
  public static int inicjuj(){
    if(init == 1)
      finish(ERROR, "Program zawodnika moze wywolac funkcje inicjuj tylko raz!!!");
    scanner = new Scanner(System.in);
    init = 1;
    K = scanner.nextInt();
    if (K > 0){
      TYP = 0;
      N = MAX_N + 2;
      return K;
    }
    int magic_begin, magic_end;
    magic_begin = scanner.nextInt();
    TYP = scanner.nextInt();
    if(magic_begin != MAGIC_BEGIN || TYP < MIN_TYP || TYP > MAX_TYP)
      finish(ERROR, "Program zawodnika nie moze korzystac z stdin!!!");
    N = scanner.nextInt();
    K = scanner.nextInt();
    A = scanner.nextInt();
    PAR = scanner.nextInt();
    if(N < 1 || N > MAX_N || N < K || K > MAX_K || A < MIN_A || A > MAX_A 
        || PAR < MIN_PAR || PAR > MAX_PAR)
      finish(ERROR, "Program zawodnika nie moze korzystac z stdin!!!");
    magic_end = scanner.nextInt();
    if(magic_end != MAGIC_END)
      finish(ERROR, "Program zawodnika nie moze korzystac z stdin!!!");
    con_k = 0;
    lib_n = 0;
    is_end = 0;
    if(TYP == 2 || TYP == 3) {
      len_sub = PAR;
      bre = 0;
    }
    if(TYP == 2)
      bou = A--;
    return K;
  }

  /* Sluzy do wczytania ciagu reprezentujacego jakosci projektow */
  public static int wczytaj(){
    if(init == 0)
      finish(ERROR, "Program zawodnika nie wywolal funkcji inicjuj!!!");
    if(lib_n > N || is_end == 1)
      finish(ERROR, "Program zawodnika wywolal funkcje wczytaj po otrzymaniu informacji o koncu ciagu!!!");
    if(lib_n == N)
      return 0;
    lib_n++;
    switch (TYP) {
      case 0:
        A = scanner.nextInt();
        if(A == 0)
          is_end = 1;
        return A;
      case 1: return random_test();
      case 2: return increasing_test();
      case 3: return decreasing_test();
      default:
        finish(ERROR, "Nieznany typ testu");
    }
    return -1;
  }

  /* Sluzy do wypisania wyznaczonego podciagu */
  public static void wypisz(int jakoscProjektu){
    if(init == 0)
      finish(ERROR, "Program zawodnika nie wywolal funkcji inicjuj!!!");
    System.out.println("" + jakoscProjektu);
    if(++con_k == K)
      finish(CORRECT, "");
  }
};
