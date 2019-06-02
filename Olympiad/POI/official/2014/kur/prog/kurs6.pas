(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Kurierzy                                      *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(nm)                                         *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Algorytm wyszukiwania lidera zastosowany dla  *
 *                         kazdego zapytania.                            *
 *                                                                       *
 *************************************************************************)

const
	MAXN = 500005;

var
	t: array[0..MAXN-1] of longint;
	n, m, a, b, i, j, leader, leaderCount, realCount: longint;

begin
	readln(n, m);
	for i:=0 to n-1 do
		read(t[i]);
	
	for i:=0 to m-1 do
	begin
		readln(a, b);
		dec(a);
		dec(b);

		leader := -1;
		leaderCount := 0;
		for j:=a to b do
		begin
			if (leaderCount = 0) then
			begin
				leader := t[j];
				leaderCount := 1;
			end
			else 
			begin
				if (leader = t[j]) then
					inc(leaderCount)
				else
					dec(leaderCount);
			end;
		end;

		realCount := 0;
		for j:=a to b do
			if (t[j] = leader) then
				inc(realCount);

		if (realCount > (b-a+1) div 2) then
			writeln(leader)
		else
			writeln(0);
	end;
end.
