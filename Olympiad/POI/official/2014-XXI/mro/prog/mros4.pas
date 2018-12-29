(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Mrowisko                                      *
 *   Autor:                Bartlomiej Dudek                              *
 *   Zlozonosc czasowa:    O(n^2 * g)                                    *
 *   Zlozonosc pamieciowa: O(n+g)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Symulujemy ruch kazdej grupy mrowek           *
 *                         z kazdego liscia.                             *
 *                                                                       *
 *************************************************************************)
 
program mros4;

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
    sasiadow: array[1..MAXN] of longint;
    ile: int64;



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

function dfs(u,pr,xpocz: longint) : Boolean;
var
    iter: Lista;
    t,x,dziel: longint;
begin
    dziel:= sasiadow[u];
    if pr <>-1 then dziel:=dziel-1;
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
iter:=kra[u];
while iter <> nil do
begin
    if iter^.u <> pr then
    begin
        t:=iter^.u;
        if ((u = mrowa) and (t = mrowb)) or ((u=mrowb) and (t=mrowa)) then
        begin
            if x=k then dfs:=true
        else dfs:=false;
        exit;
    end;
    if dfs(t,u,x)=true then 
begin
    dfs:=true;
    exit;
end;
    end;
    iter := iter^.nast;
end;
dfs:=false;
exit;
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

begin
    read(n);
    read(g);
    read(k);

    for i:=1 to n do
    begin
        kra[i]:=nil;
        ost[i]:=nil;
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
    ile:=0;

    for i:=1 to n do
    begin
        if sasiadow[i]=1 then
        begin
            for j:=1 to g do
            begin
                if dfs(i,-1,rozmiar[j]) then ile:=ile+1;
            end;
        end;
    end;
    writeln(ile*k);
end.
