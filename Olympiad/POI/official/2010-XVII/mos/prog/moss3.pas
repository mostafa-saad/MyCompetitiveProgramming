(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Mosty (MOS)                                   *
 *   Plik:                 moss3.pas                                     *
 *   Autor:                Tomasz Kulczynski                             *
 *   Opis:                 Rozwiazanie powolne.                          *
 *   Zlozonosc czasowa:    O(2^m * m)                                    *
 *   Zlozonosc pamieciowa: O(n + m)                                      *
 *                                                                       *
 *************************************************************************)

const MM=2001;
const NN=1001;

var n,m:longint;
    a,b,l,p:array[1..MM] of longint;
    stopien,x:array[1..NN] of longint;

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

            ll:=kr[u]^.nast;
            dispose(kr[u]);
            kr[u]:=ll;

            u:=a[e]+b[e]-u;
        end;
    p:=wynik;
    while p^.nast<>nil do
        begin
            u:=g;
            q:=p;
            while kr[u]<>nil do
                begin
                    e:=kr[u]^.x;
                    
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
            p:=q^.nast;
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

function max(a:longint;b:longint):longint;
begin
    max:=b;
    if a>b then
        max:=a;
end;

var i,ret,rozw,w,maska:longint;
    xx:lista;
    ok:boolean;

begin
    read(n,m);
    for i:=1 to NN do 
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
    ret:=1 shl 30;
    if m>30 then 
        while true do
            begin
            end;
    for maska:=0 to (1 shl m)-1 do
        begin
            w:=0;
            for i:=1 to n do
                x[i]:=0;
            for i:=1 to m do
                if (maska and (1 shl (i-1)))<>0 then
                    begin
                        w:=max(w,l[i]);
                        inc(x[a[i]]);
                    end
                else
                    begin
                        w:=max(w,p[i]);
                        inc(x[b[i]]);
                    end;
            ok:=true;
            for i:=1 to n do
                if x[i]<>(stopien[i] div 2) then
                    ok:=false;
            if ok and (ret>w) then
                begin
                    ret:=w;
                    rozw:=maska;
                end;
        end;
    if ret=(1 shl 30) then
        writeln('NIE')
    else
        begin
            writeln(ret);
            for i:=1 to m do
                if (rozw and (1 shl (i-1)))<>0 then
                    begin
                        xx:=kr[a[i]];
                        new(kr[a[i]]);
                        kr[a[i]]^.x:=i;
                        kr[a[i]]^.nast:=xx;
                    end
                else
                    begin
                        xx:=kr[b[i]];
                        new(kr[b[i]]);
                        kr[b[i]]^.x:=i;
                        kr[b[i]]^.nast:=xx;
                    end;
            euler();
        end;
end.
