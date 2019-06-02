(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Karty                                         *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(nm)                                         *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Prosty algorytm dynamiczny                    *
 *                                                                       *
 *************************************************************************)

program Karty;
var 
  A,B : array[1..200000] of LongInt;
  m,n,tmp : LongInt;
  i,j,p,x,y : LongInt;
  ok : Boolean;

begin
  ReadLn(n);
  for i:=1 to n do
  begin
    ReadLn(A[i],B[i]);
    if A[i]>B[i] then
    begin
      tmp := A[i];
      A[i] := B[i];
      B[i] := tmp;
    end;
  end;
  ReadLn(m);
  for j:=1 to m do
  begin
    ReadLn(x,y);
    tmp:=A[x];
    A[x]:=A[y];
    A[y]:=tmp;
    tmp:=B[x];
    B[x]:=B[y];
    B[y]:=tmp;
    p := -1000000001;
    ok := true;
    for i:=1 to n do begin
      if A[i]>=p then
        p := A[i]
      else if B[i]>=p then
        p := B[i]
      else begin
        ok := false; 
        break;
      end;
    end;
    if ok then 
      WriteLn('TAK')
    else 
      WriteLn('NIE');
  end;
end.
