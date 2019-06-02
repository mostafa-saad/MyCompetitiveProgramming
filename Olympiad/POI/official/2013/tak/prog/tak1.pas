(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Taksowki                                      *
 *   Autor:                Igor Adamski                                  *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************)

const MAX = 500000;

var n : longint;
    m, d : int64;
    taksowki : array[0..MAX] of int64;
    tmp : array[0..MAX] of int64;

procedure sort(b, e : longint);
var i, j, k, mid : longint;
begin
  if b+1 = e then
    exit;
  mid := (b+e) div 2;
  sort(b, mid);
  sort(mid, e);
  for i:=b to e-1 do
    tmp[i] := taksowki[i];
  i := b;
  j := mid;
  k := b;
  while (i < mid) or (j < e) do
  begin
    if (i = mid) or ((j < e) and (tmp[j] > tmp[i])) then
    begin
      taksowki[k] := tmp[j];
      inc(j);
    end
    else
    begin
      taksowki[k] := tmp[i];
      inc(i);
    end;
    inc(k);
  end;
end;

function solve() : longint;
var i, k : longint;
    ostatnia, pozycja : int64;
begin
  // jesli zadna taksowka nie jest w stanie
  // dojechac z postoju do celu to zwracamy 0
  if taksowki[0] < m-d then
  begin
    solve := 0;
    exit;
  end;
  // szukamy najmniejszej taksowki, ktora dojedzie
  // z postoju do celu
  k := 0;
  while (k+1 < n) and (taksowki[k+1] >= m-d) do
    inc(k);
  // to bedzie ostatnia taksowka, ktora bedzimey jechac
  ostatnia := taksowki[k];
  // usuwamy ja z ciagu taksowek
  while k+1 < n do
  begin
    taksowki[k] := taksowki[k+1];
    inc(k);
  end;
  dec(n);
  // nasza aktualna pozycja
  pozycja := 0;
  for i:=0 to n-1 do
  begin
    // sprawdzamy czy dojedziemy juz ostatnia taksowka
    if (d-pozycja)*2 + m-d <= ostatnia then
    begin
      solve := i+1;
      exit;
    end;
    // jesli nie, to sprawdzamy czy i-ta taksowka
    // jest w stanie do nas dojechac
    // i jesli nie to nie jestesmy w stanie dojechac do celu
    if d-pozycja > taksowki[i] then
    begin
      solve := 0;
      exit;
    end;
    // w przeciwnym wypadku jedziemy ile mozemy
    pozycja += (taksowki[i] - (d-pozycja));
    if pozycja >= m then
    begin
      solve := i+1;
      exit;
    end;
    if pozycja > d then
      pozycja := d;
  end;
  // po wykorzystaniu n-1 taksowek zostala jeszcze ostatnia
  // wiec sprawdzamy czy mozemy nia dojechac
  if (d-pozycja)*2 + m-d <= ostatnia then
    solve := n+1
  else
    solve := 0;
end;

var i : longint;

begin
  read(m, d, n);
  for i:=0 to n-1 do
    read(taksowki[i]);
  sort(0, n);
  writeln(solve());
end.

