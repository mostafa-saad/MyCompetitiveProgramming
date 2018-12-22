var n, x, i, j, br: longint;
    sol: int64;
    cnt: array[1..2000000] of longint;
begin

  readln(n);
  sol:= n;

  for i:= 1 to n do begin
    read(x);
    inc(cnt[x]);
  end;

  for i:= 1 to 2000000 do begin
    j:= i;
    br:= 0;
    while(j <= 2000000) do begin
      inc(br, cnt[j]);
      inc(j, i);
    end;
    if(br > 1) and (br * i > sol) then sol:= br * i;
  end;

  writeln(sol);

end.
