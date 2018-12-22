program parking;

var
   i, t, t1, t2, ukupno : longint;
   cijena : array[1..3] of longint;
   koliko : array[1..100] of longint;

begin
   readln( cijena[1], cijena[2], cijena[3] );

   for t := 1 to 100 do koliko[t] := 0;

   for i := 1 to 3 do begin
      readln( t1, t2 );
      for t := t1 to t2-1 do koliko[t] := koliko[t] + 1;
   end;

   ukupno := 0;
   for t := 1 to 100 do
      ukupno := ukupno + koliko[t] * cijena[koliko[t]];
   writeln( ukupno );
end.
