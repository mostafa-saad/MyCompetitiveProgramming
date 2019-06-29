(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Straz pozarna (STR)                                       *
 *   Plik:     str1.pas                                                  *
 *   Autor:    Tomasz Kulczynski                                         *
 *   Opis:     Rozwiazanie wzorcowe O(p+z)*log(p+z))                     *
 *                                                                       *
 *************************************************************************)

const ZZ = 100000;
const PP = 100000;
const inf = 1000000000;
const XX = 4*PP + ZZ;

var n,m,z,p:longint;
    x,y:array[1..ZZ] of longint;
    w:array[0..3*PP-1] of longint;

type wektor=record
                a1,a2,a3,a4,a5:longint;
            end;

var x1,x2,x3,x4:array[0..XX] of wektor;
    x1size,x2size,x3size,x4size:longint;

function sign(x:longint):longint;
begin
    if x=0 then 
        sign:=0
    else if x>0 then
        sign:=1
    else sign:=-1;
end;

function min(a,b:longint):longint;
begin
    if a>b then 
        min:=b
    else min:=a;
end;

function max(a,b:longint):longint;
begin
    if a<b then
        max:=b
    else max:=a;
end;

function wekt(a,b,c,d,e:longint):wektor;
var v:wektor;
begin
    v.a1:=a;
    v.a2:=b;
    v.a3:=c;
    v.a4:=d;
    v.a5:=e;
    wekt:=v;
end;

var u:array[0..2*XX] of longint;
    usize: longint;

function szukaj(a:longint):longint;
var l,p,s:longint;
begin
    l:=0;
    p:=usize-1;
    while l<p do
        begin
            s:=(l+p) div 2;
            if u[s]<a then 
                l:=s+1
            else 
                p:=s;
        end;
    szukaj:=l;
end;

const MM = 1 shl 19;
var e:array[1..2*MM-1] of longint;

procedure iinsert(a:longint);
begin
    a:=a+MM;
    while a<>0 do
        begin
            inc(e[a]);
            a:=a div 2;
        end;
end;

function pyt(a:longint):longint;
begin
    pyt:=0;
    a:=a+MM;
    while a>1 do
        begin
            if (a mod 2)<>0 then
                pyt:=pyt + e[a-1];
            a:=a div 2;
        end;
end;

function pytaj(a,b:longint):longint;
begin
    pytaj:=pyt(b+1)-pyt(a);
end;

function mniejszy(var a,b:wektor):boolean;
begin
    if a.a1<b.a1 then
        mniejszy:=true
    else if a.a1>b.a1 then
        mniejszy:=false
    else if a.a2<b.a2 then
        mniejszy:=true
    else if a.a2>b.a2 then
        mniejszy:=false
    else if a.a3<b.a3 then
        mniejszy:=true
    else if a.a3>b.a3 then
        mniejszy:=false
    else if a.a4<b.a4 then
        mniejszy:=true
    else if a.a4>b.a4 then
        mniejszy:=false
    else if a.a5<b.a5 then
        mniejszy:=true
    else mniejszy:=false;
end;

var xpomoc:array[0..XX] of wektor;
procedure sortuj_x(var x:array of wektor; a,b:longint);
var i,s,c,d:longint;
begin
    if a<b then
        begin
            s:=(a+b) div 2;
            sortuj_x(x,a,s);
            sortuj_x(x,s+1,b);
            c:=a;
            d:=s+1;
            i:=a;
            while i<=b do
                if (c<=s) and ( (d>b) or mniejszy(x[c],x[d]) ) then
                    begin
                        xpomoc[i]:=x[c];
                        inc(i);
                        inc(c);
                    end
                else
                    begin
                        xpomoc[i]:=x[d];
                        inc(i);
                        inc(d);
                    end;
            for i:=a to b do
                x[i]:=xpomoc[i];
        end;
end;

var pomoc:array[0..2*XX] of longint;
procedure sortuj_u(a,b:longint);
var i,s,c,d:longint;
begin
    if a<b then
        begin
            s:=(a+b) div 2;
            sortuj_u(a,s);
            sortuj_u(s+1,b);
            c:=a;
            d:=s+1;
            i:=a;
            while i<=b do
                if (c<=s) and ( (d>b) or (u[c]<u[d]) ) then
                    begin
                        pomoc[i]:=u[c];
                        inc(i);
                        inc(c);
                    end
                else
                    begin
                        pomoc[i]:=u[d];
                        inc(i);
                        inc(d);
                    end;
            for i:=a to b do
                u[i]:=pomoc[i];
        end;
end;

