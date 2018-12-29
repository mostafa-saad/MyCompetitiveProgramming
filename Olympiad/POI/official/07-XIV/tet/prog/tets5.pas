{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Tetris attack (TET)                                        *}
{*   Plik:    tets5.pas                                                  *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Rozwiazanie za wolne. Zlozonosc: O(n^2), kwadratowa        *}
{*            implementacja rozwiazania wzorcowego                       *}
{*                                                                       *}
{*************************************************************************}
const MAX_N = 50000;

var
  n, il, licz : LongInt;
  t : array[0..2 * MAX_N] of LongInt;
  p1, p2 : array[0..MAX_N] of LongInt;
  tab : array[0..1000000] of LongInt;
  i, x, x0, m, pocz : LongInt;

begin
  ReadLn(n);
  il := 2 * n;
  for i := 0 to 2 * n - 1 do
    ReadLn(t[i]);
  for i := 0 to n do
  begin
    p1[i] := -1;
    p2[i] := -1;
  end;
  for i := 0 to 2 * n - 1 do
    if p1[t[i]] = -1 then
      p1[t[i]] := i
    else
      p2[t[i]] := i;
  m := 0; pocz := 0; licz := 0;
  while il - pocz > 0 do
  begin
    x := 3 * MAX_N; x0 := -1;
    for i := pocz to il - 1 do
      if i = p2[t[i]] then
      begin
        x0 := t[i];
        x := p2[t[i]] - p1[t[i]];
        break;
      end;
    Inc(m, x - 1);
    for i := p2[x0] - 1 downto p1[x0] + 1 do
    begin
      Inc(p1[t[i]]);
      t[i + 1] := t[i];
    end;
    for i := p1[x0] - 1 downto pocz do
    begin
      Inc(p1[t[i]], 2);
      t[i + 2] := t[i];
    end;
    for i := p1[x0] to p2[x0] - 2 do
    begin
      tab[licz] := (i + 1) - pocz;
      Inc(licz);
    end;
    Inc(pocz, 2);
  end;
  WriteLn(m);
  for i := 0 to licz - 1 do
    WriteLn(tab[i]);
end.
