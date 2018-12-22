program majstor;

const MAXN = 50;

var 
   N, R, i, runda, A, B : longint;
   Sven : string;
   prijatelj : array[1..MAXN] of string;

function bodovi( runda : longint; sven : char ) : longint;
var
   i : longint;
begin
   bodovi := 0;
   for i := 1 to N do begin
      if sven = prijatelj[i][runda] then bodovi := bodovi + 1;

      if (sven = 'S') and (prijatelj[i][runda] = 'P') then bodovi := bodovi + 2;
      if (sven = 'P') and (prijatelj[i][runda] = 'K') then bodovi := bodovi + 2;
      if (sven = 'K') and (prijatelj[i][runda] = 'S') then bodovi := bodovi + 2;
   end;   
end;

function max( a, b, c : longint ) : longint;
begin
   if (a >= b) and (a >= c) then max := a;
   if (b >= a) and (b >= c) then max := b;
   if (c >= a) and (c >= b) then max := c;
end;

begin
   readln( R );
   readln( Sven );
   readln( N );
   for i := 1 to n do readln( prijatelj[i] );

   A := 0;
   B := 0;
   for runda := 1 to R do begin
      A := A + bodovi( runda, Sven[runda] );
      B := B + max( bodovi( runda, 'S' ), bodovi( runda, 'P' ), bodovi( runda, 'K' ) );
   end;

   writeln( A );
   writeln( B );
end.
