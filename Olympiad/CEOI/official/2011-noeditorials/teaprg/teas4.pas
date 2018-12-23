{ TEA - O(n^2) solution }

program teas3;

const
	MAXN = 1000005;
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
	cnt: longint;
	a: array[0..MAXN] of pair;
	grsize: array[0..MAXN] of longint;
	bucket: array[0..MAXN+100] of wskList;
	it: wskNode;
	R, S: array[0..MAXN] of longint;

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

function max(a, b: longint): longint;
begin
	if a > b then max := a else max := b;
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
	for i:=0 to n-1 do R[i] := 0;
	for i:=0 to n-1 do
	begin
		if i-a[i].first >= -1 then
		begin
			R[i] := 1;
			S[i] := i+1;
			grsize[i] := i+1;
		end;
		for j := i-a[i].first downto 0 do
		begin
			if R[j]>0 then
			begin
				if R[j]+1>R[i] then
				begin
					R[i] := R[j] + 1;
					S[i] := 0;
				end;
				if (R[i] = R[j]+1) and ((max(S[j],i-j)<S[i]) or (S[i]=0)) then
				begin
					S[i] := max(S[j],i-j);
					grsize[i] := i-j;
				end;
			end;
		end;
	end;
	writeln(R[n-1]);
	i := n-1;
	while i>=0 do
	begin
		write(grsize[i]);
		for j:=i downto i-grsize[i]+1 do
			write(' ',a[j].second+1);
		writeln;
		i := i - grsize[i];
	end;
end.
