(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Okropny wiersz                                   *
 *   Autor:             Lech Duraj                                       *
 *   Zlozonosc czasowa: O(n + q sqrt(n))                                 *
 *   Opis:              Rozwiazanie powolne (haszowanie)                 *
 *                                                                       *
 *************************************************************************)

const
  Base = 97;
  Modulo : QWord = QWord(1) shl 31;
  MaxN = 500000;

var 
  A      : AnsiString;
  Hash,Powers   : array[0..MaxN] of QWord;
  n,i,j,q,s,x,y : LongInt;
  len, period : LongInt;


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
  ReadLn(q);
  for i:=1 to q do
  begin
    ReadLn(x,y);
    len := y-x+1;
    period := len;
    s := Trunc(Sqrt(len))+1;
    for j:=1 to s do
    begin
      if len mod j <> 0 then continue;
      if Equals(x,x+j,len-j) then
      begin
        period := j;
        break;
      end;
    end;
    if period=len then
    for j:=s downto 2 do
    begin
      if len mod j <> 0 then continue;
      if Equals(x,x+(len div j),len-(len div j)) then
      begin
        period := len div j;
        break;
      end;
    end;      
    WriteLn(period);
  end;
end.
