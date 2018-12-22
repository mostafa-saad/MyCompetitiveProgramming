program planina;

var
	i, n, r : longint;
	
begin
	read( n );
	r := 2;
	
	for i := 1 to n do
		r := 2 * r - 1;
	
	writeln( r * r );
end.
