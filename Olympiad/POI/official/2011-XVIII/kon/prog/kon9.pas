{*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kon9.pas                                                   *}
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
	n, m, k, a, counter : Longint;
	degree, RedDegree :  array [0 .. MAX_N - 1] of Longint;
	vertexColour : array [0 .. MAX_N - 1] of Char;
	edgeColour : array [0 .. MAX_N - 1, 0 .. MAX_N - 1] of Char;
	chosenColour : Char;

procedure init(n : Longint);
var
	i, j : Longint;
begin
	for i := 0 to n - 1	do
	begin
		redDegree[i] := 0;
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

function oppositeColour(colour : Char) : Char;
begin
	if colour = 'R' then
		oppositeColour := 'B'
	else
		oppositeColour := 'R'
end;

function paint(v : Longint; colour : Char) : Boolean;
var
	i : Longint;
	res : Boolean;
begin
	if vertexColour[v] <> '?' then
	begin
		paint := vertexColour[v] = colour;
		exit
	end;
	vertexColour[v] := colour;
	Dec(m);
	if vertexColour[v] = chosenColour then
		Dec(counter);
	if counter < 0 then
	begin
		paint := false;
		exit
	end;
	degree[v] := 0;
	for i := 0 to n - 1 do
		if (edgeColour[v][i] = chosenColour) and (vertexColour[i] = '?') then
			Dec(degree[i]);
	res := true;
	for i := 0 to n - 1 do
	begin
		if not res then
			break;
		if (i <> v) and (edgeColour[v][i] = oppositeColour(vertexColour[v])) then
				res := res and paint(i, edgeColour[v][i]);
	end;
	paint := res
end;

function getVertex(gr, gb, n, m : Longint) : Longint;
var
	i : Longint;
begin
	for i := 0 to n - 1 do
		if (vertexColour[i] = '?') and (((m - 1 - degree[i]) >= gb) or
			(degree[i] >= gr)) then
		begin
			getVertex := i;
			exit
		end;
	getVertex := -1
end;

function countSolutions(k : Longint) : Longint;
var
	i, v, gr, gb, left : Longint;
	d : array [0 .. 2] of Longint;
begin
	if (k <= 0) or (k >= n) then
	begin
		countSolutions := 0;
		exit
	end;
	for i := 0 to n - 1 do
	begin
		vertexColour[i] := '?';
		degree[i] := redDegree[i]
	end;
	v := -1;
	gr := -1;
	gb := -1;
	chosenColour := 'R';
	counter := k;
	m := n;
	while counter > 2 do
	begin
		gr := counter + 1;
		gb := (m - counter + 1);
		if counter >= m - 2 then
		begin
			counter := m - counter;
			chosenColour := 'B';
			for i := 0 to n - 1 do
				degree[i] := m - 1 - degree[i];
			gr := counter + 1;
			gb := (m - counter + 1);
			break
		end
		else
			v := getVertex(gr, gb, n, m);
		if v = -1 then
			break;
		if degree[v] >= gr then
		begin
			if not paint(v, 'R') then
			begin
				countSolutions := 0;
				exit
			end
		end
		else
			if not paint(v, 'B') then
			begin
				countSolutions := 0;
				exit
			end
	end;
	for i := 0 to n - 1 do
		if vertexColour[i] = '?' then
		begin
			if degree[i] > counter then
			begin
				if not paint(i, chosenColour) then
				begin
					countSolutions := 0;
					exit
				end
			end
			else
				if (degree[i] < (counter - 1)) and (counter > 2) then
					if not paint(i, oppositeColour(chosenColour)) then
					begin
						countSolutions := 0;
						exit
					end
		end;
	if counter = 0 then
	begin
		countSolutions := 1;
		exit
	end;
	left := 0;
	for i := 0 to 2 do
		d[i] := 0;
	for i := 0 to n - 1 do
		if vertexColour[i] = '?' then
		begin
			Inc(d[degree[i]]);
			Inc(left);
		end;
	if counter = 1 then
	begin
		if d[1] = 0 then
			countSolutions := left
		else
			if d[1] = 2 then
				countSolutions := 2
			else
				countSolutions := 0;
		exit
	end;
	if counter = 2 then
	begin
		if ((d[1] = 2) and (d[2] = 0)) or ((d[1] = 2) and (d[2] = 2)) then
			countSolutions := 1
		else
			if (d[1] = 2) and (d[2] = 1) then
				countSolutions := 2
			else
				if (d[1] = 0) and (d[2] = 3) then
					countSolutions := 3
				else
					countSolutions := 0;
		exit
	end;
	countSolutions := 0
end;

function solve() : Longint;
var
	i, j : Longint;
begin
	for i := 0 to n - 1 do
		for j := 0 to n - 1 do
			if edgeColour[i][j] = 'R' then
				Inc(redDegree[i]);
	for i := 0 to n - 1 do
		degree[i] := redDegree[i];
	for i := 0 to n - 1 do
		for j := 0 to i - 1 do
			if degree[j] < degree[i] then
			begin
				degree[j] := degree[i] xor degree[j];
				degree[i] := degree[i] xor degree[j];
				degree[j] := degree[i] xor degree[j]
			end;
	k := 0;
	while (k < n) and (degree[k] >= k) do
		Inc(k);
	solve := countSolutions(k - 1) + countSolutions(k)
end;

begin
	readGraph();
	writeln(solve())
end.
