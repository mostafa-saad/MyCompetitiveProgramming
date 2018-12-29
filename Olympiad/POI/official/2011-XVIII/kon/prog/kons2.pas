{*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kons2.pas                                                  *}
{*   Autor:   Bartosz Górski                                             *}
{*   Opis:    Rozwiązanie nieefektywne czasowo                           *}
{*            Złożoność: O(n ^ 6 log n)                                  *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************}
program kon;

const
  MAX_N = 5000;

var 
	n, k, a, inr, i, j : Longint;
	nr : array [0 .. MAX_N - 1] of Longint;
	vis, col : array [0 .. MAX_N - 1] of Boolean;
	e : array [0 .. MAX_N - 1, 0 .. MAX_N - 1] of Boolean;
	sol : array [0 .. MAX_N, 0 .. MAX_N - 1] of Boolean;

function go(v : Longint; c : Boolean; var vis, col : 
	array of Boolean) : Boolean;
var
	i : Longint;
	res : Boolean;
begin
	if vis[v] then
	begin
		go := (col[v] = c);
		exit;
	end;
	vis[v] := true;
	col[v] := c;
	res := true;
	for i := 0 to n - 1 do
	begin
		if not res then
			break;
		if (i <> v) and (e[v][i] = (not col[v])) then
			res := res and go(i, e[v][i], vis, col);
	end;
	go := res
end;

function rek(nv : Longint; var ver : array of Longint; var vis, col : 
	array of Boolean) : Boolean;

function paint(a : Longint; c : Boolean; nv : Longint; var ver : array of
	Longint; var vis, col : array of Boolean) : Boolean;
var
	i, inn : Longint;
	nr : array [0 .. MAX_N - 1] of Longint;
	nvis, ncol : array [0 .. MAX_N - 1] of Boolean;
	ok : Boolean;
begin
	for i := 0 to n - 1 do
	begin
		nvis[i] := vis[i];
		ncol[i] := col[i];
	end;
	ok := go(a, c, nvis, ncol);
	if not ok then
	begin
		paint := false;
		exit
	end;
	inn := 0;
	for i := 0 to nv - 1 do
		if not nvis[ver[i]] then
		begin
			nr[inn] := ver[i];
			Inc(inn);
		end;
	paint := rek(inn, nr, nvis, ncol);
end;


function check(a, b, c, nv : Longint; var ver : array of
	Longint; var vis, col : array of Boolean; var tri : Boolean) : Boolean;
begin
	if e[a][b] and (e[a][c] and (not e[b][c])) then
	begin
		tri := true;
		check := paint(a, true, nv, ver, vis, col);
	end;
	if (not e[a][b]) and ((not e[a][c]) and e[b][c]) then
	begin
		tri := true;
		check := paint(a, false, nv, ver, vis, col);
	end;
	check := true
end;

function lower (var ncol : array of Boolean; nr : Longint) : Boolean;
var
	i : Longint;
begin
	if nr = -1 then
	begin
		lower := false;
		exit
	end;
	for i := 0 to n - 1 do
		if sol[nr][i] <> ncol[i] then
		begin
			lower := (ncol[i] < sol[nr][i]);
			exit
		end;
	lower := false;
end;

function bs(var ncol : array of Boolean) : Longint;
var
	l, c, r : Longint;
begin
	l := -1;
	r := inr - 1;
	while l < r do
	begin
		c := (l + r + 1) div 2;
		if lower(ncol, c) then
			r := c - 1
		else
			l := c;
	end;
	bs := l
end;

function equal(var ncol : array of Boolean; nr : Longint) : Boolean;
var
	i : Longint;
begin
	if nr = -1 then
	begin
		equal := false;	
		exit;
	end;
	for i := 0 to n - 1 do
		if sol[nr][i] <> ncol[i] then
		begin
			equal := false;
			exit
		end;
	equal := true
end;

procedure add(var ncol : array of Boolean);
var
	i, j, poz : Longint;
begin
	poz := bs(ncol);
	if equal(ncol, poz) then
		exit;
	Inc(poz);
	for i := inr downto poz + 1 do
		for j := 0 to n - 1 do
			sol[i][j] := sol[i - 1][j];
	for i := 0 to n - 1 do
		sol[poz][i] := ncol[i];
	Inc(inr)
end;

var
	a, b, c, inn : Longint;
	nr : array [0 .. MAX_N - 1] of Longint;
	ok, tri, k : Boolean;
begin
	if n = 0 then
	begin
		rek := true;
		exit
	end;
	if n = 1 then
	begin
		col[ver[0]] := true;
		add(col);
		col[ver[0]] := false;
		add(col);
		rek := true;
		exit
	end;
	ok := true;
	tri := false;
	for a := 0 to nv - 1 do
	begin
		if not ok then
			break;
		for b := a + 1 to nv - 1 do
		begin
			if not ok then
				break;
			for c := b + 1 to nv - 1 do
			begin
				if not ok then
					break;
				ok := ok and check(ver[a], ver[b], ver[c], nv, ver, vis, col, tri);
				ok := ok and check(ver[b], ver[a], ver[c], nv, ver, vis, col, tri);
				ok := ok and check(ver[c], ver[a], ver[b], nv, ver, vis, col, tri);
			end;
		end;
	end;
	if ok and (not tri) then
	begin
		inn := 0;
		for a := 0 to nv - 1 do
			if not vis[ver[a]] then
			begin
				nr[inn] := ver[a];
				Inc(inn);
			end;
		k := e[nr[0]][nr[1]];
		for a := 0 to inn - 1 do
			col[nr[a]] := k;
		add(col);
		for a := 0 to inn - 1 do
		begin
			col[nr[a]] := not col[nr[a]];
			add(col);
			col[nr[a]] := not col[nr[a]];
		end;
	end;
	rek := ok
end;

begin
	readln(n);
	for i := 0 to n - 1 do
	begin
		nr[i] := i;
		read(k);
		for j := 0 to k - 1 do
		begin
			read(a);
			e[i][a - 1] := true
		end;
		readln();
	end;
	rek(n, nr, vis, col);
	if inr > n then 
		Dec(inr);
	writeln(inr)
end.

