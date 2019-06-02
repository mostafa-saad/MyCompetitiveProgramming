(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kamyki (KAM)                                              *
 *   Plik:     kamb2.cpp                                                 *
 *   Autor:    Szymon Wrzyszcz                                           *
 *   Opis:     Rozwiazanie niepoprawne. Zaklada, ze r_n=r_{n-2}=...=0    *
 *             jest warunkiem dostatecznym, zeby uklad byl przegrywajacy.*
 *                                                                       *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000; {max. liczba kupek kamieni}

var
a    : array [0..MAXN] of longint; {liczba kamieni na poszczegolnych kupkach}
u    : longint;  {liczba ustawien poczatkowych do przeanalizowania}
n    : longint;  {liczba kupek kamieni}
i, j : longint;
odp  : string;
  
begin
  read(u);       
  for i:=1 to u do 
    begin    
      read(n);
      if n mod 2 = 0 then 
        begin
          for j:=0 to n-1 do
            read(a[j]);
        end 
      else 
        begin
          a[0] := 0;
	  for j:=1 to n do
	    read(a[j]);
	  inc(n);
        end;
      odp := 'NIE';
      j := 0;
      while j < n do 
        begin
          if a[j] <> a[j+1] then 
            begin
              odp := 'TAK';
              break;
            end;
          j := j + 2;
        end;
      
      writeln(odp);
    end
end.
