(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Szatnia                                          *
 *   Autor:             Miroslaw Michalski                               *
 *   Zlozonosc czasowa: O(nlogn + plogp + n*maxK)                        *
 *   Opis:              Rozwiazanie weryfikujace                         *
 *                                                                       *
 *************************************************************************)

const
MAXN = 1000123;
MAXM = 1123;
MAXK = 100000;
MAXKK = MAXK + 123;
INF = 2000000123;

type
  Quad = record
    x, y, w, z : longint;
  end;

var
  poss: array[0..MAXKK] of longint;
  res: array[0..MAXN] of boolean;
  v:array[0..MAXN + MAXM] of Quad;
  p, n, m, a, b, c, i, totWeight, maxOrder: longint;

procedure makeQuad(a, b, c, d : longint; var q:Quad);
  begin
  q.x := a;
  q.y := b;
  q.w := c;
  q.z := d;
  end;

function max(x, y : longint):longint;
  begin
  if (x > y) then
    max := x
  else
    max := y
  end;

function min(x, y : longint):longint;
  begin
  if (x > y) then
    min := y
  else
    min := x
  end;


procedure qsort(left, right : longint);
var
  i, j : longint;
  pivot, x : Quad;
begin
  i := left;
  j := right;
  pivot := v[(i + j) div 2];
  repeat
    while (v[i].x < pivot.x) do inc(i);
    while (pivot.x < v[j].x) do dec(j);
    if (i <= j) then
      begin
      x := v[i];
      v[i] := v[j];
      v[j] := x;
      inc(i); dec(j);
      end;
  until (i > j);
  if (left < j) then qsort(left, j);
  if (i < right) then qsort(i, right);
end;

begin
  maxOrder := 0;
  totWeight := 0;
  readln(n);
  for i := 0 to n - 1 do
    begin
    readln(a, b, c);
    makeQuad(2 * b, c, a, -1, v[i]);
    totWeight := totWeight + a;
    end;
  readln(m);
  for i := 0 to m - 1 do
    begin
    readln(a, b, c);
    makeQuad(2 * a + 1, a + c, b, i, v[n + i]);
    maxOrder := max(maxOrder, b);
    end;
    totWeight := min(totWeight, maxOrder);

    qsort(0, n + m - 1);

    for i := 0 to m - 1 do
      res[i] := false;
    for i := 1 to MAXKK do
      poss[i] := -INF;
    poss[0] := INF;

    for i := 0 to n + m - 1 do
      begin
      if (v[i].z > -1) then
        res[v[i].z] := (poss[v[i].w] > v[i].y)
      else
        begin
        for p := totWeight - v[i].w downto 0 do
          if (poss[p] <> -INF) then
            poss[p + v[i].w] :=
              max(poss[p + v[i].w], min(poss[p], v[i].y))
        end;
      end;
  for i := 0 to m - 1 do
    if (res[i]) then writeln('TAK') else writeln('NIE');
end.
