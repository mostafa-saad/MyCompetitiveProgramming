{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Powodz (POW)                                               *}
{*   Plik:    pows4.pas                                                  *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Rozwiazanie za wolne.                                      *}
{*            Zlozonosc: b. pesymistycznie O(mn*max_h).                  *}
{*                                                                       *}
{*************************************************************************}
const MAX_N = 1000;
const MAX_R = 1000;
const INFTY = 10000; (* nieskonczonosc *)

type pair = record
              first, second : LongInt;
            end;

var
  n, m, wyn : LongInt;
  i, j, pom, first, second : LongInt;
  t : array[0..MAX_N, 0..MAX_N] of LongInt;
  tab : array[0..MAX_N * MAX_N] of pair;
  ile : array[0..MAX_R + 1] of LongInt;
  col : array[0..MAX_N, 0..MAX_N] of Boolean;
  wys : array[0..MAX_N, 0..MAX_N] of LongInt;

  
procedure odczyt;
begin
  (* Odczyt *)
  ReadLn(n, m);
  for i := 0 to n - 1 do
    for j := 0 to m - 1 do
      Read(t[i, j]);
end;

const x : array[0..3] of LongInt = (1, -1, 0, 0);
const y : array[0..3] of LongInt = (0, 0, 1, -1);

function ins(x, n : LongInt) : Boolean;
begin
  ins := (x >= 0) and (x < n);
end;

function max(a, b : LongInt) : LongInt;
begin
  if a < b then
    max := b
  else
    max := a;
end;

function make_pair(x, y : LongInt) : pair;
var p : pair;
begin
  p.first := x; p.second := y;
  make_pair := p;
end;

procedure dfs(first, second, w : LongInt);
var pomx, pomy, poz : LongInt;
begin
  wys[first, second] := w;
  if w = abs(t[first, second]) then
    col[first, second] := true;
  
  for poz := 0 to 3 do
  begin
    pomx := first + x[poz]; pomy := second + y[poz];
    if ins(pomx, n) and ins(pomy, m) then
    begin
      if col[pomx, pomy] or (w >= wys[pomx, pomy]) then
        continue;
      dfs(pomx, pomy, max(w, abs(t[pomx][pomy])));
    end;
  end;
end;

begin
  odczyt;
  
  (* Sortowanie kubelkowe *)
  for i := 1 to MAX_R do
    ile[i] := 0;
  for i := 0 to n - 1 do
    for j := 0 to m - 1 do
    begin
      inc(ile[abs(t[i, j])]);
      col[i, j] := false;
      wys[i, j] := INFTY;
    end;
  for i := 2 to MAX_R do
    ile[i] := ile[i - 1] + ile[i];
  ile[0] := 0;
  for i := 0 to n - 1 do
    for j := 0 to m - 1 do
    begin
      tab[ile[abs(t[i, j]) - 1]] := make_pair(i, j);
      Inc(ile[abs(t[i, j]) - 1]);
    end;

  wyn := 0;
  for i := 1 to MAX_R do
  begin
    if i = 1 then pom := 0 else pom := ile[i - 2] + 1;
    for j := pom to ile[i - 1] do
    begin
      first := tab[j].first; second := tab[j].second;
      if col[first, second] then
        continue;
      if t[first, second] > 0 then
      begin
        Inc(wyn);
        dfs(first, second, t[first, second]);
      end;
    end;
  end;
  WriteLn(wyn);
end.
