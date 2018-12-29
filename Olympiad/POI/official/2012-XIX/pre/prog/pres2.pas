(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Prefiksufiks                                     *
 *   Autor:             Dawid Dabrowski                                  *
 *   Zlozonosc czasowa: O(n^3)                                           *
 *   Opis:              Rozwiazanie powolne: naiwne sprawdzanie          *
 *                      rownowaznosci cyklicznej slow                    *
 *                                                                       *
 *************************************************************************)

const
	MAXN = 1000005;

var
	n: longint;
	w: ansistring;
	i: longint;
	wyp: boolean;

function cycEq(len: longint): boolean;
var
	i,j: longint;
	res: boolean;
	ok: boolean;
begin
	res := false;
	for i:=1 to len do
	begin
		ok := true;
		for j:=1 to len do
		begin
			if not ok then break;
			if w[n-len+j] <> w[((i+j-2) mod len) + 1] then
				ok := false;
		end;
		if ok then
		begin
			res := true;
			break;
		end;
	end;
	cycEq := res;
end;

begin
	readln(n);
	readln(w);
	wyp := false;
	for i:=n div 2 downto 1 do
		if cycEq(i) then
		begin
			writeln(i);
			wyp := true;
			break;
		end;
	if not wyp then writeln(0);
end.
