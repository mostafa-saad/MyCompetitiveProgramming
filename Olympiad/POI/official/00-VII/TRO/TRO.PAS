{*************************************************************************}
{*                                                                       *}
{*                   VII Olimpiada Informatyczna                         *}
{*                                                                       *}
{*   Rozwi•zanie zadania: TR‡JRAMIENNY DçWIG                             *}
{*   Plik:                TRO.PAS                                        *}
{*   Autor:               TOMASZ WALE„                                   *}
{*************************************************************************}

{$A+,B-,D+,E-,F+,G+,I+,L+,N+,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
{$M 64000,0,655360}
program tro;
const
  f_in = 'tro.in';
  f_out= 'tro.out';
  max=60000;
var
  p,q,pq,pq1,n:longint;
  f:text;
  a:array[0..max] of boolean;{kt¢re wagony (mod pq1) s• juæ zaj©te}

  procedure readdata;
  var
    tmp:longint;
  begin
    Assign(f,f_in);
    reset(f);
    readln(f,p,q,n);
    close(f);
    {zamiana p,q tak by p<=q}
    if p>q then begin tmp:=p; p:=q; q:=tmp; end;
    pq:=p+q;
    pq1:=pq+1;
  end;

  {generowanie programu: jeòli w=TRUE, to wynik jest zapisywany do pliku f}
  function gen(w:boolean):longint;
  var
    i:longint;
    m:longint;
  begin
    fillchar(a,sizeof(a),0);
    i:=0;
    m:=0;
    while (i<n) do
    begin
      inc(m);
      a[i mod pq1]:=true;
      a[(i+pq) mod pq1]:=true;
      if (w) then
      begin
        {jeòli to moæliwe wybieraj ruch, i, i+p, i+pq}
        if not a[(i+p) mod pq1] then begin
          a[(i+p) mod pq1]:=true;
          Writeln(f,i+1,' ',i+1+p,' ',i+1+pq);
        end else if not a[(i+q) mod pq1] then begin {wpp}
          a[(i+q) mod pq1]:=true;
          Writeln(f,i+1,' ',i+1+q,' ',i+1+pq);
        end;
      end else begin
        if not a[(i+p) mod pq1] then a[(i+p) mod pq1]:=true
        else if not a[(i+q) mod pq1] then a[(i+q) mod pq1]:=true;
      end;

      {powi©kszenie wartoòci licznika juz zapeànionych wagon¢w}
      while (a[i mod pq1]) do
      begin
        a[i mod pq1]:=false;
        inc(i);
      end;
    end;
    gen:=m;
  end;

  procedure solve;
  var
    m:longint;
  begin
    m:=gen(false);
    Assign(f,f_out);
    rewrite(f);
    Writeln(f,m);
    gen(true);
    close(f);
  end;

begin
  readdata;
  solve;
end.