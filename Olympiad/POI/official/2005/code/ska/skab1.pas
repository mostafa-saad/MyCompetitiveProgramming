(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SKA (Skarbonki)                                *
 *   Plik:                skab1.pas                                      *
 *   Autor:               Pawe³ Wolff                                    *
 *   Opis:                Rozwi±zanie niepoprawne zadania SKARBONKI      *
 *                        (zlicza liczbê cykli jednoelementowych)        *
 *                                                                       *
 *************************************************************************)

program Skarbonki_b1;

var
  i, n, k, wynik: longint;

begin
  Readln(n);
  
  wynik := 0;
  for i := 1 to n do begin
    Readln(k);
    if i = k then
      Inc(wynik);
  end;
  
  Writeln(wynik);
end.
