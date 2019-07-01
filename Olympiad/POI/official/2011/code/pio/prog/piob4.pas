(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Piorunochron                                     *
 *   Autor:             Juliusz Sompolski                                *
 *   Zlozonosc czasowa: O(n * sqrt(n))                                   *
 *          pamieciowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************)

uses Math;

const MAXN=100000;
const LOGN=22;
const MAXSQRTN=820;

{ Liczba budynkow }
var N,sqrtN:longint;
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

{ MAX[k][j] - maksimum z tablicy H na przedziale [j, j+2^k) }
var MAX:Array[0..LOGN,0..MAXN] of longint;

{ Oblicza tablice MAX na podstawie tablicy H }
procedure calc_MAX();
	var i,j,k,p:longint;
begin
	for i := 0 to N-1 do
		MAX[0][i] := H[i];
	p := 1;
	for k := 1 to MAXN do
	begin
		if 2*p > N then break; { prawdziwy warunek stopu petli }
		for j := 0 to N-1 do
		begin
			MAX[k][j] := MAX[k-1][j];
			if (j + p < N) and (MAX[k-1][j+p] > MAX[k][j]) then
				MAX[k][j] := MAX[k-1][j+p];
		end;
		p := 2*p;
	end;
end;

{ Zwraca w czasie O(1) maksimum z tablicy H na przedziale [a,b)
    * - tak naprawde to dziala w czasie log(log(b-a)), ale dla int jest to ogr przez stala.
    * wstawka assemblerowa mozna by to zrobic komenda bsr
}
function get_max(a,b:longint):longint;
	var length,k:longint;
begin
	if(a < 0) then a := 0;
	if(b >= N) then b := N;
	length := b-a; k := 31;
	if ((length and $FFFF0000) = 0) then begin
		k := k-16; length := length shl 16;
	end;
	if ((length and $FF000000) = 0) then begin
		k := k-8; length := length shl 8;
	end;
	if ((length and $F0000000) = 0) then begin
		k := k-4; length := length shl 4;
	end;
	if ((length and $C0000000) = 0) then begin
		k := k-2; length := length shl 2;
	end;
	if ((length and $80000000) = 0) then begin
		k := k-1; length := length shl 1;
	end;
	{ k - najwieksze k, ze 2^k <= (b-a) }
	get_max := MAXIMUM(MAX[k][a], MAX[k][b-(1 shl k)]);
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
