{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Powodz (POW)                                               *}
{*   Plik:    pow1.pas                                                   *}
{*   Autor:   Marek Zylak                                                *}
{*   Opis:    Rozwi±zanie wzorcowe O(n * m + max_wys_gory)               *}
{*                                                                       *}
{*************************************************************************}
program pow;

const
  MAXW = 1000;
  MAXA = 1000;
  MAXN = MAXW * MAXW;
var
  w,h,n,inf,ans: longint;

  a,f: array[0..MAXN-1] of longint;
  c: array[0..MAXN-1] of boolean;
  next: array[0..MAXN-1,0..1] of longint;
  head: array[1..MAXA,0..1] of longint;

  i,j,k,l: longint;
  x,y: longint;
  dx: array[0..3] of longint;
  i0,j0,i1,j1,d: longint;

  function max(a,b: longint): longint;
  begin
    if a > b then
      max := a
    else
      max := b;
  end;
begin
  dx[0] :=  1;
  dx[1] :=  0;
  dx[2] := -1;
  dx[3] :=  0;

  readln(h,w);

  n := w * h;

  for j := 0 to h-1 do
  begin
    for i := 0 to w-1 do
    begin
      x := j * w + i;
      c[x] := true;
      read(a[x]);
      if a[x] < 0 then
      begin
        a[x] := -a[x];
        c[x] := false
      end
    end;
    readln 
  end;

  inf := 0;
  for i := 0 to n-1 do inf := max(inf, a[i] + 1);

  for i := 0 to n-1 do f[i] := inf;

  for i := 1 to inf-1 do for j := 0 to 1 do head[i][j] := -1;

  for i := 0 to n-1 do
  begin
    if c[i] then
    begin
      next[i][1] := head[a[i]][1];
      head[a[i]][1] := i
    end
  end;

  ans := 0;

  for k := 1 to inf-1 do
  begin
    while (head[k][0] >= 0) or (head[k][1] >= 0) do
    begin
      l := 0;
      if head[k][0] < 0 then l := 1;

      x := head[k][l];
      head[k][l] := next[x][l];

      if (l = 0) or (f[x] = inf) then
      begin
        if l <> 0 then
        begin
          inc(ans);
          f[x] := a[x]
        end;

        i0 := x mod w;
        j0 := x div w;
        for d := 0 to 3 do
        begin
          i1 := i0 + dx[d];
          j1 := j0 + dx[(d+1) mod 4];
          if (i1 >= 0) and (i1 < w) and (j1 >= 0) and (j1 < h) then
          begin
            y := j1 * w + i1;
            if f[y] = inf then
            begin
              f[y] := max(f[x], a[y]);
              next[y][0] := head[f[y]][0];
              head[f[y]][0] := y
            end
          end
        end
      end
    end
  end;
  writeln(ans)
end.
