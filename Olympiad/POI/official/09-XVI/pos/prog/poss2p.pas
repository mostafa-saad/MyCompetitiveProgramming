(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Poszukiwania (POS)                                        *
 *   Plik:     poss2p.pas                                                *
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

{
	Podzial przedzialu dlugosci n na przedzialy dlugosci i dla TAK i n-i dla NIE.
	Pesymistyczny koszt, to wiekszy z kosztow odpowiedzi 
	- TAK i kosztu dla przedzialu dlugosci i
	- NIE i kosztu dla przedzialu dlugosci n-i
	czyli f(i) = MAX(a+t(i),b+t(n-i))
	t(n) jest niemalejace, a wiec a+t(i) jest niemalejace, b+t(n-i) jest nierosnace,
	czyli f(i) ma co najwyzej jedno minimum lokalne.
		
	Funkcja oblicza minimum funkcji f(i) w danym przedziale i dla danego n
}
function t_(n:longint):longint; forward;

function min(n,l,r:longint):longint;
	var i,wyn,p1,p2,f1,f2:longint;
begin
	if (r - l >= 250) then begin
		p1 := (2*l+r) div 3; p2 := (l+2*r) div 3; // punkty podzialu przedzialu [l,r] na 3
		if a+t_(p1) > b+t_(n-p1) then f1 := a+t_(p1) else f1 := b+t_(n-p1);
		if a+t_(p2) > b+t_(n-p2) then f2 := a+t_(p2) else f2 := b+t_(n-p2);
		if (f1 < f2) then min := min(n,l,p2-1) // f(p2)>f(p1), wiec minimum jest w [l,p2]
		else if( f1 > f2) then min := min(n,p1+1,r) // f(p1)>f(p2), wiec minimum jest w [p1,r]
		else { f1 == f2 } begin
			{
				Jezeli w ktorymkolwiek z przedzialow [l,p1], [p1,p2], [p2,r] jest wartosc mniejsza,
				to jest ona minimum.
			}
			if (min(n,p1,p2) < f1) then begin min := T[n]; exit; end
			else if(min(n,l,p1) < f1) then begin min := T[n]; exit; end
			else if(min(n,p2,r) < f1) then begin min := T[n]; exit; end
		end;
	end else begin
		T[n] := INF;
		for i := l to r do begin
			if a+t_(i) > b+t_(n-i) then wyn := a+t_(i) else wyn := b+t_(n-i);
			if (wyn < T[n]) then begin T[n]:=wyn; P[n]:=i; end // podzial lepszy od dotychczas obliczonego minimum.
		end;
	end;
	min := T[n];
end;

{
Oblicza lub zwraca spamietane t[i] i p[i]
}
function t_(n:longint):longint;
begin
	if (n <= 1) then begin t_ := 0; exit; end;
	if (T[n] = 0) then min(n,1,n-1);
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
