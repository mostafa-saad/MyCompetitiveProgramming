(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Studnia                                          *
 *   Autor:             Igor Adamski                                     *
 *   Zlozonosc czasowa: O(n^2 * m)                                       *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Sprawdzenie kazdego miejsca po kolei do 0        *
 *                      i zachlanne wyrownywanie terenu                  *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000000;

function min(a, b : longint) : longint;
begin
  if a < b then
    min := a
  else
    min := b;
end;

function max(a, b : longint) : longint;
begin
  if a > b then
    max := a
  else
    max := b;
end;

var x : array[0..MAXN] of longint;
  pom : array[0..MAXN] of longint;
  n : longint;
  m : int64;

function kop(mini : longint) : longint;
  var dif, difi, i, z : longint;
    pomm : int64;
begin
  for i := 1 to n do
    pom[i] := x[i];
  pomm := m - pom[mini];
  pom[mini] := 0;
  while pomm <> 0 do
  begin
    difi := 1;
    dif := pom[1] - pom[2];
    if pom[n] - pom[n-1] > dif then
    begin
      difi := n;
      dif := x[n] - x[n-1];
    end;
    for i := 2 to n-1 do
      if pom[i] - min(pom[i-1], pom[i+1]) > dif then
      begin
        difi := i;
        dif := pom[i] - min(pom[i-1], pom[i+1]);
      end;
    pomm := pomm - 1;
    pom[difi] := pom[difi] - 1;
  end;
  z := max(pom[0] - pom[1], pom[n] - pom[n-1]);
  for i := 2 to n-1 do
  begin
    z := max(z, pom[i] - pom[i-1]);
    z := max(z, pom[i] - pom[i+1]);
  end;
  kop := z;
end;

var miejsce : longint;
  i, z, pomz : longint;

Begin
  readln(n, m);
  for i := 1 to n do
    read(x[i]);
  miejsce := 1;
  z := kop(1);
  for i := 2 to n do
  begin
    pomz := kop(i);
    if pomz < z then
    begin
      z := pomz;
      miejsce := i;
    end;
  end;
  writeln(miejsce, ' ', z);
End.
