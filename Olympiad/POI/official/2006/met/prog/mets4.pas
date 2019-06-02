(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MET (Metro)                                    *
 *   Plik:                mets4.pas                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        Zlozonosc obliczeniowa: O(n*l)                 *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000000;

type
  Pedge = ^Edge;
  Edge = record
    v : LongInt;
    n : Pedge;
  end; {record}

var
  n, l, i : LongInt;
  g : array[0..MAXN] of Pedge;
  used : array[0..MAXN] of Boolean;
  root : LongInt;
  deg, level, son, prev : array[0..MAXN] of LongInt;
  f, b : LongInt;

procedure add(a, b : LongInt);
var kr : Pedge;
begin
  New(kr);
  kr^.n := g[a]^.n;
  kr^.v := b;
  g[a]^.n := kr
end; {add}


(* Wczytuje dane wejsciowe i zeruje zmienne *)
procedure odczyt;
var
  a, b : LongInt;
begin
  Read(n, l);
  for i := 0 to n - 1 do
    deg[i] := 0;
  for i := 0 to n - 1 do
  begin
    New(g[i]);
    g[i]^.n := NIL
  end; {for}
  for i := 0 to n - 2 do
  begin
    Read(a, b);
    Dec(a); Dec(b);
    add(a, b); add(b, a);
    Inc(deg[a]); Inc(deg[b])
  end; {for}
  for i := 0 to n - 1 do
    used[i] := FALSE
end; {odczyt}

(*
 * Oblicza dlugosc najdluzszej sciezki w grafie
 * Zwraca wierzcholek bedacy koncem aktualnie znalezionej
 * najdluzszej sciezki.
 * len - dlugosc najdluzszej sciezki od liscia do wierzcholka
 * lenmax - dlugosc najdluzszej sciezki w poddrzewie
 *)
function longest_path(node : LongInt; var len, lenmax : LongInt) : LongInt;
var
  lmax1, lmax2, nmax, res, n2, len2, lenmax2 : LongInt;
  kr : Pedge;
begin
  lmax1 := -1;
  lmax2 := -1;
  nmax := node;
  res := node;  
  
  used[node] := TRUE;
  len := 0;
  lenmax := 0;
  kr := g[node];
  while kr^.n <> NIL do
  begin
    kr := kr^.n;
    if not used[kr^.v] then
    begin
      n2 := longest_path(kr^.v, len2, lenmax2);
      if len2 > lmax1 then
      begin
        lmax2 := lmax1;
        lmax1 := len2;
        nmax := n2
      end {if}
      else
      if len2 > lmax2 then
        lmax2 := len2;
      if lenmax2 > lenmax then
      begin
        lenmax := lenmax2; res := n2
      end {if}
    end {if}
  end; {while}
  Inc(lmax1);
  Inc(lmax2);
  if lmax1 + lmax2 > lenmax then
  begin
    lenmax := lmax1 + lmax2; res := nmax
  end; {if}
  len := lmax1;
  longest_path := res
end; {longest_path}

(* Oblicza wysokosci wierzcholkow w drzewie *)
procedure make_tree(node : LongInt);
var
  kr : Pedge;
begin
  used[node] := TRUE;
  level[node] := 0;
  son[node] := -1;
  kr := g[node];
  while kr^.n <> NIL do
  begin
    kr := kr^.n;
    if not used[kr^.v] then
    begin
      make_tree(kr^.v);
      prev[kr^.v] := node;
      if level[kr^.v] + 1 > level[node] then
      begin
        son[node] := kr^.v;
        level[node] := level[kr^.v] + 1
      end {if}
    end {if}
  end {while}
end; {make_tree}

procedure mark_lp;
var
  act : longInt;
begin
  act := root;
  while act <> -1 do
  begin
    used[act] := TRUE;
    act := son[act]
  end {while}
end; {mark_lp}

function go(node : LongInt) : Longint;
begin
  if used[node] then
    go :=0
  else
  begin
    go(prev[node]);
    level[node] := level[prev[node]] + 1;
    go := level[node]
  end {else}
end; {go}

procedure set1(node : LongInt);
var
  n : LongInt;
begin
  n := node;
  while not used[n] do
  begin
    used[n] := TRUE;
    n := prev[n]
  end {while}
end; {set1}

(* Glowna petla algorytmu *)
function solve : LongInt;
var
  res, mlen, mw, j : LongInt;
begin
  res := 0;

  for i := 0 to 2 * l - 3 do
  begin
    mlen := 0; mw := 0;
    for j := 0 to n - 1 do
      level[j] := 0;
    for j := 0 to n - 1 do
      if (deg[j] = 1) and (level[j] = 0) then
      begin
        res := go(j);
        if res > mlen then
        begin
          mlen := res; mw := j
        end {if}
      end; {if}
    set1(mw)
  end; {for}
  res := 0;
  for i := 0 to n - 1 do
    if used[i] then
      Inc(res);
  solve := res
end; {res}

begin
  odczyt;
  if l = 0 then
  begin
    WriteLn(0);
    Exit
  end; {if}
  root := longest_path(0, f, b);
  for i := 0 to n - 1 do
    used[i] := FALSE;
  make_tree(root);
  for i := 0 to n - 1 do
    used[i] := FALSE;
  mark_lp();
  WriteLn(solve)
end. {program}
