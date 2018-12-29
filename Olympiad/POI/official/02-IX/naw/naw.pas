(*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Nawiasy                                        *
 *   Plik:                naw.pas                                        *
 *   Autor:               Remigiusz Ró¿ycki                              *
 *   Uwagi:               rozwi±zanie wzorcowe                           *
 *   Z³o¿ono¶æ:           czas O(n^2), pamiec O(n)                       *
 *************************************************************************)
const max=5000;  { gorne ograniczenie na 'n' }
      m=1000000000;
var c:array[1..max-1]of char;
    w:array[1..max-1]of longint;
    i,j,n,l:integer;
    t1,t2:text;
begin
  assign(t1,'naw.in');
  reset(t1);
  readln(t1,n);
  l:=n-1;
  for i:=1 to l do readln(t1,c[i]);
  close(t1);
  
  assign(t2,'naw.out');
  rewrite(t2);
  if c[1]='+' then begin
    writeln(t2,0);  close(t2);  exit;
  end;
  for i:=1 to l do w[i]:=1;
  for i:=2 to l-1 do
    if (c[i]='+')and(c[i+1]='-') then
      for j:=i+1 to l do begin
        w[j]:=w[j]+w[j-1];
        if w[j]>=m then w[j]:=w[j]-m;
      end;
  writeln(t2,w[l]);
  close(t2);
end.
