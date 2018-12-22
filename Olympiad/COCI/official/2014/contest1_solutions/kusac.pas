var n, m, d, ans, i: integer;
begin
  readln(n, m);
  ans:= 1000;
  for i:= 1 to m do
    if((n mod i = 0) and (m mod i = 0)) then d:= i;

  writeln(d * (m div d - 1));

end.
