program otoci;

type 
    UnionFind = record
        parent : array[1..30000] of longint;
        rank : array[1..30000] of longint;
    end;    

    Fenwick = record
        n : longint;
        a : array of longint;
    end;
    
    pNode = ^Node;
    pEdge = ^Edge;
    pPath = ^Path;
    
    Node = record
        index : longint;
        parent : pNode;
        adj_list : pEdge;
        my_path : pPath;       
        depth, penguins : longint;
        heaviest : pNode;
        weight, length : longint;
    end;
    
    Edge = record
        source, destination : pNode;
        next : pEdge;
    end;
    
    Path = record
        top : pNode;
        L : Fenwick;
    end;
   
    Forest = record
        n : longint;
        nodes : array[1..30000] of pNode;
    end;
    
    Command = record
        ch : char;
        A, B : longint;
    end;



procedure UnionFind_Init( var UF : UnionFind; n : longint );
var
    i : longint;
begin
    for i := 1 to n do begin
        UF.parent[i] := i;
        UF.rank[i] := 0;
    end;
end;

function UnionFind_Find( var UF : UnionFind; a : longint ) : longint;
begin
    if UF.parent[a] <> a then UF.parent[a] := UnionFind_Find( UF, UF.parent[a] );
    UnionFind_Find := UF.parent[a];
end;

function UnionFind_Union( var UF : UnionFind; a, b : longint ) : boolean;
var
    tmp : longint;
begin
    a := UnionFind_Find( UF, a );
    b := UnionFind_Find( UF, b );
    if a = b then 
        UnionFind_Union := false
    else begin
        if UF.rank[a] < UF.rank[b] then begin tmp := a; a := b; b := tmp; end;
        if UF.rank[a] = UF.rank[b] then UF.rank[a] += 1;
        UF.parent[b] := a;
        UnionFind_Union := true;
    end;
end;

procedure Fenwick_Init( var F : Fenwick; n : longint );
begin
    F.n := n;
    setlength( F.a, F.n );
end;

procedure Fenwick_Update( var F : Fenwick; x, v : longint );
begin
    while x <= F.n do begin
        F.a[x] += v;
        x += x and -x;
    end;   
end;

function Fenwick_Query( var F : Fenwick; x : longint ) : longint;
begin
    Fenwick_Query := 0;
    while x > 0 do begin
        Fenwick_Query += F.a[x];
        x -= x and -x;
    end;    
end;

procedure Path_Init( P : pPath; n : longint; top : pNode );
begin
    P^.top := top;
    Fenwick_Init( P^.L, n+1 );   
end;

procedure Path_Update( P : pPath; a : pNode; v : longint );
begin
    Fenwick_Update( P^.L, a^.depth - P^.top^.depth + 1, v );
end;

function Path_Query( P : pPath; a : pNode ) : longint;
begin
    Path_Query := Fenwick_Query( P^.L, a^.depth - P^.top^.depth + 1 ); 
end;

function Path_Query2( P : pPath; a, b : pNode ) : longint;
var
    tmp : pNode;
begin
    if a^.depth < b^.depth then begin tmp := a; a := b; b := tmp; end;
    Path_Query2 := 
        Fenwick_Query( P^.L, a^.depth - P^.top^.depth + 1 ) - 
        Fenwick_Query( P^.L, b^.depth - P^.top^.depth );        
end;

procedure Node_Init( N : pNode );
begin
    N^.parent := nil;
    N^.adj_list := nil;
    N^.my_path := nil;
    N^.depth := 0;
    N^.heaviest := nil;
    N^.weight := 1;
    N^.length := 1;
end;

procedure Node_AddNeighbour( N, other : pNode );
var
    e : pEdge;
begin
    e := new( pEdge );
    e^.source := N;
    e^.destination := other;
    e^.next := N^.adj_list;
    N^.adj_list := e;
end;

procedure Node_BuildTree( N : pNode );
var
    e : pEdge;
begin
    e := N^.adj_list;
    while e <> nil do begin
        if e^.destination <> N^.parent then begin         
            e^.destination^.parent := N;
            e^.destination^.depth := N^.depth + 1;
            Node_BuildTree( e^.destination );        
            N^.weight += e^.destination^.weight;
            if (N^.heaviest = nil) or (e^.destination^.weight > N^.heaviest^.weight) then begin
                N^.heaviest := e^.destination;
                N^.length := e^.destination^.length + 1;
            end;
        end;
        
        e := e^.next;
    end;