procedure zamiec(var x:array of wektor; var xsize:longint);
var i:longint;
begin
    i:=0;
    while i<xsize do
        begin
            if (x[i].a2>=0) and (x[i].a4>x[i].a5) then
                begin
                    x[i]:=x[xsize-1];
                    dec(xsize);
                end;
            inc(i);
        end;
    sortuj_x(x,0,xsize-1);
    usize:=0;
    for  i:=1 to 2*MM-1 do 
        e[i]:=0;
    for  i:=0 to xsize-1 do
        if x[i].a2<0 then
            begin
                u[usize]:=x[i].a3;
                inc(usize);
            end
        else
            begin
                u[usize]:=x[i].a4;
                u[usize+1]:=x[i].a5;
                usize:=usize+2;
            end;
    sortuj_u(0,usize-1);
    for i:=0 to xsize-1 do
        if x[i].a2<0 then
            iinsert(szukaj(x[i].a3))
        else
            w[x[i].a2] := w[x[i].a2] + pytaj( szukaj(x[i].a4), szukaj(x[i].a5) ) * x[i].a3;
end;

var k,i,j,a,b,c,d,komu:longint;
    s,s2:longword;
begin
    x1size:=0;
    x2size:=0;
    x3size:=0;
    x4size:=0;
    read(n,m,z,p);
    for i:=1 to z do
        read(x[i],y[i]);
    for j:=0 to p-1 do
        begin
            komu:=0;
            read(a,b,c,d);
            if a>c then
                komu:=1;
            if a=c then
                begin
                    if b>d then
                        komu:=1;
                    x2[x2size]:=( wekt( (b+d-1) div 2,      3*j+komu,  1, 0,            inf ) );
                    inc(x2size);
                    x2[x2size]:=( wekt( (b+d) div 2,    3*j+2,     1,  0,           inf ) );
                    inc(x2size);
                end
            else if b=d then
                begin
                    x1[x1size]:=( wekt( (a+c-1) div 2,      3*j+komu,  1,  0,           inf ) );
                    inc(x1size);
                    x1[x1size]:=( wekt( (a+c) div 2,    3*j+2,     1,  0,           inf ) );
                    inc(x1size);
                end
            else if abs(a-c)=abs(b-d) then
                begin
                    if (a+b)=(c+d) then
                        begin
                            x3[x3size]:=( wekt( inf+c-b-1,  3*j+komu,  1, min(b,d)+1,   max(b,d)-1 ) );
                            inc(x3size);
                            x3[x3size]:=( wekt( inf+c-b,    3*j+2,     1, min(b,d),     max(b,d)-1 ) );
                            inc(x3size);
                            x1[x1size]:=( wekt( max(a,c)-1, 3*j+komu,  1, max(b,d),     inf ) );
                            inc(x1size);
                            x1[x1size]:=( wekt( max(a,c),   3*j+2,     1, max(b,d),     inf ) );
                            inc(x1size);

                            x1[x1size]:=( wekt( min(a,c),   3*j+2,     1, 0,            min(b,d)-1 ) );
                            inc(x1size);

                            w[3*j+2]:=z;
                            x2[x2size]:=( wekt( max(b,d)-1,     3*j+2,     1, 0    ,   max(a,c) ) );
                            inc(x2size);
                            x2[x2size]:=( wekt( inf,            3*j+2,    -1, 0    ,   max(a,c) ) );
                            inc(x2size);
                            x2[x2size]:=( wekt( max(b,d)-1,     3*j+2,    -1, 0    ,   inf ) );
                            inc(x2size);
                        end
                    else
                        begin
                            x4[x4size]:=( wekt( b+c-1,      3*j+komu,  1, min(b,d)+1,   max(b,d)-1 ) );
                            inc(x4size);
                            x4[x4size]:=( wekt( b+c,        3*j+2,     1, min(b,d)+1,   max(b,d) ) );
                            inc(x4size);
                            x1[x1size]:=( wekt( max(a,c)-1, 3*j+komu,  1, 0,            min(b,d) ) );
                            inc(x1size);
                            x1[x1size]:=( wekt( max(a,c),   3*j+2,     1, 0,            min(b,d) ) );
                            inc(x1size);

                            x1[x1size]:=( wekt( min(a,c),   3*j+2,     1, max(b,d)+1,   inf ) );
                            inc(x1size);

                            x2[x2size]:=( wekt( min(b,d),   3*j+2,     1, max(a,c)+1,   inf ) );
                            inc(x2size);
                        end;
                end
            else if abs(a-c)>abs(b-d) then
                begin
                    if sign(a-c)=sign(b-d) then
                        begin 
                            s:=a+b;
                            s2:=c+d;
                            s:=s+s2;
                            x4[x4size]:=( wekt( (s-1) div 2,            3*j+komu,  1, min(b,d),     max(b,d) ) );
                            inc(x4size);
                            x4[x4size]:=( wekt( s div 2,                3*j+2,     1, min(b,d),     max(b,d) ) );
                            inc(x4size);
                            x1[x1size]:=( wekt( (s-1) div 2-max(b,d),   3*j+komu,  1, max(b,d)+1,   inf ) );
                            inc(x1size);
                            x1[x1size]:=( wekt( s div 2-max(b,d),       3*j+2,     1, max(b,d)+1,   inf ) );
                            inc(x1size);
                            x1[x1size]:=( wekt( (s-1) div 2-min(b,d),   3*j+komu,  1, 0,            min(b,d)-1 ) );
                            inc(x1size);
                            x1[x1size]:=( wekt( s div 2-min(b,d),       3*j+2,     1, 0,            min(b,d)-1 ) );
                            inc(x1size);
                        end
                    else
                        begin
                            s:=inf+a-b;
                            s2:=inf+c-d;
                            s:=s+s2;
                            x3[x3size]:=( wekt( (s-1) div 2,                3*j+komu,  1, min(b,d),     max(b,d) ) );
                            inc(x3size);
                            x3[x3size]:=( wekt( s div 2,                    3*j+2,     1, min(b,d),     max(b,d) ) );
                            inc(x3size);
                            x1[x1size]:=( wekt( (s-1) div 2+max(b,d)-inf,   3*j+komu,  1, max(b,d)+1,   inf ) );
                            inc(x1size);
                            x1[x1size]:=( wekt( s div 2+max(b,d)-inf,       3*j+2,     1, max(b,d)+1,   inf ) );
                            inc(x1size);
                            x1[x1size]:=( wekt( (s-1) div 2+min(b,d)-inf,   3*j+komu,  1, 0,            min(b,d)-1 ) );
                            inc(x1size);
                            x1[x1size]:=( wekt( s div 2+min(b,d)-inf,       3*j+2,     1, 0,            min(b,d)-1 ) );
                            inc(x1size);
                        end;
                end
            else
                begin
                    if sign(a-c)=sign(b-d) then
                        begin
                            s:=a+b;
                            s2:=c+d;
                            s:=s+s2;
                            x4[x4size]:=( wekt( (s-1) div 2,    3*j+komu,  1, (s-1) div 2-max(a,c)+1,   (s-1) div 2-min(a,c) ) );
                            inc(x4size);
                            x4[x4size]:=( wekt( s div 2,        3*j+2,     1, s div 2-max(a,c)+1,   s div 2-min(a,c)     ) );
                            inc(x4size);
                            x1[x1size]:=( wekt( inf,        3*j+komu,  1, 0,                (s-1) div 2-max(a,c) ) );
                            inc(x1size);
                            x1[x1size]:=( wekt( inf,        3*j+2,     1, 0,                s div 2-max(a,c)     ) );
                            inc(x1size);
                        end
                    else
                        begin
                            s:=inf+a-b;
                            s2:=inf+c-d;
                            s:=s+s2;
                            x3[x3size]:=( wekt( (s-1) div 2,    3*j+komu,  1, min(a,c)+inf-(s-1) div 2,     max(a,c)+inf-(s-1) div 2-1 ) );
                            inc(x3size);
                            x3[x3size]:=( wekt( s div 2,        3*j+2,     1, min(a,c)+inf-s div 2,         max(a,c)+inf-s div 2-1 ) );
                            inc(x3size);
                            x1[x1size]:=( wekt( inf,        3*j+komu,  1, max(a,c)+inf-(s-1) div 2,     inf      ) );
                            inc(x1size);
                            x1[x1size]:=( wekt( inf,        3*j+2,     1, max(a,c)+inf-s div 2,         inf      ) );
                            inc(x1size);
                        end;
                end;
            w[3*j+1-komu]:=-1;
        end;
    for i:=1 to z do
        begin
            x1[x1size]:=( wekt( x[i], -1, y[i] ,0,0) );
            inc(x1size);
        end;
    zamiec(x1,x1size);
    for i:=1 to z do
        begin
            x2[x2size]:=( wekt( y[i], -1, x[i] ,0,0) );
            inc(x2size);
        end;
    zamiec(x2,x2size);
    for i:=1 to z do
        begin
            x3[x3size]:=( wekt( inf+x[i]-y[i], -1, y[i] ,0,0) );
            inc(x3size);
        end;
    zamiec(x3,x3size);
    for i:=1 to z do
        begin
            x4[x4size]:=( wekt( x[i]+y[i], -1, y[i] ,0,0) );
            inc(x4size);
        end;
    zamiec(x4,x4size);
    for j:=0 to p-1 do
        begin
            for k:=0 to 1 do
                if w[3*j+k]<0 then
                    begin
                        w[3*j+k]:=z-w[3*j+2];
                        w[3*j+2]:=w[3*j+2]-w[3*j+1-k];
                    end;
             writeln(w[3*j],' ',w[3*j+1],' ',w[3*j+2]);
        end;
end.
