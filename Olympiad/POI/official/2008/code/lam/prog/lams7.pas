(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Lampki (LAM)                                              *
 *   Plik:     lams7.pas                                                 *
 *   Autor:    Michal Brzozowski                                         *
 *   Opis:     Rozwiazanie zbyt wolne, podstawa reprezentacji duzych     *
 *             liczb jest 10.                                            *
 *                                                                       *
 *************************************************************************)

const l_length = 10000;
      base = 10;

type 
liczba = record
    c:array[0..l_length-1] of longint;
    l:longint;
end;

function liczba_const : liczba;
var a:liczba;
i:longint;
begin
    a.l := 0;
    for i:=0 to l_length-1 do 
    a.c[i]:=123;
    liczba_const:=a;
end;

procedure sub(var a,b:liczba);
var r,i:longint;
begin
    i:=0;
    r:=0;
    while (i<b.l) or (r>0) do begin
    if i<b.l then a.c[i]:=a.c[i] - b.c[i];
    a.c[i]:=a.c[i]-r;
    if a.c[i]<0 then begin
        a.c[i]:=a.c[i] + base;
        r:=1;
    end else
        r:=0;
    i:=i+1;
    end;
    while (a.l>0) and (a.c[a.l-1]=0)do
    a.l:=a.l-1;
end;

function divl(var a:liczba; x:int64):liczba;
var r:int64;
    z:longint;
    ret:liczba;
begin
    ret:=liczba_const;
    r:=0;
    z:=a.l;
    while (z>0) do begin
    while (r<x) do begin
        r:= base*r + a.c[z-1];
        ret.c[z-1]:=0;
        z:=z-1;
        if z=0 then break;
    end;
    if z+1 > ret.l then ret.l := z+1;
    ret.c[z]:=r div x;
    r:=r mod x;
    end;
    divl:=ret;
end;

procedure times(var a:liczba; x:int64);
var r,nl,i:longint;
    mul:int64;
begin
    r:=0;
    nl:=0;
    i:=0;
    while (i<a.l) or (r>0) do begin
    mul:= r;
    if i<a.l then mul:=mul + a.c[i]*x;
    a.c[i] := mul mod base;
    r:=mul div base;
    nl:=i+1;
    i:=i+1;
    end;
    if nl>a.l then 
    a.l := nl;
end;

function dl(a:int64):liczba;
var ret:liczba;
begin
    ret:=liczba_const;
    if a=0 then begin
    dl:=ret;
    exit;
    end;
    ret.l:=0;
    while (a>0) do begin
    ret.c[ret.l]:=a mod base;
    ret.l:=ret.l+1;
    a:=a div base;
    end;
    dl:=ret;
end;

function ld(var a:liczba):int64;
var ret:int64;
    i:longint;
begin
    ret:=0;
    for i:=a.l-1 downto 0 do begin
    ret:= ret*base + a.c[i];
    end;
    ld:=ret;
end;

function nwdl(a,b:int64):int64;
begin
    if b=0 then 
    nwdl:=a else
    nwdl:=nwdl(b, a mod b);
end;

function nwdi(a:liczba; b:int64):int64;
var dz:liczba;
begin
    dz:=divl(a,b);
    times(dz,b);
    sub(a,dz);
    nwdi:=nwdl(b, ld(a));
end;

var licz,mian:liczba;
    out:array[0..10000, 0..1000, 0..1] of byte;
    out_length:array[0..1000, 0..1] of longint;
    num:array[0..1000] of longint;
    n,i,j,plicz,pmian,pnwd,lg,lm:longint;
begin
    readln(n);
    for i:=0 to n-1 do
    readln(num[i]);
    mian:=dl(num[n-1]);
    licz:=dl(1);
    for i:=n-2 downto 0 do begin
    plicz:=num[i+1]-1;
    pmian:=num[i];
    if plicz=0 then
        licz := dl(0);
    if licz.l>0 then begin
        pnwd:=nwdl(plicz,pmian);
        plicz:=plicz div pnwd;
        pmian:=pmian div pnwd;
        lg:=nwdi(licz, pmian);
        lm:=nwdi(mian, plicz);
        pmian:=pmian div lg;
        plicz:=plicz div lm;
        mian:=divl(mian,lm);
        licz:=divl(licz,lg);
        times(mian,pmian);
        times(licz,plicz);
    end else
        mian := dl(1);
    for j:=0 to licz.l-1 do 
        out[j][i][0]:=licz.c[j];
    out_length[i][0]:=licz.l;

    for j:=0 to mian.l-1 do 
        out[j][i][1]:=mian.c[j];
    out_length[i][1]:=mian.l;
    end;
    for i:=0 to n-2 do begin
        for j:=out_length[i][0]-1 downto 0 do
        write(out[j][i][0]);
    if out_length[i][0]=0 then write(0);
    write('/');
    for j:=out_length[i][1]-1 downto 0 do
        write(out[j][i][1]);
    if out_length[i][1]=0 then write(0);
    writeln;
    end;
    writeln('1/', num[n-1]);

end.
