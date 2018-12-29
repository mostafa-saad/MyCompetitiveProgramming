{*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kon4.pas                                                   *}
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
	n, k, a, cliqueSize, edgeToClique, firstVertexInClique : Longint;
	cliqueColour : Char;
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

function extortVertexColour(u : Longint) : Boolean;
var
	v : Longint;
begin
	edgeToClique := 0;
	firstVertexInClique := -1;
	for v := 0 to u - 1 do
		if vertexColour[v] = '?' then
		begin
			if firstVertexInClique = -1 then
				firstVertexInClique := v;
			if edgeColour[u][v] <> cliqueColour then
				Inc(edgeToClique)
		end
		else
			if edgeColour[u][v] <> vertexColour[v] then
			begin
				if (vertexColour[u] <> '?') and (vertexColour[u] <> edgeColour[u][v]) then
				begin
					extortVertexColour := true;
					exit
				end;
				vertexColour[u] := edgeColour[u][v];
			end;	
	extortVertexColour := false
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
	u, v : Longint;
begin
	cliqueColour := edgeColour[0][1];
	cliqueSize := 2;
	for u := 2 to n - 1 do
	begin
		if extortVertexColour(u) then
		begin
			solve := 0;
			exit
		end;
		if vertexColour[u] = '?' then
		begin
			if (edgeToClique = 0) or (cliqueSize < 2)  then
			begin
				if cliqueSize = 1 then
					cliqueColour := edgeColour[firstVertexInClique][u];
				Inc(cliqueSize);
				continue
			end;
			if edgeToClique = 1 then
			begin
				for v := 0 to u - 1 do
					if (vertexColour[v] = '?') and (edgeColour[u][v] = cliqueColour) then
						vertexColour[v] := cliqueColour;
				cliqueColour := oppositeColour(cliqueColour);
				cliqueSize := 2;
				continue
			end;
			if edgeToClique >= 2 then
				vertexColour[u] := oppositeColour(cliqueColour);
		end;
		if cliqueSize = 0 then
			continue;
		if cliqueSize = 1 then
		begin
			if vertexColour[u] <> edgeColour[u][firstVertexInClique] then
			begin
				vertexColour[firstVertexInClique] := edgeColour[u][firstVertexInClique];
				Dec(cliqueSize)
			end;
			continue;
		end;
		if vertexColour[u] = cliqueColour then
		begin
			if edgeToClique > 1 then
			begin
				solve := 0;
				exit
			end;
			if edgeToClique = 1 then
			begin
				for v := 0 to u - 1 do
					if vertexColour[v] = '?' then
					begin
						if vertexColour[u] = edgeColour[u][v] then
							vertexColour[v] := cliqueColour
						else
							vertexColour[v] := oppositeColour(cliqueColour)
					end;
				cliqueColour := '?';
				cliqueSize := 0
			end
		end
		else
		begin
			for v := 0 to u - 1 do
				if (vertexColour[v] = '?') and (vertexColour[u] <> edgeColour[u][v]) then
				begin
					vertexColour[v] := cliqueColour;
					Dec(cliqueSize)
				end
		end
	end;
	if cliqueSize < n then
		Inc(cliqueSize);
	solve := cliqueSize
end;

begin
	readGraph();
	writeln(solve())
end.

