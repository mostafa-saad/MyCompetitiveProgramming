(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SKA (Skarbonki)                                *
 *   Plik:                skas1.pas                                      *
 *   Autor:               Pawe³ Wolff                                    *
 *   Opis:                Rozwi±zanie nieoptymalne zadania SKARBONKI     *
 *                        (zliczaj±ce liczbê spójnych sk³adowych;        *
 *                        dzia³a w czasie O(n^2))                        *
 *                                                                       *
 *************************************************************************)

program Skarbonki_2;


const
  MAX_N = 1000000;


var
  n: longint;
  klucz: array [1..MAX_N] of longint;
    { klucz[i] = numer skarbonki, w której znajduje siê i-ty klucz;
      tablica ta definiuje graf skierowany: wierzcho³kami s± klucze
      o numerach 1, 2, ..., n, a krawêdzie prowadz± od wierzcho³ka 
      o numerze i do wierzcho³ka o numerze klucz[i] (dla wszystkich
      i = 1, 2, ..., n); zatem jest to graf, w którym stopieñ wyj¶ciowy
      ka¿dego wierzcho³ka jest równy 1 }

  odwiedzony: array [1..MAX_N] of boolean;
  kolejka: array [1..MAX_N] of longint;



procedure WczytajDane;
var
  i: longint;

begin
  Readln(n);
  
  for i := 1 to n do begin
    Readln(klucz[i]);
    odwiedzony[i] := false;
  end;    
end;



function IleSkladowych: longint;
{ zlicza liczbê spójnych sk³adowych grafu nieskierowanego indukowanego
  z grafu skierowanego opisanego w tablicy klucz;
  w tym celu stosuje algorytm przechodzenia grafu wszerz }

  procedure Odwiedz(l, p: longint);

    procedure Wstaw(i: longint);
    begin
      if not odwiedzony[i] then begin
        odwiedzony[i] := true;
        Inc(p);
        kolejka[p] := i;
      end;
    end;
    
  var
    i, j: longint;
  begin
    while l <= p do begin
      i := kolejka[l];
      Inc(l);
      Wstaw(klucz[i]);
      for j := 1 to n do
        if klucz[j] = i then
          Wstaw(j);
    end;
  end;


var
  i, lSkladowych: longint;

begin
  lSkladowych := 0;

  for i := 1 to n do
    if not odwiedzony[i] then begin
      odwiedzony[i] := true;
      Inc(lSkladowych);      
      kolejka[1] := i;
      Odwiedz(1, 1);
    end;

  IleSkladowych := lSkladowych;
end;



begin
  WczytajDane;
  Writeln(IleSkladowych);
end.
