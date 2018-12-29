(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Piorunochron                                     *
 *   Autor:             Juliusz Sompolski                                *
 *   Zlozonosc czasowa: O(n * sqrt(n) * lg(n))                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************)

uses Math;

const MAXN=500000;
const LOGN=22;
const MAXSQRTN=800;

{ Liczba budynkow }
var N:longint;
{ Wysokosci budynkow }
var H:Array[0..MAXN-1] of longint;

{ Kwadraty liczb naturalnych }
var SQ:array[0..MAXSQRTN] of longint;
{ Oblicza kwadraty liczb naturalnych }
procedure calc_SQ();
	var i:longint;
begin
	for i := 0 to MAXSQRTN do
		SQ[i] := i*i;
end;

{ Maximum }
function MAXIMUM(a,b:longint):longint;
begin
	if a > b then MAXIMUM := a else MAXIMUM := b;
end;

{ Spamietywanie maksimow na przedzialach jako slownik podslow bazowych. }

{ MAX[j] - drzewo przedzialowe; maksimum z tablicy H na przedziale [j*2^k, (j+1)*2^k) }
var MAX:Array[0..4*MAXN] of longint;
var START:longint;

{ Oblicza tablice MAX na podstawie tablicy H }
procedure calc_MAX();
	var i:longint;
begin
	START := 1;
	while(START < N) do
		START := START * 2;
	START := START - 1;
	for i := 0 to N-1 do
		MAX[START+i] := H[i];
	for i := START-1 downto 0 do
		MAX[i] := MAXIMUM(MAX[2*i+1], MAX[2*i+2]);
end;

{ Zwraca w czasie O(log(n)) maksimum z tablicy H na przedziale [a,b) }
function get_max(a,b:longint):longint;
	function _get_max(a,b,i,_start,_end:longint):longint;
		var m,l,r:longint;
	begin
		if (b <= _start) or (a >= _end) then begin
			_get_max := 0;
			exit;
		end;
		if (a <= _start) and (b >= _end) then begin
			_get_max := MAX[i];
			exit;
		end;
		m  := (_start+_end) div 2;
		l := _get_max(a, b, 2*i+1, _start, m);
		r := _get_max(a, b, 2*i+2, m, _end);
		_get_max := MAXIMUM(l,r);
	end;
begin
	if(a < 0) then a := 0;
	if(b >= N) then b := N;
	get_max := _get_max(a, b, 0, 0, START+1);
end;

{ Liczenie odpowiedzi dla danego budynku }
function get_answer(i:longint):longint;
	var ret,bonus,maxH:longint;
begin
	ret := 0;
	{*
	 * k >= H[j] -H[i] + bonus
	 * bonus+1 - bonus do wysokosci piorunochrona, wynikajacy ze sqrt(|i-j|)
	 * maxH - max(H[j]) na przedziale o danym bonusie.
	 *}
	// w prawo
	for bonus := 0 to N do
	begin
		if i + SQ[bonus] + 1 >= N then break; { prawdziwy warunek stopu petli }
		maxH := get_max(i+SQ[bonus]+1, i+SQ[bonus+1]+1);
		if maxH-H[i]+bonus+1 > ret then
			ret := maxH-H[i]+bonus+1;
	end;
	// w lewo
	for bonus := 0 to N do
	begin
		if i - SQ[bonus] - 1 < 0 then break; { prawdziwy warunek stopu petli }
		maxH := get_max(i-SQ[bonus+1], i-SQ[bonus]);
		if maxH-H[i]+bonus+1 > ret then
			ret := maxH-H[i]+bonus+1;
	end;
	get_answer := ret;
end;

var i:longint;

BEGIN
	read(N);
	for i := 0 to N-1 do
		read(H[i]);
	
	{ Preprocessing }
	calc_SQ();
	calc_MAX();
	
	{ Odpowiedzi }
	for i := 0 to N-1 do
		writeln(get_answer(i));
END.
