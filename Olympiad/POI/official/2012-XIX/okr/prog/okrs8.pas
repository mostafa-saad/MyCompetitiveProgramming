(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Okropny wiersz                                *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(n*q*sqrt(n))                                *
 *   Opis:                 Rozwiazanie powolne (naiwne sprawdzanie       *
 *                         dzielnikow)                                   *
 *                                                                       *
 *************************************************************************)

const
  MaxN = 500000;

var 
  A      : AnsiString;
  i,q,s,x,y,j,d,f,n : LongInt;
  period,len : LongInt;
  ok : Boolean;

begin
  ReadLn(n);
  ReadLn(A);
  ReadLn(q);
  for i:=1 to q do
  begin
    ReadLn(x,y);
    len := y-x+1;
    period := len;
    s:=Trunc(Sqrt(len))+1;
    for d:=1 to s do
    begin
      if len mod d<>0 then continue;
      ok := true;
      for j:=x to y-d do
        if A[j]<>A[j+d] then
        begin
          ok := false;
          break;
        end;
      if ok then
      begin
        period := d;
        break;
      end;
    end;
    if period=len then
    for d:=s downto 2 do
    begin
      if len mod d<>0 then continue;
      ok := true;
      f:=len div d;
      for j:=x to y-f do
        if A[j]<>A[j+f] then
        begin
          ok := false;
          break;
        end;
      if ok then
      begin
        period := f;
        break;
      end;
    end;
    WriteLn(period);
  end;
end.
