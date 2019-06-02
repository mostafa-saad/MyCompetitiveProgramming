(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Poszukiwania (POS)                                        *
 *   Plik:     poss1p.pas                                                *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Rozwiazanie wolne O(n^2). Pamiec O(n).                    *
 *                                                                       *
 *************************************************************************)

uses poslib;

const INF = 2000000000;

var n,a,b:longint;
var l,r:longint;

{
Oblicza lub zwraca spamietane t[i] i p[i]
	t[n] - koszt odpowiedzi dla przedzialu zawierajacego i pieter.
	p[n] - dlugosc przedzialu dla odpowiedzi TAK jaki nalezy zadac majac przedzial zawierajacy n pieter aby utrzymac sie w pesymistycznym koszcie.
}
var T,P:array[1..2000000] of longint;
function t_(n:longint):longint;
	var i,wyn:longint;
begin
	if (n <= 1) then begin t_ := 0; exit; end;
	if (T[n] = 0) then begin
		T[n] := INF;
		for i := 1 to n-1 do begin
			{
			Podzial przedzialu dlugosci n na przedzialy dlugosci i dla TAK i n-i dla NIE.
			Pesymistyczny koszt, to wiekszy z kosztow odpowiedzi 
			- TAK i kosztu dla przedzialu dlugosci i
			- NIE i kosztu dla przedzialu dlugosci n-i
			}
			if a+t_(i) > b+t_(n-i) then wyn := a+t_(i) else wyn := b+t_(n-i);
			if (wyn < T[n]) then begin T[n]:=wyn; P[n]:=i; end // podzial lepszy od dotychczas obliczonego minimum.
		end;
	end;
	t_ := T[n];
end;

function p_(n:longint):longint;
begin
	if (P[n] = 0) then t_(n); // efektem ubocznym obliczenia t[n] bedzie obliczenie p[n].
	p_ := P[n];
end;

var i:longint;

begin
	inicjuj(n, a, b);
	l := 1; r := n;
	
	// Szuka Bajtyny
	while (l < r) do begin
		i := p_(r-l+1); // dlugosc przedzialu na ktory pytanie powinno dawac odpowiedz TAK
		if (pytaj('N', l+i)) then r := l+i-1 else l := l+i;
	end;
	
	// Udziela odpowiedzi
	odpowiedz(l);
end.
