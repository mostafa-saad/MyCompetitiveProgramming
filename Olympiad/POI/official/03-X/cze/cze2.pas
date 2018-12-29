(*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi±zanie zadania: Czekolada                                      *
 *   Plik:                cze2.pas                                       *
 *   Autor:               Marcin Kubica                                  *
 *************************************************************************)
const
  MaxKoszt = 1000;

var 
  pionowe, poziome: array [1..MaxKoszt] of integer;
  n, m, i, k, lpion, lpoz: integer; 
  koszt: longint;

begin
  { Inicjacja struktury danych. }
  for i := 1 to MaxKoszt do begin
    pionowe[i] := 0;
    poziome[i] := 0
  end;
  
  { Wczytanie danych. }
  readln(m, n);
  for i := 1 to m-1 do begin
    readln(k);
    inc(pionowe[k])
  end;
  for i := 1 to n-1 do begin
    readln(k);
    inc(poziome[k])
  end;
  
  { Obliczenie wyniku. }
  koszt := 0;
  lpion := 0;
  lpoz  := 0;
  for i := MaxKoszt downto 1 do begin
    koszt := koszt + (lpoz + 1) * pionowe[i] * i;
    lpion := lpion + pionowe[i];
    koszt := koszt + (lpion + 1) * poziome[i] * i;
    lpoz  := lpoz  + poziome[i]
  end;
  
  { Wypisanie wyniku }
  writeln(koszt)
end.
  
  
  
  
  
  
  
  