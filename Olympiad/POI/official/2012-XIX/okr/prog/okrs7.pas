(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Okropny wiersz                                *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(n*q)                                        *
 *   Opis:                 Rozwiazanie powolne (KMP przy kazdym          *
 *                         zapytaniu)                                    *
 *                                                                       *
 *************************************************************************)

const
  MaxN = 500000;

var 
  A      : AnsiString;
  KMP   : array[0..MaxN] of LongInt;
  i,q,s,x,y,j,n : LongInt;
  len : LongInt;

begin
  ReadLn(n);
  ReadLn(A);
  ReadLn(q);
  for i:=1 to q do
  begin
    ReadLn(x,y);
    len := y-x+1;
    KMP[0] := 0;
    KMP[1] := 0;
    s:=0;
    for j:=x+1 to y do
    begin
      while (s>0) and (A[j]<>A[x+s]) do
        s := KMP[s];
      if A[j] = A[x+s] then
        s := s+1;
      KMP[j-x+1] := s;
    end;
    if len mod (len-KMP[len]) = 0 then
      WriteLn(len-KMP[len])
    else
      WriteLn(len);
  end;
end.
