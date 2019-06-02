(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Superkomputer                                 *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O((q+n) log* (q+n))                           *
 *   Zlozonosc pamieciowa: O(q+n)                                        *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                         Rozwiazanie wykorzystuje autorska strukture   *
 *                         danych do szybkiego aktualizowania liczby     *
 *                         wierzcholkow na kazdym poziomie.              *
 *                         Roznica polega na zastosowaniu Find&Union     *
 *                         w miejscu list.                               *
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
	n, m, i, maxD, curResult, x, more, nextBlock, dd: longint;
	t, d, s, result, tmp: array[0..MAXN] of longint;
	p: array[0..3*MAXN] of longint;
	block: array[0..3*MAXN,0..1] of longint;
	q: array[0..MAXQ] of longint;
	adj, ps: array[0..MAXN] of TList;
	posit: TList;

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

procedure Clear(var currentPos: TList);
var
	element: TList;
begin
	while (currentPos <> NIL) do
	begin
		element := currentPos;
		currentPos := currentPos^.next;
		dispose(element);
	end;

	new(currentPos);
end;

function Max(a, b: longint): longint;
begin
	if (a >= b) then
		Max := a
	else
		Max := b;
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

function FindSet(u: longint): longint;
begin
	if (u <> p[u]) then
		p[u] := FindSet(p[u]);
	FindSet := p[u];
end;

procedure Union(u, v: longint);
begin
	p[FindSet(u)] := FindSet(v);
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

	for i:=0 to maxD do
	begin
		block[i][0] := s[i];
		block[i][1] := 1;
		PushBack(ps[block[i][0]], i);
	end;

	curResult := maxD+1;
	result[n] := curResult;

	for i:=0 to 3*n do
		p[i] := i;

	for i:=n downto 2 do
	begin
		posit := ps[i];
		dd := 0;
		while (true) do
		begin
			x := ReadNext(posit);
			if (x = -1) then
				break;
			tmp[dd] := x;
			inc(dd);
		end;

		while (dd >= 0) do
		begin
			x := tmp[dd];
			dec(dd);

			more := 0;

			if (x <> FindSet(x)) then
				continue;
			if (block[FindSet(x+1)][0] = block[x][0]) then
			begin
				inc(block[FindSet(x+1)][1], block[x][1]);
				Union(x, FindSet(x+1));
				continue;
			end;
			if (block[x][0] <= i-1) then
				continue;

			repeat
				inc(more, (block[x][0]-(i-1))*block[x][1]);
				if (more > 0) then
					nextBlock := block[FindSet(x+1)][0]*block[FindSet(x+1)][1]+more;

				if (nextBlock > i-1) then
				begin
					more := nextBlock-Max(1,block[FindSet(x+1)][1])*(i-1);
					block[x][0] := i-1;
					block[FindSet(x+1)][0] := i-1;
					dec(curResult, block[FindSet(x+1)][1]);
					block[FindSet(x+1)][1] := Max(1,block[FindSet(x+1)][1]);
					inc(curResult, block[FindSet(x+1)][1]);
					PushBack(ps[block[x][0]], x);
					PushBack(ps[block[FindSet(x+1)][0]], x+1);
				end
				else if (more > 0) then
				begin
					more := 0;
					block[x][0] := i-1;
					block[FindSet(x+1)][0] := nextBlock;
					PushBack(ps[block[x][0]], x);
					PushBack(ps[block[FindSet(x+1)][0]], FindSet(x+1));
					if (block[FindSet(x+1)][1] = 0) then
					begin
						block[FindSet(x+1)][1] := 1;
						inc(curResult);
					end;
				end;

				x := FindSet(x+1);
			until (more <= 0);
		end;

		Clear(ps[i]);
		result[i-1] := curResult;
	end;

	for i:=0 to m-1 do
	begin
		if (i > 0) then
			write(' ');    
		if (q[i] < n) then
			write(result[q[i]])
		else
			write(result[n]);
	end;
	writeln;
end.
