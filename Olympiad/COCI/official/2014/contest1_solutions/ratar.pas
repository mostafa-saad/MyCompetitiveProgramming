const delta = 2500000;

var n, m, i, j, k, l, sol: longint;
    v: array[1..50, 1..50] of longint;
    cnt: array[1..5000010] of longint;
    sum: array[1..50, 1..50] of longint;

procedure init;
var i, j: integer;
begin
  for i:= 1 to n do
    for j:= 1 to m do begin
      sum[i][j]:= v[i][j];
      if(i > 1) then inc(sum[i][j], sum[i - 1][j]);
      if(j > 1) then inc(sum[i][j], sum[i][j - 1]);
      if((i > 1) and (j > 1)) then dec(sum[i][j], sum[i - 1][j - 1]);
    end;
end;

function get_sum(x1, y1, x2, y2: longint): longint;
var ret: longint;
begin
  ret:= sum[x2][y2];
  if(x1 > 1) then dec(ret, sum[x1 - 1][y2]);
  if(y1 > 1) then dec(ret, sum[x2][y1 - 1]);
  if((x1 > 1) and (y1 > 1)) then inc(ret, sum[x1 - 1][y1 - 1]);
  get_sum:= ret;
end;

begin

  readln(n);
  m:=n;
  for i:= 1 to n do
    for j:= 1 to m do read(v[i][j]);

  init;

  for i:= 1 to n-1 do
    for j:= 1 to m-1 do begin
      for k:= 1 to i do
        for l:= 1 to j do
          inc(cnt[delta + get_sum(k, l, i, j)]);

      for k:= i + 1 to n do
        for l:= j + 1 to m do
          inc(sol, cnt[delta + get_sum(i + 1, j + 1, k, l)]);

      for k:= 1 to i do
        for l:= 1 to j do
          dec(cnt[delta + get_sum(k, l, i, j)]);
    end;

  for i:= 2 to n do
    for j:= 1 to m-1 do begin
      for k:= i to n do
        for l:= 1 to j do
          inc(cnt[delta + get_sum(i, l, k, j)]);

      for k:= 1 to i - 1 do
        for l:= j + 1 to m do
          inc(sol, cnt[delta + get_sum(k, j + 1, i - 1, l)]);

      for k:= i to n do
        for l:= 1 to j do
          dec(cnt[delta + get_sum(i, l, k, j)]);
    end;

  writeln(sol);

end.
