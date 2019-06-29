(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Ucieczka (UCI)                                            *
 *   Plik:     ucis4.pas                                                 *
 *   Autor:    Wojciech Tyczynski                                        *
 *   Opis:     Rozwiazanie nioptymalne zapisane w Pascalu.               *
 *                                                                       *
 *************************************************************************)

const
  step: array[0..3, 0..1] of longint = ((-1,0), (0,1), (1,0), (0,-1));

var
  n, m, md, x, y: longint;
  a, b: longint;
  inpline: string;
  police: array[0..100, 0..100] of boolean;

function compute(a, b, dir: longint): longint;
var
  cnt, aa, bb, ret: longint;

begin
  if (a+1 = y) and (b+1 = x) then
    compute := 1
  else begin
    ret := 0;
    police[a][b] := true;
    for cnt := 0 to 1 do begin
      aa := a + step[dir][0];
      bb := b + step[dir][1];
      if (0 <= aa) and (aa < n) and (0 <= bb) and (bb < m) and (not police[aa][bb]) then
        ret := (ret + compute(aa,bb,dir)) mod md;
      dir := (dir+1) mod 4;
    end;
    police[a][b] := false;
    compute := ret;
  end;
end;

begin
  readln(n, m, md);
  readln(x, y);
  for a := 0 to n-1 do
  begin
    readln(inpline);
    for b := 0 to m-1 do
      police[a][b] := inpline[b+1] = '*';
  end;
  writeln(compute(n-1,0,0));
end.

