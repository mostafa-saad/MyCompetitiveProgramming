var n, i: integer;
    a: array['a'..'z'] of integer;
    s, ans: string;
    c: char;
begin
  readln(n);
  for i:= 1 to n do begin
    readln(s);
    inc(a[s[1]]);
  end;

  for c:= 'a' to 'z' do begin
    if(a[c] >= 5) then ans:= ans + c;
  end;

  if(ans = '') then writeln('PREDAJA') else writeln(ans);
end.
