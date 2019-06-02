(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Bar salatkowy                                 *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Dla kazdego miejsca zapamietujemy najdluzszy  *
 *                         skok jaki mozna zrobic w lewo i w prawo.      *
 *                         Nastepnie sprawdzamy kazdy spojny fragment    *
 *                         w czasie stalym, w kolejnosci malejacych      *
 *                         dlugosci fragmentow.                          *
 *                                                                       *
 *************************************************************************)

const MAX_N = 1000*1000;
var
   n: longint;
   nxt : array[1..2] of array[0..MAX_N] of longint;
   fruit : array[0..MAX_N] of char;


{ oblicza tablice nxt }
procedure calc_nxt;
var
   i, mins : longint;
   sums : array[0..MAX_N] of longint;
   last : array[0..MAX_N+1] of longint;
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
   Dec(mins);

   for i := 0 to n + 1 do
      last[i] := n + 1;
   for i := n downto 0 do
   begin
      nxt[1][i] := last[sums[i] - 1 - mins];
      last[sums[i] - mins] := i;
   end;

   mins := 0;
   sums[n] := 0;
   for i := n - 1 downto 0 do
   begin
      sums[i] := sums[i + 1];     
      if fruit[i] = 'p' then
         Inc(sums[i])
      else
         Dec(sums[i]);
      if sums[i] < mins then
         mins := sums[i];
   end;
   Dec(mins);

   for i := 0 to n + 1 do
      last[i] := -1;
   for i := 0 to n do
   begin
      nxt[2][i] := last[sums[i] - 1 - mins];
      last[sums[i] - mins] := i;
   end;
end;

function check(a, b : longint): boolean;
begin
   check := (nxt[1][a] > b + 1) and (nxt[2][b + 1] < a);
end;

function calc_res : longint;
var
   i, l : longint;
begin
   for l := n downto 1 do
      for i := 0 to n - l do
         if check(i, i + l - 1) then
            exit(l);
   calc_res := 0;
end;

begin
   readln(n);
   readln(fruit);
   calc_nxt;
   writeln(calc_res);
end.

