(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Gra w minima (GRA)                               *
 *   Plik:              gras2.pas                                        *
 *   Autor:             Jakub Lacki                                      *
 *   Opis:              Rozwiazanie powolne - nieefektywne sortowanie.   *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000000;

type tab = array [0..MAXN-1] of longint;

procedure wolne_sortowanie (var t:tab; n:longint);
   var 
       i,j,tmp:longint;
   begin 
	for i:= 1 to n - 1 do
	    for j:= i downto 1 do begin
		if t[j] >= t[j-1] then
		    break;
		tmp := t[j];
		t[j] := t[j-1];
		t[j-1] := tmp;
	    end;
   end;


var
    karty : array [0..MAXN-1] of longint;
    wynik : array [0..MAXN-1] of int64;
    n, i : longint;

begin
    read(n);
    for i:=0 to n-1 do
	read(karty[i]);

    wolne_sortowanie(karty, n);

    wynik[0] := karty[0];

    for i:=1 to n-1 do
	if wynik[i-1] > karty[i] - wynik[i-1] then
	    wynik[i] := wynik[i-1]
	else 
    	    wynik[i] := karty[i] - wynik[i-1];

    writeln(wynik[n-1]);
end.
