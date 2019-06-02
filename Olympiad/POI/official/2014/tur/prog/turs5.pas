(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Turystyka                                     *
 *   Autor:                Marcin Andrychowicz                           *
 *   Zlozonosc czasowa:    O(4^t * (n+m))                                *
 *                         (t - dlugosc najdluzszej sciezki w grafie)    *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************)

const MAXT = 10;
const MAXN = 20000;
const MAXM = 2*50000;
const INF = 1000000000;
const MASKS = 1 shl MAXT;

var
	n,m,t,res,i,k,X,Y,a,b,Gc,one,newt,nei,cover : Longint;
	c,where,head : array[0..MAXN] of Longint;
	act, next : array[0..MASKS,0..MASKS] of Longint;
	vis : array[0..MAXN] of Boolean;
	Gval, Gnext : array[0..MAXM] of Longint;

type pointer = ^Longint;

procedure mini(a : pointer; b : Longint);
begin
	if (a^) > b then
		(a^) := b;
end;

procedure change(v : Longint; add : Boolean);
begin
	{ przygotowanie }
	if add then
	begin
		one := 1 shl t;
		newt := t + 1;
	end else begin
		one := 1 shl (t - 1);
		newt := t - 1;
	end;
	for X := 0 to (1 shl newt) - 1 do
		for Y := 0 to (1 shl newt) - 1 do
			next[X][Y] := INF;
	{ wykonanie operacji }
	if add then
	begin
		nei := 0;
		i := head[v];
		while i > 0 do
		begin
			if not (where[Gval[i]] = -1) then
				nei := nei or (1 shl where[Gval[i]]);
			i := Gnext[i];
		end;
		where[v] := t;
		for X := 0 to (1 shl t) - 1 do
			for Y := 0 to (1 shl t) - 1 do
		begin
			cover := 0;
			if (X and nei) > 0 then
				cover := one;
			mini(@next[X][Y or cover], act[X][Y]);
			mini(@next[X or one][Y or one or nei], act[X][Y] + c[v]); 
		end;
	end else begin
		where[v] := -1;
		i := head[v];
		for X := 0 to (1 shl t) - 1 do
			for Y := 0 to (1 shl t) - 1 do
		begin
			if (Y and one) > 0 then
				mini(@next[X and (not one)][Y and (not one)], act[X][Y]);
		end;
	end;
	t := newt;
	for X := 0 to (1 shl t) - 1 do
		for Y := 0 to (1 shl t) - 1 do
	begin
		act[X][Y] := next[X][Y];
	end;
end;

procedure dfs(v : Longint);
var ii : Longint;
begin
	vis[v] := True;
	change(v, True);
	ii := head[v];
	while ii > 0 do
	begin
		if not vis[Gval[ii]] then
			dfs(Gval[ii]);
		ii := Gnext[ii];
	end;
	change(v, False);
end;

begin
	Gc := 0;
	t := 0;
	res := 0;
	{ wczytanie wejscia }
	Read(n);
	Read(m);
	for i := 1 to n do
	begin
		head[i] := 0;
		where[i] := -1;
		Read(c[i]);
		vis[i] := False;
	end;
	for i := 1 to m do
	begin
		Read(a);
		Read(b);
		Inc(Gc);
		Gval[Gc] := b;
		Gnext[Gc] := head[a];
		head[a] := Gc;
		Inc(Gc);
		Gval[Gc] := a;
		Gnext[Gc] := head[b];
		head[b] := Gc;
	end;
	{ rozwiazanie }
	for k := 1 to n do
		if not vis[k] then
		begin
			act[0][0] := 0;
			dfs(k);
			res := res + act[0][0];
		end;
	{ wypisanie wyniku }
	Writeln(res);
end.
