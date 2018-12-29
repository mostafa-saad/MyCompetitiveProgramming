/**************************************************************************}
{*                                                                        *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                            *}
{*   Plik:    jarclib.java                                                *}
{*   Opis:    Biblioteka dla zawodnikow.                                  *}
{*                                                                        *}
{**************************************************************************/

import java.util.*;

public class jarclib{
  final static int MIN_K = 1;
  final static int MAX_K = 1000000;
  final static int MIN_P = 1;
  final static int MAX_P = 1000000000;

  private static int K, P, ile_wypisano_liczb;
  private static boolean koniec_ciagu, zainicjowano = false;
  private static Scanner skaner;

  private static void blad(String com)
  {
    System.err.println(com);
    System.exit(0);
  }

  public static int inicjuj()
  {
    if(zainicjowano)
      blad("Program zawodnika moze wywolac funkcje inicjuj tylko raz!!!");
    skaner = new Scanner(System.in);
    K = skaner.nextInt();
    if(K < MIN_K || K > MAX_K)
      blad("Niepoprawna wartosc k!!!");
    zainicjowano = true;
    ile_wypisano_liczb = 0;
    koniec_ciagu = false;
    return K;
  }

  public static int wczytaj()
  {
    if(!zainicjowano)
      blad("Program zawodnika nie wywolal funkcji inicjuj!!!");
    if(koniec_ciagu)
      blad("Program zawodnika wywolal funkcje wczytaj po otrzymaniu informacji o koncu ciagu!!!");
    P = skaner.nextInt();
    if(P == 0) {
      koniec_ciagu = true;
      return 0;
    }
    if(P < MIN_P || P > MAX_P)
      blad("Nieprawidlowa jakosc projektu");
    return P;
  }

  public static void wypisz(int jakoscProjektu)
  {
    if(!zainicjowano)
      blad("Program zawodnika nie wywolal funkcji inicjuj!!!");
    System.out.println("" + jakoscProjektu);
    if(++ile_wypisano_liczb == K)
      System.exit(0);
  }
};
