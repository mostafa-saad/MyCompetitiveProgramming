program vuk;

type longstring = packed array [ 1..505 ] of char;

var
	heapsize, Qpoc, Qkraj, poz, nind : longint;
	i, j, n, m, vrow, vcol, jrow, jcol :integer;
	trow, tcol, level, tmp, nval : integer;
	dobar, nrow, ncol: integer;
	
	mat : array[ 1..505 ] of longstring;
	udalj, best : array[ 1..505, 1..505 ] of integer;
	Q, heapkey, heaprow, heapcol : array[ 1..5000000 ] of integer;
	dr, dc : array[ 1..4 ] of integer;


procedure Qpop();
begin
	Qpoc := Qpoc + 1;
end;

procedure Qinsert( x : integer );
begin
	Q[ Qkraj ] := x; Qkraj := Qkraj + 1;
end;

function min( a, b : integer ) : integer;
begin
	if a < b then min := a else min := b;
end;

procedure heapinsert( x, hrow, hcol : longint );
begin
	heapsize := heapsize + 1;
	heapkey[ heapsize ] := x;
	heaprow[ heapsize ] := hrow;
	heapcol[ heapsize ] := hcol;
	
	poz := heapsize;
	while poz > 1 do begin
		if heapkey[ poz div 2 ] > heapkey[ poz ] then poz := 1
		else begin
			tmp := heapkey[ poz ];
			heapkey[ poz ] := heapkey[ poz div 2 ];
			heapkey[ poz div 2 ] := tmp;
			
			tmp := heaprow[ poz ];
			heaprow[ poz ] := heaprow[ poz div 2 ];
			heaprow[ poz div 2 ] := tmp;
			
			tmp := heapcol[ poz ];
			heapcol[ poz ] := heapcol[ poz div 2 ];
			heapcol[ poz div 2 ] := tmp;
			
			poz := poz div 2;
		end;
	end;
end;

procedure heappop();
begin
	heapkey[ 1 ] := heapkey[ heapsize ];
	heaprow[ 1 ] := heaprow[ heapsize ];
	heapcol[ 1 ] := heapcol[ heapsize ];
	heapsize := heapsize - 1; poz := 1;
	
	dobar := 1;
	while dobar = 1 do begin
		nind := -1; nval := heapkey[ poz ];
		
		if 2 * poz <= heapsize then
			if heapkey[ 2 * poz ] > nval then begin
				nval := heapkey[ 2 * poz ]; nind := 2 * poz;
			end;
		
		if 2 * poz + 1 <= heapsize then
			if heapkey[ 2 * poz + 1 ] > nval then begin
				nval := heapkey[ 2 * poz + 1 ]; nind := 2 * poz + 1;
			end;
		
		if nval = heapkey[ poz ] then dobar := 0
		else begin
			tmp := heapkey[ poz ];
			heapkey[ poz ] := heapkey[ nind ];
			heapkey[ nind ] := tmp;
			
			tmp := heaprow[ poz ];
			heaprow[ poz ] := heaprow[ nind ];
			heaprow[ nind ] := tmp;
			
			tmp := heapcol[ poz ];
			heapcol[ poz ] := heapcol[ nind ];
			heapcol[ nind ] := tmp;
			
			poz := nind;
		end;
	end;
end;

begin
	Qpoc := 0; Qkraj := 0; heapsize := 0;
	dr[ 1 ] := -1; dr[ 2 ] := 0;
	dr[ 3 ] := 1; dr[ 4 ] := 0;
	dc[ 1 ] := 0; dc[ 2 ] := 1;
	dc[ 3 ] := 0; dc[ 4 ] := -1;
	
	readln( n, m );
	for i := 1 to n do
		readln( mat[ i ] );
	
	for i := 1 to n do
		for j := 1 to m do begin
			udalj[ i, j ] := -1;
			best[ i, j ] := -1;
		end;
	
	for i := 1 to n do
		for j := 1 to m do begin
			if mat[ i, j ] = '+' then begin
				udalj[ i, j ] := 0;
				Qinsert( i );
				Qinsert( j );
				Qinsert( 0 );
			end;
			
			if mat[ i, j ] = 'V' then begin
				vrow := i; vcol := j;
			end;
			if mat[ i, j ] = 'J' then begin
				jrow := i; jcol := j;
			end;
		end;
	
	while Qpoc < Qkraj do begin
		trow := Q[ Qpoc ]; Qpop();
		tcol := Q[ Qpoc ]; Qpop();
		level := Q[ Qpoc ]; Qpop();
		
		for i := 1 to 4 do begin
			nrow := trow + dr[ i ];
			ncol := tcol + dc[ i ];
			dobar := 1;
			
			if ( nrow < 1 ) or ( nrow > n ) then dobar := 0;
			if ( ncol < 1 ) or ( ncol > m ) then dobar := 0;
			
			if ( dobar = 1 ) and ( udalj[ nrow, ncol ] = -1 ) then begin
				udalj[ nrow, ncol ] := level + 1;
				Qinsert( nrow ); Qinsert( ncol );
				Qinsert( level + 1 );
			end;
		end;
	end;
	
	best[ vrow, vcol ] := udalj[ vrow, vcol ];
	heapinsert( best[ vrow, vcol ], vrow, vcol );
	
	while heapsize > 0 do begin
		trow := heaprow[ 1 ]; tcol := heapcol[ 1 ];
		level := heapkey[ 1 ]; heappop();
		
		for i := 1 to 4 do begin
			nrow := trow + dr[ i ];
			ncol := tcol + dc[ i ];
			dobar := 1;
			
			if ( nrow < 1 ) or ( nrow > n ) then dobar := 0;
			if ( ncol < 1 ) or ( ncol > m ) then dobar := 0;
			
			if ( dobar = 1 ) and ( best[ nrow, ncol ] = -1 ) then begin
				best[ nrow, ncol ] := min( level, udalj[ nrow, ncol ] );
				heapinsert( best[ nrow, ncol ], nrow, ncol );
			end;
		end;
	end;
	
	writeln( best[ jrow, jcol ] );
end.
