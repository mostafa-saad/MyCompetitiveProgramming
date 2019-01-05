{ Problem BUGS
  CEOI 2002, Kosice
  by David Pal
}

Program Bugs;

const MaxN = 1000;
      MaxM = 10;
      Max = 3*243; { 3^10 }

var D,N,M,K,i,j,x,y:longint;
    bad:array[0..MaxN-1, 0..MaxM-1] of boolean;  { bad squares }
    pow3:array[0..MaxM] of longint; { powers of 3 }

function maximum(a,b:longint):longint;
begin
     if a>b then maximum:=a else maximum:=b;
end;

function compute:longint;
var i,j,p,k:longint;
    base,base1back,base2back,base3back:longint;
    lying, standing:boolean;
    A:array[0..3,0..Max-1] of longint;
    pp:array[0..MaxM] of longint;
begin
     fillchar(A, sizeof(A), 0);
     base:=0;

     for i:=1 to N-1 do
     for j:=0 to M-1 do
     begin
          base:=(base+1) mod 4;
          base1back:=(base+3) mod 4;    { -1 = 3 (mod 4)  }
          base2back:=(base+2) mod 4;    { -2 = 2 (mod 4)  }
          base3back:=(base+1) mod 4;    { -3 = 1 (mod 4)  }

          lying:= (i>=2) and (j>=1) and { can be put a 3x2 rectangle with right bottom corner on (i,j) }
                not (bad[i,j] or bad[i-1,j] or  bad[i-2,j] or
                     bad[i,j-1] or bad[i-1,j-1] or  bad[i-2,j-1]);

          standing:= (i>=1) and (j>=2) and { can be put a 2x3 rectangle with right bottom corner on (i,j) }
                not (bad[i,j] or bad[i-1,j] or
                     bad[i,j-1] or bad[i-1,j-1] or
                     bad[i,j-2] or bad[i-1,j-2]);

          fillchar(pp, sizeof(pp), 0);

          for p:=0 to pow3[M]-1 do
          begin
               if pp[j]>0 then A[base][p]:=A[base1back][p-pow3[j]]
               else
               begin  { pp[j]=0 }
                      A[base][p]:=A[base1back][p];

                      if lying and (pp[j-1]=0) then  { try to put a lying rectangle on (i,j) }
                         A[base][p]:=maximum(A[base][p], A[base2back][p+8*pow3[j-1]]+1);

                      if standing and (pp[j-1]=0) and (pp[j-2]=0) then { try to put a standing rectangle on (i,j) }
                         A[base][p]:=maximum(A[base][p], A[base3back][p+13*pow3[j-2]]+1);
               end;

               k:=0;      { increase pp by one }
               while (pp[k]=2) do begin pp[k]:=0; inc(k); end;
               inc(pp[k]);
          end;

     end;

     compute:=A[base][0];
end;

begin
     read(D);
     for i:=1 to D do
     begin
          read(N,M,K);

          fillchar(bad, sizeof(bad), 0);
          for j:=1 to K do
          begin
               read(x,y);
               bad[x-1,y-1]:=true;
          end;

          pow3[0]:=1;
          for j:=1 to M do pow3[j]:=3*pow3[j-1];

          writeln(compute);
     end;
end.
