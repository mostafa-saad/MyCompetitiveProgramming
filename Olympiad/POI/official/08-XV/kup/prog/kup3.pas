(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kupno gruntu (KUP)                                        *
 *   Plik:     kup3.pas                                                  *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie wzorcowe, izomorficzne z kup2.cpp.            *
 *                                                                       *
 *************************************************************************)

const MAX_N = 2000;

var
  n, k : LongInt;
  mapa : array[0..MAX_N - 1, 0..MAX_N - 1] of LongInt;
  sumy : array[0..MAX_N - 1, 0..MAX_N - 1] of Int64;

(* wdol[i, j] oznacza ile pol w dol od danego mozna isc, nie natrafiwszy
 * na pole o wartosci wiekszej niz 2*k. *)
  wdol : array[0..MAX_N, 0..MAX_N - 1] of LongInt;

(* wlewo[j] (dla wiersza i-tego) oznacza najwiekszy numer a<j pola mapa[i, a],
 * ktore jest mniejsze od mapa[i, j]. wprawo[j] -- analogicznie, ale w prawo.
 *)
  wlewo, wprawo : array[0..MAX_N - 1] of LongInt;

procedure licz_sumy;
var
  i, j : LongInt;
begin
  for i := 0 to n - 1 do
    for j := 0 to n - 1 do
    begin
      sumy[i, j] := mapa[i, j];
      if j > 0 then
        Inc(sumy[i, j], sumy[i, j - 1]);
    end;
  for j := 0 to n - 1 do
    for i := 0 to n - 1 do
      if i > 0 then
        Inc(sumy[i, j], sumy[i - 1, j]);
end;

function suma(x1, y1, x2, y2 : LongInt) : Int64;
begin
  suma := sumy[x2, y2];
  if x1 > 0 then
    Dec(suma, sumy[x1 - 1, y2]);
  if y1 > 0 then
    Dec(suma, sumy[x2, y1 - 1]);
  if (x1 > 0) and (y1 > 0) then
    Inc(suma, sumy[x1 - 1, y1 - 1]);
end;

function duze(pole : LongInt) : Boolean;
begin
  duze := (pole > 2 * k);
end;

function dzialka(var x1, y1, x2, y2 : LongInt) : Boolean;
var
  i, j, pop, nast : LongInt;
begin
  dzialka := false;
  (* wdol *)
  for j := 0 to n - 1 do
  begin
    wdol[n, j] := 0;
    for i := n - 1 downto 0 do
      if duze(mapa[i, j]) then
        wdol[i, j] := 0
      else
        wdol[i, j] := wdol[i + 1, j] + 1;
  end;
  for i := 0 to n - 1 do
  begin
    (* wlewo *)
    wlewo[0] := -1;
    for j := 1 to n - 1 do
    begin
      pop := j - 1;
      while (pop >= 0) and (wdol[i, pop] >= wdol[i, j]) do
        pop := wlewo[pop];
      wlewo[j] := pop;
    end;
    (* wprawo *)
    wprawo[n - 1] := n;
    for j := n - 2 downto 0 do
    begin
      nast := j + 1;
      while (nast < n) and (wdol[i, nast] >= wdol[i, j]) do
        nast := wprawo[nast];
      wprawo[j] := nast;
    end;
    for j := 0 to n - 1 do
      if (wdol[i, j] > 0) and
          (suma(i, wlewo[j] + 1, i + wdol[i, j] - 1, wprawo[j] - 1) >= Int64(k)) then
      begin
        x1 := i; y1 := wlewo[j] + 1;
        x2 := i + wdol[i, j] - 1; y2 := wprawo[j] - 1;
        dzialka := true;
      end;
  end;
end;

function siedzi(x : Int64) : Boolean;
begin
  siedzi := (x >= Int64(k)) and (x <= Int64(2 * k));
end;

(* Przycina przysporawy prostokat. *)
procedure tnij(var x1, y1, x2, y2 : LongInt);
var
  x, y : LongInt;
  koniec : Boolean;
begin
  koniec := false;
  for y := y1 to y2 do
    if suma(x1, y, x2, y) >= k then
    begin
      y1 := y; y2 := y;
      (* Tne pionowy pasek *)
      for x := x1 to x2 do
        if siedzi(suma(x1, y, x, y)) then
        begin
          x2 := x;
          koniec := true;
          Break;
        end;
      if koniec then Break;
    end;
  if not koniec then
    for y := y1 to y2 do
      if siedzi(suma(x1, y1, x2, y)) then
      begin
        y2 := y;
        Break;
      end;
end;

var
  i, j : LongInt;
  x1, y1, x2, y2 : LongInt;

begin
  ReadLn(k, n);
  for i := 0 to n - 1 do
    for j := 0 to n - 1 do
      Read(mapa[i, j]);
  licz_sumy;
  if not dzialka(x1, y1, x2, y2) then
  begin
    WriteLn('NIE');
    Exit;
  end;
  tnij(x1, y1, x2, y2);
  Inc(x1); Inc(y1); Inc(x2); Inc(y2);
  WriteLn(y1, ' ', x1, ' ', y2, ' ', x2);
end.
