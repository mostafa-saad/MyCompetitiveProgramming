program posl;

const
	maxl = 200;

var
	n, l, k: longint;
	counts: array[0..maxl] of qword;
	i: longint;
	sum, tmp: qword;
	offset: longint;

begin
	readln(n, l, k);

	dec(l);

	for i := 0 to l - 1 do
		counts[i] := 0;
	counts[0] := k;

	sum := k;
	offset := 0;
	for i := 1 to n - 1 do begin
		offset := (offset - 1 + l) mod l;
		tmp := sum;
		sum := sum - counts[offset] + 4000000009;
		counts[offset] := (tmp * (k - 1)) mod 4000000009;
		inc(sum, counts[offset]);
		sum := sum mod 4000000009;
	end;

	if n = 0 then
		sum := 1;

	writeln(sum);
end.
