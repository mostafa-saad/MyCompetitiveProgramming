(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gdzie jest jedynka?                           *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(n lg n)                                     *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************)

program gdz1;

uses pgdzlib;

type Pair = record
  x, y : LongInt;
end;

var
n, j : LongInt;
q : array[0..500000-1] of LongInt;
cand : Pair;

function FindCandidates(b, e, d : LongInt) : Pair;
var
mid, i, temp, delta: LongInt;
c1, c2 : Pair;
begin
  if (e - b) = 2 then
  begin
    FindCandidates.x := q[b];
    FindCandidates.y := q[b+1];
  end
  else
  begin
    mid := b + 1;
    for i := b + 1 to e - 1 do
      if f(q[b], q[i], d * 2) = 1 then
      begin
        temp := q[i];
        q[i] := q[mid];
        q[mid] := temp;
        mid := mid + 1;
      end;

    if (mid - b) = (e - mid) then
    begin
      c1 := FindCandidates(b, mid, d*2);
      c2 := FindCandidates(mid, e, d*2);
      delta := (e - b - 1) * d;
      if f(c1.x, c2.x, delta) = 1 then
      begin
        FindCandidates.x := c1.x;
        FindCandidates.y := c2.x;
      end;
      if f(c1.x, c2.y, delta) = 1 then
      begin
        FindCandidates.x := c1.x;
        FindCandidates.y := c2.y;
      end;
      if f(c1.y, c2.x, delta) = 1 then
      begin
        FindCandidates.x := c1.y;
        FindCandidates.y := c2.x;
      end;
      if f(c1.y, c2.y, delta) = 1 then
      begin
        FindCandidates.x := c1.y;
        FindCandidates.y := c2.y;
      end;
    end;

    if (mid - b) > (e - mid) then
      FindCandidates := FindCandidates(b, mid, d*2);
    if (mid - b) < (e - mid) then
      FindCandidates := FindCandidates(mid, e, d*2);
  end;
end;


begin
  n := inicjuj;

  if n = 1 then odpowiedz(1);

  for j := 0 to n - 1 do
    q[j] := j + 1;
  cand := FindCandidates(0, n, 1);
  if g(cand.x, cand.y) = 0 then
    odpowiedz(cand.x)
  else
    odpowiedz(cand.y);
end.

