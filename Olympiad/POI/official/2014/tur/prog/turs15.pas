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
	n,m,res,i,j,k,X,Y,Z,a,b,Gc,one : Longint;
	c,head,h : array[0..MAXN] of Longint;
	vis : array[0..MAXN] of Boolean;
	validX, validY : array[0..MAXT,0..100000] of Longint;
	validC : array[0..MAXT] of Longint;
	Gval, Gnext : array[0..MAXM] of Longint;
	dp : array[0..MAXT,0..MASKS,0..MASKS] of Longint;
	match : array[0..MAXT,0..MASKS,0..MASKS] of Longint;
	tmp : array[0..MASKS,0..MASKS] of Longint;
	matchC : array[0..MAXT,0..MASKS] of Longint;

type pointer = ^Longint;

procedure mini(a : pointer; b : Longint);
begin
	if (a^) > b then
		(a^) := b;
end;

procedure join(a, b, t : Longint);
begin
	for i := 1 to validC[t-1] do
		tmp[validX[t-1][i]][validY[t-1][i]] := INF;
	one := 1 shl (t-1);
	for i := 1 to validC[t] do
	begin
		X := validX[t][i];
		Y := validY[t][i];
		if (Y and one) > 0 then
			for j := 1 to matchC[t-1][X and (not one)] do
			begin
				Z := match[t-1][X and (not one)][j];
				mini(@tmp[X and (not one)][(Y or Z) and (not one)], dp[a][X][Y] + dp[b][X and (not one)][Z]);
			end
	end;
	for i := 1 to validC[t-1] do
	begin
		X := validX[t-1][i];
		Y := validY[t-1][i];
		dp[b][X][Y] := tmp[X][Y];
	end;
end;

procedure dfs(x, hh : Longint);
var i, j, nei, one, m, cover : Longint;
begin
	vis[x] := True;
	h[x] := hh;
	nei := 0;
	one := 1 shl hh;
	i := head[x];
	while i>0 do
	begin
		if vis[Gval[i]] then
			nei := nei or (1 shl h[Gval[i]]);
		i := Gnext[i];
	end;
	for i := 0 to (1 shl (hh+1)) - 1 do
		for j := 0 to (1 shl (hh+1)) - 1 do
			dp[hh][i][j] := INF;
	for m := 0 to (1 shl hh) - 1 do
	begin
		cover := 0;
		if (m and nei) > 0 then
			cover := one;
		dp[hh][m][m or (m shl 1) or (m shr 1) or cover] := 0;
		dp[hh][m or one][m or (m shl 1) or (m shr 1) or one or nei] := c[x];
	end;
	i := head[x];
	while i>0 do
	begin
		if not vis[Gval[i]] then
		begin
			dfs(Gval[i], hh+1);
			join(hh+1, hh, hh+2);
		end;
		i := Gnext[i];
	end;
end;

begin
	Gc := 0;
	res := 0;
	{ sensowne maski }
	for i := 1 to MAXT do
		begin
			validC[i] := 0;
			for j := 0 to (1 shl i) - 1 do
				matchC[i][j] := 0;
		end;
	for i := 0 to MAXT do
		for X := 0 to (1 shl i) - 1 do
			for Y := 0 to (1 shl i) - 1 do
				if ((X or (X shl 1) or (X shr 1)) and ((1 shl i) - 1) and (not Y)) = 0 then
				begin
					inc(validC[i]);
					validX[i][validC[i]] := X;
					validY[i][validC[i]] := Y;
					inc(matchC[i][X]);
					match[i][X][matchC[i][X]] := Y;
				end;
	{ wczytanie wejscia }
	Read(n);
	Read(m);
	for i := 1 to n do
	begin
		head[i] := 0;
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
			dfs(k, 0);
			if dp[0][0][1] < dp[0][1][1] then
				res := res + dp[0][0][1]
			else
				res := res + dp[0][1][1];
		end;
	{ wypisanie wyniku }
	Writeln(res);
end.
