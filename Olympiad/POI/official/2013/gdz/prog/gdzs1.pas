(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gdzie jest jedynka?                           *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(1)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************)

program gdzs1;

uses pgdzlib;

var i, j, n : LongInt;

begin
  n := inicjuj();
  if n = 1 then odpowiedz(1);
  for i := 1 to n do
    for j := i + 1 to n do
      if f(i, j, n - 1) = 1 then
      begin
        if g(i, j) = 0 then
          odpowiedz(i)
        else
          odpowiedz(j);
      end;
end.

