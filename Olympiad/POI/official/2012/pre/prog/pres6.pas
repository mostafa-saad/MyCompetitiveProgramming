(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Prefiksufiks                                     *
 *   Autor:             Dawid Dabrowski                                  *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie powolne: sprawdzanie rownowaznosci   *
 *                      cyklicznej slow za pomoca magicznego algorytmu   *
 *                      liniowego                                        *
 *                                                                       *
 *************************************************************************)

const
	MAXN = 1000005;

var
	M: longint;
	w: ansistring;
	i: longint;
	wyp: boolean;

function cycEq(len: longint): boolean;
var
	start1,start2: longint;
	n,i,j,k: longint;
begin
	start1 := 1;
	start2 := M-len+1;
	n := len; i:=0; j:=0; k:=0;
	while (i<n) and (j<n) and (k<n) do
	begin
		k:=1;
		while (k<=n) and (w[start1+(i+k)mod n]=w[start2+(j+k)mod n]) do inc(k);
		if k<=n then
		begin
			if ord(w[start1+(i+k)mod n])>ord(w[start2+(j+k)mod n]) then i:=i+k
			else j:=j+k;
		end;
	end;
	cycEq := k>n;
end;

begin
	readln(M);
	readln(w);
	wyp := false;
	for i:=M div 2 downto 1 do
		if cycEq(i) then
		begin
			writeln(i);
			wyp := true;
			break;
		end;
	if not wyp then writeln(0);
end.
