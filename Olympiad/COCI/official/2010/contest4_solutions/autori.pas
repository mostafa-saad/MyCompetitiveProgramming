program autori;

var
	S : String[ 105 ];
	i, len : integer;

begin
	readln( S );
	write( S[ 1 ] );
	
	len := Length( S );
	for i := 1 to len do
		if S[ i ] = '-' then
			write( S[ i+1 ] );
	
	writeln;
end.
