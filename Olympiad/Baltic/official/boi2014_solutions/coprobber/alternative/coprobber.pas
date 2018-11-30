unit coprobber;

interface
  const MAX_N = 500;

  type Matrix = array [0..MAX_N - 1, 0..MAX_N - 1] of Boolean;

  function Start(N: Integer; var A: Matrix): Integer;
  function NextMove(R: Integer): Integer;

implementation
const COP = 0; ROBBER = 1;
var 
  NextPos: array [0..MAX_N - 1, 0..MAX_N - 1] of Integer;
  copPos: Integer;
  LeftToWin: array [0..1, 0..MAX_N - 1, 0..MAX_N - 1] of Integer;
  //Queue
  qc, qr, qt: array [0..2*MAX_N * MAX_N] of Integer; //Cop, Robber, Winner
  front, back: Longint;
  r, degree, c, t, i: Integer;
function Start(N: Integer; var A: Matrix): Integer;
begin
  for r := 0 to N - 1 do begin
    degree := 0;
    for c := 0 to N - 1 do
      if (A[r][c]) then degree += 1;
    for c := 0 to N - 1 do
      if c <> r then begin
	LeftToWin[COP][c][r] := 1;
	LeftToWin[ROBBER][c][r] := degree;
      end;
  end;
  
  for i := 0 to N - 1 do begin
    qc[i] := i; qr[i] := i; qt[i] := COP;
    qc[N + i] := i; qr[N + i] := i; qt[N + i] := ROBBER;
  end;
  front := 0; back := 2 * N;
  
  while (front < back) do begin
    t := qt[front]; c := qc[front]; r := qr[front];
    front += 1;
    if (t = COP) then begin
      for i := 0 to N - 1 do
	if (A[r][i] and (LeftToWin[ROBBER][c][i] > 0)) then begin
	  LeftToWin[ROBBER][c][i] -= 1;
	  if (LeftToWin[ROBBER][c][i] = 0) then begin
	    qt[back] := ROBBER; qc[back] := c; qr[back] := i;
	    back += 1;
	  end;
	end;
    end else begin
      for i := 0 to N - 1 do
	if (((c = i) or A[c][i]) and (LeftToWin[COP][i][r] > 0)) then begin
	  LeftToWin[COP][i][r] := 0;
	  qt[back] := COP; qc[back] := i; qr[back] := r;
	  back += 1;
	  NextPos[i][r] := c;
	end;
    end;
  end;

  copPos := 0;
  if (front = 2 * N * N) then Start := 0 else Start := -1;
end;
  
function NextMove(R: Integer): Integer;
begin
  copPos := NextPos[copPos][R];  
  NextMove := copPos;
end;

end.
