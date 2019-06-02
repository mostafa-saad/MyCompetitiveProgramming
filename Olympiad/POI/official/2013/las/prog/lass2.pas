(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Laser                                         *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(n^k)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Backtrack                                     *
 *                                                                       *
 *************************************************************************)

program Laser;

const MaxV = 500000;

type Point = record
               x, y : LongInt;
               t    : ShortInt;
               num  : LongInt;
             end;


type PointArray = array[1..2*MaxV] of Point;

function det(var a,b : Point) : Int64;
begin
  det := a.x*Int64(b.y)-a.y*Int64(b.x);
end;

function cmp(var a,b : Point) : Boolean;
var d : Int64;
begin
  d := det(a,b);
  if (d<0) or ((d=0) and (a.t>b.t)) then
    cmp := True
  else
    cmp := False;
end;

function Max(x,y : LongInt) : LongInt; inline;
begin
  if x>y then
    Max := x
  else
    Max := y;
end;

procedure QuickSort(var T : PointArray; p,q : LongInt);
var pivot,tmp : Point;
    i,j   : LongInt;
begin
  pivot := T[(4*p+5*q) div 9];
  i := p;
  j := q;
  repeat
    while (i<=q) and cmp(T[i],pivot) do Inc(i);
    while (j>=p) and cmp(pivot,T[j]) do Dec(j);
    if (i<=j) then begin
      tmp := T[i];
      T[i] := T[j];
      T[j] := tmp;
      Inc(i);
      Dec(j);
    end;
  until (i>j);
  if (j>p) then QuickSort(T,p,j);
  if (i<q) then QuickSort(T,i,q);
end;


var 
  k, n : LongInt;
  i, j, f, c, s : LongInt;
  x1,y1,x2,y2   : LongInt;
  P : PointArray;
  Number,Rightmost,Weight,Finish : array[1..2*MaxV] of LongInt;
  

function Backtrack(a,shots : LongInt) : LongInt;
var partial : LongInt;
    q       : LongInt;
begin
  partial := 0;
  if shots=0 then
    Backtrack := 0
  else begin
    for q:=a to s do
      partial := Max(partial,Weight[q]+Backtrack(Rightmost[q]+1,shots-1));
    Backtrack := partial;
  end;
end;

begin
  ReadLn(k,n);

  for i:=1 to n do 
  begin
    ReadLn(x1,y1,x2,y2);
    P[2*i-1].x := x1;
    P[2*i-1].y := y1;
    P[2*i-1].t := 1;
    P[2*i-1].num := i;
    P[2*i].x := x2;
    P[2*i].y := y2;
    P[2*i].t := -1;
    P[2*i].num := i;
    if cmp(P[2*i],P[2*i-1]) then begin
      P[2*i-1].t := -1;
      P[2*i].t := 1;
    end;
  end;
  if n=0 then begin
    WriteLn(0);
    Halt(0);
  end;
  QuickSort(P,1,2*n);
  
  Number[1] := 1;
  for i:=2 to 2*n do
    if det(P[i-1],P[i])<0 then 
      Number[i] := Number[i-1]+1
    else
      Number[i] := Number[i-1];
      
  for i:=1 to 2*n do
    if P[i].t=-1 then
      Finish[P[i].num] := Number[i];
      
  s := Number[2*n];
  c := 0;
  for j:=1 to s do begin
    Weight[j] := 0;
    Rightmost[j] := 1;
  end;
  for i:=1 to 2*n do begin
    if (c>Weight[Number[i]]) then
      Weight[Number[i]] := c;
    c := c+P[i].t;
    if (c>Weight[Number[i]]) then
      Weight[Number[i]] := c;
  end;
  f := 1;
  for i:=1 to 2*n do begin
    j := P[i].num;
    if Finish[j]>f then
      f := Finish[j];
    if f>Rightmost[Number[i]] then
      Rightmost[Number[i]] := f;
  end;
    
  WriteLn(Backtrack(1,k));
end.
