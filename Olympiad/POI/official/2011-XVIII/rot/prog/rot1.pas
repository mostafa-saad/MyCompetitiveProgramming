(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Rotacje na drzewie                               *
 *   Autor:             Adam Karczmarz                                   *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *   Zlozonosc czasowa: O(n*lg^2(n))                                     *
 *                                                                       *
 *************************************************************************)

program rot;
uses math;

type node_ptr = ^node;
node = record
	left, right, prev : node_ptr;
	sz, mn : longint;
	inv : Int64;
end;

var p : array[1..200100] of node_ptr;
var cnt : array[1..200100] of longint;
var cur, MX, i : longint;
var root, tmp : node_ptr;

// drzewo potegowe
function get(x: longint) : longint;
begin
	get:=0;
	while x>0 do begin
		get:=get+cnt[x];
		x:=x-(x and (-x))
	end;
end;

procedure ins(x : longint; v : longint);
begin
	while x<=MX do begin
		cnt[x]:=cnt[x]+v;
		x:=x+(x and (-x))
	end;
end;

// wczytywanie danych
procedure read_input(tr : node_ptr);
var c : longint;
begin
	Read(c); tr^.inv:=0;
	if c<>0 then begin
		tr^.sz:=1; Inc(cur);
		tr^.mn:=cur; 
		p[c]:=tr;
	end
	else begin
		New(tr^.left); New(tr^.right);
		read_input(tr^.left); read_input(tr^.right);
		tr^.mn:=tr^.left^.mn;
		tr^.sz:=tr^.left^.sz+tr^.right^.sz;
	end;
end;

// wstepne rotacje i liczenie dla kazdego wezla "prawego" poprzednika na sciezce do korzenia
procedure prepare(tr : node_ptr; par : node_ptr; x : boolean);
var tmp : node_ptr;
begin
	if par<>nil then begin
		if x then
			tr^.prev:=par
		else
			tr^.prev:=par^.prev;
	end;
	if tr^.sz<>1 then begin
		if tr^.right^.sz>tr^.left^.sz then begin
			tmp:=tr^.left;
			tr^.left:=tr^.right;
			tr^.right:=tmp;
		end;
		prepare(tr^.left, tr, false);
		prepare(tr^.right, tr, true);
	end;
end;

// obliczanie wyniku przy znanej liczbie inwersji w kazdym wezle
function compute(tr : node_ptr) : Int64;
var pro : Int64;
begin
	if tr^.sz=1 then
		compute:=0
	else begin
		pro:=tr^.left^.sz; pro:=pro*tr^.right^.sz;
		compute:=compute(tr^.left)+compute(tr^.right)+min(tr^.inv, pro-tr^.inv);
	end;
end;

begin
	Read(MX); New(root); cur:=0;
	read_input(root);
	prepare(root, nil, false);
	for i:=1 to MX do
		ins(i, 1);
	for i:=1 to MX do begin
		tmp:=p[i]^.prev;
		// aktualizacja "prawych" poprzednikow na sciezce do korzenia
		while tmp<>nil do begin
			tmp^.inv:=tmp^.inv+get(tmp^.left^.mn+tmp^.left^.sz-1)-get(tmp^.left^.mn-1);
			tmp:=tmp^.prev;
		end;
		ins(p[i]^.mn, -1);
	end;
	WriteLn(compute(root));
end.
