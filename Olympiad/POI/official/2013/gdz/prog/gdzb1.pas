(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gdzie jest jedynka?                           *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(1)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Uzywa tylko funkcji g                         *
 *                                                                       *
 *************************************************************************)

program gdzb1;

uses pgdzlib;

var n, best, i : LongInt;

begin
  n := inicjuj;
  best := 1;
  for i := 2 to n do
    if g(i, best) = 0 then
      best := i;
  odpowiedz(best);
end.

