(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Bar salatkowy                                 *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************)

const MAX_N = 1000 * 1000;

var
   n, res, mins : longint;
(* sums[] - sumy prefiksowe
   nxt[i] = min takie j > i, ze sums[i] = sums[j]
   peak[i] = max takie j, ze sums[i] <= sums[k] <= sums[j] dla i < k < j *)
   sums, nxt, peak : array[0..MAX_N] of longint;
   fruit : array[0..MAX_N] of char;

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
end;

{ oblicza tablice nxt }
procedure calc_nxt;
var
   i : longint;
   last : array[0..MAX_N] of longint;
begin
   for i := 0 to n do
      last[i] := -1;
   for i := n downto 0 do
   begin
      nxt[i] := last[sums[i] - mins];
      last[sums[i] - mins] := i;
   end;
end;

{ oblicza tablice peak oraz wynik }
procedure calc_res;
var
   cpeak, i : longint;
begin      
   cpeak := n;
   res := 0;
   for i := 0 to n do
      peak[i] := i;
   for i := n - 1 downto 0 do
      if fruit[i] = 'p' then
      begin
         if (nxt[i] <> -1) and (sums[peak[nxt[i]]] >= sums[cpeak]) then 
            cpeak := peak[nxt[i]];
         peak[i] := cpeak;
         if cpeak - i > res then
            res := cpeak - i;
      end
      else
         cpeak := i;   
end;

begin
   readln(n);
   readln(fruit);
   calc_sums;
   calc_nxt;
   calc_res;
   writeln(res);
end.

