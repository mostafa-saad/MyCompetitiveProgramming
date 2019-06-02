(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Inspekcja                                        *
 *   Autor:             Dawid Dabrowski                                  *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie wzorcowe - trudniejsze               *
 *                                                                       *
 *************************************************************************)

program ins0;

{ Lista wskaznikowa krawedzi. }

type
	Lista = ^wsk;
	wsk =
	record
		u: longint;
		nast: Lista;
	end;

const
	MAXN = 1000000;

var
	n: longint;
	kra, ost: array[1..MAXN] of Lista;
	i, a, b: longint;
	p: array[1..MAXN] of longint;
	u: longint;
	l: longint;
	ok: boolean;
	best: int64;
	it: Lista;
	wiel, najgl: array[1..MAXN] of longint;
	{ Bardzo wazne wielkosci z opracowania. Pamietamy o tym, by suma byla 64-bitowa. }
	poddrzewo, najglebszy_dol, najglebszy_gora: array[1..MAXN] of longint;
	suma: array[1..MAXN] of int64;

function min(a,b: longint): longint;
begin
	if a < b then min := a
	else min := b;
end;

function max(a,b: longint): longint;
begin
	if a > b then max := a
	else max := b;
end;

{ Dfs liczacy wielkosci poddrzew, sume odleglosci od potomkow oraz najdalszego potomka. Idzie od lisci do korzenia. }
procedure dfs(u: longint);
var
	iter: Lista;
begin
	poddrzewo[u] := 1;
	najglebszy_dol[u] := 0;
	iter := kra[u];
	while iter <> nil do
	begin
		if iter^.u <> p[u] then
		begin
			p[iter^.u] := u;
			dfs(iter^.u);
			poddrzewo[u] := poddrzewo[u] + poddrzewo[iter^.u];
			if najglebszy_dol[iter^.u] + 1 > najglebszy_dol[u] then
				najglebszy_dol[u] := najglebszy_dol[iter^.u] + 1;
			suma[u] := suma[u] + suma[iter^.u] + poddrzewo[iter^.u];
		end;
		iter := iter^.nast;
	end;
end;

{ Dfs liczacy sume odleglosci od wszystkich wierzcholkow oraz najdalszy wierzcholek, do ktorego sciezka prowadzi przez ojca. Idzie od korzenia do lisci. }
procedure dfs2(u: longint);
var
	iter: Lista;
	mx1, mx2, best: longint;
begin
	mx1 := -1;
	mx2 := -1;
	iter := kra[u];
	while iter <> nil do
	begin
		if iter^.u <> p[u] then
		begin
			if najglebszy_dol[iter^.u] > mx1 then
			begin
				mx2 := mx1;
				mx1 := najglebszy_dol[iter^.u];
			end
			else
			begin
				if najglebszy_dol[iter^.u] > mx2 then
					mx2 := najglebszy_dol[iter^.u];
			end;
		end;
		iter := iter^.nast;
	end;

	{ Magic :) }
	iter := kra[u];
	while iter <> nil do
	begin
		if iter^.u <> p[u] then
		begin
			suma[iter^.u] := suma[u] - 2*poddrzewo[iter^.u] + n;
			best := mx1;
			if najglebszy_dol[iter^.u] = mx1 then
				best := mx2;
			if najglebszy_gora[u] + 1 > max(1, best+2) then
				najglebszy_gora[iter^.u] := najglebszy_gora[u] + 1
			else
				najglebszy_gora[iter^.u] := max(1, best+2);
			dfs2(iter^.u);
		end;
		iter := iter^.nast;
	end;
end;

procedure dodaj(a,b: longint);
var
	cur: Lista;
begin
	new(cur);
	cur^.u := b;
	cur^.nast := nil;
	if kra[a] = nil then
	begin
		kra[a] := cur;
		ost[a] := cur;
	end
	else
	begin
		ost[a]^.nast := cur;
		ost[a] := cur;
	end;
end;

begin
	readln(n);
	if n = 1 then writeln(0) else begin
	for i:=1 to n do
	begin
		kra[i] := nil;
		ost[i] := nil;
	end;

	for i:=1 to n-1 do
	begin
		readln(a,b);
		dodaj(a,b);
		dodaj(b,a);
	end;

	p[1] := 0;

	for u:=1 to n do
		suma[u] := 0;

	dfs(1); { Do gory. }
	dfs2(1); { Na dol. }

	for u:=1 to n do
	begin
		l := 1;
		it := kra[u];
		while it <> nil do
		begin
			if it^.u <> p[u] then
			begin
				wiel[l] := poddrzewo[it^.u];
				najgl[l] := najglebszy_dol[it^.u];
				inc(l);
			end
			else
			begin
				wiel[l] := n - poddrzewo[u];
				najgl[l] := najglebszy_gora[u] - 1;
				inc(l);
			end;
			it := it^.nast;
		end;
		best := 2*suma[u];
		ok := true;
		for i:=1 to l-1 do
		begin
			if 2*wiel[i] > n then
			begin
				best := -1;
				ok := false;
				break;
			end;
			if 2*wiel[i] = n then
			begin
				best := 2*suma[u] - najgl[i] - 1;
				ok := false;
				break;
			end;
		end;
		if ok then
			for i:=1 to l do
				if 2*suma[u] - najgl[i] - 1  < best then
					best := 2*suma[u] - najgl[i] - 1;
		writeln(best);
	end;
end;
end.
