(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Poszukiwania (POS)                                        *
 *   Plik:     pos1.pas                                                  *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Rozwiazanie wzorcowe O(max(a,b)*log n)                    *
 *                                                                       *
 *************************************************************************)

uses poslib;

const MAXN=1000000000;
const MAXAB=10000;

const TAK=1;
const NIE=0;

var n,a,b:longint;

{
Oblicza lub zwraca spamietane Q[i]
Q[i] - maksymalna liczba pieter wsrod ktorych mozna znalezc odpowiedz kosztem i
}
var Q:array[0..100*MAXAB] of longint;
function q_(i:longint):longint;
begin
	if i < 0 then begin q_ := 0; exit; end;
	if Q[i] = 0 then begin // jesli nie bylo jeszcze obliczone, to oblicz
		{ Majac do dyspozycji i bajtalarow zadajemy pytanie
		i albo zostajemy z i-a bajtalarami i maksymalnie mozemy obsluzyc i-a pieter
		albo zostajemy z i-b bajtalarami i maksymalnie mozemy obsluzyc i-b pieter
		}
		Q[i] := q_(i-a) + q_(i-b);
		if Q[i] = 0 then Q[i] := 1; // zawsze mozna zgadnac jak sie ma jedno pietro.
	end;
	q_ := Q[i];
end;

var l,r,w:longint;

BEGIN
	inicjuj(n, a, b);
	l := 1; r := n;
	
	(* Wyznacza koszt, jaki musi poniesc Bajtek. *)
  w := 0;
  while q_(w) < n do Inc(w);
	
	(* Szuka Bajtyny *)
	while l < r do begin
		(* Po odpowiedzi Bitocego moglo sie poprawic szacowanie *)
		while q_(w) >= r-l+1 do w := w - 1;
		w := w + 1;
		
		(* Zadaj pytanie *)
		if pytaj('N', l+q_(w-a)) then begin // odpowiedz TAK
			(* Bajtyna w przedziale [l, l+q_(w-A)-1] dlugosci q_(w-A) => do znalezienia w koszcie w-A *)
			r := l+q_(w-a)-1;
			w := w-a;
		end else begin // odpowiedz NIE
			(* Bajtyna w przedziale [l+q_(w-A), r] dlugosci q_(w)-q_(w-A)=q_(w-B) => do znalezienia w koszcie w-B *)
			l := l+q_(w-a);
			w := w-b;
		end;
	end;
	
	(* Udziela odpowiedzi *)
	odpowiedz(l);
END.
