program iks;
var
	pon, A : array[ 1..1000000 ] of longint;
	niz : array[ 1..105 ] of longint;
	counter, n : longint;

procedure dodajfaktore( x : longint );
var
	tr, org : longint;
begin
	tr := 2; org := x;
	
	while ( tr * tr <= org ) do begin
		while( x mod tr = 0 ) do begin
			inc( pon[ tr ] );
			x := x div tr;
		end;
		inc( tr );
	end;
	
	if ( x > 1 ) then inc( pon[ x ] );
end;

function solve() : longint;
var
	rez, i, j : longint;
begin
	rez := 1; counter := 0;
	for i := 2 to 1000000 do begin
		pon[ i ] := pon[ i ] div n;
		for j := 1 to pon[ i ] do
			rez := rez * i;
			
		if ( pon[ i ] > 0 ) then begin
			inc( counter );
			A[ counter ] := i;
		end;
	end;
	
	solve := rez;
end;

function calcprom( x : longint ) : longint;
var
	prom, i, br, tr : longint;
begin
	prom := 0;
	
	for i := 1 to counter do begin
		br := A[ i ]; tr := pon[ br ];
		while ( x mod br = 0 ) do begin
			dec( tr ); x := x div br;
		end;
		if ( tr > 0 ) then
			prom := prom + tr;
	end;
	
	calcprom := prom;
end;

var
	rez, prom, i : longint;
begin
	for i := 1 to 1000000 do
		pon[ i ] := 0;
	
	read( n );
	for i := 1 to n do begin
		read( niz[ i ] );
		dodajfaktore( niz[ i ] );
	end;
	
	rez := solve(); prom := 0;
	for i := 1 to n do
		prom := prom + calcprom( niz[ i ] );
	
	writeln( rez, ' ', prom );
end.
