program sequence;
{Erik Panzer}

const
  MAX_N = 100000;
  MAX_A = 1000000;

var
  F: Text;
  N, V, K: LongInt;
  C: Int64;
  a: Array[0..MAX_N+1] of LongInt;

begin
  (* Input *)
  Assign(F, 'sequence.in');
  Reset(F);
  ReadLn(F, N);
  C := 0;
  K := 1;
  a[0] := MAX_A+1;
  a[1] := MAX_A+1;
  while N>0 do begin
    Dec(N);
    ReadLn(F, V);
    while a[K-1]<=V do begin
      Inc(C, a[K-1]);
      Dec(K);
    end;
    if a[K]<=V then
      Inc(C, V)
    else
      Inc(K);
    a[K] := V;
  end;
  For V:=2 to K-1 do
    Inc(C, a[V]);
  Close(F);
  (* Output *)
  Assign(F, 'sequence.out');
  Rewrite(F);
  WriteLn(F, C);
  Close(F);
end.
