(*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Izolator                                       *
 *   Plik:                izo.pas                                        *
 *   Autor:               Marcin Mucha                                   *
 *************************************************************************)
const
   I_MAX = 10000;
   N_MAX = 100000;

var
   t : array[1..I_MAX] of longint;
   i : word;
   j, n, sum : longint;
   f : text;

begin
   for i := 1 to I_MAX do t[i] := 0;
   assign( f, 'izo.in');
   reset( f);
   readln( f, n);
   sum := 0;
   for j := 1 to n do
   begin readln( f, i); inc( t[i]); inc( sum, i) end;
   close( f);
   j := 0;
   i := 1;
   while (i <= I_MAX) and (j < n) do
   begin
      if 2*(j+1) > (n+1) then {j+1 > (n+1)/2}
         inc( sum, t[i]*i)
      else if 2*(j+t[i]) < (n+1) then {j+t[i] < (n+1)/2}
         dec( sum, t[i]*i)
      else {j+t[i] >= (n+1)/2}
         inc( sum, ((j+t[i]-(n+1) div 2)-((n div 2)-j))*i);
      inc( j, t[i]);
      inc( i);
   end;   
   assign( f, 'izo.out');
   rewrite( f);
   writeln( f, sum);
   close( f);
end.
