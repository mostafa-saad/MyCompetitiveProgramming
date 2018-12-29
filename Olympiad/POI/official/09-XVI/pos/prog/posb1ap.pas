(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Poszukiwania (POS)                                        *
 *   Plik:     posba1ap.pas                                              *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Rozwiazanie bledne. Zaklada, ze zawsze nalezy dzielic     *
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
		p := (l*a + r*b) div (a+b); // odpowiedz TAK "powyzej" p, odpowiedz NIE "ponizej" p
		if(pytaj('W', p)) then l := p+1 else r := p;
	end;
	
	// Udziela odpowiedzi
	odpowiedz(l);
end.
