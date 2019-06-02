(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TAN (Tance w kolkach)                          *
 *   Plik:                tan0.pas                                       *
 *   Autor:               Marcin Michalski                               *
 *   Opis:                Rozwiazanie wzorcowe.                          *
 *                                                                       *
 *************************************************************************)

const MAX_N = 2005;

var
  n, k, l : LongInt;
  wynik : array[0..1, 0..MAX_N] of LongInt;
  iloczyny : array[0..MAX_N] of LongInt;
  modulo5, modulo401, wyn, i : LongInt;


(* Funkcja licz±ca rozwi±zanie zadania mod modulo, je¿eli
 * parametrami zadania s± n i k. *)
function policz(modulo, n, k : LongInt) : LongInt;
var s, i, j, q : LongInt;
begin
  { Mamy zbyt wiele dzieci, by stworzyæ k kó³ek. }
  if Int64(k) * l > Int64(n) then
    policz := 0
  else
  begin
    s := 0;
    { W tablicy iloczyny przechowujemy iloczyny (n-l+1)*...*(n-1). }
    for i := l to n do
    begin
      iloczyny[i] := 1;
      for j := i - l + 1 to i - 1 do
        iloczyny[i] := ((iloczyny[i]) * (j mod modulo)) mod modulo
    end;
    for i := 0 to n do
      wynik[s, i] := 0;
    wynik[s, 0] := 1;

    { Liczenie wyniku metod± programowania dynamicznego.
      Wiêcej szczegó³ów na jego temat mo¿na znale¼æ w opisie rozwi±zania. }
    for i := 1 to k do
    begin
      s := 1 - s;
      for j := 0 to n do
        wynik[s, j] := 0;
      for q := i * l to n do
        wynik[s, q] :=
          ((q - 1) * wynik[s, q - 1] + iloczyny[q] * wynik[1 - s, q - l]) mod modulo
    end;
    policz := wynik[s, n]
  end
end;

function liczWynikMod(modulo : LongInt) : LongInt;
var liczbaKolekWielkosciModulo, zostaloKolek, wyn : LongInt;
begin
  { Nie da siê skonstruowaæ kó³ek o rozmiarze L. }
  if modulo < l then
    liczWynikMod := 0
  else
  begin
    liczbaKolekWielkosciModulo := n div modulo;
    zostaloKolek := k - liczbaKolekWielkosciModulo;

    { Je¿eli mieli¶my niewystarczaj±c± liczbê kó³ek. }
    if zostaloKolek < 0 then
      liczWynikMod := 0
    else
    begin
      wyn := policz(modulo, n mod modulo, zostaloKolek);
      if liczbaKolekWielkosciModulo mod 2 = 1 then
      wyn := wyn * (modulo - 1) mod modulo;
      liczWynikMod := wyn
    end
  end
end;


begin
  Read(n, k, l);
  { Rozwa¿amy przypadki szczególne. }
  if k = 1 then
  begin
    if n = 3 then
    begin
      WriteLn(2);
      Exit
    end;
    if n = 4 then
    begin
      WriteLn(6);
      Exit
    end
  end;

  { Liczymy wynik modulo 5 i 401, gdy¿ 2005 = 5 * 401. }
  modulo5 := liczWynikMod(5);
  modulo401 := liczWynikMod(401);

  { Znaj±c wynik modulo 5 i 401, liczymy wynik modulo 2005. }
  wyn := 0;
  for i := 0 to 5 * 401 - 1 do
  begin
    if (i mod 5 = modulo5) and (i mod 401 = modulo401) then
    begin
      wyn := i;
      Break
    end
  end;

  { Wypisujemy wynik. }
  WriteLn(wyn)
end.
