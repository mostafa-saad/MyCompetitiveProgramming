(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Laser                                         *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(n^2*k)                                      *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Programowanie dynamiczne, ale zamiast         *
 *                         spamietywac konce liczy je za kazdym razem    *
 *                         od nowa                                       *
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
  i, j, s, q, r, m : LongInt;
  leftmost,weight : LongInt;
  x1,y1,x2,y2   : LongInt;
  P : PointArray;
  Number,Start,Finish : array[1..2*MaxV] of LongInt;
  Result : array[0..1,0..2*MaxV] of LongInt;
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
  s:=Number[2*n];      
  for i:=1 to 2*n do
    if P[i].t=1 then
      Start[P[i].num] := Number[i]
    else
      Finish[P[i].num] := Number[i];
  
  for j:=0 to s do 
    Result[0,j]:=0;
  Result[1,0]:=0;
  for i:=1 to k do begin
    q := i mod 2;
    r := (i-1) mod 2;
    for j:=1 to s do begin
      weight := 0;
      leftmost := s;
      for m := 1 to n do 
        if (Start[m]<=j) and (Finish[m]>=j) then begin
          Inc(weight);
          if Start[m]<leftmost then
            leftmost := Start[m];
        end;
      Result[q,j] := Max(Result[q,j-1],Result[r,leftmost-1]+weight);
    end;
  end;
    
  WriteLn(Result[k mod 2,s]);
end.
