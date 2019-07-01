{*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kon1.pas                                                   *}
{*   Autor:   Bartosz Górski                                             *}
{*   Opis:    Rozwiązanie wzorcowe                                       *}
{*            Złożoność: O(n ^ 2)                                        *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************}
program kon;

const
  MAX_N = 5000;

var 
	n, k, a, xRedEdge, yRedEdge, xBlueEdge, yBlueEdge : Longint;
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
		edgeColour[i][i] := '?'
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
			edgeColour[i][a - 1] := 'R'
		end;
		readln;
	end
end;

function check(a, b : Longint) : Boolean;
begin
	if ((vertexColour[a] <> '?') and (edgeColour[a][b] = vertexColour[a]))
		or ((vertexColour[b] <> '?') and (edgeColour[a][b] = vertexColour[b])) then
		check := true
	else
		check := false
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
		exit
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

function paint(a, b, c : Longint) : Boolean;
begin
	if (edgeColour[a][b] = 'R') and (edgeColour[b][c] = 'R') then
		paint := go(b, edgeColour[a][b])
	else
		paint := go(c, edgeColour[a][c])
end;


function triangle(a, b, c, d : Longint) : Boolean;
begin
	if a = c then
		triangle := paint(a, b, d)
	else
		if a = d then
			triangle := paint(a, b, c)
		else
			if b = c then
				triangle := paint(b, a, d)
			else
				if b = d then
					triangle := paint(b, a, c)
				else
					if edgeColour[a][c] = 'R' then
						triangle := paint(c, a, d)
					else
						triangle := paint(a, b, c)
end;

procedure next(var x, y : Longint);
begin
	Inc(x);
	if x >= n then
	begin
		x := 0;
		Inc(y)
	end
end;

function solve() : Longint;
var
	i, res : Longint;
begin
	while true do
	begin
		while (yRedEdge < n) and ((xRedEdge = yRedEdge) or
				(edgeColour[xRedEdge][yRedEdge] = 'B') or check(xRedEdge, yRedEdge)) do
			next(xRedEdge, yRedEdge);
		while (yBlueEdge < n) and ((xBlueEdge = yBlueEdge) or 
				(edgeColour[xBlueEdge][yBlueEdge] = 'R') or check(xBlueEdge, yBlueEdge)) do
			next(xBlueEdge, yBlueEdge);
		if (yRedEdge >= n) or (yBlueEdge >= n) then
			break;
		if not triangle(xRedEdge, yRedEdge, xBlueEdge, yBlueEdge) then
		begin
			solve := 0;
			exit
		end
	end;
	res := 0;
	for i := 0 to n - 1 do
		if vertexColour[i] = '?' then
			Inc(res);
	if res < n then
		Inc(res);
	solve := res
end;

begin
	readGraph();
	writeln(solve())
end.

