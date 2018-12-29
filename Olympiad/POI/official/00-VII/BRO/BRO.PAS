{*************************************************************************}
{*                                                                       *}
{*                   VII Olimpiada Informatyczna                         *}
{*                                                                       *}
{*   Rozwi¥zanie zadania: BROWARY                                        *}
{*   Plik:                BRO.PAS                                        *}
{*   Autor:               TOMASZ WALEã                                   *}
{*************************************************************************}

{$A+,B-,D+,E-,F+,G+,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
{$M 64000,0,655360}

program bro;
const
  maxn = 10000;
  f_in = 'bro.in';
  f_out= 'bro.out';

var
  z:array[0..maxn-1] of integer; {zapotrzebowanie}
  d:array[0..maxn-1] of longint; {odleglo˜ci mi©dzy miastami}
  n:integer;
  f:text;
  min:comp;
  min_n:integer; {nr miasta, w kt¢rym nale¾y umie˜ci† browar}

  procedure readdata;
  var
    i:integer;
  begin
    Assign(f,f_in);
    reset(f);
    readln(f,n);
    for i:=0 to n-1 do readln(f,z[i],d[i]);
    close(f);
  end;

  procedure solve;
  var
    i,l,r,j:integer;
    dl,dr,zl,zr:longint;
    c,cc:comp;
  begin
    {wyliczanie kosztu dla browaru w 0}
    dl:=0;dr:=0;l:=0;r:=0;zl:=0;zr:=0;
    j:=1;c:=0;
    while (j<n) do
    begin
      if (dl+d[(l+n-1) mod n])<(dr+d[r]) then
      begin
        dl:=dl+d[(l+n-1) mod n];
        l:=(l+n-1) mod n;
        c:=c+dl*z[l];
        zl:=zl+z[l];
      end else begin
        dr:=dr+d[r];
        r:=(r+1) mod n;
        c:=c+dr*z[r];
        zr:=zr+z[r];
      end;
      inc(j);
    end;
    min:=c;min_n:=0;

    {obliczanie koszt¢w dla pozostaˆych miast}
    for i:=1 to n-1 do
    begin
      {przesuni©cie browaru do miasta o numerze i, poprawienie kosztu}
      zl:=zl+z[i-1];
      cc:=d[(i+n-1) mod n];
      cc:=cc*(zl-zr);
      c:=c+cc;
      zr:=zr-z[i];
      dl:=dl+d[(i+n-1) mod n];
      dr:=dr-d[(i+n-1) mod n];
      {poprawianie kosztu poprzez zwi©kszanie liczby cystern
       wysyˆanych w kierunku zgodnym z ruchem
       wskaz¢wek i zmniejszanie dla kierunku przeciwnego}
      while dl>(dr+d[r]) do
      begin
        dr:=dr+d[r];
        r:=(r+1) mod n;
        l:=(l+1) mod n;
        zr:=zr+z[r];
        zl:=zl-z[r];
        c:=c+z[r]*(dr-dl);
        dl:=dl-d[r];
      end;
      if (c<min) then begin min:=c; min_n:=i; end;
    end;
  end;

  procedure writeanswer;
  begin
    Assign(f,f_out);
    rewrite(f);
    Writeln(f,min:1:0);
    close(f);
  end;

begin
  readdata;
  solve;
  writeanswer;
end.