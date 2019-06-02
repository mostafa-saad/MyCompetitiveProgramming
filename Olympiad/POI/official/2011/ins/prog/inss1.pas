(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Inspekcja                                        *
 *   Autor:             Dawid Dabrowski                                  *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************)

program ins0;

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
	wiel, najgl: array[1..MAXN] of longint;
	poddrzewo, najglebszy: array[1..MAXN] of longint;
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

procedure dfs(u: longint);
var
	iter: Lista;
begin
	poddrzewo[u] := 1;
	najglebszy[u] := 0;
	iter := kra[u];
	while iter <> nil do
	begin
		if iter^.u <> p[u] then
		begin
			p[iter^.u] := u;
			dfs(iter^.u);
			poddrzewo[u] := poddrzewo[u] + poddrzewo[iter^.u];
			if najglebszy[iter^.u] + 1 > najglebszy[u] then
				najglebszy[u] := najglebszy[iter^.u] + 1;
			suma[u] := suma[u] + suma[iter^.u] + poddrzewo[iter^.u];
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

procedure odpowiedz(v: longint);
var
	j: longint;
	it: Lista;
	best: int64;
	ok: boolean;
begin
	for j:=1 to n do
	begin
		p[j] := 0;
		suma[j] := 0;
	end;
	dfs(v);
	l := 1;
	it := kra[v];
	while it <> nil do
	begin
		wiel[l] := poddrzewo[it^.u];
		najgl[l] := najglebszy[it^.u];
		inc(l);
		it := it^.nast;
	end;
	ok := true;
	best := 2*suma[v];
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
		for i:=1 to l-1 do
			best := min(best, 2*suma[u] - najgl[i] - 1);
	writeln(best);
end;

begin
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

	for u:=1 to n do
		odpowiedz(u);
end.
