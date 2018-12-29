(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Festyn                                           *
 *   Autor:             Michal Bejda                                     *
 *   Zlozonosc czasowa: O(n^3)                                           *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************)

const
    MAXN = 610;
    INF = 1000000000;

var
    n,m1,m2,ssCnt,ordCnt : longint;
    M : Array[1..MAXN, 1..MAXN] of longint;
    LP : Array[1..MAXN, 1..MAXN] of longint;
    ordT : Array[1..MAXN] of longint;
    ss : Array[1..MAXN] of longint;
    sslp : Array[1..MAXN] of longint;
    v : Array[1..MAXN] of Boolean;
    
    
function Max (a, b: longint): longint;
begin
  if a < b then
    Max := b
  else
    Max := a;
end;

procedure dfs1( a: longint );
var
    b : longint;
begin
    v[a] := true;
    for b:=1 to n do
        if ( M[a][b] > (-1*INF) ) and ( not v[b] ) then
            dfs1(b);
    ordT[ordCnt] := a;
    ordCnt := ordCnt + 1;
end;

procedure dfs2( a, p: longint );
var
    b : longint;
begin
    ss[a] := p;
    v[a] := true;
    for b:=1 to n do
    begin
        if ( M[b][a] > (-1*INF) ) and ( not v[b] ) then 
            dfs2(b, p);
    end;
end;

procedure Compute_ssc ();
var
    i : longint;
begin
    for i:=1 to n do
        ss[i] := -1;
    for i:=1 to n do
        v[i] := false;
    ssCnt := 0;
    ordCnt := 1;
    
    for i:=1 to n do
        if not v[i] then
            dfs1(i);
    
    for i:=1 to n do
        v[i] := false;
    while ordCnt > 1 do
    begin
        ordCnt := ordCnt - 1;
        if not v[ ordT[ordCnt] ] then
        begin
            ssCnt := ssCnt + 1;
            dfs2( ordT[ordCnt], ssCnt );
        end;
    end;
end;

procedure Compute_lp ();
var
    i, j, k : longint;
begin
    for i:=1 to n do
        for j:=1 to n do
            if ss[i] = ss[j] then
                LP[i][j] := M[i][j]
            else
                LP[i][j] := -1 * INF;
    for k:=1 to n do
        for j:=1 to n do
            for i:=1 to n do
                if (LP[i][k] > (-1 * INF)) and (LP[k][j] > (-1 * INF)) then
                    LP[i][j] := Max( LP[i][j], LP[i][k] + LP[k][j] );
    for i:=1 to n do
        if LP[i][i] > 0 then
        begin
            Write('NIE');
            WriteLn;
            HALT;
        end;
end;

procedure Wczytaj;
var
    a,b,i,j,result : longint;
begin

    for i:=1 to n do 
        for j:=1 to n do
            if i=j then
                M[i,j] := 0
            else
                M[i,j] := -1 * INF;
                
                
    while m1>0 do
    begin
        Read(a, b);
        M[a][b] := Max(M[a][b], 1);
        M[b][a] := Max(M[b][a], -1);
        m1 := m1 - 1;
    end;
    
    while m2>0 do
    begin
        Read(a, b);
        M[a][b] := Max(M[a][b], 0);
        m2 := m2 - 1;
    end;
    
    Compute_ssc();
    
    Compute_lp();
    
    result := 0;


    for i:=1 to ssCnt do sslp[i] := 0;
    for i:=1 to n do
        for j:=1 to n do
            if ss[i] = ss[j] then
                sslp[ ss[i] ] := Max( sslp[ ss[i] ], Max( LP[i][j], -1 * LP[j][i] ) + 1 );
    for i:=1 to ssCnt do
        result := result + sslp[i];
    Write(result);
    Writeln;

end;
    
begin
    Read(n, m1, m2);
    Wczytaj();
end.
