(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Litery                                           *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************)

Program litery;
const 
  MAXN = 1000005;
var
  n, i, j: longint;
  wynik : int64;
  s1, s2 : array[0..MAXN] of char;
  temp : char;

begin
  n := 0; j := 0; wynik := 0;

  readln(n);
  readln(s1);
  readln(s2);

  for i := 0 to n - 1 do begin
    j := i;
    while s2[j] <> s1[i] do inc(j);
    while j > i do begin
      temp := s2[j];
      s2[j] := s2[j-1];
      s2[j-1] := temp;
      dec(j);
      inc(wynik);
    end;
  end;
  
  writeln(wynik);
end.
