(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Bar salatkowy                                 *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie alternatywne                      *
 *                         Dla kazdego i znajdujemy najwieksze           *
 *                         takie j, ze ciag i..j jest lewostronnie       *
 *                         legalny, a nastepnie wyszukujemy takie        *
 *                         i <= x <= j, ze (sums[x], x) jest maksymalna. * 
 *                         Wtedy i..x to najdluzszy legalny podciag      *
 *                         o poczatku w i.                               *
 *                                                                       *
 *************************************************************************)

const MAX_N = 1000 * 1000;
const SZ = 1024 * 1024;

var
   n, res, mins : longint;
(* sums[] - sumy prefiksowe
   nxt[i] = min takie j > i, ze ciag i..(j-1) ma wiecej jablek *)
   sums, nxt : array[0..MAX_N] of longint;
   fruit : array[0..MAX_N] of char;
(* tree dla przedzialu trzyma takie i, ze 
   para (sums[i], i) jest leksykograficznie maksymalna *)
   tree : array[1..2*SZ] of longint;

{ robi x := y jesli (sums[y], y) > (sums[x], x) }
procedure update(var x : longint; y : longint);
begin
   if (y <= n) and ((sums[x] < sums[y]) or 
      ((sums[x] = sums[y]) and (x < y))) then
         x := y;
end;

{ inicjalizacja drzewa }
procedure tree_init;
var
   i : longint;
begin
   for i := 0 to SZ do 
      tree[i + SZ] := i;
   for i := SZ - 1 downto 1 do
   begin
      tree[i] := tree[2 * i];
      update(tree[i], tree[2 * i + 1]);
   end;
end;

{ zwraca takie l <= x <= r, ze (sums[x], x) jest maksymalna }
function tree_get(l, r : longint) : longint;
var
   ret : longint;
begin
   Inc(l, SZ);
   Inc(r, SZ);
   ret := tree[l];
   update(ret, tree[r]);
   while (l div 2) <> (r div 2) do
   begin
      if l mod 2 = 0 then
         update(ret, tree[l + 1]);
      if r mod 2 = 1 then
         update(ret, tree[r - 1]);
      l := l div 2;
      r := r div 2;
   end;
   tree_get := ret;
end;

{ oblicza tablice sums }
procedure calc_sums;
var
   i : longint;
begin
   mins := 0;
   sums[0] := 0;
   for i := 1 to n do
   begin
      sums[i] := sums[i - 1];     
      if fruit[i - 1] = 'p' then
         Inc(sums[i])
      else
         Dec(sums[i]);
      if sums[i] < mins then
         mins := sums[i];
   end;
   tree_init;
end;

{ oblicza tablice nxt }
procedure calc_nxt;
var
   i : longint;
   last : array[0..MAX_N+1] of longint;
begin
   Dec(mins);
   for i := 0 to n do
      last[i] := n + 1;
   for i := n downto 0 do
   begin
      nxt[i] := last[sums[i] - 1 - mins];
      last[sums[i] - mins] := i;
   end;
end;

{ oblicza wynik }
procedure calc_res;
var
   cpeak, i : longint;
begin      
   res := 0;
   for i := n - 1 downto 0 do
      if fruit[i] = 'p' then
      begin
         cpeak := tree_get(i, nxt[i] - 1);
         if cpeak - i > res then
            res := cpeak - i;
      end
end;

begin
   readln(n);
   readln(fruit);
   calc_sums;
   calc_nxt;
   calc_res;
   writeln(res);
end.

