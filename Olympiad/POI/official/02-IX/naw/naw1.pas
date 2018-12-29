(*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Nawiasy                                        *
 *   Plik:                naw1.pas                                       *
 *   Autor:               Remigiusz Ró¿ycki                              *
 *   Uwagi:               rozwi±zanie niewzorcowe                        *
 *   Z³o¿ono¶æ:           czas O(n^2), pamiec O(n^2)                     *
 *************************************************************************)
const
  max=1000;
  m=1000000000;
var
  c:array[1..max]of char;
  t:array[1..max-1,0..max-1]of longint;
  i,j,n,alt:integer;
  t1,t2:text;
begin
  assign(t1,'naw.in');
  reset(t1);
  readln(t1,n);
  for i:=1 to n-1 do readln(t1,c[i]);
  close(t1);

  fillchar(t,sizeof(t),0);
  assign(t2,'naw.out');
  rewrite(t2);
  if c[1]='+' then begin
    writeln(t2,0);  close(t2);  exit;
  end;
  
  c[n]:='-';
  if c[2]='-' then begin
    t[1,0]:=1;
    alt:=0;
  end else begin
    t[1,1]:=1;
    alt:=1;
  end;

  for i:=2 to n-1 do
    if c[i+1]<>c[i] then begin
      alt:=alt+1;
      t[i,alt]:=t[i-1,alt-1];
      for j:=alt-2 downto 1 do
        t[i,j]:=(t[i,j+2]+t[i-1,j-1])mod m;
      t[i,0]:=t[i,2];
    end else begin
      t[i,alt]:=t[i-1,alt];
      for j:=alt-2 downto 0 do
        t[i,j]:=(t[i,j+2]+t[i-1,j])mod m;
    end;
  writeln(t2,t[n-1,0]);
  close(t2);
end.
