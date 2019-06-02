(*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Nawiasy                                        *
 *   Plik:                naw2.pas                                       *
 *   Autor:               Remigiusz Ró¿ycki                              *
 *   Uwagi:               rozwi±zanie niewzorcowe                        *
 *   Z³o¿ono¶æ:           czas O(n^2), pamiec O(n)                       *
 *************************************************************************)
const
  max=5000;
  m=1000000000;
type
  tab=array[0..max-1]of longint;
var
  c:array[1..max]of char;
  tNew,tOld,tmp:^tab;
  i,j,n,alt:integer;
  t1,t2:text;
begin
  assign(t1,'naw.in');
  reset(t1);
  readln(t1,n);
  for i:=1 to n-1 do readln(t1,c[i]);
  close(t1);

  assign(t2,'naw.out');
  rewrite(t2);
  if c[1]='+' then begin
    writeln(t2,0);  close(t2); exit;
  end;

  new(tNew);
  new(tOld);
  c[n]:='-';
  if c[2]='-' then begin
    tNew^[0]:=1;
    alt:=0;
  end else begin
    tNew^[1]:=1;
    alt:=1;
  end;

  for i:=2 to n-1 do begin
    tmp:=tNew;  tNew:=tOld;  tOld:=tmp;
    fillchar(tNew^,sizeof(tNew^),0);
    if c[i+1]<>c[i] then begin
      alt:=alt+1;
      tNew^[alt]:=tOld^[alt-1];
      for j:=alt-2 downto 1 do
        tNew^[j]:=(tNew^[j+2]+tOld^[j-1])mod m;
      tNew^[0]:=tNew^[2];
    end else begin
      tNew^[alt]:=tOld^[alt];
      for j:=alt-2 downto 0 do
        tNew^[j]:=(tNew^[j+2]+tOld^[j])mod m;
    end;
  end;
  writeln(t2,tNew^[0]);
  close(t2);
end.
