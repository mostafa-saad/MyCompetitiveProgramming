(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Ucieczka (UCI)                                            *
 *   Plik:     ucib3.pas                                                 *
 *   Autor:    Wojciech Tyczynski                                        *
 *   Opis:     Rozwiazanie niepoprawne zapisane w Pascalu.               *
 *                                                                       *
 *************************************************************************)

const
  step: array[0..3, 0..1] of longint = ((-1,0), (0,1), (1,0), (0,-1));

var
  n, m, md, x, y: longint;
  inpline: string;
  police: array[0..40, 0..40] of boolean;
  memoize: array[0..3, 0..40, 0..40, 0..40, 0..40] of longint;

function compute(dir, l0, l1, l2, l3: longint): longint;
var
  a, cura, curb, mva, mvb, ret: longint;
  clear: boolean;

begin
  if memoize[dir][l0][l1][l2][l3] = 0 then
  begin
    cura := y-1 + step[(dir+3) mod 4, 0] * l0;
    curb := x-1 + step[(dir+3) mod 4, 1] * l0;
    mva := step[dir][0];
    mvb := step[dir][1];
    clear := true;
    for a := 1 to l3 do
    begin
      dec(cura, mva);
      dec(curb, mvb);
      clear := clear and (not police[cura][curb]);
    end;
    if not clear then
    begin
      memoize[dir][l0][l1][l2][l3] := 1;
      compute := 0
    end else if l0 = 0 then
    begin
      memoize[dir][l0][l1][l2][l3] := 2;
      compute := 1
    end else begin
      ret := 0;
      cura := y-1 + step[(dir+3) mod 4, 0] * l0;
      curb := x-1 + step[(dir+3) mod 4, 1] * l0;
      for a := 0 to l1 do
      begin
        clear := clear and (not police[cura][curb]);
        if not clear then
          break;
        inc(cura, mva);
        inc(curb, mvb);
        ret := (ret + compute((dir+1) mod 4, a, l2, l3, l0-1)) mod md;
      end;
      memoize[dir][l0][l1][l2][l3] := ret+1;
      compute := ret;
    end;
  end else
    compute := memoize[dir][l0][l1][l2][l3] - 1;
end;

function min(a, b: longint): longint;
begin
  if a < b then
    min := a
  else
    min := b;
end;

function max(a, b: longint): longint;
begin
  if a < b then
    max := b
  else
    max := a;
end;

var
  a, b: longint;

begin
  readln(n, m, md);
  readln(x, y);
  for a := 0 to n-1 do
  begin
    readln(inpline);
    for b := 0 to m-1 do
      police[a][b] := inpline[b+1] = '*';
  end;
  writeln(compute(0, x-1, y-1, m-x, n-y));
end.

