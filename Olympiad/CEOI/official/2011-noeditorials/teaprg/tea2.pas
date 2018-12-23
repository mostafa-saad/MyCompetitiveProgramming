{ Task TEA, O(n) solution, Dawid Dabrowski }

const
	MAXN = 1000005;

type pair = record
	first: longint;
	second: longint;
end;

type 
	wskPairNode = ^pairNode;
	pairNode = record
		value: pair;
		next: wskPairNode;
end;

type 
	wskNode = ^node;
	node = record
		value: longint;
		next: wskNode;
end;

type list = record
	head, tail: ^node
end;

type pairList = record
	head, tail: ^pairNode;
end;

type wskList = ^list;
type wskPairList = ^pairList;

function new_list: wskList;
var
	res: wskList;
begin
	new(res);
	res^.head := nil;
	res^. tail := nil;
	new_list := res;
end;

function make_node(x: longint): wskNode;
var
	res: ^node;
begin
	new(res);
	res^.value := x;
	res^.next := nil;
	make_node := res;
end;

function new_pair_list: wskPairList;
var
	res: wskPairList;
begin
	new(res);
	res^.head := nil;
	res^. tail := nil;
	new_pair_list := res;
end;

function make_pair_node(x: pair): wskPairNode;
var
	res: ^pairNode;
begin
	new(res);
	res^.value := x;
	res^.next := nil;
	make_pair_node := res;
end;

procedure add_to_list(l: wskList; x: longint);
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

procedure add_to_pair_list(l: wskPairList; x: pair);
var
	tmp: ^pairNode;
begin
	if l^.tail = nil then
	begin
		tmp := make_pair_node(x);
		l^.head := tmp;
		l^.tail := tmp;
	end
	else
	begin
		tmp := make_pair_node(x);
		l^.tail^.next := tmp;
		l^.tail := tmp;
	end;
end;
{
function size(l: wskList): longint;
var
	res: longint;
	it: wskNode;
begin
	res := 0;
	it := l^.head;
	while it<>nil do
	begin
		inc(res);
		it := it^.next;
	end;
	size := res;
end;
}
function max(a, b: longint): longint;
begin
	if a > b then max := a else max := b;
end;

var
	n: longint;
	i, j,cur: longint;
	mnsize: longint;
	a: array[0..MAXN] of pair;
	grsize: array[0..MAXN] of longint;
	R, S: array[0..MAXN] of longint;
	res: array[0..MAXN] of wskList;
	wielk: array[0..MAXN] of longint;
	t: array[0..MAXN] of wskList;
	size: array[0..MAXN] of longint;
	resSize: longint;
	bucket: array[0..MAXN+100] of wskPairList;
	buckets: array[0..MAXN+100] of wskList;
	cnt: longint;
	it: ^pairNode;
	it2: ^node;
	tmpmin: longint;
	stack: array[0..MAXN] of longint;
	top: longint;
	tmp: pair;
	zm1, zm2, zm3: int64;

procedure reconstruct;
var
	ps: longint;
	i, j, k: longint;
