(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kamyki (KAM)                                              *
 *   Plik:     kam1.pas                                                  *
 *   Autor:    Szymon Wrzyszcz                                           *
 *   Opis:     Rozwiazanie wzorcowe O(n)                                 *
 *                                                                       *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000; {max. liczba kupek kamieni}

var
a : array [1..MAXN] of longint; {liczba kamieni na poszczegolnych kupkach}
d : array [1..MAXN] of longint; {odwrocony ciag roznic rozmiarow kolejnych kupek kamieni}
u : longint;  {liczba ustawien poczatkowych do przeanalizowania}
n : longint;  {liczba kuek kamieni}
x : longint;  {xor d[1], d[3], ..}
i, j : longint;
  
begin
  read(u);       
  for i:=1 to u do 
    begin 
      x := 0;
      
      read(n);
      for j:=1 to n do
        read(a[j]);
    
      for j:=1 to n-1 do
        d[j] := a[n-j+1] - a[n-j]; {wyznaczanie ciagu d}  
      d[n] := a[1];
  
      j := 1;
      while j <= n do {xor-uj elementy o nieparzystych indeksach}
        begin
          x := x xor d[j];
          j := j + 2;
        end;
      
      if x > 0 then
        writeln('TAK')
      else
        writeln('NIE');
    end
end.
