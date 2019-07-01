(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Luk triumfalny                                *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************)

const
	MAXN = 1000001;

type
	TNode = ^TList;
	TList = record
		value: longint;
		next: TNode;
	end;

var
	adj, firstNode: array[0..MAXN] of TNode;
	N, answ, i, u, v: longint;
	visited: array[0..MAXN] of boolean;

procedure PushBack(u, value: longint);
var
	tmpNode: TNode;
begin
	New(tmpNode);
	tmpNode^.value := value;
	tmpNode^.next := adj[u];
	firstNode[u] := tmpNode;
	adj[u] := tmpNode;
end;

function Next(u: longint): longint;
begin
	if (adj[u] = nil) then
		Next := -1
	else
	begin
		Next := adj[u]^.value;
		adj[u] := adj[u]^.next;
	end;
end;

function Max(a, b: longint): longint;
begin
	if (a < b) then
		Max := b
	else
		Max := a;
end;

procedure ResetPtr(u: longint);
begin
	adj[u] := firstNode[u];
end;

function Check(u, k: longint): longint;
var
	v, numChildren, sumTree: longint;
begin
	numChildren := 0;
	sumTree := 0;
	visited[u] := true;

	while (true) do
	begin
		v := Next(u);
		if (v = -1) then
			break;

		if (not visited[v]) then
		begin
			inc(sumTree, Check(v, k));
			inc(numChildren);
		end;
	end;

	Check := Max(0, numChildren+sumTree-k);
end;

begin
	readln(N);

	for i:=0 to N-2 do
	begin
		readln(u, v);
		dec(u);
		dec(v);
		PushBack(u, v);
		PushBack(v, u);
	end;

	for answ := 0 to N do
	begin
		for i := 0 to N-1 do
		begin
			ResetPtr(i);
			visited[i] := false;
		end;

		if (Check(0, answ) = 0) then
		begin
			writeln(answ);
			break;
		end;
	end;
end.
