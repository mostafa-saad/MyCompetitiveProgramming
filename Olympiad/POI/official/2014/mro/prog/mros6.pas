(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Mrowisko                                      *
 *   Autor:                Bartlomiej Dudek                              *
 *   Zlozonosc czasowa:    O(ng)                                         *
 *   Zlozonosc pamieciowa: O(n+g)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Dla kazdego liscia liczymy przedzial, w jakim *
 *                         musialby byc rozmiar grupy, by startujac tu   *
 *                         zostal zjedzony przez mrowkojada. Potem       *
 *                         liniowo sprawdzamy, czy kazda z grup miesci   *
 *                         sie w tym przedziale.                         *
 *                                                                       *
 *************************************************************************)

program mros6;

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
    for i:=1 to n do
    begin
        if sasiadow[i]=1 then
        begin
            for i2:=1 to g do
            begin
                if (rozmiar[i2]>=prz[i,1]) and (rozmiar[i2]<prz[i,2]) then ile:=ile+1;
            end;
        end;
    end;
    writeln(ile*k);
end.
