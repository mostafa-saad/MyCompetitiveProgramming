(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Rozklad Fibonacciego                             *
 *   Autor:             Jakub Radoszewski                                *
 *   Zlozonosc czasowa: O(log(k))                                        *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************)

function rozklad(var k : Int64) : LongInt;
var
  x, y, z : Int64;
  r : LongInt;
begin
  x := 1; y := 1;
  while y < k do
  begin
    z := x + y;
    x := y;
    y := z;
  end;
  r := 0;
  while k > 0 do
  begin
    (* Niezmiennik: x <= k < y, x i y to kolejne liczby Fibonacciego *)
    if k - x <= y - k then
      k := k - x
    else
      k := y - k;
    Inc(r);
    while x >= k do
    begin
      z := y - x;
      y := x;
      x := z;
    end;
  end;
  rozklad := r;
end;

var
  p : LongInt;
  k : Int64;

begin
  ReadLn(p);
  while p > 0 do
  begin
    Dec(p);
    ReadLn(k);
    WriteLn(rozklad(k));
  end;
end.
