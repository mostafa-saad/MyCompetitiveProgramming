(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Litery                                           *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      Drzewa przedzialowe                              *
 *                                                                       *
 *************************************************************************)

Program litery;
const 
  SIZE = 20;
  MAXN = 1000005;
var
  w : array[0..(1 shl (SIZE + 1))] of longint;
  n, pos, i: longint;
  wynik : int64;
  tab : array['A' .. 'Z'] of array[0..MAXN] of longint;
  ind : array['A' .. 'Z'] of longint;
  s : array[0..MAXN] of char;
  c : char;

(* Implementacja drzew przedzialowych wg strony:
 * http://was.zaa.mimuw.edu.pl/?q=node/9
 *)

procedure insert(x,val:longint);
var 
  v : longint;
begin
  v := (1 shl SIZE) + x;
  w[v] := val;
  while v <> 1 do begin
    v := v div 2;
    w[v] := w[2 * v] + w[2 * v + 1];
  end
end;

function query(a, b : longint) : longint;
var
  va, vb, wyn : longint;
begin
  va := (1 shl SIZE) + a;
  vb := (1 shl SIZE) + b;
  
  wyn := w[va];
  if va <> vb then wyn := wyn + w[vb];

  while ((va div 2) <> (vb div 2)) do begin
    if va mod 2 = 0 then wyn := wyn + w[va + 1];
    if vb mod 2 = 1 then wyn := wyn + w[vb - 1];
    va := va div 2;
    vb := vb div 2;
  end;
  query := wyn;
end;

begin
  n := 0; pos := 0; wynik := 0;
  for i := 0 to (1 shl (SIZE + 1)) do w[i] := 0;
  for c := 'A' to 'Z' do
    for i := 0 to MAXN do
      tab[c][i] := 0;
  for c := 'A' to 'Z' do
    ind[c] := 0;

  readln(n);
  readln(s);
  for i := n - 1 downto 0 do begin
    tab[s[i]][ind[s[i]]] := i;
    inc(ind[s[i]]);
  end;
  readln(s);

  for i := 0 to n - 1 do begin
    pos := tab[s[i]][ind[s[i]] - 1];
    dec(ind[s[i]]);
    insert(pos, 1);
    pos := pos + query(pos + 1, MAXN);
    wynik := wynik + pos - i;
  end;
  
  writeln(wynik);
end.
