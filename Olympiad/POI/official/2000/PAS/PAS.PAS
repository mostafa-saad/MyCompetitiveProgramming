{*************************************************************************}
{*                                                                       *}
{*                   VII Olimpiada Informatyczna                         *}
{*                                                                       *}
{*   Rozwi¥zanie zadania: PASKI                                          *}
{*   Plik:                PAS.PAS                                        *}
{*   Autor:               TOMASZ WALEã                                   *}
{*************************************************************************}

{$A+,B-,D+,E+,F+,G+,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
{$M 64000,0,655360}
program paski;
const
 f_in  = 'pas.in';
 f_out = 'pas.out';
 max_n   = 1000; {maksymalny rozmiar planszy}
 max_kat = max_n*3+1; {to jest bardzo zgrubne oszacowanie,
                       zazwyczaj max_kat<300}
var
  f, g : text;
  a : array[1..3] of word; {dˆugo˜ci pask¢w}
  p : array[0..max_n] of word; {kategorie-klasy plansz o wymiarach 1xi}
  s : integer;
  m : integer;
  rozmiar_planszy : integer;
  max_obliczony : integer;

  procedure gen;
  var
    i,ii,j,jj : integer;
    max,x     : integer;
    k : array[0..max_kat] of boolean;
  begin
    if max_obliczony >= rozmiar_planszy then
      Exit;
    fillchar(k,sizeof(k),false);
    max:=0;
    for i:= max_obliczony+1 to rozmiar_planszy do
    begin
      for ii:=1 to 3 do if i>=a[ii] then
      begin
        j:=0;jj:=i-a[ii];
        while (j<=jj) do begin {wykonywanie ruchow}
          x:=p[j] xor p[jj];
          k[x]:=true;
          if x>max then max:=x;
          inc(j);
          dec(jj);
        end;
      end;
      j:=0;
      while (k[j]) do inc(j);
      p[i]:=j;
      fillchar(k,max+1,false);{czyszczenie tylko perwszych max+1 bajt¢w}
      max:=0;
    end;
    max_obliczony := rozmiar_planszy;
  end;

begin
  Assign(f,f_in);
  reset(f);
  Assign(g,f_out);
  rewrite(g);

  readln(f,a[1],a[2],a[3]);
  readln(f,m);

  p[0]:=0;
  max_obliczony := 0;

  for s:=1 to m do
  begin
    Readln (f, rozmiar_planszy);
    gen;

    if p[rozmiar_planszy]=0 then Writeln(g,'2')
                            else Writeln(g,'1');

  end;
  close (f);
  close(g);
end.

