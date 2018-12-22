program nikola;

const inf = 1000000000;

var
   i, j, n : longint;
   pristojba : array[1..1000] of longint;
   memo : array[1..1000, 1..1000] of longint;

function min( a, b : longint ) : longint;
begin
   if a < b then min := a else min := b;
end;

function opt( polje, skok : longint ) : longint;
begin
   if (polje < 1) or (polje > n) then opt := inf
   else if polje = n then opt := pristojba[n]
   else begin
      if memo[polje,skok] = -1 then
         memo[polje,skok] := pristojba[polje] + min( opt( polje-skok, skok ), opt( polje+skok+1, skok+1 ) );
      opt := memo[polje,skok];
   end;
end;

begin
   readln( n );
   for i := 1 to n do readln( pristojba[i] );

   for i := 1 to n do
      for j := 1 to n do
         memo[i,j] := -1;

   writeln( opt( 2, 1 ) );
end.
