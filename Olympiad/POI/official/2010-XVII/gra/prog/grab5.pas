(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Gra w minima (GRA)                               *
 *   Plik:              grab5.pas                                        *
 *   Autor:             Jakub Lacki                                      *
 *   Opis:              Rozwiazanie niepoprawne.                         *
 *                      Rozwiazanie brutalne. Ze wzgledu na uzycie masek *
 *                      bitowych dla n>20 daje zle wyniki                *
 *   Zlozonosc czasowa: O(3^n)                                           *
 *                                                                       *
 *************************************************************************)
uses math;

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

const p20 = 1048576;

function max(a,b:longint):longint;
begin
    if a > b then
	max := a
    else
	max := b;
end;

var
    karty : array [0..MAXN-1] of longint;
    wynik : array [0..p20-1] of longint;
    n, k, i, maska, akt, pierwszy_bit, potega : longint;

begin
    read(n);
    for i:=0 to n-1 do
	read(karty[i]);

    quicksort(karty, 0, n-1);

    potega := round(power(2.0, n));

    wynik[0] := 0;

    for i:=1 to potega-1 do begin
	wynik[i] := 0;
	maska := i;
	akt := maska;
	while(akt <> 0) do begin
	    pierwszy_bit := 0;
	    while(akt and (1 shl pierwszy_bit) = 0) do
		inc(pierwszy_bit);
	    wynik[maska] := max(wynik[maska], karty[pierwszy_bit] - wynik[maska xor akt]);
	    akt := (akt - 1) and maska;
	end;
    end;

    writeln(wynik[potega-1]);
end.
