program perket;

const MAXN = 10;

var
   i, n : longint;
   k, g : array[1..MAXN] of longint;
   best : longint;

function diff( x, y : longint ) : longint;
begin
   if x < y then diff := y-x else diff := x-y;
end;

procedure rek( i, kis, gor : longint );
begin
   if i > n then begin
      if (gor > 0) and (diff(kis,gor) < best) then best := diff(kis,gor);
   end else begin
      rek( i+1, kis, gor );
      rek( i+1, kis*k[i], gor+g[i] );
   end;
end;

begin
   readln( n );
   for i := 1 to n do readln( k[i], g[i] );
   
   best := 1000000000;
   rek( 1, 1, 0 );

   writeln( best );   
end.