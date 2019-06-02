(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Karty                                         *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(n + m sqrt(n))                              *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************)

program Karty;
var
   P,Q : array[0..300000] of LongInt;
   B   : array[0..1,0..300000] of LongInt;
   A   : array[0..1,0..2000] of Boolean;
   s   : LongInt;
   
procedure recompute(j : LongInt);
var x,y : LongInt;
    i : LongInt;
    r : ShortInt;
begin
  x := j*s;
  y := j*s+s-1;
  A[0][j] := true;
  A[1][j] := true;
  B[0][x] := P[x];
  B[1][x] := Q[x];
  for r:=0 to 1 do 
  begin
    for i:=x+1 to y do
    begin
      if P[i] >= B[r][i-1] then
        B[r][i] := P[i]
      else 
      begin
        if Q[i] >= B[r][i-1] then
          B[r][i] := Q[i]
        else 
        begin 
          A[r][j] := false; break;
        end;
      end;
    end;
  end;
end;

procedure Swap(var x,y : LongInt);
var tmp : LongInt;
begin
  tmp:=x;
  x:=y;
  y:=tmp;
end;

var
  n,m,k,t : LongInt;
  i,j   : LongInt;
  x,y   : LongInt;
  ok    : Boolean;
  
begin
  ReadLn(n);
  s := Round(Sqrt(n));
  if s<3 then
    s := 3;
  for i:=0 to n-1 do
  begin
    ReadLn(P[i],Q[i]);
    if (P[i]>Q[i]) then swap(P[i],Q[i]);
  end;
  while (n mod s) <> 0 do 
  begin
    P[n] := 100000001;
    Q[n] := 100000001;
    n := n+1;
  end;
  k := n div s;
  for i:=0 to k-1 do
    recompute(i);
  ReadLn(m);
  for j:=0 to m-1 do
  begin
    ReadLn(x,y);
    x:=x-1; y:=y-1;
    swap(P[x],P[y]);
    swap(Q[x],Q[y]);
    recompute(x div s);
    recompute(y div s);
    t := -1000000001;
    ok := true;
    for i:=0 to k-1 do
    begin
      ok := false;
      if (t<=P[i*s]) and A[0][i] then
      begin
        t := B[0][i*s+s-1]; 
        ok := true;
      end
      else
      if (t<=Q[i*s]) and A[1][i] then
      begin
        t := B[1][i*s+s-1]; 
        ok := true;
      end;
      if not ok then break;
    end;
    if ok then WriteLn('TAK') else WriteLn('NIE');
  end;
end.
