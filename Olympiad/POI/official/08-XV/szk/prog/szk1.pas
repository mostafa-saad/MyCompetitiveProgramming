(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Szklana pulapka (SZK)                                     *
 *   Plik:     szk1.pas                                                  *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie wzorcowe O(l*log l) (l- dlugosc boku)}.       *
 *                                                                       *
 *************************************************************************)
program szk;

const MAX1=150000;
const MAX2=510000;

type point=record
    x:longint;
    y:longint;
    ver:longint;
    num:longint;
end;

var n,m,akt,a,b,c,p,q,i,j:longint;
    len:array [0..MAX1] of longint;
    next:array [0..MAX2,0..1] of longint;
    side:array [0..MAX2] of point;
    pom:array [0..MAX2] of point;

function comp(aa,bb:point;w:longint):boolean;
begin
    if (w=0) then
        if (not(aa.x=bb.x)) then exit(aa.x<bb.x) else exit(aa.y<bb.y)
    else
        if (not(aa.y=bb.y)) then exit(aa.y<bb.y) else exit(aa.x<bb.x);
end;

procedure msort(lo,hi,which:longint);
var s:longint;
begin
    if not(lo=hi) then
    begin
        s:=((lo+hi) shr 1);
        msort(lo,s,which);
        msort(s+1,hi,which);
        a:=lo;
        c:=lo;
        b:=s+1;
        while (c<=hi) do
        begin
            if ((b=hi+1) or ((a<=s) and (comp(side[a],side[b],which)))) then
            begin
                pom[c]:=side[a];
                inc(a);
            end
            else
            begin
                pom[c]:=side[b];
                inc(b);
            end;
            inc(c);
        end;
        for c:=lo to hi do
            side[c]:=pom[c];
    end;
end;

procedure make_next(wh:longint);
begin
    msort(0,n-1,wh);
    akt:=(-1);
    for i:=0 to (n-1) do
    begin
        if ((side[i].ver>=0) and (not((side[i].ver mod 2)=wh))) then
            next[side[i].num,wh]:=(-(side[i].ver shr 1)-1)
        else
        begin
            if (akt<0) then akt:=i else
                begin
                    next[side[akt].num,wh]:=side[i].num;
                    next[side[i].num,wh]:=side[akt].num;
                    akt:=(-1);
                end;
        end;
    end;
end;

procedure insert();
begin
    side[n].x:=a-b;
    side[n].y:=a+b;
    side[n].ver:=(-1);
    side[n].num:=n;
    inc(n);
end;

procedure find(fr:longint);
begin
    p:=fr;
    if (next[fr,0]>=0) then akt:=0 else akt:=1;
    while true do
    begin
        if (next[p,akt]<0) then break;
        p:=next[p,akt];
        akt:=(akt xor 1);
    end;
    next[p,akt]:=(next[p,akt]*(-1));
    p:=next[p,akt];
end;

function pp(k:longint):longint;
begin
    exit((k+m) mod m);
end;

begin
    readln(m);
    writeln(m shr 1);
    for i:=0 to m-1 do
    begin
        readln(a,b);
        len[i]:=a+b;
    end;
    c:=len[m-1];
    for i:=m-1 downto 1 do dec(len[i],len[i-1]);
    dec(len[0],c);
    a:=0; b:=0; n:=0;
    for i:=0 to m-1 do
    begin
        if ((i mod 2)=1) then
        begin
            if (len[i]>0) then
            begin
                for j:=0 to len[i]-1 do
                begin
                    insert();
                    inc(a);
                end;
                side[n-len[i]].ver:=(i shl 1);
                if (len[pp(i-1)]>0) then
                    inc(side[n-len[i]].ver);
            end
            else
            begin
                for j:=0 to (len[i]+1)*(-1) do
                begin
                    insert();
                    dec(a);
                end;
                side[n+len[i]].ver:=(i shl 1);
                if (len[pp(i-1)]<0) then
                    inc(side[n+len[i]].ver);
            end;
        end
        else
        begin
            if (len[i]>0) then
            begin
                for j:=0 to len[i]-1 do
                begin
                    insert();
                    inc(b);
                end;
                side[n-len[i]].ver:=(i shl 1);
                if (len[pp(i-1)]>0) then
                    inc(side[n-len[i]].ver);
            end
            else
            begin
                for j:=0 to (len[i]+1)*(-1) do
                begin
                    insert();
                    dec(b);
                end;
                side[n+len[i]].ver:=(i shl 1);
                if (len[pp(i-1)]<0) then
                    inc(side[n+len[i]].ver);
            end;
        end;
    end;
    make_next(0); make_next(1);
    for i:=0 to n-1 do
    begin
        if ((next[i,0]<0) or (next[i,1]<0)) then
        begin
            find(i);
            if (next[i,0]<0) then q:=(next[i,0]*(-1)) else q:=(next[i,1]*(-1));
            writeln(pp(q-2)+1,' ',pp(p-2)+1);
        end;
    end;
end.