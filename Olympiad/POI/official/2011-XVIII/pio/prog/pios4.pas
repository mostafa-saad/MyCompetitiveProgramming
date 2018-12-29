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
const MAXSQRTN=800;

type pair = record
	first,second:longint;
end; 

function leq(var a,b:pair):boolean;
begin
	leq := a.first <= b.first;
end;

{ Sortowanie }

{ podzial do sortowania szybkiego }
function partition(var a:Array of pair;l,r:longint):longint;
	var i,j,rnd:longint;
	    x,tmp:pair;
begin
	{ randomizacja elementu dzielacego }
	rnd := l+random(r-l+1);
	tmp := a[l]; a[l] := a[rnd]; a[rnd] := tmp;
	
	x := a[l];
	i := l; j := r+1;
	repeat
		repeat i := i+1; until not ((i<=r) and (leq(a[i],x)));
		repeat j := j-1; until leq(a[j],x);
		if i>=j then break;
		tmp := a[i]; a[i] := a[j]; a[j] := tmp;
	until false;
	
	tmp := a[l]; a[l] := a[j]; a[j] := tmp;
	partition := j;
end;

{ sortowanie szybkie }
procedure quicksort(var a:Array of pair;l,r:longint);
var j:longint;
begin
	if l<r then begin
		j := partition(a,l,r);
		quicksort(a,l,j-1);
		quicksort(a,j+1,r);
	end;
end;

{ Liczba budynkow }
var N,sqrtN:longint;
{ Wysokosci budynkow }
var H:Array[0..MAXN-1] of longint;
{ Posortowane interesujace budynki }
var HMax,interesting_count:longint;
var HSort:Array[0..MAXN-1] of pair;

{ Czy budynek o takiej wysokosci juz byl }
var was:Array[0..MAXSQRTN] of boolean;

{ Liczenie odpowiedzi dla danego budynku }
function get_answer(i:longint):longint;
	var max_bonus,j,htmp:longint;
begin
	get_answer := 0;
	{ Maksymalny bonus do wysokosci piorunochronu dla tego budynku }
	max_bonus :=  max(ceil(sqrt(i)), ceil(sqrt(N-1-i)));
	{ Szuka najdluzszego piorunochronu od najwyzszego budynku }
	for j := N - 1 downto 0 do
	begin
		{ Dalsze budynki sa za niskie zeby zmienic odpowiedz. }
		if HSort[j].first - H[i] + max_bonus <= get_answer then
			break;
		htmp := HSort[j].first - H[i] + ceil(sqrt(abs(HSort[j].second-i)));
		if htmp > get_answer then
			get_answer := htmp;
	end;
end;

var i:longint;

BEGIN
	read(N);
	for i := 0 to N-1 do
		read(H[i]);
	
	{ Preprocessing }
	for i := 0 to N-1 do begin
		HSort[i].first := H[i];
		HSort[i].second := i;
	end;
	quicksort(HSort, 0, N-1);
	{ Odpowiedzi }
	for i := 0 to N-1 do
		writeln(get_answer(i));
END.
