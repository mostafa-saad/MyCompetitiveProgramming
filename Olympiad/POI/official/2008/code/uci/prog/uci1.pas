(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Ucieczka (UCI)                                            *
 *   Plik:     uci1.pas                                                  *
 *   Autor:    Filip Wolski                                              *
 *   Opis:     Rozwiazanie wzorcowe, zapisane w Pascalu.                 *
 *                                                                       *
 *************************************************************************)

const
  step: array[0..3, 0..1] of longint = ((-1,0), (0,1), (1,0), (0,-1));

var
  n, m, md, x, y: longint;
  a, b: longint;
  inpline: string[200];
  police: array[0..100, 0..100] of boolean;
  res: array[0..3, 0..100, 0..100, 0..100, 0..1] of longint;
  clear: array[0..3, 0..100, 0..100, 0..100] of boolean;
  dir, l0, l1, l2, l3, sz, szn, tmp: longint;

function compute(): longint;
var
  cura, curb, mva, mvb, ret: longint;

begin
  cura := y-1 + step[(dir+3) mod 4, 0] * l0;
  curb := x-1 + step[(dir+3) mod 4, 1] * l0;
  mva := step[dir][0];
  mvb := step[dir][1];
  clear[dir][l0][l1][l3] := (not police[cura + mva * l1][curb + mvb * l1]) and (not police[cura - mva * l3, curb - mvb * l3]);
  if l1 > 0 then
    clear[dir, l0, l1, l3] := clear[dir, l0, l1, l3] and clear[dir, l0, l1-1, l3];
  if l3 > 0 then
    clear[dir, l0, l1, l3] := clear[dir, l0, l1, l3] and clear[dir, l0, l1, l3-1];
  if not clear[dir][l0][0][l3] then
    compute := 0
  else if l0 = 0 then
    compute := 1
  else begin
    ret := 0;
    if l1 > 0 then
      inc(ret, res[dir, l0, l1-1, l2, (sz-1) mod 2]);
    if clear[dir, l0, l1, l3] then
      inc(ret, res[(dir+1) mod 4, l1, l2, l3, (sz-1) mod 2]);
    compute := ret;
  end;
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

begin
  readln(n, m, md);
  readln(x, y);
  for a := 0 to n-1 do
  begin
    readln(inpline);
    for b := 0 to m-1 do
      police[a][b] := inpline[b+1] = '*';
  end;
  for sz := 2 to n+m do
    for szn := max(1,sz-m) to min(n,sz-1) do
      for a := 0 to n-szn do
        for b := 0 to m-sz+szn do
          begin
            l0 := x-1 - b;
            l1 := y-1 - a;
            l2 := b+sz-szn - x;
            l3 := a+szn - y;
            if (l0 < 0) or (l1 < 0) or (l2 < 0) or (l3 < 0) then
              continue;
            for dir := 0 to 3 do
            begin
              res[dir, l0, l1, l2, sz mod 2] := compute() mod md;
              tmp := l0; l0 := l1; l1 := l2; l2 := l3; l3 := tmp;
            end;
          end;
  writeln(res[0, x-1, y-1, m-x, (n+m) mod 2]);
end.

