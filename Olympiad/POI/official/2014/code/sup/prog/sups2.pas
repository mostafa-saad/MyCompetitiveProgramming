(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Superkomputer                                 *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(q*n^2*k)                                    *
 *   Zlozonosc pamieciowa: O(q+n)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
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
	completed: array[0..MAXN] of boolean;
	n, m, i, maxLvl, origMaxLvl, sizeCompleted: longint;
	t, d, parent, turnCompleted, sizeLvl, completedLvl, childCompleted, numChild: array[0..MAXN] of longint;
	q: array[0..MAXQ] of longint;
	adj, lvl: array[0..MAXN] of TList;

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

		parent[v] := u;
		d[v] := d[u]+1;
		Dfs(v);
	end;
	
	PushBack(lvl[d[u]], u);
	inc(sizeLvl[d[u]]);
	if (d[u] > maxLvl) then
		maxLvl := d[u];
end;

function FindNextV: longint;
var
	i, u: longint;
	currentPos: TList;
begin
	for i:=maxLvl downto 0 do
	begin
		if (completedLvl[i] = sizeLvl[i]) then
			continue;

		currentPos := lvl[i];

		while (true) do
		begin
			u := ReadNext(currentPos);

			if (u = -1) then
				break;

			if ((not completed[u]) and (childCompleted[u] = numChild[u])) then
			begin
				FindNextV := u;
				exit;
			end;
		end;
	end;

	FindNextV := -1;
end;

procedure MarkPath(u: longint; value: boolean);
begin
	if (u >= 0) then
	begin
		while (u <> -1) do
		begin
			completed[u] := value;
			u := parent[u];
		end;
	end;
end;

function ComputeQuery(maxTurn: longint): longint;
var
	i, res, numCompleted, u: longint;
begin
	numCompleted := 0;
	res := 0;
	maxLvl := origMaxLvl;

	for i:=0 to n-1 do
	begin
		completed[i] := false;
		completedLvl[i] := 0;
		childCompleted[i] := 0;
	end;

	while (numCompleted < n) do
	begin
		for i:=0 to maxTurn-1 do
		begin
			u := FindNextV;

			if (u <> -1) then
			begin
				MarkPath(u, true);
				if (u <> 0) then
					inc(childCompleted[parent[u]]);
				turnCompleted[sizeCompleted] := u;
				inc(sizeCompleted);
				inc(numCompleted);
				inc(completedLvl[d[u]]);

				while ((maxLvl > 0) and (completedLvl[maxLvl] = sizeLvl[maxLvl])) do
					dec(maxLvl);
			end
			else
				break;
		end;

		for i:=0 to sizeCompleted-1 do
		begin
			MarkPath(parent[turnCompleted[i]], false);
			turnCompleted[i] := 0;
		end;
		sizeCompleted := 0;

		inc(res);
	end;

	ComputeQuery := res;
end;

begin
	readln(n, m);

	for i:=0 to m-1 do
		read(q[i]);
	
	for i:=1 to n-1 do
	begin
		read(t[i]);
		dec(t[i]);
		inc(numChild[t[i]]);
		PushBack(adj[t[i]], i);
	end;

	Dfs(0);

	parent[0] := -1;

	origMaxLvl := maxLvl;

	for i:=0 to m-1 do
	begin
		if (i > 0) then
			write(' ');
		write(ComputeQuery(q[i]));
	end;		
	writeln;
end.
