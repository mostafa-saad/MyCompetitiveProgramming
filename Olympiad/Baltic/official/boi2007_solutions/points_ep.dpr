program points;
{ Erik Panzer }

const
  Dim = 3;
  Base = 1000000000;

type
  TMat = Array[0..DIM-1, 0..DIM-1] of Int64;

var
  F: Text;
  n: LongInt;
  A: TMat   = ((0,0,1),
               (0,0,2),
               (2,1,4));
  Pot: TMat = ((1,0,0),
               (0,1,0),
               (0,0,1));

Procedure Copy(var X, Y: TMat);
Var
  i, j: LongInt;
Begin
  For i:=0 to Dim-1 do
    For j:=0 to Dim-1 do
      Y[i][j] := X[i][j];
End;

Procedure Mult(var X, Y, Z: TMat);
Var
  i, j, k: LongInt;
Begin
  For i:=0 to Dim-1 do
    For j:=0 to Dim-1 do begin
      Z[i][j] := 0;
      for k:=0 to Dim-1 do
        Inc(Z[i][j], X[i][k]*Y[k][j]);
      Z[i][j] := Z[i][j] mod BASE;
    end;
End;

Function Calc: LongInt;
Var
  T: TMat;
Begin
  if (n<2) then begin
    Calc := 0;
    Exit;
  end;
  Dec(n, 2);
  while (n>0) do begin
    if (n AND 1 = 1) then begin
      Mult(A, Pot, T);
      Copy(T, Pot);
    end;
    Mult(A, A, T);
    Copy(T, A);
    n := n div 2;
  end;
  Calc := (4*Pot[0,1]+2*Pot[0,2]+2*Pot[2,1]+Pot[2,2]) mod BASE;
End;

begin
  Assign(F, 'points.in');
  Reset(F);
  ReadLn(F, n);
  Close(F);
  Assign(F, 'points.out');
  Rewrite(F);
  WriteLn(F, calc);
  Close(F);
end.
