(* Model solution for the task BAL (Balloons)
 * Author: Jakub Pachocki
 * O(n) time solution
 *)


program Balloons;

Type
	Balloon = Record
		x : Longint;
		radius : Extended;
	end;

function sq(x : Extended) : Extended;
begin
	sq := x * x
end;

function min(a, b : Extended) : Extended;
begin
	if a < b then
		min := a
	else
		min := b
end;

var
	s : Array[0..199999] of Balloon;
	n, ss : Longint;
	i, pos, size : Longint;
	maxRadius, c : Extended;

begin
	readln(n);
	ss := 0;
	for i := 0 to n - 1 do
	begin
		readln(pos, size);
		maxRadius := size;
		while ss > 0 do
		begin
			c := sq(s[ss - 1].x - pos);
			maxRadius := min(maxRadius, c / (4 * s[ss - 1].radius));
			if maxRadius > s[ss - 1].radius - 1e-10 then
				dec(ss)
			else
				break
		end;
		writeln(maxRadius:0:6);
		s[ss].x := pos;
		s[ss].radius := maxRadius;
		inc(ss)
	end
end.
