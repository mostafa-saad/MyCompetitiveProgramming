(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Spacer                                        *
 *   Autor:                Wiktor Kuropatwa                              *
 *   Zlozonosc czasowa:    O(n^2 * k)                                    *
 *   Zlozonosc pamieciowa: O(nk)                                         *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************)

const 
	MAXK = 500009;
	HSIZE = 5000011;
	MAXNK = 5000005;
	
var
	forbidden: array[0..MAXK] of Int64;
	fprev: array[0..MAXK] of LongInt;
	fhash: array[0..MAXK] of LongInt;
	visited: array[0..MAXNK] of Int64;
	vprev: array[0..MAXNK] of LongInt;
	vhash: array[0..HSIZE] of LongInt;
	q: array[0..MAXNK] of Int64;
	ffree,vfree,i,n,k,j: LongInt;
	x,y,a,one: Int64;
	
procedure finsert(v: Int64);
begin
	forbidden[ffree] := v;
	fprev[ffree] := fhash[v mod MAXK];
	fhash[v mod MAXK] := ffree;
	ffree := ffree + 1;
end;

function flookup(v: Int64): boolean;
var
temp: LongInt;
begin
	flookup := false;
	temp := fhash[v mod MAXK];
	while temp > 0 do begin
		if forbidden[temp] = v then flookup := true;
		temp := fprev[temp];
	end;
end;

procedure vinsert(v: Int64);
begin
	visited[vfree] := v;
	vprev[vfree] := vhash[v mod HSIZE];
	vhash[v mod HSIZE] := vfree;
	vfree := vfree + 1;
end;

function vlookup(v: Int64): boolean;
var
temp: LongInt;
begin
	vlookup := false;
	temp := vhash[v mod HSIZE];
	while temp > 0 do begin
		if visited[temp] = v then vlookup := true;
		temp := vprev[temp];
	end;
end;

procedure vclear();
begin
	for i:=0 to (HSIZE-1) do
	begin
		vhash[i] := 0;
	end;
	vfree := 1;
end;

function search(s: Int64; t: Int64; bound: LongInt): boolean;
var
b,e,c: LongInt;
v,next: Int64;
begin
	b := 0;
	e := 1;
	q[b] := s;
	c := 1;
	vinsert(s);
	search := false;
	while b < e do begin
		v := q[b];
		b := b + 1;
		for i:=0 to (n-1) do begin
			next := v xor (one shl i);
			if next = t then begin
				search := true;
				break;
			end;
			if (not flookup(next) and (not vlookup(next))) then begin
				q[e] := next;
				e := e+1;
				vinsert(next);
				c := c + 1;
			end;
			if c >= bound then begin
				search := true;
				break;
			end;
		end;
		if search then break;
	end;
end;

function solve(): boolean;
var
a,b: boolean;
bnd: LongInt;
begin
	bnd := n*k + 1;
	a := search(x,y,bnd);
	vclear();
	b := search(y,x,bnd);
	solve := (a and b);
end;

procedure readXY();
var
	buf: string;
	t: Int64;
begin
	readln(buf);
	t := 0;
	for i:=1 to n do begin
		if buf[i] = '1' then t := t + (one shl (n-i));
	end;
	x := t;
	t := 0;
	for i:=1 to n do begin
		if buf[n+i+1] = '1' then t := t + (one shl (n-i));
	end;
	y := t;
end;

function readBinary(): Int64;
var
	buf: string;
	res: Int64;
begin
	readln(buf);
	res := 0;
	for j:= 1 to n do begin
		if buf[j] = '1' then begin
			res := res + (one shl (n-j));
		end;
	end;
	readBinary := res;
end;

procedure input();
begin
	one := 1;
	for i:=0 to (MAXK-1) do begin
		fhash[i] := 0;
	end;
	for i:=0 to (HSIZE-1) do begin
		vhash[i] := 0;
	end;
	ffree := 1;
	vfree := 1;
	read(n);
	readln(k);
	readXY();
	for i:=1 to k do begin
		a := readBinary();
		finsert(a);
	end;
end;

begin
	input();
	if solve() then writeln('TAK') else writeln('NIE');
end.
