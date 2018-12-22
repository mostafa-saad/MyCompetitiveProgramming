program svada;

const MAXN = 100;

type
   niz = array[1..MAXN] of longint;

var
   t, n, m : longint;
   a, b, c, d : niz;

procedure load;
var
   i : longint;
begin
   readln( t );
   readln( n );
   for i := 1 to n do readln( a[i], b[i] );
   readln( m );
   for i := 1 to m do readln( c[i], d[i] );
end;

function f( v, x, y : longint ) : longint;
begin
   if v < x then f := 0 else f := (v-x) div y + 1;
end;

function koliko( v, n : longint; var x, y : niz ) : longint;
var
   i : longint;
begin
   koliko := 0;
   for i := 1 to n do koliko := koliko + f( v, x[i], y[i] );
end;

function solve : longint;
var
   l, r, v : longint;
begin
   l := 1;
   r := t;
   while r-l > 1 do begin
      v := (l+r) div 2;
      if koliko( v, n, a, b ) <= koliko( t-v, m, c, d ) then l := v else r := v;      
   end;
   solve := l;
end;

begin
   load;
   writeln( solve() );   
end.
