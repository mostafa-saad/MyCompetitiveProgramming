(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SKA (Skarbonki)                                *
 *   Plik:                skab3.pas                                      *
 *   Autor:               Micha³ Adamaszek                               *
 *   Opis:                Rozwi±zanie niepoprawne zadania SKARBONKI      *
 *                        (zlicza liczbê cykli jednoelementowych plus    *
 *                        jeden)                                         *
 *                                                                       *
 *************************************************************************)


program Skarbonki_b3;

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
  
  Writeln(wynik + 1);
end.
