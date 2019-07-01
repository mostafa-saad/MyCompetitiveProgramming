(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Rajd                                          *
 *   Autor:                Karol Farbis                                  *
 *   Zlozonosc czasowa:    O(n(n+m))                                     *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************)

program raj;

const
	N = 500 * 1000;

type
	nodep = ^node;
	node = record
		key : longint;
		next : nodep;
	end;

	list = record
		head : nodep;
		tail : nodep;
	end;
var
	G : array[1..N] of list;
	topo : array[1..N] of longint;
	indeg : array[1..N] of longint;
	res : array[1..N] of longint;
	dp : array[1..N] of longint;

function min(a, b: longint) : longint;
begin
	min := a;
	if b < a then min := b;
end;

function max(a, b: longint) : longint;
begin
	max := a;
	if b > a then max := b;
end;

procedure push_list(var l : list; k : longint);
var
	elem : nodep;
begin
	new(elem);
	elem^.key := k;

	if l.head = nil then begin
		l.head := elem;
		l.tail := elem;
	end else begin
		l.tail^.next := elem;
		l.tail := elem;
	end
end;

function pop_list(var l: list) : longint;
var
	tmp : nodep;
begin
	pop_list := l.head^.key;
	tmp := l.head;
	l.head := l.head^.next;
	dispose(tmp);
end;

function empty_list(var l: list) : boolean;
begin
	empty_list := l.head = nil;
end;

procedure add_edge(u, v: longint);
begin
	push_list(G[u], v);
end;

procedure toposort(n : longint);
var
	i : longint;
	nr : longint;
	v : longint;
	queue : list;
	it : nodep;
begin
	queue.head := nil;
	for i := 1 to n do
		if indeg[i] = 0 then begin
			push_list(queue, i);
		end;

	nr := 0;
	while not empty_list(queue) do begin
		v := pop_list(queue);
		nr := nr + 1;
		topo[nr] := v;

		it := G[v].head;

		while it <> nil do begin
			dec(indeg[it^.key]);
			if indeg[it^.key] = 0 then
				push_list(queue, it^.key);
			it := it^.next;
		end
	end
end;

function calc(k, n : longint) : longint;
var
	i, v, me: longint;
	it : nodep;
begin
	for i := 1 to n do dp[i] := 0;
	for i := 1 to n do begin
		v := topo[i];
		if v = k then dp[v] := -n;
		it := G[v].head;
		while it <> nil do begin
			dp[it^.key] := max(dp[it^.key], dp[v]+1);
			it := it^.next;
		end;
	end;
	me := 1;
	for i := 2 to n do
		if dp[me] < dp[i] then
			me := i;

	calc := dp[me];
end;

procedure main;
var
	n, m, i, a, b, me: longint;
begin
	readln(n, m);
	for i := 1 to m do begin
		readln(a, b);
		add_edge(a,b);
		inc(indeg[b])
	end;

	toposort(n);
	
	for i := 1 to n do begin
		res[i] := calc(i, n);
	end;

	me := 1;
	for i := 2 to n do
		if res[i] < res[me] then
			me := i;
	writeln(me, ' ', res[me]);

end;

begin
	main
end.
