(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Rajd                                          *
 *   Autor:                Karol Farbis                                  *
 *   Zlozonosc czasowa:    O(m + 2^n * n)                                *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Znajdowanie wszystkich sciezek                *
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
	ret : array[1..N] of longint;
	st : array[1..N] of boolean;


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

procedure dfs(v,l,n : longint);
var
	i : longint;
	it : nodep;
begin
	st[v] := True;

	for i:=1 to n do
		if not st[i] then
			ret[i] := max(ret[i], l);

	it := G[v].head;
	while it <> nil do begin
		dfs(it^.key, l+1, n);
		it := it^.next;
	end;

	st[v] := False;
end;

procedure main;
var
	n, m, i, a, b, me : longint;
begin
	readln(n, m);
	for i := 1 to m do begin
		readln(a, b);
		add_edge(a,b);
	end;

	for i:=1 to n do
		dfs(i, 0, n);

	me := 1;
	for i := 2 to n do
		if ret[i] < ret[me] then
			me := i;
	writeln(me, ' ', ret[me]);

end;

begin
	main
end.
