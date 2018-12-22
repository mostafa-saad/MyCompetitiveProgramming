program genijalac;

var
	niz : array[ 1..1000005 ] of longint;
	cikl : array[ 1..1000005 ] of longint;
	n, c, d, i, overflow : longint;
	a, b, period : int64;

function shirise( poc, tren, lev : longint ) : longint;
begin
	if ( poc = tren ) and ( lev > 0 ) then shirise := lev
	else begin
		cikl[ tren ] := shirise( poc, niz[ tren ], lev + 1 );
		shirise := cikl[ tren ];
	end;
end;

function gcd( x, y : int64 ) : int64;
var o : int64;
begin
	while y > 0 do begin
		o := x mod y;
		x := y; y := o;
	end;
	
	gcd := x;
end;

function solve( x : int64 ) : int64;
begin
	if overflow = 1 then solve := 0
	else solve := ( x + period - 1 ) div period;
end;

begin
	read( n, a, b, c, d );
	for i := 1 to n do begin
		read( niz[ i ] );
		cikl[ i ] := -1;
	end;
	
	for i := 1 to n do
		if cikl[ i ] = -1 then
			shirise( i, i, 0 );
		
	overflow := 0; period := 1;
	for i := c+1 to n-d do begin
		period := ( period * cikl[ i ] ) div gcd( period, cikl[ i ] );
		
		if period > b then begin
			overflow := 1;
			break;
		end;
	end;
		
	writeln( solve( b ) - solve( a-1 ) );
end.
