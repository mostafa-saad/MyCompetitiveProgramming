(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Superkomputer                                 *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O(qn log n)                                   *
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
	n, m, i, heapSize, origHeapSize: longint;
	t, d, parent, childCompleted, turnCompleted, numChild, posHeap, heap, origPos, origHeap, origD, resetD: array[0..MAXN] of longint;
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

procedure SwapVal(var x: longint; var y: longint);
var
	tmp: longint;
begin
	tmp := x;
	x := y;
	y := tmp;
end;

procedure HeapSwap(u: longint; v: longint);
begin
	SwapVal(posHeap[heap[u]], posHeap[heap[v]]);
	SwapVal(heap[u], heap[v]);
end;

procedure Heapify(u: longint);
begin
	if (d[heap[u]] > d[heap[(u-1) div 2]]) then
	begin
		HeapSwap(u, (u-1) div 2);
		Heapify((u-1) div 2);
	end;
end;

procedure DecreaseKey(u: longint; value: longint);
begin
	d[u] := value;
	Heapify(posHeap[u]);
end;

procedure EraseHeap;
var
	posit: longint;
begin
	posit := 0;

	HeapSwap(0, heapSize-1);
	dec(heapSize);

	while (2*posit+1 < heapSize) do
	begin
		if ((2*posit+2 >= heapSize) or (d[heap[2*posit+1]] >= d[heap[2*posit+2]])) then
		begin
			if (d[heap[posit]] < d[heap[2*posit+1]]) then
			begin
				HeapSwap(posit, 2*posit+1);
				posit := 2*posit+1;
			end
			else
				break;
		end
		else if (d[heap[posit]] < d[heap[2*posit+2]]) then
		begin
			HeapSwap(posit, 2*posit+2);
			posit := 2*posit+2;
		end
		else
			break;
	end;
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
end;

function ComputeQuery(maxTurn: longint): longint;
var
	i, res, numCompleted, u, sizeTurn: longint;
begin
	numCompleted := 0;
	res := 0;
	sizeTurn := 0;

	for i:=0 to n-1 do
	begin
		childCompleted[i] := 0;
		heap[i] := origHeap[i];
		posHeap[i] := origPos[i];
		d[i] := resetD[i];
	end;
	heapSize := origHeapSize;
	
	while (numCompleted < n) do
	begin
		for i:=0 to sizeTurn-1 do
		begin
			DecreaseKey(turnCompleted[i], origD[turnCompleted[i]]);
			turnCompleted[i] := 0;
		end;
		sizeTurn := 0;

		for i:=0 to maxTurn-1 do
		begin
			if (heapSize = 0) then
				break;

			u := heap[0];

			if (d[u] = -1) then
				break;

			EraseHeap();

			if (u <> 0) then
			begin
				inc(childCompleted[parent[u]]);

				if (childCompleted[parent[u]] = numChild[parent[u]]) then
				begin
					turnCompleted[sizeTurn] := parent[u];
					inc(sizeTurn);
				end;
			end;

			inc(numCompleted);
		end;

		inc(res);
	end;

	ComputeQuery := res;
end;

begin
	heapSize := 0;
	origHeapSize := 0;

	readln(n, m);

	for i:=0 to n-1 do
		numChild[i] := 0;

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

	for i:=0 to n-1 do
	begin
		inc(heapSize);
		inc(origHeapSize);

		if (numChild[i] = 0) then
			resetD[i] := d[i]
		else
			resetD[i] := -1;
		origD[i] := d[i];
		d[i] := resetD[i];
		heap[i] := i;
		posHeap[i] := i;

		Heapify(i);
	end;

	for i:=0 to n-1 do
	begin
		origHeap[i] := heap[i];
		origPos[i] := posHeap[i];
	end;

	parent[0] := -1;

	for i:=0 to m-1 do
	begin
		if (i > 0) then
			write(' ');
		write(ComputeQuery(q[i]));
	end;		
	writeln;
end.
