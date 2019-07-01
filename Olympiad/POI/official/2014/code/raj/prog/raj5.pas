(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Rajd                                          *
 *   Autor:                Karol Farbis                                  *
 *   Zlozonosc czasowa:    O(m log n + n)                                *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                         Rekurencyjne sortowanie topologiczne          *
 *                                                                       *
 *************************************************************************)

program raj;

const
	N = 500 * 1000;
	PN = 1 shl 19;
	M = 1000 * 1000;

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
	topor : array[1..N] of longint;
	indeg : array[1..N] of longint;
	maxin : array[1..N] of longint;
	maxout : array[1..N] of longint;
	res : array[1..N] of longint;

	tree : array[1..2*PN] of longint;

	vis : array[1..N] of boolean;
	order : longint;

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

procedure dfs(v : longint);
var
	it : nodep;
begin
	vis[v] := true;

	it := G[v].head;
	while it <> nil do begin
		if not vis[it^.key] then
			dfs(it^.key);
		it := it^.next
	end;
	topor[v] := order;
	topo[order] := v;
	dec(order)
end;

procedure toposort(n : longint);
var
	i : longint;
begin
	order := n;
	for i:=1 to n do
		if not vis[i] then
			dfs(i);
end;

procedure _tree_set(ss, ee, s, e, x, v: longint);
var
	m : longint;
begin
	if (ee < s) or (e < ss) then exit;
	if (s <= ss) and (ee <= e) then begin
		tree[x] := max(tree[x], v);
		exit
	end;
	m := (ss + ee) div 2;
	_tree_set(ss, m, s, e, 2*x, v);
	_tree_set(m+1, ee, s, e, 2*x+1, v);
end;

procedure tree_set(s, e, v: longint);
begin
	_tree_set(1, PN, s, e, 1, v)
end;

function tree_get(x : longint) : longint;
var
	ret : longint;
begin
	x := x + PN - 1;
	ret := 0;
	while x <> 0 do begin
		ret := max(ret, tree[x]);
		x := x div 2
	end;
	tree_get := ret;
end;

procedure main;
var
	n, m, i, a, b, v, u, pmax, smax, me : longint;
	it : nodep;
begin
	readln(n, m);
	for i := 1 to m do begin
		readln(a, b);
		add_edge(a,b);
		inc(indeg[b])
	end;

	toposort(n);
	
	for i := 1 to n do begin
		v := topo[i];
		it := G[v].head;
		while it <> nil do begin
			maxin[it^.key] := max(maxin[it^.key], maxin[v] + 1);
			it := it^.next;
		end
	end;

	for i := n downto 1 do begin
		v := topo[i];
		it := G[v].head;
		while it <> nil do begin
			maxout[v] := max(maxout[v], maxout[it^.key] + 1);
			it := it^.next;
		end
	end;

	for v := 1 to n do begin
		it := G[v].head;
		while it <> nil do begin
			u := it^.key;
			if topor[u] > topor[v] + 1 then
				tree_set(topor[v] + 1, topor[u] - 1, maxin[v] + 1 + maxout[u]);
			it := it^.next;
		end;
	end;

	for i := 1 to n do begin
		res[i] := tree_get(topor[i]);
	end;

	pmax := 0;
	for i := 2 to n do begin
		pmax := max(pmax, maxin[topo[i-1]]);
		res[topo[i]] := max(res[topo[i]], pmax)
	end;

	smax := 0;
	for i := n-1 downto 1 do begin
		smax := max(smax, maxout[topo[i+1]]);
		res[topo[i]] := max(res[topo[i]], smax)
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
