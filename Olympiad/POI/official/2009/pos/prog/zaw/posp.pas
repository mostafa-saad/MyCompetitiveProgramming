(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Poszukiwania (POS)                                        *
 *   Plik:     posp.pas                                                 *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Rozwiazanie przykladowe dla zawodnikow                    *
 *                                                                       *
 *************************************************************************)

uses poslib;

var n, a, b, p:longint;
var l, r:longint;

begin
	inicjuj(n, a, b);
	l := 1; r := n;
	
	(* Szuka Bajtyny *)
	while (l < r) do begin
		p := (l + r) div 2;
		if(pytaj('W', p)) then l := p + 1 else r := p;
	end;
	
	(* Udziela odpowiedzi *)
	odpowiedz(l);
end.
