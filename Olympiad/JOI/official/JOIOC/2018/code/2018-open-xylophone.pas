unit xylophone;

interface

procedure solve(N: longint);

implementation
uses xylophone_lib;

procedure solve(N: longint);
var
  A: array of longint;
  prv, crt, sig, min: longint;
  pos1, posN: longint;
  i: longint;
begin
  setlength(A, N + 1);
  sig := +1;
  prv := query(1, 2);
  A[1] := 0;
  A[2] := prv;
  for i := 3 to N do begin
    crt := query(i - 1, i);
    if prv + crt <> query(i - 2, i) then sig *= -1;
    A[i] := A[i - 1] + sig * crt;
    prv := crt;
  end;
  min := 0;
  for i := 1 to N do begin
    if min > A[i] then min := A[i];
  end;
  for i := 1 to N do begin
    A[i] += 1 - min;
  end;
  pos1 := -1;
  posN := -1;
  for i := 1 to N do begin
    if A[i] = 1 then pos1 := i;
    if A[i] = N then posN := i;
  end;
  if pos1 > posN then begin
    for i := 1 to N do begin
      A[i] := N + 1 - A[i];
    end;
  end;
  for i := 1 to N do begin
    answer(i, A[i]);
  end;
end;

end.
