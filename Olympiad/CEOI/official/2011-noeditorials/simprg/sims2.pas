{ CEOI 2011
	TASK: SIM (Similarity)
	AUTHOR: Karol Pokorski
	Correct, but slow solution
}

var
	pattern, text: ansistring;
	lenPattern, lenText, i, j: longint;
	result: int64;
begin
	readln(pattern);
	readln(text);

	lenPattern := length(pattern);
	lenText := length(text);

	{we try every valid position of pattern under text}
	for i:=1 to lenText-lenPattern+1 do
		for j:=1 to lenPattern do {we simply check equality of letters like in an example}
			if (pattern[j] = text[i+j-1]) then
				inc(result);

	writeln(result);
end.
