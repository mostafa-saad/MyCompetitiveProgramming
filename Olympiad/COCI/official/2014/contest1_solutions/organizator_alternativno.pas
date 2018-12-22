var n, x, i: longint;
    sol: int64;
    d: array[1..2000010] of longint;
    c: array[1..2000010] of longint;
    tmp: array[0..10000] of longint;

procedure init;
var i, j: longint;
begin
  for i:= 2 to 2000000 do begin
    if(d[i] = 0) then begin
      j:= i;
      while(j <= 2000000) do begin
        if((j < 1) or (j > 2000000)) then halt(1);
        d[j]:= i;
        inc(j, i);
      end;
    end;
  end;
end;

procedure factor(x: longint);
var num, power, p, i: longint;
begin
  num:= 1;
  tmp[0]:= 1;
  while(x > 1) do begin
    power:= 0;
    p:= d[x];
    while(x mod p = 0) do begin
      x:= x div p;
      inc(power);
    end;
    for i:= num to (power + 1) * num do
      tmp[i]:= tmp[i - num] * p;
    num:= (power + 1) * num;
  end;
  for i:= 0 to num - 1 do inc(c[tmp[i]]);
end;

begin

  init;

  readln(n);

  for i:= 1 to n do begin
    read(x);
    factor(x);
  end;

  sol:= -1;

  for i:= 1 to 2000000 do
    if((c[i] > 1) and (c[i] * i > sol)) then sol:= c[i] * i;

  writeln(sol);

end.
