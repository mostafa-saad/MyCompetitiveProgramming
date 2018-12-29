(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Inspekcja                                        *
 *   Autor:             Dawid Dabrowski                                  *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie wzorcowe - sprytniejsze              *
 *                                                                       *
 *************************************************************************)

program ins0;

{ Lista jednokierunkowa krawedzi. Czemu w Pascalu nie ma vectora? :( }
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
	p, p2: array[1..MAXN] of longint;
	u: longint;
	it: Lista;
	poddrzewo: array[1..MAXN] of longint;
	suma: int64;
	mx, najgl, cur, akt: longint;

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

{ Dwa proste dfsy, opisane w opracowaniu. Oba korzystaja z listy wskaznikowej, stad obecnosc
  iteratorow "iter". Pierwszy liczy poddrzewa, drugi reszte. }

procedure dfs(u: longint);
var
	iter: Lista;
begin
	poddrzewo[u] := 1;
	iter := kra[u];
	while iter <> nil do
	begin
		if iter^.u <> p[u] then
		begin
			p[iter^.u] := u;
			dfs(iter^.u);
			poddrzewo[u] := poddrzewo[u] + poddrzewo[iter^.u];
		end;
		iter := iter^.nast;
	end;
end;

function dfs2(u,gleb: longint): longint;
var
	iter: Lista;
	res: longint;
begin
	res := 0;
	iter := kra[u];
	while iter <> nil do
	begin
		if (iter^.u <> p2[u]) and (iter^.u <> akt) then
		begin
			p2[iter^.u] := u;
			cur := dfs2(iter^.u, gleb+1);
			res := max(res, cur+1);
		end;
		iter := iter^.nast;
	end;
	suma := suma + gleb;
	dfs2 := res;
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
	{ Budujemy graf. }
	readln(n);
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

	{ Liczymy jedynie wielkosci poddrzew. }
	p[1] := 0;
	dfs(1);

	for u:=1 to n do
	begin
		mx := -1;
		it := kra[u];
		while it <> nil do
		begin
			if it^.u <> p[u] then
				mx := max(mx, poddrzewo[it^.u]);
			it := it^.nast;
		end;
		mx := max(mx, n-poddrzewo[u]);

		if 2*mx <= n then { Sprawdzamy, czy istnieje przechadzka. }
		begin
			{ Tu bedziemy co najwyzej dwa razy =) }
			akt := u;
			for i:=1 to n do
				p2[i] := 0;
			suma := 0;
			najgl := 0;
			it := kra[u];

			{ Uruchamiamy dfs2 dla poddrzew. Czyli liczymy sume odleglosci do pozostalych
        wierzcholkow oraz najglebsze wierzcholki w poddrzewach. }
			while it <> nil do
			begin
				if it^.u <> p[u] then
				begin
					cur := dfs2(it^.u, 1);
					if (2*mx < n) or (poddrzewo[it^.u] = mx) then
            { Uaktualniamy jedynie, jesli mozemy skonczyc w danym poddrzewie. * }
						najgl := max(najgl, cur+1);
				end;
				it := it^.nast;
			end;
			if p[u] <> 0 then
			begin
				cur := dfs2(p[u], 1);
				if (2*mx < n) or (n-poddrzewo[u] = mx) then { * }
					najgl := max(najgl, cur+1);
			end;
			writeln(2*suma - najgl); { Wypisujemy odpowiedz. }
		end
		else
			writeln(-1);
	end;
end.
