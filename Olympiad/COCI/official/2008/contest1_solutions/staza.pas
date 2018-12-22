program staza;
uses Classes;

const MAXN = 10000;

const PUT = 0;
const DJIR = 1;

var
   n, m : longint;
   i : longint;
   a, b : longint;
   adj : array[1..MAXN] of TList;

   nPrstena : longint;
   broj : array[1..MAXN] of longint;
   prsten : array[1..MAXN] of TList;

   stack : array[1..MAXN] of longint;
   stackTop : longint;

   prsteni : array[1..MAXN] of TList;
   mostovi : array[1..MAXN] of TList;

   traversalTime : longint;
   discover : array[1..MAXN] of longint;
   lowlink : array[1..MAXN] of longint;

   memo : array[1..MAXN,0..1] of longint;

procedure dfs( u, dad : longint );
var
   i, v : longint;
begin
   traversalTime := traversalTime + 1;
   discover[u] := traversalTime;
   lowlink[u] := discover[u];

   stackTop := stackTop + 1;
   stack[stackTop] := u;

   for i := 0 to adj[u].Count-1 do begin
      v := longint(adj[u].Items[i]);
      if v = dad then continue;

      if discover[v] <> 0 then begin
         if discover[v] < lowlink[u] then lowlink[u] := discover[v];
      end else begin
         dfs( v, u );

         if lowlink[v] < discover[u] then begin
            if lowlink[v] < lowlink[u] then lowlink[u] := lowlink[v];
         end else if lowlink[v] = discover[u] then begin

            nPrstena := nPrstena + 1;
            prsten[nPrstena] := TList.Create;

            while stack[stackTop] <> v do begin
               prsten[nPrstena].Add( Pointer( broj[stack[stackTop]] ) );
               stackTop := stackTop-1;
            end;
            prsten[nPrstena].Add( Pointer( broj[stack[stackTop]] ) );
            stackTop := stackTop-1;

            prsteni[u].Add( Pointer( broj[nPrstena] ) );
         end else begin
            mostovi[u].Add( Pointer( broj[stack[stackTop]] ) );
            stackTop := stackTop-1;
         end;
      end;
   end;
end;

function max( a, b : longint ) : longint;
begin
   if a > b then max := a else max := b;
end;

function rec( X, stoRacunam : longint ) : longint;
var
   profit : longint;
   P : longint;
   best, smjer1, smjer2, ciklus : longint;
   i, j : longint;
begin
   if memo[X][stoRacunam] >= 0 then begin
      rec := memo[X][stoRacunam];
   end else begin
      memo[X][stoRacunam] := 0;

      profit := 0; (* koliko maksimalno mogu profitirati ako se ne moram vratiti u X *)

      for i := 0 to mostovi[X].Count-1 do begin (* za sve mostove koji izlaze iz X *)
         profit := max( profit, 1 + rec( longint(mostovi[X].Items[i]), PUT ) );
      end;

      for i := 0 to prsteni[X].Count-1 do begin (* za sve prstene koji vise iz X *)
         P := longint(prsteni[X].Items[i]);

         best := 0;
         smjer1 := 1; smjer2 := 1;
         ciklus := prsten[P].Count + 1;

         for j := 0 to prsten[P].Count-1 do begin
            best := max( best, smjer1 + rec( longint(prsten[P].Items[j]), PUT ) );
            smjer1 := smjer1 + 1 + rec( longint(prsten[P].Items[j]), DJIR );

            best := max( best, smjer2 + rec( longint(prsten[P].Items[prsten[P].Count-j-1]), PUT ) );
            smjer2 := smjer2 + 1 + rec( longint(prsten[P].Items[prsten[P].Count-j-1]), DJIR );

            ciklus := ciklus + rec( longint(prsten[P].Items[j]), DJIR );
         end;

         memo[X][stoRacunam] := memo[X][stoRacunam] + ciklus;

         profit := max( profit, best - ciklus );
      end;

      if stoRacunam = PUT then memo[X][stoRacunam] := memo[X][stoRacunam] + profit;

      rec := memo[X][stoRacunam];
   end;
end;

begin
   readln( n, m );

   for i := 1 to n do begin
      adj[i] := TList.Create;
      mostovi[i] := Tlist.Create;
      prsteni[i] := Tlist.Create;
      broj[i] := i;
   end;

   for i := 1 to m do begin
      readln( a, b );

      adj[a].Add( Pointer( broj[b] ) );
      adj[b].Add( Pointer( broj[a] ) );
   end;

   traversalTime := 0;
   for i := 1 to n do discover[i] := 0;
   stackTop := 0;
   nPrstena := 0;
   dfs( 1, 0 );


   for i := 1 to n do begin
      memo[i,0] := -1;
      memo[i,1] := -1;
   end;

   writeln( rec( 1, 0 ) );
end.
