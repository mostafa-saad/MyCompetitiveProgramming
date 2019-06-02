(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Piorunochron                                     *
 *   Autor:             Juliusz Sompolski                                *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************)

uses Math;

const MAXN=500000;

{ Liczba budynkow }
var N:longint;
{ Wysokosci budynkow }
var H:Array[0..MAXN-1] of longint;

{ Liczenie odpowiedzi dla danego budynku }
function get_answer(i:longint):longint;
	var j,k:longint;
begin
	get_answer := 0;
	for j := 0 to N-1 do
	begin
		k := H[j]-H[i] + ceil(sqrt(abs(j-i)));
		if k > get_answer then get_answer := k;
	end;
end;

var i:longint;

BEGIN
	read(N);
	for i := 0 to N-1 do
		read(H[i]);
	
	{ Odpowiedzi }
	for i := 0 to N-1 do
		writeln(get_answer(i));
END.
