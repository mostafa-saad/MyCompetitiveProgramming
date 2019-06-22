(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SKA (Skarbonki)                                *
 *   Plik:                skas2.pas                                      *
 *   Autor:               Pawe³ Wolff                                    *
 *   Opis:                Rozwi±zanie nieoptymalne zadania SKARBONKI     *
 *                        (dzia³a w czasie O(n^2))                       *
 *                                                                       *
 *************************************************************************)

program Skarbonki_3;


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

  odwiedzony, naCyklu: array [1..MAX_N] of boolean;


procedure WczytajDane;
var
  i: longint;

begin
  Readln(n);
  
  for i := 1 to n do begin
    Readln(klucz[i]);
    odwiedzony[i] := false;
    naCyklu[i] := false;
  end;    
end;


function IleDoRozbicia: longint;
var
  i, j, k, ile: longint;

begin
  ile := 0;

  for i := 1 to n do begin
    j := i;
    while not odwiedzony[j] and not naCyklu[j] do begin
      odwiedzony[j] := true;
      j := klucz[j];
    end;
    
    if not naCyklu[j] then begin
      Inc(ile);

      k := j;
      repeat
        naCyklu[k] := true;
        odwiedzony[k] := false;
        k := klucz[k];
      until k = j;

      j := i;
      while not naCyklu[j] do begin
        odwiedzony[j] := false;
        j := klucz[j];
      end;
    end
    else begin
      j := i;
      while not naCyklu[j] do begin
        odwiedzony[j] := false;
        j := klucz[j];
      end;
    end;
  end;
    
  IleDoRozbicia := ile;
end;



begin
  WczytajDane;
  Writeln(IleDoRozbicia);
end.
