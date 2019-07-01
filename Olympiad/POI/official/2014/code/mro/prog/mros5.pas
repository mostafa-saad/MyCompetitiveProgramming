(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Mrowisko                                      *
 *   Autor:                Bartlomiej Dudek                              *
 *   Zlozonosc czasowa:    O(ng log m)   m - rozmiar najwiekszej z grup  *
 *   Zlozonosc pamieciowa: O(n+g)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Kompresujemy drzewo tak, aby nie bylo         *
 *                         wierzcholkow o stopniu 2 (poza dwoma          *
 *                         wyroznionymi). W kazdym kroku teraz grupa     *
 *                         bedzie zmniejszac sie przynajmniej dwukrotnie.*
 *                                                                       *
 *************************************************************************)

program mros5;

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

var
    n,k,g,mrowa,mrowb: longint;
    a,b,i,j: longint;
    kra,ost: array[1..MAXN] of Lista;
    rozmiar: array[1..MAXG] of longint;
    sasiadow,kier: array[1..MAXN] of longint;
    ile: int64;
    start: Boolean;

function min(a,b: longint): longint;
begin
    if a < b then min := a
else min := b;
end;

function max(a,b: longint): longint;
begin
    if a > b then max := a
else max := b;
end;

function dfs(u,xpocz: longint) : Boolean;
var
    t,x,dziel: longint;
begin
    dziel:= sasiadow[u];
    if start=false then dziel:=dziel-1;
    start:=false;
    if dziel=0 then 
begin
    dfs:=false;
    exit;
end;
x:=xpocz div dziel;
if x=0 then
begin
    dfs:=false;
    exit;
end;
t:=kier[u];
if ((u = mrowa) and (t = mrowb)) or ((u=mrowb) and (t=mrowa)) then
begin

    if x=k then dfs:=true
else dfs:=false;
exit;
end;
if dfs(t,x)=true then dfs:=true
else dfs:=false;
end;
procedure dfs_pocz(u:longint);
var
    iter: Lista;
    t: longint;
begin
    iter:=kra[u];
    while iter <> nil do
    begin
        t:=iter^.u;
        if kier[t]=-1 then
        begin
            kier[t]:=u;
            dfs_pocz(t);
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
        kier[i]:=-1;
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
    for i:=1 to n do
    begin
        if(sasiadow[i] <>2) then popraw(i);
    end;
    kier[mrowa]:=mrowb;
    kier[mrowb]:=mrowa;
    dfs_pocz(mrowa);
    dfs_pocz(mrowb);
    ile:=0;	
    for i:=1 to n do
    begin
        if sasiadow[i]=1 then
        begin
            for j:=1 to g do
            begin
                start:=true;
                if dfs(i,rozmiar[j]) then ile:=ile+1;
            end;
        end;
    end;
    writeln(ile*k);
end.
