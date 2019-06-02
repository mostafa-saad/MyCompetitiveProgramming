{*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kons4.pas                                                  *}
{*   Autor:   Bartosz Górski                                             *}
{*   Opis:    Rozwiązanie nieefektywne czasowo                           *}
{*            Złożoność: O(n ^ 3)                                        *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************}

program kon;

const
  MAX_N = 5000;

var 
	n, k, a : Longint;
	vertexColour : array [0 .. MAX_N - 1] of Char;
	edgeColour : array [0 .. MAX_N - 1, 0 .. MAX_N - 1] of Char;

procedure init(n : Longint);
var
	i, j : Longint;
begin
	for i := 0 to n - 1	do
	begin
		vertexColour[i] := '?';
		for j := 0 to n - 1 do
			edgeColour[i][j] := 'B';
		edgeColour[i][i] := '?';
	end
end;

procedure readGraph();
var
	i, j : Longint;
begin
	readln(n);
	init(n);
	for i := 0 to n - 1 do
	begin
		read(k);
		for j := 0 to k - 1 do
		begin
			read(a);
			edgeColour[i][a - 1] := 'R';
		end;
		readln;
	end
end;

function oppositeColour(colour : Char) : Char;
begin
	if colour = 'R' then
		oppositeColour := 'B'
	else
		oppositeColour := 'R'
end;

function go(v : Longint; colour : Char) : Boolean;
var
	i : Longint;
	res : Boolean;
begin
	if vertexColour[v] <> '?'	then
	begin
		go := vertexColour[v] = colour;
		exit;
	end;
	vertexColour[v] := colour;
	res := true;
	for i := 0 to n - 1 do
	begin
		if not res then
			break;
		if (i <> v) and ((vertexColour[v] = '?') or 
				(edgeColour[v][i] = oppositeColour(vertexColour[v]))) then
			res := res and go(i, edgeColour[v][i]);
	end;
	go := res
end;

function check(a, b, c : Longint) : Boolean;
begin
	if (edgeColour[a][b] = edgeColour[a][c]) and 
			(edgeColour[a][b] <> edgeColour[b][c]) then
		check := go(a, edgeColour[a][b])
	else
		check := true 
end;

function solve() : Longint;
var
	a, b, c, res : Longint;
begin
	for a := 0 to n - 1 do
		for b := a + 1 to n - 1 do
			for c := b + 1 to n - 1 do
				if (not check(a, b, c)) or (not check(b, a, c)) or 
						(not check(c, a, b)) then
				begin
					solve := 0;
					exit;
				end;
	res := 1;
	for a := 0 to n - 1 do
		if vertexColour[a] = '?' then
			Inc(res);
	if res > n then
		Dec(res);
	solve := res
end;

begin
	readGraph();
	writeln(solve());
end.

