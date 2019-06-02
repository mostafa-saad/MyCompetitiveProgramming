(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Taksowki                                      *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie nieoptymalne,                     *
 *                         nieefektywne sortowanie                       *
 *                                                                       *
 *************************************************************************)

program taks3;

var 
  n : LongInt;
  m, d : Int64;
  x : array[0..500000] of Int64;

  i, j, best, result : LongInt;
  temp, cur_m, cur_d, delta : Int64;
begin
  Read(m, d, n);
  for i := 0 to n-1 do
    Read(x[i]);
  
  for i := 1 to n-1 do
  begin
    j := i;
    temp := x[i];
    while (j > 0) and (x[j-1] < temp) do
    begin
      x[j] := x[j-1];
      j := j-1;
    end;
    x[j] := temp;
  end;
  
  best := 0;
  
  for i := 0 to n-1 do
  begin
    if x[i] < m - d then continue;
    cur_m := m;
    cur_d := d;
    result := 1;
    for j := 0 to n do
    begin
      if j = i then continue;
      if (x[i] >= cur_m + cur_d) or ((j < n) and (x[j] >= cur_m + cur_d)) then
      begin
        if (best = 0) or (best > result) then best := result;
        break;
      end;
      if (j = n) or (x[j] < cur_d) then break;
      delta := x[j] - cur_d;
      if delta > cur_d then delta := cur_d;
      cur_d := cur_d - delta;
      cur_m := cur_m - delta;
      result := result + 1;
    end;
  end;
  
  WriteLn(best);
end.

