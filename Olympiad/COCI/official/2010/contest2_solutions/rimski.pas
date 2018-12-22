program rimski;

var
	st : string;
	i, pI, pV, pX, pL, pC : integer;

begin
	pI := 0; pV := 0; pX := 0;
	pL := 0; pC := 0;
	
	readln( st );
	for i := 1 to length( st ) do begin
		if st[ i ] = 'I' then inc( pI );
		if st[ i ] = 'V' then inc( pV );
		if st[ i ] = 'X' then inc( pX );
		if st[ i ] = 'L' then inc( pL );
		if st[ i ] = 'C' then inc( pC );
	end;
	
	if pC = 1 then begin
		write( 'XC' ); dec( pC ); dec( pX );
	end;
	if pL = 1 then begin
		if ( pX = 1 ) or ( ( pX = 2 ) and ( pI = 1 ) and ( pV = 0 ) ) then begin
			write( 'X' ); dec( pX );
		end;
		write( 'L' ); dec( pL );
	end;
	
	while pX > 1 do begin
		write( 'X' ); dec( pX );
	end;
	if ( pX = 1 ) and ( pV = 0 ) and ( pI = 1 ) then begin
		write( 'IX' ); dec( pX ); dec( pI );
	end;
	if pX = 1 then begin
		write( 'X' ); dec( pX );
	end;
	
	if ( pI = 1 ) and ( pV = 1 ) then begin
		write( 'I' ); dec( pI );
	end;
	if pV = 1 then begin
		write( 'V' ); dec( pV );
	end;
	
	while pI > 0 do begin
		write( 'I' ); dec( pI );
	end;
	
	writeln();
end.
