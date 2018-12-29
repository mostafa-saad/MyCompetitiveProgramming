(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MET (Metro)                                    *
 *   Plik:                met1.pas                                       *
 *   Autor:               Szymon Wasik                                   *
 *   Opis:                Rozwiazanie wzorcowe.                          *
 *                        Zlozonosc obliczeniowa: O(n)                   *
 *                                                                       *
 *************************************************************************)

program Metro;

const 
  MAXN = 1000000;

type 
  pedge = ^edge;
  edge = record
    next : pedge;
    v : LongInt;
  end;

var
  n, l, root, i : LongInt;
  g : array[0..MAXN-1] of ^edge;
  used : array[0..MAXN-1] of Boolean;
  level, son, count, nodes : array[0..MAXN-1] of LongInt;
  foo, baz : LongInt;

{ Dodaje krawedz do grafu }
procedure add_edge(a, b : LongInt);
var
  tmp : ^edge;
begin
  New(tmp);
  tmp^.next := g[a];
  g[a] := tmp;
  tmp^.v := b;
end;
  
{ Wczytuje dane wejsciowe i zeruje zmienne }
procedure readdata;
var 
  a, b, i : LongInt;
begin
  read(n, l);
  for i := 0 to n-1 do g[i] := nil;
  for i := 0 to n-2 do begin  
    read(a, b);
    Dec(a);
    Dec(b);
    add_edge(a, b);
    add_edge(b, a);
  end;
  for i := 0 to n-1 do used[i] := False;
end;

(*
 * Oblicza dlugosc najdluzszej sciezki w grafie
 * Zwraca wierzcholek bedacy koncem aktualnie znalezionej
 * najdluzszej sciezki.
 * len - dlugosc najdluzszej sciezki od liscia do wierzcholka
 * lenmax - dlugosc najdluzszej sciezki w poddrzewie
 *)
function longest_path(node : LongInt; var len, lenmax : LongInt) : LongInt;
var
  lmax1, lmax2, nmax : LongInt;  
  n2, len2, lenmax2 : LongInt;
  act : ^edge;
begin
  lmax1 := -1;
  lmax2 := -1;
  nmax := node;
  longest_path := node;
  used[node] := true;
  len := 0;
  lenmax := 0;
  act := g[node];
  while act <> nil do begin
    if not used[act^.v] then begin
      n2 := longest_path(act^.v, len2, lenmax2);
      if len2 > lmax1 then begin
        lmax2 := lmax1;
        lmax1 := len2;
        nmax := n2;
      end
      else if len2 > lmax2 then lmax2 := len2;
      if lenmax2 > lenmax then begin
        lenmax := lenmax2;
        longest_path := n2;
      end;
    end;
    act := act^.next;
  end;
  Inc(lmax1);
  Inc(lmax2);
  if lmax1 + lmax2 > lenmax then begin
    lenmax := lmax1 + lmax2;
    longest_path := nmax;
  end;
  len := lmax1;
end;

{ Oblicza wysokosci wierzcholkow w drzewie }
procedure make_tree(node : LongInt);
var 
  act : ^edge;
begin
  used[node] := True;
  level[node] := 0;
  son[node] := -1;
  act := g[node];
  while act <> nil do begin
    if not used[act^.v] then begin
      make_tree(act^.v);
      if level[act^.v] + 1 > level[node] then begin
        son[node] := act^.v;
        level[node] := level[act^.v] + 1;
      end;
    end;
    act := act^.next;
  end;
  Inc(count[level[node]]);
end;

{ Sortuje wieszcholki po poziomach przez zliczanie }
procedure counting_sort;
var
  i : LongInt;
begin
  for i := 1 to n-1 do
    Inc(count[i], count[i-1]);
  for i := 0 to n-1 do begin
    Dec(count[level[i]]);
    nodes[count[level[i]]] := i;
  end;
end;

{ Glowna petla algorytmu }
function solve : LongInt;
var
  act, apos, i, result : LongInt;
begin
  apos := n-1;  
  i := 0;
  result := 0;
  while (i < 2*l-1) and (result < n) do begin
    while used[nodes[apos]] do Dec(apos);
    act := nodes[apos];
    while act <> -1 do begin
      Inc(result);
      used[act] := true;
      act := son[act];
    end;
    Inc(i);
  end;  
  solve := result;
end;

begin
  readdata;
  root := longest_path(0, foo, baz);
  for i := 0 to n-1 do begin
    used[i] := false;
    count[i] := 0;
  end;
  make_tree(root);
  counting_sort;
  for i := 0 to n-1 do
    used[i] := false;
  writeln(solve);
end.
