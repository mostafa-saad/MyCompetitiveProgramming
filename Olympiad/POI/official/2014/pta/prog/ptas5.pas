(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Ptaszek                                       *
 *   Autor:                Aleksander Lukasiewicz                        *
 *   Zlozonosc czasowa:    O(qnk)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************)

program Ptaszek;

const max_n = 1000003;
const inf = 1000000008;

var
  n, k, q, test, i, j, stop, add : longint;
  d : array[1..max_n] of longint;
  w : array[1..max_n] of longint;
  
begin
  Read(n);
  for i := 1 to n do
  begin
    Read(d[i]);
  end;
  Read(q);
  for test := 1 to q do
  begin
    Read(k);
  
    w[1] := 0;
    
    for i := 2 to n do
    begin
      w[i] := inf;
      stop := i-k;
      if stop < 1 then
	stop := 1;
      for j := i-1 downto stop do
      begin
	if d[j] <= d[i] then
	  add := 1
	else
	  add := 0;
	if w[i] > w[j] + add then
	  w[i] := w[j] + add;
      end;
    end;
    Writeln(w[n]);
    
    for i := 1 to n+1 do
      w[i] := 0;
    stop := 0;
    add := 0;  
  end;
end.