begin
	mnsize := 0;
	for i:=0 to MAXN do
	begin
		res[i] := new_list;
		wielk[i] := 0;
	end;
	top := -1;
	ps := n;
	while ps >= 1 do
	begin
		inc(top);
		stack[top] := ps;
		if R[ps] = 1 then break;
		if grsize[ps] = -1 then dec(ps) else ps := ps - grsize[ps];
	end;
		for k := top downto 0 do
		begin
			i := stack[k];
			if R[i] = 1 then
			begin
				t[resSize] := new_list;
				for j:=1 to i do
				begin
					add_to_list(t[resSize], a[j].first);
					inc(size[resSize]);
				end;
				add_to_list(res[size[resSize]], resSize);
				inc(wielk[size[resSize]]);
				if size[resSize] < mnsize then mnsize := size[resSize];
				inc(resSize);
			end
			else
			begin
				if grsize[i] = -1 then
				begin
					while wielk[mnsize] = 0 do
					begin
						inc(mnsize);
					end;
					{writeln('mnsize = ', mnsize);
					writeln('head = ', res[mnsize]^.head^.value);}
					add_to_list(t[res[mnsize]^.head^.value], a[i].first);
					{writeln('dodalem');}
					inc(size[res[mnsize]^.head^.value]);
					dec(wielk[mnsize]);
					add_to_list(res[mnsize+1], res[mnsize]^.head^.value);
					{writeln('debug   ', res[mnsize+1]^.head^.value);}
					if res[mnsize]^.head = res[mnsize]^.tail then
						begin
							res[mnsize]^.head := nil;
							res[mnsize]^.tail := nil;
						end
						else res[mnsize]^.head := res[mnsize]^.head^.next;
					inc(wielk[mnsize+1]);
					{writeln('przepisalem do ',mnsize+1,'   wielk = ',wielk[mnsize+1]); }
				end
				else
				begin
					t[resSize] := new_list;
					for j:=i-grsize[i]+1 to i do
					begin
						add_to_list(t[resSize],a[j].first);
						inc(size[resSize]);
					end;
					add_to_list(res[size[resSize]], resSize);
					inc(wielk[size[resSize]]);
					if size[resSize] < mnsize then mnsize := size[resSize];
					inc(resSize);
				end
			end
		end;
end;

begin
	mnsize := -1;
	top := -1;
	for i:=0 to MAXN do
		bucket[i] := new_pair_list;
	read(n);
	for i:=1 to n do
	begin
		read(a[i].first);
		a[i].second := i;
		add_to_pair_list(bucket[a[i].first], a[i]);
	end;
	cnt := 0;
	for i:=0 to MAXN do
	begin
		it := bucket[i]^.head;
		while it <> nil do
		begin
			inc(cnt);
			a[cnt] := it^.value;
			it := it^.next;
		end;
	end;
	for i := 1 to (cnt div 2) do
	begin
		tmp := a[i];
		a[i] := a[n-i+1];
		a[n-i+1] := tmp;
	end;
	for i := 1 to n do
	begin
		j := a[i].first;
		a[i].first := a[i].second;
		a[i].second := j;
	end;
	{for i := 1 to cnt do
	begin
		write(a[i].first,' ');
	end;
	writeln;}
	R[a[1].second] := 1;
	S[a[1].second] := a[1].second;
	for i := 0 to MAXN do buckets[i] := new_list;
	for i := a[1].second+1 to n do
	begin
		if i+a[i].second < MAXN then add_to_list(buckets[i+a[i].second],i);
		S[i] := MAXN;
		R[i] := 0;
		tmpmin := MAXN;
		it2 := buckets[i+1]^.head;
		while it2<>nil do
		begin
			cur := it2^.value;
			if R[cur-1] = R[i-1] then
			begin
				R[i] := R[i-1] + 1;
				if S[i] > max(S[cur-1], a[cur].second) then
				begin
					S[i] := max(S[cur-1], a[cur].second);
					grsize[i] := i-cur+1;
				end
			end
			else
			begin
				if (R[cur-1] = R[i-1]-1) and (S[i] = MAXN) then
				begin
					if tmpmin > max(S[cur-1], a[cur].second) then
					begin
						tmpmin := max(S[cur-1], a[cur].second);
						grsize[i] := i-cur+1;
					end
				end
			end;
			it2 := it2^.next;
		end;
		if R[i] = 0 then
		begin
			R[i] := R[i-1];
			S[i] := tmpmin;
			zm1 := R[i-1];
			zm2 := S[i-1];
			zm3 := i-1;
			if zm1*zm2 = zm3 then
			begin
				if S[i-1]+1<tmpmin then
				begin
					S[i] := S[i-1]+1;
					grsize[i] := S[i-1]+1;
				end;
			end
			else
			begin
				if S[i-1]<tmpmin then
				begin
					S[i] := S[i-1];
					grsize[i] := -1;
				end;
			end;
		end;
	end;
	writeln(R[n]);
	reconstruct;
		for i:=0 to resSize-1 do
		begin
			write(size[i]);
			it2 := t[i]^.head;
			while it2<>nil do
			begin
				write(' ', it2^.value);
				it2 := it2^.next;
			end;
			writeln;
		end;
end.
