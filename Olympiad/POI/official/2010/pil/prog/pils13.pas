(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Piloci (PIL)                                     *
 *   Plik:              pils13.pas                                       *
 *   Autor:             Bartosz Gorski                                   *
 *   Opis:              Rozwiazanie powolne.                             *
 *                      Wyszukiwanie binarne i kolejki dwustronne.       *
 *   Zlozonosc czasowa: O(n * log n)                                     *
 *                                                                       *
 *************************************************************************)

const
	MAX_N = 3000000;

var
	n, t, ibx, iex, ibn, ien, l, c, r, i : longint;
	a, qmin, qmax : array [0 .. MAX_N - 1] of longint;

procedure add(i : longint);
begin
	while ((ibn < ien) and (a[qmin[ien - 1]] >= a[i])) do
		dec(ien);
	qmin[ien] := i;
	inc(ien);
	while ((ibx < iex) and (a[qmax[iex - 1]] <= a[i])) do
		dec(iex);
	qmax[iex] := i;
	inc(iex);
end;

procedure remove(i : longint);
begin
	while ((ibn < ien) and (qmin[ibn] < i)) do
		inc(ibn);
	while ((ibx < iex) and (qmax[ibx] < i)) do
		inc(ibx);
end;

function check(l : longint) : boolean;
var
	i : longint;
begin
	ibx := 0; iex := 0; ibn := 0; ien := 0;
	for i := 0 to l - 2 do
		add(i);
	for i := 0 to n - l do
	begin
		remove(i);
		add(i + l - 1);
		if (a[qmax[ibx]] - a[qmin[ibn]]) <= t then
		begin
			check := true;
			exit;
		end;
	end;
	check := false;
end;

begin
	readln(t, n);
	for i := 0 to n - 1 do
		read(a[i]);
	l := 1; r := n;
	while (l < r) do
	begin
		c := (l + r + 1) div 2;
		if check(c) then
			l := c
		else
			r := c - 1;
	end;
	writeln(l);
end.
