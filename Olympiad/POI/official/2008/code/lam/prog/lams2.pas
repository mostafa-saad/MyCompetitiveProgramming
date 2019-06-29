(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Lampki (LAM)                                              *
 *   Plik:     lams2.pas                                                 *
 *   Autor:    Michal Brzozowski                                         *
 *   Opis:     Rozwiazanie zbyt wolne, reprezentuje duze liczby          *
 *             za pomoca rozkladow na czynniki pierwsze.                 *
 *             Rozwiazanie izomorficzne z lams1.cpp.                     *
 *                                                                       *
 *************************************************************************)

const nprime = 60000;
base = 10;
basel = 1;


var n,cprime:longint;
    num:array[0..1000] of longint;
    buf:array[0..10000] of longint;
    primes:array[0..nprime] of longint;

procedure razy(var k: longint; n:int64);
var
    r,a:int64;
    tmp,i:longint;
    begin
    i:=0;
    r:=0;
    while (i<k) or (r>0) do begin
        if i<k then
        a:=buf[i] else
        a:=0;
        a:=a*n+r;
        buf[i]:=a mod base;
        r:=a div base;
        if buf[i]>0 then
        tmp:=i+1;
        i:=i+1;
    end;
    k:=tmp;
    end;

type liczba = record
    zero:boolean;
    p:array[0..60000] of longint;
end;

function liczba_const(k:longint):liczba;
var i:longint;
    l:liczba;
begin
    l.zero:=false;
    if k=0 then begin
    l.zero:=true;
    for i:=0 to cprime-1 do
        l.p[i]:=0;
    end else
    for i:=0 to cprime-1 do begin
    l.p[i]:=0;
    while k mod primes[i] = 0 do begin
        l.p[i]:=l.p[i]+1;
        k:=k div primes[i];
    end;

    end;
    liczba_const:=l;
end;

procedure liczba_razy(var l1:liczba; l2:liczba);
var i:longint;
begin
    if l2.zero then l1.zero :=true else
    for i:=0 to cprime-1 do
    l1.p[i] := l1.p[i] + l2.p[i];
end;

procedure liczba_skroc(var l1, l2:liczba);
var k,i:longint;
begin
    for i:=0 to cprime-1 do begin
    if l1.p[i] < l2.p[i] then
        k:=l1.p[i] else
        k:=l2.p[i];
    l1.p[i] := l1.p[i]-k;
    l2.p[i] := l2.p[i]-k;
    end;
end;

procedure liczba_napis(var l1: liczba; var k:longint);
var i,j:longint;
begin
    if l1.zero then begin
    buf[0]:=0;
    k:=1;
    exit;
    end;
    buf[0]:=1;
    for i:=0 to cprime-1 do
    for j:=0 to l1.p[i]-1 do
        razy(k, primes[i]);
    
    
end;

procedure rozklad(k:longint);
var i:longint;
    podz:boolean;
begin
    while k>1 do begin
    i:=2;
    podz:=false;
    while i*i <= k do begin
        if k mod i = 0 then begin
        podz:=true;
        k:=k div i;
        primes[cprime]:=i;
        cprime:=cprime + 1;
        end;
        i:=i+1;
    end;
    if not podz then begin
        primes[cprime]:=k;
        cprime:=cprime+1;
        break;
    end;
    
    end;
end;

procedure zamien(var a,b:longint);
var c:longint;
begin
    c:=a;
    a:=b;
    b:=c;
end;
(* Sortowanie tablicy liczb pierwszych. *)
procedure sortuj(l,r:longint);
var
    x,i,j:longint;
begin
    i:=l;
    j:=r;
    x:=primes[(l+r) div 2];
    repeat
        while primes[i]<x do i:=i+1;
        while x<primes[j] do j:=j-1;
        if i<=j then begin
            zamien(primes[i],primes[j]);
            i:=i+1;
            j:=j-1;
        end;
    until i>j;
    if l<j then sortuj(l,j);
    if i<r then sortuj(i,r);
end;


var i,j,tmp:longint;
    tab:array[0..60000] of longint;
    licz, mian: liczba;
    bufsize:longint;
    out:array[0..10000, 0..1000, 0..1] of byte;
    out_length:array[0..1000, 0..1] of longint;
begin
readln(n);
for i:=0 to n-1 do begin
    readln(num[i]);
    rozklad(num[i]);
    rozklad(num[i]-1);
end;

sortuj(0,cprime-1);

tmp:=0;
for i:=0 to cprime-1 do
    if (i=0) or (primes[i]<>primes[i-1]) then begin
    tab[tmp]:=primes[i];
    tmp:=tmp+1;
    end;
cprime:=tmp;
for i:=0 to cprime-1 do begin
    primes[i]:=tab[i];
end;

licz := liczba_const(1);
mian := liczba_const(num[n-1]);

for i:=n-2 downto 0 do begin
    liczba_razy(licz, liczba_const(num[i+1]-1));
    liczba_razy(mian, liczba_const(num[i]));
    liczba_skroc(licz, mian);
    bufsize:=1;
    liczba_napis(licz, bufsize);
    for j:=0 to bufsize-1 do
    out[j][i][0]:=byte(buf[j]);
    out_length[i][0]:=bufsize;

    if licz.zero then
    mian:=liczba_const(1);
    bufsize:=1;
    liczba_napis(mian, bufsize);
    for j:=0 to bufsize-1 do
    out[j][i][1]:=byte(buf[j]);
    out_length[i][1]:=bufsize;
end;
for i:=0 to n-2 do begin
    for j:=out_length[i][0]-1 downto 0 do
    write(out[j][i][0]);
    write('/');
    for j:=out_length[i][1]-1 downto 0 do
    write(out[j][i][1]);
    writeln;
end;
writeln('1/', num[n-1]);

end.
