{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Tetris attack (TET)                                        *}
{*   Plik:    tets4.pas                                                  *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Rozwiazanie za wolne. Zlozonosc: O(n^2), w kazdym kroku    *}
{*            usuwamy dwa najblizsze klocki                              *}
{*                                                                       *}
{*************************************************************************}
const MAX_N = 50000;

var
  n, licz : LongInt;
  t : array[0..2 * MAX_N] of LongInt;
  p1, p2 : array[0..MAX_N] of LongInt;
  tab : array[0..1000000] of LongInt;
  c : array[0..MAX_N] of Boolean;
  i, m, l, x, x0, j : LongInt;

begin
  ReadLn(n);
  licz := 0;
  for i := 0 to 2 * n - 1 do
    ReadLn(t[i]);
  for i := 0 to n do
  begin
    p1[i] := -1;
    p2[i] := -1;
    c[i] := true;
  end;
  for i := 0 to 2 * n - 1 do
    if p1[t[i]] = -1 then
      p1[t[i]] := i
    else
      p2[t[i]] := i;
  m := 0;
  l := 2 * n;
  while l > 0 do
  begin
    x := 3 * MAX_N; x0 := 0;
    for i := 1 to n do
      if c[i] then
      begin
        if p2[i] - p1[i] < x then
        begin
          x := p2[i] - p1[i];
          x0 := i;
        end;
      end;
    Inc(m, x - 1);
    i := l - 1;
    while i <> p2[x0] do
    begin
      if p1[t[i]] = i then
        Dec(p1[t[i]], 2)
      else
        Dec(p2[t[i]], 2);
      Dec(i);
    end;
    for j := i + 1 to l - 1 do
      t[j - 1] := t[j];
    Dec(i); Dec(l);
    while i <> p1[x0] do
    begin
      if p1[t[i]] = i then
        Dec(p1[t[i]])
      else Dec(p2[t[i]]);
      Dec(i);
    end;
    for j := i + 1 to l - 1 do
      t[j - 1] := t[j];
    Dec(l);
    for i := p1[x0] to p2[x0] - 2 do
    begin
      tab[licz] := i + 1;
      Inc(licz);
    end;
    c[x0] := false;
  end;
  WriteLn(m);
  for i := 0 to m - 1 do
    WriteLn(tab[i]);
end.
