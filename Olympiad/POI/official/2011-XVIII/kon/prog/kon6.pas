{*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kon6.pas                                                   *}
{*   Autor:   Bartosz Górski                                             *}
{*   Opis:    Rozwiązanie alternatywne                                   *}
{*            Złożoność: O(n ^ 2)                                        *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************}
program kon;

const
  MAX_N = 5000;

var 
	n, m, k, a, io : Longint;
	order :  array [0 .. 2 * MAX_N - 1] of Longint;
	vertexColour : array [0 .. MAX_N - 1] of Char;
	colour :  array [0 .. 2 * MAX_N - 1] of Char;
	edgeColour : array [0 .. MAX_N - 1, 0 .. MAX_N - 1] of Char;
	graph : array [0 .. 2 * MAX_N - 1, 0 .. 2 * MAX_N - 1] of Boolean;
	visit : array [0 .. 2 * MAX_N - 1] of Boolean;

procedure init(n : Longint);
var
	i, j : Longint;
begin
	m := 2 * n;
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

procedure reverseDfs(a : Longint);
var
	i : Longint;
begin
	visit[a] := true;
	for i := 0 to m - 1 do
		if graph[i][a] and (not visit[i]) then
			reverseDfs(i);
	order[io] := a;
	Inc(io)
end;

procedure paintDfs(a : Longint);
var
	i : Longint;
begin
	visit[a] := true;
	if colour[a xor 1] = '?' then
		colour[a] := 'R'
	else
		colour[a] := 'B';
	for i := 0 to m - 1 do
		if graph[a][i] and (not visit[i]) then
			paintDfs(i)
end;

function findSolution() : Boolean;
var
	i, j : Longint;
begin
	for i := 0 to m - 1 do
		for j := 0 to m - 1 do
			graph[i][j] := false;
	for i := 0 to n - 1 do
		for j := i + 1 to n - 1 do
			if edgeColour[i][j] = 'R' then
			begin
				graph[2 * i + 1][2 * j] := true;
				graph[2 * j + 1][2 * i] := true
			end
			else
			begin
				graph[2 * i][2 * j + 1] := true;
				graph[2 * j][2 * i + 1] := true
			end;
	for i := 0 to m - 1 do
	begin
		visit[i] := false;
		colour[i] := '?'
	end;
	for i := 0 to m - 1 do
		if not visit[i] then
			reverseDfs(i);
	for i := 0 to m - 1 do
		visit[i] := false;
	for i := m - 1 downto 0 do
		if not visit[order[i]] then
			paintDfs(order[i]);
	for i := 0 to m - 1 do
		for j := 0 to m - 1 do
			if graph[i][j] and (colour[i] = 'R') and (colour[j] = 'B') then
			begin
				findSolution := false;
				exit
			end;
	for i := 0 to n - 1 do
		vertexColour[i] := colour[2 * i];
	findSolution := true
end;

function oppositeColour(colour : Char) : Char;
begin
	if colour = 'R' then
		oppositeColour := 'B'
	else
		oppositeColour := 'R'
end;

function solve() : Longint;
var
	i, j, ir, ib, res: Longint;
	red, blue, deg : array [0 .. MAX_N - 1] of Longint;
begin
	ir := 0;
	ib := 0;
	if not findSolution() then
	begin
		solve := 0;
		exit
	end;
	for i := 0 to n - 1 do
		if vertexColour[i] = 'R' then
		begin
			red[ir] := i;
			Inc(ir)
		end
		else
		begin
			blue[ib] := i;
			Inc(ib)
		end;
	res := 1;
	for i := 0 to ir - 1 do
	begin
		deg[red[i]] := 0;
		for j := 0 to ib - 1 do
			if edgeColour[red[i]][blue[j]] = 'R' then
				Inc(deg[red[i]])
	end;
	for i := 0 to ib - 1 do
	begin
		deg[blue[i]] := 0;
		for j := 0 to ir - 1 do
			if edgeColour[blue[i]][red[j]] = 'B' then
				Inc(deg[blue[i]])
	end;
	for i := 0 to ir - 1 do
		for j := 0 to ib - 1 do
			if edgeColour[red[i]][blue[j]] = 'R' then
			begin
				if (deg[red[i]] = 1) and (deg[blue[j]] = 0) then
					Inc(res)
			end
			else
			begin
				if (deg[red[i]] = 0) and (deg[blue[j]] = 1) then
					Inc(res)
			end;
	for i := 0 to n - 1 do
		if deg[i] = 0 then
			Inc(res);
	if res > n then
		Dec(res);
	solve := res
end;

begin
	readGraph();
	writeln(solve())
end.

