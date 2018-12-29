(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Superkomputer                                 *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    pesymistycznie O(qn), srednio O(q+n)          *
 *   Zlozonosc pamieciowa: O(q+n)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Bliskie wzorcowemu. Brakuje struktury         *
 *                         pozwalajacej szybko aktualizowac liczby       *
 *                         zajetych wierzcholkow w danym poziomie.       *
 *                                                                       *
 *************************************************************************)

const
	MAXN = 1000001;
	MAXQ = 1000001;

type
	TList = ^TListElement;

	TListElement = record
		value: longint;
		next: TList;
	end;

var
	n, m, i, j, maxD: longint;
	t, d, s, result: array[0..MAXN] of longint;
	q: array[0..MAXQ] of longint;
	adj: array[0..MAXN] of TList;

procedure PushBack(var head: TList; value: longint);
var
	element: TList;
begin
	new(element);
	element^.value := value;
	element^.next := head;
	head := element;
end;

function ReadNext(var currentPos: Tlist): longint;
var
	returnValue: longint;
begin
	if (currentPos = NIL) then
	begin
		ReadNext := -1;
		exit;
	end;
	returnValue := currentPos^.value;
	currentPos := currentPos^.next;
	ReadNext := returnValue;
end;

procedure Dfs(u: longint);
var
	currentPos: TList;
	v: longint;
begin
	currentPos := adj[u];

	while (true) do
	begin
		v := ReadNext(currentPos);
		if (v = -1) then
			break;

		d[v] := d[u]+1;
		Dfs(v);
	end;
	
	inc(s[d[u]]);
	if (d[u] > maxD) then
		maxD := d[u];
end;

begin
	readln(n, m);

	for i:=0 to m-1 do
		read(q[i]);
	
	for i:=1 to n-1 do
	begin
		read(t[i]);
		dec(t[i]);
		PushBack(adj[t[i]], i);
	end;

	Dfs(0);

	for i:=n downto 1 do
	begin
		for j:=0 to n do
		begin
			if (s[j] = 0) then
				break;
			if (s[j] > i) then
			begin
				s[j+1] := s[j+1]+s[j]-i;
				s[j] := i;
			end;
			if (j > maxD) then
				maxD := j;
		end;
		result[i] := maxD+1;
	end;

	for i:=0 to m-1 do
	begin
		if (i > 0) then
			write(' ');
		if (q[i] <= n) then
			write(result[q[i]])
		else
			write(result[n]);
	end;
	writeln;
end.
