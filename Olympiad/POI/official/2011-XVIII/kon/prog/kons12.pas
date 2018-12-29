{*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kons12.pas                                                 *}
{*   Autor:   Bartosz Górski                                             *}
{*   Opis:    Rozwiązanie nieefektywne czasowo                           *}
{*            Złożoność: O(3 ^ (log n) * n ^ 2)                          *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************}

program kon;

const
  MAX_N = 5000;

var 
	n, m, k, a : Longint;
	degree, RedDegree :  array [0 .. MAX_N - 1] of Longint;
	vertexColour : array [0 .. MAX_N - 1] of Char;
	edgeColour : array [0 .. MAX_N - 1, 0 .. MAX_N - 1] of Char;

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

procedure swap(var a, b : Longint);
var
	tmp : Longint;
begin
	tmp := a;
	a := b;
	b := tmp
end;

function paint(v : Longint; colour, chosenColour : Char; var vertexColour : array of char;
	var degree : array of Longint; var counter : Longint) : Boolean;
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
		if (i <> v) and (edgeColour[v][i] = chosenColour) and (vertexColour[i] = '?') then
			Dec(degree[i]);
	res := true;
	for i := 0 to n - 1 do
	begin
		if not res then
			break;
		if (i <> v) and (edgeColour[v][i] = oppositeColour(vertexColour[v])) then
				res := res and paint(i, edgeColour[v][i], chosenColour, vertexColour, degree, counter);
	end;
	paint := res
end;

function isClique(m : Longint; colour, chosenColour : Char; var u, v : Longint;
	var nr : array of Longint) : Longint;
var
	i, j, maxD, equal1, higher, badVertexCounter : Longint;
	deg : array [0 .. MAX_N - 1] of Longint;
begin
	u := -1;
	v := -1;
	for i := 0 to m - 1 do
		deg[i] := 0;
	for i := 0 to m - 1 do
		for j := i + 1 to m - 1 do
			if edgeColour[nr[i]][nr[j]] <> colour then
			begin
				u := i;
				v := j;
				Inc(deg[i]);
				Inc(deg[j])
			end;
	maxD := 0;
	equal1 := 0;
	higher := 0;
	for i := 0 to m - 1 do
	begin
		if maxD < deg[i] then
			maxD := deg[i];
		if deg[i] = 1 then
			Inc(equal1);
		if deg[i] > 1 then
			Inc(higher)
	end;
	if (u <> -1) and (v <> -1) then
	begin
		if deg[u] < deg[v] then
			swap(u, v);
		if (colour <> chosenColour) and (deg[u] > deg[v])  then
		begin
				u := nr[u];
				v := -1
		end
		else 
		begin
			u := nr[u];
			v := nr[v]
		end
	end;
	badVertexCounter := n;
	if maxD = 0 then
		badVertexCounter := 0
	else
		if (higher <= 1) and (maxD = (equal1 + higher - 1)) then
			badVertexCounter := 2;
	isClique := badVertexCounter
end;

function swapVertex(ic, inn, v : Longint; chosenColour : Char;
	var clique, noClique : array of Longint) : Boolean;
var
	i, j, edgeFromV, tmp, edgeFromI, u : Longint;
begin
	if v = -1 then
	begin
		swapVertex := false;
		exit
	end;
	edgeFromV := 0;
	edgeFromI := 0;
	u := -1;
	for i := 0 to ic - 1 do
		if edgeColour[v][clique[i]] = chosenColour then
			Inc(edgeFromV);
	for i := 0 to ic - 1 do
	begin
		edgeFromI := 0; 
		for j := 0 to inn - 1 do
			if (edgeColour[clique[i]][noClique[j]] = chosenColour) and (noClique[j] <> v) then
				Inc(edgeFromI);
		tmp := edgeFromV;
		if edgeColour[clique[i]][v] = chosenColour then
			Dec(tmp);
		if (tmp = ic - 1) and (edgeFromI = 0) then
		begin
			u := clique[i];
			break
		end
	end;
	if u = -1 then
	begin
		swapVertex := false;
		exit
	end;
	for i := 0 to ic - 1 do
		if clique[i] = u then
		begin
			clique[i] := v;
			break
		end;
	for i := 0 to inn - 1 do
		if noClique[i] = v then
		begin
			noClique[i] := u;
			break
		end;
	swapVertex := true
end;

function countSwaps(ic, inn : Longint; chosenColour : char; var clique,
	noClique : array of Longint) : Longint;
var
	i, j, tmp1, tmp2, res : Longint;
	degree : array [0 .. MAX_N - 1] of Longint;
begin
	for i := 0 to ic - 1 do
		degree[clique[i]] := 0;
	for i := 0 to inn - 1 do
		degree[noClique[i]] := 0;
	for i := 0 to ic - 1 do
		for j := 0 to inn - 1 do
			if edgeColour[clique[i]][noClique[j]] = chosenColour then
			begin
				Inc(degree[clique[i]]);
				Inc(degree[noClique[j]])
			end;
	res := 0;
	for i := 0 to ic - 1 do
		for j := 0 to inn - 1 do
		begin
			tmp1 := degree[clique[i]];
			tmp2 := degree[noClique[j]];
			if edgeColour[clique[i]][noClique[j]] = chosenColour then
			begin
				Dec(tmp1);
				Dec(tmp2);
			end;
			if (tmp1 = 0) and (tmp2 = (ic - 1)) then
				Inc(res);
		end;
	countSwaps := res
