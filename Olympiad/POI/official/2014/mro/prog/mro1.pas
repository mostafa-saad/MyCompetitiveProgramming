(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Mrowisko                                      *
 *   Autor:                Bartlomiej Dudek                              *
 *   Zlozonosc czasowa:    O((n+g) log g)                                *
 *   Zlozonosc pamieciowa: O(n+g)                                        *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                         Dla kazdego wezla liczymy przedzial, w jakim  *
 *                         musialby byc rozmiar grupy, by startujac tu   *
 *                         zostal zjedzony przez mrowkojada.             *
 *                         Potem binarnie sprawdzamy ile z grup miesci   *
 *                         sie w tym przedziale.                         *
 *                                                                       *
 *************************************************************************)

program mro1;

type
    Lista = ^wsk;
    wsk =
    record
        u: longint;
        nast: Lista;
    end;

const
    MAXN = 1000000;
    MAXG = 1000000;
    MAXVAL=1000*1000*1000+2;
var
    n,k,g,mrowa,mrowb: longint;
    a,b,i,i2: longint;
    kra,ost: array[1..MAXN] of Lista;
    rozmiar: array[1..MAXG] of longint;
    sasiadow,ojc: array[1..MAXN] of longint;
    prz: array[1..MAXN,1..2] of longint;
    ile: int64;
    q,q2: int64;

procedure dfs(u:longint);
var
    iter: Lista;
    t,e,j: longint;
begin
    iter:=kra[u];
    while iter <> nil do
    begin
        t:=iter^.u;
        if ojc[u]<>t then
        begin
            e:=sasiadow[t];
            if e>1 then e:=e-1;
            for j:=1 to 2 do
            begin
                q:=prz[u,j];
                q:=q*e;
                if q>MAXVAL then q:=MAXVAL+1;
                prz[t,j]:=q;
            end;
            ojc[t]:=u;
            dfs(t);			
        end;
        iter:= iter^.nast;
    end;
end;



procedure dodaj(a,b: longint);
var
    cur: Lista;
begin
    new(cur);
    cur^.u := b;
    cur^.nast := nil;
    if kra[a] = nil then
    begin
        kra[a] := cur;
        ost[a] := cur;
    end
    else
    begin
        ost[a]^.nast := cur;
        ost[a] := cur;
    end;
end;

function przejdz(u0,sk0:longint): longint;
var
    u,sk,t,e:longint;
    iter: Lista;
begin
    u:=u0;
    sk:=sk0;

    while (sasiadow[u]=2) and (u<>mrowa) and (u<>mrowb) do
    begin
        e:=-1;
        iter:=kra[u];
        while iter <> nil do
        begin
            t:=iter^.u;
            if t<>sk then e:=t;
            iter:= iter^.nast;
        end;
        sk:=u;
        u:=e;
    end;
    przejdz:=u;
end;

procedure popraw(u:longint);
var
    iter: Lista;
    t: longint;
begin
    iter:=kra[u];
    while iter <> nil do
    begin
        t:=iter^.u;
        if sasiadow[t]=2 then
        begin
            iter^.u:=przejdz(t,u);
        end;
        iter:= iter^.nast;
    end;
end;
function bin_search(x:longint) :longint;
var
    m,p,k: longint;
begin
    if rozmiar[1]>=x then
    begin
        bin_search:=1;
        exit;
    end;
    p:=1;
    k:=g+1;
    while p+1<k do
    begin
        m:=(p+k) div 2;
        if rozmiar[m]<x then p:=m
    else k:=m;
end;
bin_search:=k;
end;

procedure sort(l, r: longint);

procedure swap(var x, y: longint);
var
    tmp : longint;
begin
    tmp := x;
    x := y;
    y := tmp;
end; { swap }

var
    i, j, x: longint;
begin
    i := l;
    j := r;
    x := rozmiar[(l+r) div 2];
    repeat
        while rozmiar[i]<x do
            i := i+1;
        while x<rozmiar[j] do
            j := j-1;
        if i<=j then
        begin
            swap(rozmiar[i], rozmiar[j]);
            i := i+1;
            j := j-1;
        end;
    until i>j;
    if l<j then
        sort(l, j);
    if i<r then
        sort(i, r);
    end; { sort }

begin
    read(n);
    read(g);
    read(k);

    for i:=1 to n do
    begin
        kra[i]:=nil;
        ost[i]:=nil;
        prz[i,1]:=MAXVAL;
        prz[i,2]:=MAXVAL;
        sasiadow[i]:=0;
    end;

    for i:=1 to g do
    begin
        read(rozmiar[i]);
    end;

    for i:=1 to n-1 do
    begin
        readln(a,b);
        if i=1 then
        begin
            mrowa:=a;
            mrowb:=b;
        end;
        sasiadow[a]:=sasiadow[a]+1;
        sasiadow[b]:=sasiadow[b]+1;
        dodaj(a,b);
        dodaj(b,a);
    end;
    for i:=1 to 2 do
    begin
        ojc[mrowa]:=mrowb;
        q:=sasiadow[mrowa];
        if q<>1 then q:=q-1;
        q2:=q;
        q2:=q2*k;
        if q2<MAXVAL then prz[mrowa,1]:=q2;
        q2:=(k+1)*q;
        if q2<MAXVAL then prz[mrowa,2]:=q2;
        dfs(mrowa);
        i2:=mrowa;
        mrowa:=mrowb;
        mrowb:=i2;
    end;
    ile:=0;
    sort(1,g);
    for i:=1 to n do
    begin
        if sasiadow[i]=1 then
        begin
            ile:=ile+bin_search(prz[i,2]);
            ile:=ile-bin_search(prz[i,1]);
        end;
    end;
    writeln(ile*k);
end.
