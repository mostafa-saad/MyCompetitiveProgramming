(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PRA (Prawoskrêtny wielb³ad)                    *
 *   Plik:                vis.pas                                        *
 *   Autor:               Karol Cwalina                                  *
 *   Opis:                Program do wizualizowania testow               *
 *                        ( niestety dziala tylko pod DOS'en             *
 *                                                                       *
 *************************************************************************)
{$E+,N+}

uses graph;

const
  infile = 'pra.in';
  maxn = 1000; {10000}
  debug = true;
{ takie dziwne liczby dla fpc }
  WHITE = 47100;
  RED = 47110;
  YELLOW = 47080;

type
  Tpoint = record x, y : extended; end;

var
  P, L, R : array [0..maxn] of Tpoint;
  n : longint;
  ans : extended;

procedure indata;
var f : text;
  i : longint;
begin
  assign(f, infile);
  reset(f);
  read(f, n);
  for i := 1 to n do begin
    read(f, P[i].x, P[i].y);
    P[i].y := -P[i].y;
  end;
  close(f);
end;

procedure draw;
var gd, gm : integer;
  minc, maxc, minx,maxx,miny,maxy, scale : extended;
  x,y : LongInt;
  i,j : longint;

  function sc(c : extended) : longint;
  begin sc := round((c - minc) * scale); end;

begin
  gd := detect;
  initgraph (gd, gm, 'C:\BP\BGI');
  miny := 1000000000; maxy := -1000000000;
  minx := 1000000000; maxx := -1000000000;

  for i := 1 to n do
  begin
    if P[i].x < minx then minx := P[i].x;
    if P[i].y < miny then miny := P[i].y;
    if P[i].x > maxx then maxx := P[i].x;
    if P[i].y > maxy then maxy := P[i].y;
  end;
  if minx < miny then minc := minx else minc := miny;
  if maxx > maxy then maxc := maxx else maxc := maxy;
  maxc := 2*maxc; minc := 2*minc;
  if maxc - minc = 0 then maxc := maxc + 1;
  scale := 1000 / (maxc - minc);
  if n < 50 then begin
    for x := Round(minx) to Round(maxx) do
      for y := Round(miny) to Round(maxy) do putpixel (sc(x), sc(y), WHITE);
    for i := 1 to n do
      for j := i+1 to n do line (sc(P[i].x),sc(P[i].y), sc(P[j].x),sc(P[j].y));
  end;

  for i := 3 to n do
    for x := -1 to 1 do
      for y := -1 to 1 do putpixel(sc(P[i].x)+x, sc(P[i].y)+y, WHITE);
  for i := -2 to 2 do
    for j := -2 to 2 do begin
      putpixel(sc(P[1].x)+i, sc(P[1].y)+j, RED);
      putpixel(sc(P[2].x)+i, sc(P[2].y)+j, YELLOW);
    end;

  readln;
  closegraph;
end;

begin
  indata;
  draw;
end.
