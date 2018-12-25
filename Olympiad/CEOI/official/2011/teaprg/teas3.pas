{ TEA - O(n(log^2)n) solution }

program teas3;

const
	MAXN = 1000005;
	MM = 1 shl 20;
	INF = 1000000000;

type pair = record
	first: longint;
	second: longint;
end;

type
	wskNode = ^node;
	node = record
		value: pair;
		next: wskNode;
end;

type list = record
	head, tail: ^node;
end;

type wskList = ^list;

var
	n: longint;
	i, j: longint;
	a: array[0..MAXN] of pair;
	best: longint;
	l, u, r, m: longint;
	cur: longint;
	grsize: array[0..MAXN] of longint;
	tree: array[0..2*MM] of pair;
	bucket: array[0..MAXN+100] of wskList;
	cnt: longint;
	it: wskNode;

function new_list: wskList;
var
	res: wskList;
begin
	new(res);
	res^.head := nil;
	res^.tail := nil;
	new_list := res;
end;

function make_node(x: pair): wskNode;
var
	res: ^node;
begin
	new(res);
	res^.value := x;
	res^.next := nil;
	make_node := res;
end;

procedure add_to_list(l: wskList; x: pair);
var
	tmp: ^node;
begin
	if l^.tail = nil then
	begin
		tmp := make_node(x);
		l^.head := tmp;
		l^.tail := tmp;
	end
	else
	begin
		tmp := make_node(x);
		l^.tail^.next := tmp;
		l^.tail := tmp;
	end;
end;

function make_pair(a, b: longint): pair;
var
	res: pair;
begin
	res.first := a;
	res.second := b;
	make_pair := res;
end;

function max(a, b: pair): pair;
begin
	if a.first > b.first then
		max := a
	else
		max := b;
end;

function get(a, b: longint): pair;
var
	res: pair;
begin
	if b<a then get := make_pair(-INF, -1)
	else
	begin
		a := a + MM;
		b := b + MM;
		res := max(tree[a], tree[b]);
		while (a div 2) <> (b div 2) do
		begin
			if a mod 2 = 0 then res := max(res, tree[a+1]);
			if b mod 2 = 1 then res := max(res, tree[b-1]);
			a := a div 2;
			b := b div 2;
		end;
		get := res;
	end;
end;

procedure add(u, x: longint);
begin
	u := u + MM;
	tree[u] := make_pair(x, u-MM);
	while u div 2 > 0 do
	begin
		u := u div 2;
		tree[u] := max(tree[2*u], tree[2*u+1]);
	end;
end;

procedure clear;
var
	i: longint;
begin
	for i:=0 to 2*MM do
		tree[i] := make_pair(-INF, -1);
end;

function calc(limit: longint): longint;
var
	i: longint;
	p: pair;
	l, r: longint;
begin
	clear;
	for i:=0 to n-1 do
	begin
		r := i-a[i].first;
		l := i-limit;
		if l < 0 then l := 0;
		p := get(l, r);
		{writeln('get ', l, '  ', r, '  = ', p.first);}
		if p.first <> -INF then
		begin
			grsize[i] := i-p.second;
			add(i, p.first+1);
		end
		else
		begin
			if (i+1 >= a[i].first) and (i+1 <= limit) then
			begin
				grsize[i] := i+1;
				add(i, 1);
			end
			else
				grsize[i] := -1;
		end;
	end;
	calc := tree[n-1+MM].first;
end;

begin
	for i:=0 to MAXN do
		bucket[i] := new_list;
	read(n);
	for i:=0 to n-1 do
	begin
		read(a[i].first);
		a[i].second := i;
		add_to_list(bucket[a[i].first], a[i]);
	end;
	cnt := 0;
	for i:=0 to MAXN do
	begin
		{write('i = ');
		writeln(i);}
		it := bucket[i]^.head;
		while it <> nil do
		begin
			{writeln('dodaje');}
			a[cnt] := it^.value;
			inc(cnt);
			it := it^.next;
		end;
	end;
	{for i:=0 to n-1 do
	begin
		write(a[i].first);
		write('   ');
		write(a[i].second);
		writeln;
	end;}
	best := calc(n);
	{write('best = ');
	writeln(best);}
	l := 1;
	u := n;
	r := -1;
	while l<=u do
	begin
		m := (l+u) div 2;
		cur := calc(m);
		if cur = best then
		begin
			r := m;
			u := m-1;
		end
		else
			l := m+1;
	end;
	calc(r);
	writeln(best);
	i := n-1;
	while i>=0 do
	begin
		write(grsize[i]);
		for j:=i downto i-grsize[i]+1 do
		begin
			write(' ');
			write(a[j].second+1);
		end;
		writeln;
		i := i - grsize[i];
	end;
end.
