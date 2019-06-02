{*************************************************************************}
{*                                                                       *}
{*                   VII Olimpiada Informatyczna                         *}
{*                                                                       *}
{*   Rozwi•zanie zadania: POWT‡RZENIA                                    *}
{*   Plik:                POW.PAS                                        *}
{*   Autor:               TOMASZ WALE„                                   *}
{*************************************************************************}

{$A+,B-,D+,E+,F-,G+,I+,L+,N-,O-,P-,Q+,R+,S+,T-,V+,X+,Y+}
{$M 32384,0,655360}
program pow;
const
  max_n=5;
  max_m=2000;

  max_len=(max_m+1)*max_n;

  f_in='pow.in';
  f_out='pow.out';
type
  ptab=^ttab;
  ttab=array[1..max_len,1..3] of integer;
var
  f:text;
  w:array[1..max_len] of char; {sàowa}

  num,num_p:array[1..max_len] of integer; {numery podsà¢w}

  tab,pom:ptab; {tablice pomocnicze sàuæ•ce
                 do obliczania num}

  l:array[1..max_n] of integer; {dàugoòci sà¢w}
  pocz,kon:array[1..max_n] of integer;
  n:integer;
  len:integer;
  max:integer;

  procedure Init;
  begin
    New(tab);
    New(pom);
  end;

  {***********************************************************************}
  {* Wczytanie danych wejòciowych.                                       *}
  {***********************************************************************}
  procedure WczytajDane;
  var
    i,j,k:integer;
  begin
    Assign(f,f_in);
    reset(f);

    readln(f,n);
    k:=0;
    for i:=1 to n do
    begin
      j:=0;
      pocz[i]:=k+1;
      while not eoln(f) do
      begin
        inc(j);
        inc(k);
        read(f,w[k]);
      end;
      inc(k);
      w[k]:=chr(ord('z')+i);
      kon[i]:=k;
      l[i]:=j;
      readln(f);
    end;
    len:=k;

    close(f);
  end;

  {***********************************************************************}
  {* Sortowanie tablicy pom (radix sort).                                *}
  {***********************************************************************}
  procedure sort(l:integer);
  var
    ii,jj,i,j,k : integer;
    count : array[0..max_len] of integer;
    t : array[0..1] of ptab; {tablice pomocnicze}
    t1,t2 : ptab;
  begin
    t[0]:=tab; t[1]:=pom;
    t[1]^:=t[0]^;

    for ii:=3 downto 1 do
    begin
      t1:=t[ii mod 2];
      t2:=t[(ii+1) mod 2];

      fillchar(count,sizeof(count),0);

      for i:=1 to l do inc(count[t1^[i,ii]]);

      for i:=1 to max_len do count[i]:=count[i]+count[i-1];

      for i:=l downto 1 do
      begin
        j:=t1^[i,ii];
        k:=count[j];
        dec(count[j]);
        for jj:=1 to 3 do t2^[k,jj]:=t1^[i,jj];
      end;
    end;
  end;

  {***********************************************************************}
  {* Obliczenie zawartoòci tablicy num.                                  *}
  {***********************************************************************}
  function ObliczNum(l:integer):boolean;
  var
    i,j,k:integer;
    wystepuje:array[1..max_n] of boolean;
    ok,tmp:boolean;
    nr_slowa:integer;
  begin
    j:=0;
    for k:=1 to n do wystepuje[k]:=false;
    ok:=false;
    for i:=1 to l+1 do
    begin
      if (i=1) or (i=l+1) or (tab^[i-1,1]<>tab^[i,1]) or
         (tab^[i-1,2]<>tab^[i,2]) then
      begin
        inc(j);
        tmp:=true;
        for k:=1 to n do if not wystepuje[k] then tmp:=false;
        if tmp then ok:=true;
        for k:=1 to n do wystepuje[k]:=false;
      end;

      if (i<=l) then
      begin
        num[tab^[i,3]]:=j;
        nr_slowa:=0;
        for k:=1 to n do if (tab^[i,3]>=pocz[k]) then nr_slowa:=k;
        wystepuje[nr_slowa]:=true;
      end;
    end;
    ObliczNum:=ok;
  end;

  {***********************************************************************}
  {* Rozwi•zanie zadania.                                                *}
  {***********************************************************************}
  procedure Rozwiaz;
  var
    i,j,k,ii,jj:integer;
    ok:boolean;
    pasuje:boolean;
    p:integer;
  begin
    max:=0;

    {obliczenie nr podsà¢w o dàugoòci 1}
    p:=1;
    for i:=1 to len do begin
      tab^[i,1]:=1;
      tab^[i,2]:=ord(w[i])+1-ord('a');
      tab^[i,3]:=i;
    end;
    k:=len;
    sort(k);
    ok:=ObliczNum(k);

    while (ok) and (2*p<=l[1]) do
    begin
      max:=p;
      num_p:=num;

      {obliczanie num dla r=2*p}
      for i:=1 to len+1-2*p do
      begin
        tab^[i,1]:=num[i];
        tab^[i,2]:=num[i+p];
        tab^[i,3]:=i;
      end;
      k:=len+1-2*p;

      sort(k);
      ok:=ObliczNum(k);
      p:=p*2;
      if ok then begin
        max:=p;
        num_p:=num;
      end;
    end;

    while (p>1) do
    begin
      p:=p div 2;
      if ((max+p)>l[1]) then continue;
      num:=num_p;
      {obliczanie num dla r=max+p}
      for i:=1 to len+1-(p+max) do
      begin
        tab^[i,1]:=num[i];
        tab^[i,2]:=num[i+p];
        tab^[i,3]:=i;
      end;
      k:=len+1-(p+max);
      sort(k);
      ok:=ObliczNum(k);
      if ok then begin
        max:=max+p;
        num_p:=num;
      end;
    end;
  end;

  procedure ZapiszWynik;
  begin
    Assign(f,f_out);
    rewrite(f);
    Writeln(f,max);
    close(f);
  end;

begin
  Init;
  WczytajDane;
  Rozwiaz;
  ZapiszWynik;
end.