(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Cennik                                        *
 *   Autor:                Karol Pokorski                                *
 *   Opis:                 Rozwiazanie powolne, wzorcowka bez usuwania   *
 *                         niepotrzebnych krawedzi po ich przejrzeniu    *
 *                                                                       *
 *************************************************************************)

const
	MAXN = 100001;
	MAXM = 100001;
	HASHT = 1000007;
	INF = 1000000001;

type
	TState = record
		u, v: longint;
		dist: int64;
	end;

	TNode = ^TList;
	
	TList = record
		value: int64;
		next: TNode;
		prev: TNode;
	end;

var
	adj, sadj: array[0..MAXN] of TNode;
	hashTab: array[0..HASHT] of TNode;
	q: array[0..4*MAXN] of TState;
	d1, d2: array[0..MAXN] of int64;
	vis1, vis2: array[0..MAXN] of boolean;
	n, m, s, x, i, qSize, qStart, dist: longint;
	hashHH, hashII, e1, e2, u, v: int64;
	iter: TNode;
	curState: TState;

procedure Swap(var a, b: int64);
var
	c: int64;
begin
	c := a;
	a := b;
	b := c;
end;

function ReadIter(var node: TNode): int64;
begin
	if (node = nil) then
		ReadIter := -1
	else if (node^.value = -2) then
		ReadIter := ReadIter(node^.next)
	else
		ReadIter := node^.value;
end;
	
procedure PushBack(var node: TNode; value: int64);
var
	tmpNode: TNode;
begin
	New(tmpNode);
	tmpNode^.value := value;
	tmpNode^.prev := nil;
	tmpNode^.next := nil;
	if (node <> nil) then
	begin
		tmpNode^.next := node;
		node^.prev := tmpNode;
	end;
	node := tmpNode;
end;

procedure Next(var iter: TNode);
begin
	if (iter <> nil) then
		iter := iter^.next;
end;

function TStateCons(a, b, c: longint): TState;
var
	state: TState;
begin
	state.u := a;
	state.v := b;
	state.dist := c;
	TStateCons := state;
end;

procedure QPush(value: TState);
begin
	q[qSize] := value;
	Inc(qSize);
end;

function QPop(): TState;
begin
	QPop := q[qStart];
	Inc(qStart);
end;

function QEmpty(): boolean;
begin
	if (qStart = qSize) then
		QEmpty := true
	else
		QEmpty := false;
end;

function Min(a, b: int64): int64;
begin
	if (a < b) then
		Min := a
	else
		Min := b;
end;

procedure PrintList(iter: TNode);
begin
	while (ReadIter(iter) <> -1) do
	begin
		write(ReadIter(iter), ' ');
		Next(iter);
	end;
	writeln;
end;

function CheckExistence(a, b: longint): boolean;
var
	hash, hashI, x, aa, bb: int64;
	it: TNode;
	res: boolean;
begin
	aa := a;
	bb := b;

	if (aa > bb) then
		Swap(aa, bb);

	res := false;
	hash := (aa*MAXN+bb);
	hashI := hash mod HASHT;

	it := hashTab[hashI];
	while (true) do
	begin
		x := ReadIter(it);
		if (x = -1) then
			break;
		if (x = hash) then
		begin
			res := true;
			break;
		end;
		Next(it);
	end;

	CheckExistence := res;
end;

begin
	readln(n, m, s, e1, e2);
	dec(s);

	for i:=0 to n-1 do
	begin
		adj[i] := nil;
		sadj[i] := nil;
	end;

	for i:=0 to n-1 do
	begin
		PushBack(adj[i], -1);
		PushBack(sadj[i], -1);
	end;

	for i:=0 to HASHT-1 do
		hashTab[i] := nil;

	for i:=0 to m-1 do
	begin
		readln(u, v);
		dec(u);
		dec(v);

		PushBack(adj[u], v);
		PushBack(adj[v], u);
		PushBack(sadj[u], v);
		PushBack(sadj[v], u);

		if (u > v) then
			Swap(u, v);

		hashHH := (u*MAXN+v);
		hashII := hashHH mod HASHT;
		PushBack(hashTab[hashII], hashHH);
	end;

	for i:=0 to n-1 do
	begin
		PushBack(adj[i], -2);
		PushBack(sadj[i], -2);
	end;

	for i:=0 to n-1 do
	begin
		d1[i] := INF;
		d2[i] := INF;
	end;

	vis1[s] := true;
	d1[s] := 0;

	QPush(TStateCons(s, -1, 0));
	while (not QEmpty()) do
	begin
		curState := QPop();
		u := curState.u;
		v := curState.v;
		dist := curState.dist;
		iter := adj[u];

		Next(iter);

		while (true) do
		begin
			x := ReadIter(iter);
			if (x = -1) then
				break;
			
			if (not vis1[x]) then
			begin
				QPush(TStateCons(x, 0, dist+1));
				d1[x] := dist+1;
				vis1[x] := true;
			end;
			Next(iter);
		end;
	end;

	vis2[s] := true;
	d2[s] := 0;

	QPush(TStateCons(s, -1, 0));
	while (not QEmpty()) do
	begin
		curState := QPop();
		u := curState.u;
		v := curState.v;
		dist := curState.dist;

		if (v = -1) then
		begin
			iter := adj[u];

			Next(iter);
			
			while (true) do
			begin
				x := ReadIter(iter);
				if (x = -1) then
					break;
				QPush(TStateCons(x, u, dist+1));
				Next(iter);
			end;
		end
		else
		begin
			iter := sadj[u];

			Next(iter);

			while (true) do
			begin
				x := ReadIter(iter);

				if (x = -1) then
					break;

				if ((not vis2[x]) and (not CheckExistence(v, x))) then
				begin
					QPush(TStateCons(x, -1, dist+1));
					d2[x] := dist+1;
					vis2[x] := true;
				end;

				Next(iter);
			end;
		end;
	end;

	for i:=0 to n-1 do
	begin
		if (d1[i] mod 2 = 0) then
			writeln(Min(d1[i]*e1, (d1[i] div 2)*e2))
		else
			writeln(Min(Min(d1[i]*e1, (d1[i] div 2)*e2+e1), (d2[i] div 2)*e2));
	end;
end.
