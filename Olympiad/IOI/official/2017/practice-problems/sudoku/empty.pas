var
	n, n2, i, j, x: longint;
begin
	read(n);
	n2 := n * n;
	for i := 1 to n2 do
	begin
		for j := 1 to n2 do
		begin
			read(x);
			write(x, ' ');
		end;
		writeln();
	end;
end.
