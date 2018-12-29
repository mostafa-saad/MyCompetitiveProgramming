(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Festyn                                           *
 *   Autor:             Michal Bejda                                     *
 *   Opis:              Rozwiazanie powolne, wykladnicze                 *
 *                                                                       *
 *************************************************************************)

const
    MAXN = 1010;
    INF = 1000000000;

var
    n,m1,m2 : longint;
    M : Array[1..MAXN, 1..MAXN] of longint;
    T : Array[1..MAXN] of longint;
    U : Array[1..MAXN] of Boolean;
    
function Max (a, b: longint): longint;
begin
  if a < b then
    Max := b
  else
    Max := a;
end;
    
function ValidTime (a : longint) : Boolean;
var
    i : longint;
begin
    ValidTime := true;
    for i:=1 to a do
        if not ( ( T[i] + M[i,a] <= T[a] ) and ( T[a] + M[a,i] <= T[i] ) ) then
            ValidTime := false;
end;
    
function DdSize () : longint;
var
    i,result : longint;
begin
    for i:=1 to n do
        U[i] := false;
    for i:=1 to n do
        U[ T[i] ] := true;
    result := 0;
    for i:=1 to n do
        if U[i] then
            result := result + 1;
    DdSize := result;
end;
    
function Assign (a : longint): longint;
var
    i,result : longint;
begin
    if a=n+1 then
        Assign := DdSize()
    else
    begin
        result := -1;
        for i:=1 to n do
        begin
            T[a] := i;
            if ValidTime(a) then
                result := Max( result, Assign(a+1) );
        end;
        Assign := result;
    end;
end;
    
procedure Wczytaj;
var
    a,b,i,j,result : longint;
begin

    for i:=1 to n do 
        for j:=1 to n do
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
    
    result := Assign(1);
    if result < 0 then
        Write('NIE')
    else
        Write(result);

    Writeln;

end;
    
begin
    Read(n, m1, m2);
    Wczytaj();
end.
