(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Piorunochron                                     *
 *   Autor:             Jakub Pachocki                                   *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************)

uses Math;

const maxN = 500000;
const sN = 720;

var sqt:Array[0..maxN] of double;
var h:Array[0..maxN] of longint;

var hMax:longint;

var n:longint;

function findL(a, b:longint):longint;
var
	l,r,c:longint;
begin
	l := b;
	r := n + 1;
	while l < r do
	begin
		c := (l + r) div 2;
		if h[a] + sqt[abs(a - c)] >= h[b] + sqt[abs(b - c)] then
			l := c + 1
		else
			r := c
	end;
	findL := l
end;

var s,l:Array[0..sN] of longint;
var ss:longint;

var res:Array[0..maxN] of longint;


procedure find();
var
	i,r,prev:longint;
begin
	ss := 0;
  s[0] := 0;
  h[0] := -1000000;
	prev := hMax - ceil(sqt[n]) - 1;
	for i := 1 to n do
	begin
		if h[i] > prev then
		begin
			prev := h[i];
			while (ss >= 1) and (findL(s[ss], i) <= l[ss]) do
				ss := ss - 1;
			l[ss + 1] := findL(s[ss], i);
			if (l[ss + 1] <= n) then
			begin
				ss := ss + 1;
				s[ss] := i;
			end;
		end;
	end;
	r := n;
	for i := ss downto 1 do
	begin
		while r >= l[i] do
		begin
			res[r] := max(res[r], h[s[i]] - h[r] + ceil(sqt[abs(s[i] - r)]));
			r := r - 1;
		end
	end
end;

procedure reverse(var t:array of longint);
var
	i,temp:longint;
begin
	for i := 1 to (n div 2) do
	begin
		temp := t[n - i + 1];
		t[n - i + 1] := t[i];
		t[i] := temp
	end
end;

var i:longint;

begin
	read(n);
	hMax := 0;
	for i := 1 to n do
	begin
		read(h[i]);
		hMax := max(hMax, h[i]);
	end;
	for i := 0 to n do
		sqt[i] := sqrt(i);
	find();
	reverse(h);
	reverse(res);
	find();
	reverse(res);
	for i := 1 to n do
		writeln(res[i])
end.
