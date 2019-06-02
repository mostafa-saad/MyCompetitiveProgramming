(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Piloci (PIL)                                     *
 *   Plik:              pils9.pas                                        *
 *   Autor:             Bartosz Gorski                                   *
 *   Opis:              Rozwiazanie powolne - brutalne.                  *
 *                      Nie sprawdza przedzialow krotszych od rekordu.   *
 *   Zlozonosc czasowa: O(n^3)                                           *
 *                                                                       *
 *************************************************************************)

const
	MAX_N = 3000000;

var
	n, t, r, i, j : longint;
	a : array[0 .. MAX_N - 1] of longint; 

function ok(x, y : longint) : boolean;
var
	i, j : longint;
begin
	for i := x to y do
		for j := i + 1 to y do
			if abs(a[i] - a[j]) > t then
			begin
				ok := false;
				exit;
			end;
	ok := true;
end;

begin
	readln(t, n);
	for i := 0 to n - 1 do
		read(a[i]);
	r := 0;
	for i := 0 to n - 1 do
		for j := r to n - i - 1 do
		begin
			if not ok(i, i + j) then
				break;
			r := j + 1;
		end;
	writeln(r);
end.
