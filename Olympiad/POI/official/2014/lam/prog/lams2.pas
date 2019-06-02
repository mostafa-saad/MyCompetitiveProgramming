(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Lampy sloneczne                               *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************)

program Lampy;

const MAXN = 200000;

var
  n, i, q_size, u, v : LongInt;
  angle0 : Boolean;
  x1, y1, x2, y2, temp64 : Int64;
  x, y : array[0..MAXN] of Int64;
  k, res, queue : array[0..MAXN] of LongInt;


begin
  ReadLn(n);
  ReadLn(x1, y1, x2, y2);
  angle0 := (x1 * y2 = x2 * y1);
  if x1 * y2 < x2 * y1 then
  begin
    temp64 := x1;
    x1 := x2;
    x2 := temp64;
    temp64 := y1;
    y1 := y2;
    y2 := temp64;
  end;
  for i := 0 to n - 1 do
    ReadLn(x[i], y[i]);
  for i := 0 to n - 1 do
    Read(k[i]);
  for i := 0 to n - 1 do
    res[i] := 0;
  for i := 0 to n - 1 do
  begin
    if res[i] > 0 then 
      continue;
    queue[0] := i;
    q_size := 1;
    while q_size > 0 do
    begin
      q_size := q_size - 1;
      u := queue[q_size];
      res[u] := 1 + i;
      for v := 0 to n - 1 do
        if (res[v] = 0) and
           (x1 * (y[v] - y[u]) - y1 * (x[v] - x[u]) >= 0) and
           ((x[v] - x[u]) * y2 - (y[v] - y[u]) * x2 >= 0) and
           ((not angle0) or (x1 * (x[v] - x[u]) + y1 * (y[v] - y[u]) > 0)) then
          begin
            k[v] := k[v] - 1;
            if k[v] = 0 then
            begin
              queue[q_size] := v;
              q_size := q_size + 1;
            end;
          end;
    end;
  end;
  
  for i := 0 to n - 1 do
  begin
    if i > 0 then
      Write(' ');
    Write(res[i]);
  end;
  WriteLn;
end.
