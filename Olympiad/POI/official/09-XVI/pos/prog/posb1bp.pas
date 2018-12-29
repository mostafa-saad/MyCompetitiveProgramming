(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Poszukiwania (POS)                                        *
 *   Plik:     posb1bp.pas                                               *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Rozwiazanie bledne. Zaklada, ze zawsze nalezy podzielic   *
 *             przedzial w proporcji a do b                              *
 *                                                                       *
 *************************************************************************)

uses poslib;

var n,a,b,p:longint;
var l,r:int64;

begin
	inicjuj(n, a, b);
	l := 1; r := n;
	
	// Szuka Bajtyny
	while (l < r) do begin
		p := (l*b + r*a) div (a+b); // odpowiedz TAK "ponizej" p, odpowiedz NIE "powyzej" p
		if(pytaj('N', p)) then r := p-1 else l := p;
	end;
	
	// Udziela odpowiedzi
	odpowiedz(l);
end.
