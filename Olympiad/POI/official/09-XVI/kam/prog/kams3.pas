(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kamyki (KAM)                                              *
 *   Plik:     kams3.cpp                                                 *
 *   Autor:    Szymon Wrzyszcz                                           *
 *   Opis:     Rozwiazanie wykladnicze bez spamietywania                 *
 *                                                                       *
 *                                                                       *
 *************************************************************************) 

const MAXN = 1000; {max. liczba kupek kamieni}

type
   uklad =  array[1..MAXN] of longint;

var
a    : uklad; {liczba kamieni na poszczegolnych kupkach}
u    : longint;  {liczba ustawien poczatkowych do przeanalizowania}
n    : longint;  {liczba kupek kamieni}
i, j : longint;

(* sprawdza czy nie ma juz zadnych kamieni *)
function koniec(var v : uklad) : boolean;
var
  i : integer;
begin
  i := 1;
  koniec := true;
  while (i <= n) and (koniec = true) do 
    begin
      if v[i]>0 then
        koniec := false;
      inc(i);
    end;
end;  

(* zwraca true gdy uklad v jest wygrywajacy, 0 wpp *)
function wygra(v : uklad) : boolean;
var
  i : integer;
  k : longint;
begin
  wygra := false;
  if not koniec(v) then 
    begin
      i := 1;
      while (i <= n) and (wygra = false) do 
	begin
          if i=1 then
            k := v[1]
        else
          k := v[i] - v[i-1];
	  while (k >= 1) and (wygra = false) do 
            begin
              v[i] := v[i] - k;
              if not wygra(v) then
	        wygra := true;
	      v[i] := v[i] + k;
	      dec(k);
	    end;
	  inc(i);
        end
    end
end;  
   
begin
  read(u);       
  for i:=1 to u do 
    begin 
      read(n);
      for j:=1 to n do
        read(a[j]);
   
      if wygra(a) then
        writeln('TAK')
      else
        writeln('NIE');
    end
end.
