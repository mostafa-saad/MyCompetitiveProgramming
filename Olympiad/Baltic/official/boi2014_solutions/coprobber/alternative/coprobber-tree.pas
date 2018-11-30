unit coprobber;

interface
  const MAX_N = 500;

  type Matrix = array [0..MAX_N - 1, 0..MAX_N - 1] of Boolean;

  function Start(N: Integer; var A: Matrix): Integer;
  function NextMove(R: Integer): Integer;

implementation
var
  NN, i, j, d, cop: Integer;
  AA: Matrix;
function Start(N: Integer; var A: Matrix): Integer;
begin
  NN := N;
  for i := 0 to N - 1 do
    for j := 0 to N - 1 do
      AA[i][j] := A[i][j];
  cop := 0;
  Start := 0;
end;

function dist (v, tto, parent: Integer): Integer;
var j, d: Integer;
begin
  if (v = tto) then begin
    dist := 0;
    exit;
  end;
  for j := 0 to NN - 1 do
    if ((j <> parent) and AA[v][j]) then begin
      d := dist (j, tto, v);
      if (d <> -1) then begin
        dist := d + 1;
        exit;
      end;
    end;
  dist := -1;
end;

function NextMove(R: Integer): Integer;
begin
  d := dist(cop, R, -1);
  for j := 0 to NN - 1 do
    if (AA[cop][j] and (dist(j, R, -1) < d)) then begin
      cop := j;
      NextMove := j;
      exit;
    end;
  
end;

end.
