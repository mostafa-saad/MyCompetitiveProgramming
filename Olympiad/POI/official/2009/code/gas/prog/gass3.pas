(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Gasnice (GAS)                                             *
 *   Plik:     gas3.pas                                                  *
 *   Autor:    Bartosz Gorski                                            *
 *   Opis:     Rozwiazanie nieefektywne O(n^2)                           *
 *                                                                       *
 *                                                                       *
 *************************************************************************)

const
	nmx = 100000;

var
	n, k ,res, ie, is, a, b, i, q, h, t, f, j, iff : Longint;
	QQ, D, edge, list, stack, free : array [0..nmx-1] of Longint;
	edgeTo, edgeNext, listTo, listNext : array [0..2*nmx-1] of Longint;
	W : array [0..nmx-1] of boolean;
	s, l : int64;

procedure listClear(l : Longint);
var
	i : Longint;
begin
	for i:=0 to l-1 do
		list[i]:=-1;
	iff:=nmx;
	for i:=0 to nmx-1 do
		free[i]:=i;
end;

procedure listAdd(a, b : Longint);
var
	c : Longint;
begin
	c:=free[iff-1];
	Dec(iff);
	listTo[c]:=b;
	listNext[c]:=list[a];
	list[a]:=c;
end;

procedure listRemove(a : Longint);
begin
	if list[a] <> -1 then
	begin
		free[iff]:=list[a];
		Inc(iff);
	end;
	list[a]:=listNext[list[a]];
end;

function listTop(a : Longint) : Longint;
begin
	listTop := listTo[list[a]];
end;

procedure edgeClear(e : Longint);
var
	i : Longint;
begin
	ie:=0;
	for i:=0 to e-1 do
		edge[i]:=-1;
end;

procedure edgeAdd(a, b : Longint);
begin
	edgeTo[ie]:=b;
	edgeNext[ie]:=edge[a];
	edge[a]:=ie;
	Inc(ie);
end;

procedure go(v, f, l : Longint);
var
	t : Longint;
begin
	if l > k then
		exit;
	if not W[v] then
		listAdd(D[v], v);
	t:=edge[v];
	while(t <> -1)do
	begin
		if edgeTo[t] <> f then
			go(edgeTo[t], v, l+1);
		t:=edgeNext[t];
	end;
end;

function min(a, b : Longint) : Longint;
begin
	if a<b then min:=a else min:=b;
end;


function max(a, b : Longint) : Longint;
begin
	if a>b then max:=a else max:=b;
end;

begin
	read(n,s,k);
	listClear(n);
	edgeClear(n);
	for i:=0 to n-1 do
	begin
		QQ[i]:=0;
		D[i]:=0;
		W[i]:=false;
	end;
	for i:=0 to n-2 do
	begin
		read(a,b);
		Dec(a); Dec(b);
		edgeAdd(a,b);
		edgeAdd(b,a);
	end;
	h:=0;
	q:=1;
	while(h<n)do
	begin
		a:=QQ[h];
		Inc(h);
		t:=edge[a];
		while(t <> -1)do
		begin
			if((edgeTo[t]>0) and (D[edgeTo[t]]=0)) then
			begin
				D[edgeTo[t]]:=D[a]+1;
				QQ[q]:=edgeTo[t];
				Inc(q);
			end;
			t:=edgeNext[t];
		end;
	end;
	res:=0;
	for i:=n-1 downto 0 do
	begin
		a:=QQ[i];
		go(a,-1,0);
		f:=min(D[a]+k,n-1);
		t:=max(0,D[a]-k);
		is:=0;
		for j:=t to f do
			while(list[j] <> -1)do
			begin
				stack[is]:=listTop(j);
				Inc(is);
				listRemove(j);
			end;
		while((is>0) and (D[stack[is-1]]=(D[a]+k)))do
		begin
			Inc(res);
			j:=0;
			while((j<s) and (is>0))do
			begin
				W[stack[is-1]]:=true;
				Dec(is);
				Inc(j);
			end;
		end;
	end;
	l:=0;
	for i:=0 to n-1 do
		if not W[i] then
			Inc(l);
	res:=res+Longint((l+s-1) div s);
	writeln(res);
end.
