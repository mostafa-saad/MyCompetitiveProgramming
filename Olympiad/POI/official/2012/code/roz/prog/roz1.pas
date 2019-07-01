(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Rozklad Fibonacciego                             *
 *   Autor:             Karol Pokorski                                   *
 *   Zlozonosc czasowa: O(log^2(k))                                      *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************)

const
  MAXN = 87;

var
  fib : array[0 .. MAXN] of Int64;
  i, Q, res : LongInt;
  K, n : Int64;

begin
  fib[0] := 1; fib[1] := 1;
  for i := 2 to MAXN - 1 do
    fib[i] := fib[i - 1] + fib[i - 2];

  ReadLn(Q);

  while Q > 0 do
  begin
    Dec(Q);
    res := 0;

    ReadLn(K);

    while K > 0 do
    begin
      n := K;

      for i := 0 to MAXN - 1 do
        if abs(K - fib[i]) < n then
          n := abs(K - fib[i]);

      K := n;

      Inc(res);
    end;

    WriteLn(res);
  end;
end.
