(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Okropny wiersz                                   *
 *   Autor:             Lech Duraj                                       *
 *   Zlozonosc czasowa: O(n log log n + q log n)                         *
 *   Opis:              Rozwiazanie wzorcowe (haszowanie)                *
 *                                                                       *
 *************************************************************************)

const
  Base = 97;
  Modulo : QWord = QWord(1) shl 31;
  MaxN = 500000;

var 
  A      : AnsiString;
  Divisor   : array[0..MaxN] of LongInt;
  Hash,Powers   : array[0..MaxN] of QWord;
  
  n,i,q,p,x,y     : LongInt;
  j : Int64;
  period, check : LongInt;


function Equals(a, b, len : LongInt) : Boolean;
begin
  Equals := ((Hash[a+len-1]+Modulo-Hash[a-1])*Powers[b-1]) mod Modulo = ((Hash[b+len-1]+Modulo-Hash[b-1])*Powers[a-1]) mod Modulo;
end;  
  
begin
  ReadLn(n);
  ReadLn(A);
  Powers[0] := 1;
  for i:=1 to n do 
    Powers[i] := (Powers[i-1]*Base) mod Modulo; 
  Hash[0] := 0;
  for i:=1 to n do
    Hash[i] := (Hash[i-1]+(Ord(A[i])-Ord('a'))*Powers[i-1]) mod Modulo;
  for i:=1 to n do
    Divisor[i] := i;
  for i:=2 to n do
    if Divisor[i]=i then
  begin
    j := Int64(i)*i;
    while j<=n do
    begin
      if Divisor[j]>i then Divisor[j] := i;
    j := j+i;
    end;
  end;
  ReadLn(q);
  for i:=1 to q do
  begin
    ReadLn(x,y);
  period := y-x+1;
  check := y-x+1;
  while check>1 do 
  begin
    p := Divisor[check];
    if Equals(x,x+(period div p),period-(period div p)) then
    begin
      period := period div p;
    check := check div p;
    end else
    begin
      while Divisor[check]=p do 
      check := check div p;
    end;
  end;
  WriteLn(period);
  end;
end.
