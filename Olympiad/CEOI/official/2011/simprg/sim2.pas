{ CEOI 2011,
	TASK: SIM (Similarity)
	AUTHOR: Karol Pokorski
	Optimal, correct solution
}

const
	MAXALPH = 26;
var
	pattern, text: ansistring;
	lenPattern, lenText, i: longint;
	numLett: array[0..MAXALPH-1] of longint;
	result: int64;
begin
	readln(pattern);
	readln(text);

	lenPattern := length(pattern);
	lenText := length(text);

  result := 0;
  for i := 0 to MAXALPH-1 do
    numLett[i] := 0;

	for i:=1 to lenText do
	begin
		{we have to consider one more position of pattern (this letter of pattern can be under this letter of text)}
		if (i <= lenPattern) then
			inc(numLett[ord(pattern[i])-ord('a')]);

		result := result+numLett[ord(text[i])-ord('a')]; {increase result by number of letters which can be under this letter of text}

		{the pattern must fit within text - if not, do not consider this position of pattern}
		if (lenPattern-lenText+i > 0) then
			dec(numLett[ord(pattern[lenPattern-lenText+i])-ord('a')]);
	end;

	writeln(result);
end.