end;

procedure copyColours(var vertexColour, newVertexColour : array of Char);
var
	i : Longint;
begin
	for i := 0 to n - 1 do
		newVertexColour[i] := vertexColour[i]
end;

procedure copyDegrees(var degree, newDegree : array of Longint);
var
	i : Longint;
begin
	for i := 0 to n - 1 do
		newDegree[i] := degree[i]
end;

function getUncolour(m : Longint; var vertexColour : array of Char; var nr, newNr : array of Longint) : Longint;
var
	i, inn : Longint;
begin
	inn := 0;
	for i := 0 to m - 1 do
		if vertexColour[i] = '?' then
		begin
			newNr[inn] := i;
			Inc(inn)
		end;
	getUncolour := inn
end;

function countSolutions(k, m : Longint; chosenColour : Char; var nr : array of
	Longint; var vertexColour : array of Char; var degree : array of Longint) : Longint;
var
	i, lic, ic, inn, u, v, bad, newM, newK, res : Longint;
	copyDegree, clique, noClique, newNr, newDegree : array [0 .. MAX_N - 1] of Longint;
	newVertexColour : array [0 .. MAX_N - 1] of Char;
begin
	if (k < 0) or (k > m) then
	begin
		countSolutions := 0;
		exit
	end;
	copyDegrees(degree, copyDegree);
	if k < (m + 1) / 2 then
	begin
		chosenColour := oppositeColour(chosenColour);
		for i := 0 to m - 1 do
			copyDegree[nr[i]] := m - 1 - copyDegree[nr[i]];
		k := m - k
	end;
	lic := k;
	ic := 0;
	inn := 0;
	u := -1;
	v := -1;
	for i := 0 to m - 1 do
		if (copyDegree[nr[i]] >= k - 1) and (lic > 0) then
		begin
			clique[ic] := nr[i];
			Inc(ic);
			Dec(lic)
		end
		else
		begin
			noClique[inn] := nr[i];
			Inc(inn);
		end;
	if lic > 0 then
	begin
		countSolutions := 0;
		exit
	end;
	if isClique(ic, chosenColour, chosenColour, u, v, clique) = 0 then
	begin
		bad := isClique(inn, oppositeColour(chosenColour), chosenColour, u, v, noClique);
		if bad > 2 then
		begin
			countSolutions := 0;
			exit
		end;
		if bad > 0 then 
			if not swapVertex(ic, inn, u, chosenColour, clique, noClique) then
				if not swapVertex(ic, inn, v, chosenColour, clique, noClique) then
				begin
					countSolutions := 0;
					exit
				end;
		countSolutions := 1 + countSwaps(ic, inn, chosenColour, clique, noClique);
		exit
	end
	else
	begin
		res := 0;
		copyColours(vertexColour, newVertexColour);
		copyDegrees(copyDegree, newDegree);
		newK := k;
		if paint(v, chosenColour, chosenColour, newVertexColour, newDegree, newK) then
		begin
			newM := getUncolour(m, newVertexColour, nr, newNr);
			Inc(res, countSolutions(newK, newM, chosenColour, newNr, newVertexColour, newDegree))
		end;
		copyColours(vertexColour, newVertexColour);
		copyDegrees(copyDegree, newDegree);
		newK := k;
		if paint(u, chosenColour, chosenColour, newVertexColour, newDegree, newK) then
		begin
			newM := getUncolour(m, newVertexColour, nr, newNr);
			Inc(res, countSolutions(newK, newM, chosenColour, newNr, newVertexColour, newDegree));
		end;
		copyColours(vertexColour, newVertexColour);
		copyDegrees(copyDegree, newDegree);
		newK := k;
		if paint(u, oppositeColour(chosenColour), chosenColour, newVertexColour, newDegree, newK) and
			paint(v, oppositeColour(chosenColour), chosenColour, newVertexColour, newDegree, newK) then
		begin
			newM := getUncolour(m, newVertexColour, nr, newNr);
			Inc(res, countSolutions(newK, newM, chosenColour, newNr, newVertexColour, newDegree));
		end;
		countSolutions := res
	end
end;

function solve() : Longint;
var
	i, j, res : Longint;
	nr : array [0 .. MAX_N - 1] of Longint;
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
				swap(degree[j], degree[i]);
	k := 0;
	while (k < n) and (degree[k] >= k) do
		Inc(k);
	for i := 0 to n - 1 do
	begin
		nr[i] := i;
		vertexColour[i] := '?';
	end;
	res := 0;
	if k > 1 then
		Inc(res, countSolutions(k - 1, n, 'R', nr, vertexColour, redDegree));
	if k < n then
		Inc(res, countSolutions(k, n, 'R', nr, vertexColour, redDegree));
	solve := res
end;

begin
	readGraph();
	writeln(solve())
end.
