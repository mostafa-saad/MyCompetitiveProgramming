{*************************************************************************}
{*                                                                       *}
{*                   VIII Olimpiada Informatyczna                        *}
{*                                                                       *}
{*   Rozwi¹zanie zadania: PRZEDZIA£Y                                     *}
{*   Plik:                PRZ.PAS                                        *}
{*   Autor:               MAREK PAWLICKI                                 *}
{*************************************************************************}

program Prz;
const
  (* Maksymalna liczba przedzialow *)
  MaxN  = 60000;
  (* Rozmiar tablicy *)
  MaxT  = MaxN div (SizeOf (Longint) * 2);
  (* Maksynalna liczba tablic *)
  MaxLiczT = SizeOf(Longint) * 2;
  (* Nazwa pliku wejsciowego *)
  PlikWe = 'prz.in';
  (* Nazwa pliku wyjsciowego *)
  PlikWy = 'prz.out';


type
  TPrzedzial = record
    Pocz, Koniec : Longint
  end;
  TPrzedzialy = array [1..MaxT] of TPrzedzial;
  PPrzedzialy = ^TPrzedzialy;

var
  (* Liczba przedzialow *)
  n : Longint;
  (* Liczba pelnych tablic *)
  LPelnych : Integer;
  (* Tablice z przedzialami *)
  TP : array [1..MaxLiczT] of PPrzedzialy;
  (* Liczba elementow w tablicach TP *)
  LElem : array [1..MaxLiczT] of Longint;


  procedure WczytajDane;
  (* Wczytuje poczatki i konce przedzialow do tablic TP *)
  var
    i, j, nr : Longint;
    f : Text;
  begin
    Assign (f, PlikWe);
    Reset (f);
    Readln (f, n);
    i := 0;
    while i < n do begin
      Inc (i);
      if i mod MaxT = 1 then begin
        (* Nowa tablica *)
        nr := (i-1) div MaxT + 1;
        New (TP[nr]);
        j := 1
      end else
        Inc (j);
      Readln (f, TP[nr]^[j].Pocz, TP[nr]^[j].Koniec)
    end;
    Close (f);
    LPelnych := (n-1) div MaxT;
    (* Ustalenie liczby elementow *)
    for i := 1 to LPelnych do
      LElem [i] := MaxT;
    LElem [(n-1) div MaxT + 1] := n mod MaxT
  end;

  procedure Sortuj (nr : Integer);
  (* Sortowanie nr-tej tablicy przedzialow wzgledem poczatkow *)
  (* Sortowanie pozycyjne *)
  const
    (* Maksymalna wartosc pozycji *)
    M = 255;
  type
    Cast = array [1..4] of Byte;
  var
    (* Tablica pomocnicza *)
    T : PPrzedzialy;
    (* Liczba wystapien wartosci 0..M *)
    C : array [0..M] of Integer;
    (* Numer Fazy. Poniewaz wartosci < 2^24 wiec wystarcza 3 fazy. *)
    Faza : Integer;
    (* Liczniki petli *)
    i, j : Word;
  begin
    New (T);
    for Faza := 1 to 3 do begin
      for j := 0 to M do C[j] := 0;
      for i := 1 to LElem[nr] do
        Inc (C [Cast(TP[nr]^[i].Pocz)[Faza]]);
      for j := 1 to M do
        Inc (C[j], C[j-1]);
      for i := LElem[nr] downto 1 do begin
        T^[C [Cast(TP[nr]^[i].Pocz)[Faza]]] := TP[nr]^[i];
        Dec (C [Cast(TP[nr]^[i].Pocz)[Faza]])
      end;
      for i := 1 to LElem[nr] do
        TP[nr]^[i] := T^[i]
    end;
    Dispose (T)
  end;


  procedure Polacz;
  (* Wybor przedzialow przez laczenie tablic TP^[1..LPelnych+1] *)
  var
    (* Indeks kolejnego elementu do wybrania *)
    Ind : array [1..MaxLiczT] of Integer;
    i, j : Longint;
    (* Numer tablicy z przedzialem o najmniejszym poczatku *)
    jmin : Longint;
    (* Najmniejszy poczatek przedzialu *)
    min : Longint;
    (* Poczatek i koniec biezacego przedzialu *)
    bp, bk : Longint;
    f : Text;
const
    (* MM: Do inicjalizacji *)
    big_number : Longint = 10000000;
  begin
    Assign (f, PlikWy);
    Rewrite (f);
    for j := 1 to LPelnych+1 do Ind[j] := 1;
    (* Wybierz najmniejszy poczatek *)
    { MM: to nie jest blad, ale po co?}
    min := big_number; {MM:bylo jmin := 1; min := TP[1]^[1].Pocz;}
    for j := 1 to LPelnych+1 do {MM: bylo for j := 2 to LPelnych+1 do}
      if TP[j]^[1].Pocz < min then begin
        min := TP[j]^[1].Pocz; jmin := j
      end;
    bp := TP[jmin]^[1].Pocz; bk := TP[jmin]^[1].Koniec;
    Inc (Ind[jmin]);
    (* Pozostalo n-1 przedzialow do przetworzenia *)
    i := n-1;
    while i > 0 do begin
      (* Wybierz najmniejszy *)
      min := big_number; {MM: bylo jmin := 1; min := TP[1]^[Ind[1]].Pocz;}
      for j := 1 to LPelnych+1 do {MM: bylo for j := 2 to LPelnych+1 do}
        if (Ind[j] <= LElem[j]) and (TP[j]^[Ind[j]].Pocz < min) then begin
          min := TP[j]^[Ind[j]].Pocz; jmin := j
        end;
        (* Porownanie *)
        if bk < min then begin
          (* Wypisz biezacy *)
          Writeln (f, bp, ' ', bk);
          (* Nowy biezacy *)
          bp := min; bk := TP[jmin]^[Ind[jmin]].Koniec
        end else
          (* Zmodyfikuj biezacy *)
          if bk < TP[jmin]^[Ind[jmin]].Koniec then
            bk :=  TP[jmin]^[Ind[jmin]].Koniec;
        Inc (Ind[jmin]);
      Dec (i)
    end;
    (* Wypisz ostatni *)
    Writeln (f, bp, ' ', bk);
    Close (f)
  end;

var
  i : Integer;

begin
  WczytajDane;
  for i := 1 to LPelnych + 1 do
    Sortuj (i);
  Polacz
end.
