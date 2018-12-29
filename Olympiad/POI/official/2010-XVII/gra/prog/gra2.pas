(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Gra w minima (GRA)                               *
 *   Plik:              gra2.pas                                         *
 *   Autor:             Jakub Lacki                                      *
 *   Opis:              Rozwiazanie wzorcowe.                            *
 *   Zlozonosc czasowa: O(n * log n)                                     *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000000;

type tab = array [0..MAXN-1] of longint;

procedure quicksort (var t:tab; l,r:longint);
   var 
       p,tmp:int64;
       i,j:longint;
   begin 
       if l < r then
       begin
           p := t[random(r-l) + l+1];
           i := l-1;
           j := r+1;
           repeat
               repeat i := i+1 until p <= t[i];
               repeat j := j-1 until p >= t[j];

               tmp:=t[i]; t[i]:=t[j]; t[j]:=tmp

           until i >= j;

           t[j]:=t[i];
	   t[i]:=tmp;

           quicksort(t,l,i-1);
           quicksort(t,i,r)
       end
   end;


var
    karty : array [0..MAXN-1] of longint;
    wynik : array [0..MAXN-1] of int64;
    n, i : longint;

begin
    read(n);
    for i:=0 to n-1 do
	read(karty[i]);

    quicksort(karty, 0, n-1);

    wynik[0] := karty[0];

    for i:=1 to n-1 do
	if wynik[i-1] > karty[i] - wynik[i-1] then
	    wynik[i] := wynik[i-1]
	else 
    	    wynik[i] := karty[i] - wynik[i-1];

    writeln(wynik[n-1]);
end.
