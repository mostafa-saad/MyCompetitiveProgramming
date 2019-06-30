(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Mosty (MOS)                                   *
 *   Plik:                 mos1.pas                                      *
 *   Autor:                Tomasz Kulczynski                             *
 *   Opis:                 Rozwiazanie wzorcowe.                         *
 *   Zlozonosc czasowa:    O((n + m) * m * log MAX_WIATR)                *
 *   Zlozonosc pamieciowa: O(n + m)                                      *
 *                                                                       *
 *************************************************************************)

const MM = 2001;
const NN = 1001;
const MAX_WIATR = 1000;

var n,m:longint;
    a,b,l,p:array[1..MM] of longint;
    stopien:array[1..NN] of longint;
    bylem:array[0..NN+MM+1] of boolean;

type krawedz=^kraw;
     kraw=record
        x,c:longint;
        r:krawedz;
        nast:krawedz;
     end;

var v:array[0..NN+MM+1] of krawedz;

function sciezka( x:longint; kon:longint ):boolean;
var a:krawedz;
begin
    if x=kon then sciezka:=true
    else if bylem[x] then sciezka:=false
    else begin
        bylem[x]:=true;
        a:=v[x];
        while a<>nil do
            begin
                if (a^.c>0) and (sciezka(a^.x,kon)) then
                    begin
                        dec(a^.c);
                        inc(a^.r^.c);
                        sciezka:=true;
                        exit;
                    end;
                a:=a^.nast;
            end;
        sciezka:=false;
    end;
end;

function maxflow( pocz:longint; kon:longint ):longint;
var i:longint;
begin
    maxflow:=0;
    while true do
        begin
            for i:=0 to n+m+1 do
                bylem[i]:=false;
            if not sciezka(pocz,kon) then break;
            inc(maxflow);
        end;
end;

procedure add_edge( a:longint; b:longint; p:longint );
var x,y:krawedz;
begin
    new(x);
    new(y);
    x^.x:=b;
    x^.r:=y;
    x^.c:=p;
    x^.nast:=v[a];
    v[a]:=x;

    y^.x:=a;
    y^.r:=x;
    y^.c:=0;
    y^.nast:=v[b];
    v[b]:=y;
end;

procedure tworz( x:longint);
var i:longint;
    xx:krawedz;
begin
    for i:=0 to n+m+1 do
        begin
            while v[i]<>nil do
                begin
                    xx:=v[i]^.nast;
                    dispose(v[i]);
                    v[i]:=xx;
                end;
        end;
    for i:=1 to n do
        add_edge( 0, i, stopien[i] div 2 );
    for i:=1 to m do
        begin
            if l[i]<=x then
                add_edge( a[i], n+i, 1 );
            if p[i]<=x then
                add_edge( b[i], n+i, 1 );
            add_edge( n+i, n+m+1, 1 );
        end;
end;

type lista=^list;
     list=record
        x:longint;
        nast:lista;
     end;

var kr:array[1..NN] of lista;

procedure euler();
var g,u,e:longint;
    wynik,kon,p,q,nastepny:lista;
    ll:lista;
begin
    if kr[1]=nil then exit;
    g:=1;
    new(wynik);
    kon:=wynik;
    u:=1;
    while kr[u]<>nil do
        begin
            e:=kr[u]^.x;
            
            new(kon^.nast);
            kon:=kon^.nast;
            kon^.nast:=nil;
            kon^.x:=e;
{            writeln('wrzuc norma ',e);}
            ll:=kr[u]^.nast;
            dispose(kr[u]);
            kr[u]:=ll;

            u:=a[e]+b[e]-u;
        end;
    p:=wynik;
    while p^.nast<>nil do
        begin
            q:=p;
            u:=g;
            while kr[u]<>nil do
                begin
                    e:=kr[u]^.x;
{                    writeln('wrzuc po ',p^.x,' ',e);}
                    nastepny:=p^.nast;
                    new(p^.nast);
                    p:=p^.nast;
                    p^.x:=e;
                    p^.nast:=nastepny;

                    ll:=kr[u]^.nast;
                    dispose(kr[u]);
                    kr[u]:=ll;

                    u:=a[e]+b[e]-u;
                end;
            p:=q;
            p:=p^.nast;
            g:=a[p^.x]+b[p^.x]-g;
        end;
    while wynik<>kon do
        begin
            wynik:=wynik^.nast;
            write(wynik^.x);
            write(' ');
        end;
    writeln;
end;

var i,lewo,prawo,s:longint;
    x:krawedz;
    ll:lista;

begin
    read(n,m);
    for i:=1 to n do 
        stopien[i]:=0;
    for i:=1 to m do 
    begin
        a[i]:=0;
        b[i]:=0;
        l[i]:=0;
        p[i]:=0;
        read(a[i],b[i],l[i],p[i]);
        inc(stopien[a[i]]);
        inc(stopien[b[i]]);
    end;
    for i:=0 to n+m+1 do 
        v[i]:=nil;
    for i:=1 to n do
        kr[i]:=nil;
    lewo:=1;
    prawo:=MAX_WIATR+1;
    while lewo<prawo do
    begin
        s:=(lewo+prawo) div 2;
        tworz(s);
        if maxflow(0,n+m+1)=m then 
            prawo:=s
        else 
            lewo:=s+1;
    end;
    if lewo>MAX_WIATR then
        writeln('NIE')
    else begin
        writeln(lewo);
        tworz(lewo);
        maxflow(0,n+m+1);
        for i:=1 to m do
            begin
                x:=v[n+i];
                while x<>nil do
                    begin
                        if x^.c>0 then
                            begin
                                ll:=kr[x^.x];
                                new(kr[x^.x]);
                                kr[x^.x]^.x:=i;
                                kr[x^.x]^.nast:=ll;
                            end;
                        x:=x^.nast;
                    end;
            end;
        euler();
    end;
end.
