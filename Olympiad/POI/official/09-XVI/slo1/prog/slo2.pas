(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Slonie (SLO)                                              *
 *   Plik:     slo2.pas                                                  *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Rozwiazanie wzorcowe O(n)                                 *
 *                                                                       *
 *************************************************************************)

const INF = 1000000000;

const MAXN = 1000000;

var
	N : LongInt;
	wagi,
	orig, { orig[i] = kto stal na pozycji i }
	perm : array[0..MAXN-1] of LongInt; { slon i ma wyladowac na pozycji slonia perm[i] }
	vis : array[0..MAXN-1] of Boolean; { nalezy do juz zbadanego cyklu }

	minw : Int64 = INF; { minimalna waga }

	a, nr, pocz, cur, dl : LongInt;
	wynik : Int64 = 0;
	suma, minc : Int64;

begin
	Readln(N);
	for a := 0 to N-1 do
	begin
		wagi[a] := 0; { inaczej read zglasza warning }
		Read(wagi[a]);
		if wagi[a]<minw then
			minw := wagi[a];
	end;
	Readln;
	for a := 0 to N-1 do
	begin
		orig[a] := 0; { inaczej read zglasza warning }
		Read(orig[a]);
		Dec(orig[a]);
	end;
	Readln;
	for a := 0 to N-1 do
	begin
		Read(nr);
		Dec(nr);
		perm[nr] := orig[a];
		vis[a] := false;
	end;
	for pocz := 0 to N-1 do
		if not vis[pocz] then
		begin
			minc := INF; // minimalna waga w cyklu
			suma := 0; // suma wag w cyklu
			cur := pocz;
			dl := 0; // dlugosc cyklu
			while true do 
			begin
				if wagi[cur]<minc then
					minc := wagi[cur];
				suma := suma+wagi[cur];
				cur := perm[cur];
				vis[cur] := true;
				Inc(dl);
				if cur=pocz then
					break;
			end;
			if suma+(dl-2)*minc<suma+minc+(dl+1)*minw then
				wynik := wynik+suma+(dl-2)*minc
			else
				wynik := wynik+suma+minc+(dl+1)*minw;
		end;
	Writeln(wynik);
end.