end;

procedure Node_BuildPath( N : pNode );
var
    p : pPath;
    a : pNode;
    e : pEdge;
begin
    p := new( pPath );
    Path_Init( p, N^.length, N );
        
    a := N;
    while a <> nil do begin
        a^.my_path := p;
        Path_Update( p, a, a^.penguins );
        
        e := a^.adj_list;
        while e <> nil do begin
            if (e^.destination <> a^.parent) and (e^.destination <> a^.heaviest) then
                 Node_BuildPath( e^.destination );            
                 
            e := e^.next;
        end;
        
        a := a^.heaviest;
    end; 
end;

procedure Node_UpdatePenguins( N : pNode; penguins : longint );
begin
    Path_Update( N^.my_path, N, penguins - N^.penguins );
    N^.penguins := penguins;
end;

procedure Forest_Init( var F : Forest; n : longint );
var
    i : longint;
begin
    F.n := n;
    
    for i := 1 to F.n do begin
        F.nodes[i] := new( pNode );
        Node_Init( F.nodes[i] );
        F.nodes[i]^.index := i;
        read( F.nodes[i]^.penguins );        
    end;
    readln();
end;

procedure Forest_AddEdge( var F : Forest; u, v : longint );
begin
    Node_AddNeighbour( F.nodes[u], F.nodes[v] );
    Node_AddNeighbour( F.nodes[v], F.nodes[u] );   
end;

procedure Forest_Build( var F : Forest );
var
    i : longint;
begin            
    for i := 1 to F.n do
        if F.nodes[i]^.parent = nil then begin       
            Node_BuildTree( F.nodes[i] );            
            Node_BuildPath( F.nodes[i] );
        end;          
end;

procedure Forest_UpdatePenguins( var F : Forest; i, penguins : longint );
begin
    Node_UpdatePenguins( F.nodes[i], penguins );   
end;

function Forest_CountPenguins( var F : Forest; i, j : longint ) : longint;
var
    a, b, tmp : pNode;
begin
    a := F.nodes[i];
    b := F.nodes[j];
    
    Forest_CountPenguins := 0;
        
    while a^.my_path <> b^.my_path do begin
        if a^.my_path^.top^.depth < b^.my_path^.top^.depth then begin
            tmp := a; a := b; b := tmp;
        end;
        Forest_CountPenguins += Path_Query( a^.my_path, a );
        a := a^.my_path^.top^.parent;
    end;

    Forest_CountPenguins += Path_Query2( a^.my_path, a, b );
end;

procedure DummyRead( n : longint );
var
    i : longint;
    c : char;
begin
    for i := 1 to n do read( c );    
end;

var
    N, Q, i : longint;
    F : Forest;
    UF1, UF2 : UnionFind;
    commands : array[1..300000] of Command;
begin
    readln( N );
    Forest_Init( F, N );   
    readln( Q );    
    
    UnionFind_Init( UF1, N );
    for i := 1 to Q do begin
        read(commands[i].ch);
        
        if commands[i].ch = 'b' then DummyRead( 6 );
        if commands[i].ch = 'e' then DummyRead( 9 );
        if commands[i].ch = 'p' then DummyRead( 8 );
        
        readln( commands[i].A, commands[i].B );
                       
        if commands[i].ch = 'b' then
            if UnionFind_Union( UF1, commands[i].A, commands[i].B ) then            
                Forest_AddEdge( F, commands[i].A, commands[i].B );                    
    end;
 
    Forest_Build( F );
    
    UnionFind_Init( UF2, N );

    for i := 1 to Q do begin
        if commands[i].ch = 'b' then begin        
            if UnionFind_Union( UF2, commands[i].A, commands[i].B ) then
                writeln( 'yes' )
            else
                writeln( 'no' );
        end;
        if commands[i].ch = 'e' then begin        
            if UnionFind_Find( UF2, commands[i].A ) <> UnionFind_Find( UF2, commands[i].B ) then
                writeln( 'impossible' )
            else
                writeln( Forest_CountPenguins( F, commands[i].A, commands[i].B ) );
        end;
        if commands[i].ch = 'p' then begin
            Forest_UpdatePenguins( F, commands[i].A, commands[i].B );
        end;                 
    end;      
end.