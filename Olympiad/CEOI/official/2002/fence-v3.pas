const Nmax=20;
      Up=1;
      Down=0;
type Int=0..Nmax;
     Int0=0..1;
     Intx=longint; {treba dat int64}
var A:array[1..Nmax,1..Nmax,0..1] of Intx;
    N,N1:Int;
    i,M:integer;
    P:Intx;
    Perm:array[1..Nmax] of Int;

procedure FillTab;
var i,j,k:Int;
    sum:Intx;
begin
 if N1<2 then begin
  A[1,1,Up]:=1;
  A[1,1,Down]:=1;
 end;

 for i:=N1+1 to N do begin
  sum:=0;
  for j:=1 to i do begin
   A[i,j,Down]:=sum;
   sum:=sum+A[i-1,j,Up];
  end;
  for j:=1 to i do
   A[i,j,Up]:=A[i,(i-j+1),Down];
 end;

end;

procedure FindNext(z:Int0; N0:Int; poc:Intx);
var sum:Intx;
    k:Int;
begin
 if (N0=2) then begin
  if (z=Up) then begin Perm[1]:=2; Perm[2]:=1; end;
  if (z=Down) then begin Perm[2]:=2; Perm[1]:=1; end;
 end
 else begin
  sum:=0;
  if (z=Up) then k:=1 else k:=Perm[N0+1];
  while ((sum+A[N0,k,z])<poc) do begin
   k:=k+1;
   sum:=sum+A[N0,k-1,z]
  end;

  Perm[N0]:=k;
  FindNext(1-z,N0-1,poc-sum);

  for k:=1 to N0-1 do
   if Perm[k]>=Perm[N0] then Perm[k]:=Perm[k]+1;
 end;
end;

procedure FindFirst;
var i,i0:Int;
    sum:Intx;
begin
 sum:=0;
 for i:=1 to N do begin
  if ((sum+A[N,i,Down])>=P) then begin
   Perm[N]:=i;
   FindNext(Up,N-1,P-sum);
   i0:=i;
   break;
  end;

  sum:=sum+A[N,i,Down];

  if ((sum+A[N,i,Up])>=P) then begin
   Perm[N]:=i;
   FindNext(Down,N-1,P-sum);
   i0:=i;
   break;
  end;

  sum:=sum+A[N,i,Up];
 end;

 for i:=1 to N-1 do
  if Perm[i]>=Perm[N] then Perm[i]:=Perm[i]+1;
end;

procedure Output;
var i:Int;
begin
 for i:=1 to N-1 do
  write(Perm[N-i+1],' ');
 writeln(Perm[1]);
end;

procedure Count;
begin
 if (N=1) and (P=1) then writeln('1')
 else begin
  if N1<N then begin FillTab; N1:=N; end;
  if N>2 then FindFirst else
   if (P=1) then begin Perm[1]:=2; Perm[2]:=1; end
            else begin Perm[1]:=1; Perm[2]:=2; end;
  Output;
 end;
end;

begin
 N1:=1;
 readln(M);
 for i:=1 to M do begin
  read(N);   {zubata permutacia kolkateho radu}
  readln(P); {kolkata zubata permutacia v poradi}
  Count;
 end;
end.