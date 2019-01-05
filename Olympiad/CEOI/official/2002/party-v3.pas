{Predpokladam, ze su tam cisla 1..pocet a ich zaporne tvary a operacie su:
 Imp  -> ... *
 And  &  ... &
 Or   \/ ... +}

const Nmax=200;
type Item=record t:0..2; s:string; end;
     Stack=array[1..Nmax] of Item;

var P:Stack;
    A:array[1..Nmax] of -1..1;
    B:array[1..Nmax] of -1..1;

    i,M,X,Code:integer;
    MaxItems:integer;
    StackLength:integer;

function FindOperation(S:string):integer;
var j,x:integer;
    I,Code:integer;
    s1:string;
begin

 if (S[1]<>'(') then begin
  j:=2;
  s1:=Copy(S,1,j);
  Val(s1,I,Code);
  while (Code=0) do begin
   s1:=s1+S[j+1];
   inc(j);
   Val(s1,I,Code);
  end;
  FindOperation:=j;
 end

 else begin
  x:=1;
  for j:=2 to length(S) do begin
   if S[j]='(' then inc(x);
   if S[j]=')' then dec(x);
   if (x=0) then begin FindOperation:=j+1; break; end;
  end;
 end;

end;

procedure Postfix;
var OK:boolean;
    L,X,Op,Code,I,Max:integer;
    S:string;
begin
 L:=M+(M-1);
 OK:=false;

 while not OK do begin
  OK:=true;
  for i:=1 to L do
   if P[i].t=2 then begin
    OK:=false;
    S:=P[i].s;
    X:=i;
    Op:=FindOperation(P[i].s);
   end;

  if not OK then begin
   for i:=L downto X+1 do
    P[i+2]:=P[i];

   P[X].s:=Copy(S,1,Op-1);
   Val(P[X].s,I,Code);
   if Code <> 0 then begin {it is not a number}
    P[X].t:=2;
    P[X].s:=Copy(P[X].s,2,length(P[X].s)-2);
   end
   else P[X].t:=1;       {it is a number}

   P[X+1].s:=Copy(S,Op+1,length(S)-Op);
   Val(P[X+1].s,I,Code);
   if Code <> 0 then begin {it is not a number}
    P[X+1].t:=2;
    P[X+1].s:=Copy(P[X+1].s,2,length(P[X+1].s)-2);
   end
   else P[X+1].t:=1;     {it is a number}

   P[X+2].s:=S[Op];
   P[X+2].t:=0;          {this is an operation}

   L:=L+2;
  end

 end;

 max:=1;
 for X:=1 to L do
  if (P[X].t=1) then begin
   Val(P[X].s,I,Code);
   if (abs(I)>max) then max:=abs(I);
  end;

 MaxItems:=max;
 StackLength:=L;

end;

procedure Control;
var i,j:integer;
    Code,X:integer;

 function sgn(X:integer):integer;
 begin
  if X>0 then sgn:=1 else if X<0 then sgn:=-1 else sgn:=0;
 end;

begin
 j:=2;

 Val(P[1].s,X,Code);
 B[1]:=sgn(X)*A[abs(X)];

 Val(P[2].s,X,Code);
 B[2]:=sgn(X)*A[abs(X)];

 for i:=3 to StackLength do
  if (P[i].t=1) then begin
   inc(j);
   Val(P[i].s,X,Code);
   B[j]:=A[abs(X)]*sgn(X);
  end
  else begin
   case P[i].s[1] of
    '@'{Imp}: if ((B[j-1]<0) or  (B[j]>0)) then B[j-1]:=1 else B[j-1]:=-1;
    '+'{Or} : if ((B[j-1]>0) or  (B[j]>0)) then B[j-1]:=1 else B[j-1]:=-1;
    '&'{And}: if ((B[j-1]>0) and (B[j]>0)) then B[j-1]:=1 else B[j-1]:=-1;
   end;
   dec(j);
  end;

 if B[1]>0 then begin
  for i:=1 to MaxItems-1 do write(A[i],' ');
  writeln(A[MaxItems]);
 end;

end;

procedure Generate(i:integer);
begin
 if i=MaxItems+1 then Control
 else begin
  A[i]:=-1; Generate(i+1);
  A[i]:= 1; Generate(i+1);
 end;
end;

begin
 readln(M);
 for i:=1 to M do begin
  readln(P[i].s);
  Val(P[i].s,X,Code);
  if Code <> 0 then P[i].t:=2 else P[i].t:=1;
 end;

 for i:=1 to M-1 do begin
  P[i+M].t:=0 ;
  P[i+M].s:='&';
 end;

 Postfix;
 Generate(1);
end.