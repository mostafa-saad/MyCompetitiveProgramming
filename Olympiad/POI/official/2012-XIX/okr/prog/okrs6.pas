(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Okropny wiersz                                *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(n^2 + q)                                    *
 *   Zlozonosc pamieciowa: O(n + q)                                      *
 *   Opis:                 Rozwiazanie powolne (KMP offline)             *
 *                                                                       *
 *************************************************************************)

const
  MaxN = 500000;
  MaxQ = 1000000;

var 
  A      : AnsiString;
  KMP,R,C,D   : array[0..MaxN] of LongInt;
  P1,P2,Ans : array[0..MaxQ] of LongInt;
  i,q,s,x,y,j,n,k : LongInt;
  len : LongInt;

begin
  ReadLn(n);
  ReadLn(A);
  ReadLn(q);
  for i:=1 to n do
    C[i] := 0;
  for i:=1 to q do
  begin
    ReadLn(x,y);
    P1[i] := x;
    P2[i] := y;
    Inc(C[x]);
  end;
  D[1] := 1;
  for i:=2 to n do
    D[i] := D[i-1]+C[i-1];
  for i:=1 to q do
  begin
    x := P1[i];
    R[D[x]]:=i;
    Inc(D[x]);
  end;
  k:=1;
  for i:=1 to n do
  begin
    if P1[R[k]]>i then continue;
    KMP[0] := 0;
    KMP[1] := 0;
    s:=0;
    for j:=i+1 to n do
    begin
      while (s>0) and (A[j]<>A[i+s]) do
        s := KMP[s];
      if A[j] = A[i+s] then
        s := s+1;
      KMP[j-i+1] := s;
    end;
    while (k<=q) and (P1[R[k]]=i) do
    begin
      len := P2[R[k]]-P1[R[k]]+1;
      if len mod (len-KMP[len]) = 0 then
        Ans[R[k]] := len-KMP[len]
      else
        Ans[R[k]]:=len;
      Inc(k);
    end;
  end;
  for i:=1 to q do 
    WriteLn(Ans[i]);
end.
