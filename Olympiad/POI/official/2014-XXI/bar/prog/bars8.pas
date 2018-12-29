(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Bar salatkowy                                 *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n^3)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Sprawdza kazdy spójny fragment liniowo.       *
 *                                                                       *
 *************************************************************************)

const MAX_N = 1000*1000;
var
   n, res: longint;
   s : array[1..MAX_N] of char;

function check(a, b : longint): boolean;
var
   cnt, i : longint;
begin
   cnt := 0;
   for i := a to b do
   begin
      if s[i] = 'p' then
         Inc(cnt)
      else
         Dec(cnt);
      if cnt < 0 then
         exit(false);
   end;
   cnt := 0;
   for i := b downto a do
   begin
      if s[i] = 'p' then
         Inc(cnt)
      else
         Dec(cnt);
      if cnt < 0 then
         exit(false);
   end;
   check := true;
end;

procedure calc_res;
var
   i, j, l : longint;
begin
   res := 0;
   for i := 1 to n do
      for j := i to n do
         if check(i, j) then
         begin
            l := j - i + 1;
            if l > res then
               res := l;
         end;
end;

begin
   readln(n);
   readln(s);
   calc_res;
   writeln(res);
end.

