var n, i: integer;
		x, y: integer;
		minx, maxx, miny, maxy: integer;

begin

	readln(n);
	readln(minx, miny);
	maxx:= minx;
	maxy:= maxy;
	
	for i:= 1 to n-1 do begin
		readln(x, y);
		if(x > maxx) then maxx:= x;
		if(x < minx) then minx:= x;
		if(y > maxy) then maxy:= y;
		if(y < miny) then miny:= y;
	end;

	if(maxx-minx > maxy-miny) then
		writeln((maxx-minx)*(maxx-minx))
	else
		writeln((maxy-miny)*(maxy-miny));

end.
