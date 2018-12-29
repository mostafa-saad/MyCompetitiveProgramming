(*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Izolator                                       *
 *   Plik:                izo2.pas                                       *
 *   Autor:               Marcin Mucha                                   *
 *   Uwagi:               Rozwi±zanie nieoptymalne                       *
 *************************************************************************)
const
   N_MAX = 100000;

var
   t : array[1..N_MAX] of longint;
   f : text;
   j, n, sum : longint;

procedure quicksort;

procedure sort(l, r: longint);
var
  i, j, x, y: longint;
begin
  i := l; j := r; x := t[(l+r) div 2];
  repeat
    while t[i] < x do i := i + 1;
    while x < t[j] do j := j - 1;
    if i <= j then
    begin
      y := t[i]; t[i] := t[j]; t[j] := y;
      i := i + 1; j := j - 1;
    end;
  until i > j;
  if l < j then sort(l, j);
  if i < r then sort(i, r);
end;

begin
  sort(1,n);
end;

begin
   assign( f, 'izo.in');
   reset( f);
   readln( f, n);
   sum := 0;
   for j := 1 to n do
   begin readln( f, t[j]); inc( sum, t[j]) end;
   close( f);
   quicksort;
   for j := 1 to n div 2 do
      dec( sum, t[j]);
   for j := (n+1) div 2 + 1 to n do
      inc( sum, t[j]);
   assign( f, 'izo.out');
   rewrite( f);
   writeln( f, sum);
   close( f);
end.
