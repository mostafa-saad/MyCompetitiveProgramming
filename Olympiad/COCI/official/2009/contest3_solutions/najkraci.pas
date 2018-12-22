program najkraci;

type
   PHeap = ^THeap;
   THeap = object
   n : longint;
   heap, poz, key : ^Longint;
   constructor init(cap : longint);
   procedure _set(p, x: longint);
   procedure push(x: longint);
   function pop : longint;
   procedure upheap(p : longint);
   procedure downheap(p : longint);
end;

constructor THeap.init(cap : longint);
var i : longint;
begin
   n := 0;
   getmem(heap, (cap+1)*sizeof(longint));
   getmem(poz, (cap+1)*sizeof(longint));
   getmem(key, (cap+1)*sizeof(longint));
   for i:=1 to cap do
      poz[i] := 0;
end;

procedure THeap._set(p, x : longint);
begin
   heap[p] := x;
   poz[x] := p;
end;

procedure THeap.push(x : longint);
begin
   n := n+1;
   _set(n, x);
   upheap(n);
end;

function THeap.pop : longint;
begin
   pop := heap[1];
   poz[heap[1]] := 0;
   _set(1, heap[n]);
   n := n-1;
   downheap(1);
end;

procedure THeap.upheap(p : longint);
var t : longint;
begin
   t := heap[p];
   while (p > 1) and (key[t] < key[heap[p div 2]]) do begin
      _set(p, heap[p div 2]);
      p := p div 2;
   end;
   _set(p, t);
end;

procedure THeap.downheap(p : longint);
var t, next : longint;
begin
   t := heap[p];
   while (2*p <= n) do begin
      next := 2*p;
      if (2*p+1 <= n) and (key[heap[2*p+1]] < key[heap[2*p]]) then
         next := 2*p+1;
      if key[heap[next]] < key[t] then begin
         _set(p, heap[next]);
         p := next;
      end else
         break;
   end;
   _set(p, t);
end;


const MAXV = 3000;
const MAXE = 10000;
const MODC = 1000000007;
const INF = 1000000000;

type
   PEdge = ^TEdge;
   TEdge =
   record
      u, v, weight, ret : longint;
      next              : PEdge;
   end;

var
   n, m                 : longint;
   edge                 : array[1..MAXE] of TEdge;
   adj                  : array[1..MAXV] of PEdge;
   paths_to, paths_from : array[1..MAXV] of longint;
   n_settled            : longint;
   settled              : array[1..MAXV] of longint;

procedure solve(source : longint);
var
   pq   : PHeap;
   e    : PEdge;
   i, u : longint;
begin
   new(pq, init(n));
   for i:=1 to n do pq^.key[i] := INF;

   pq^.key[source] := 0;
   paths_to[source] := 1;
   n_settled := 0;
   pq^.push(source);

   while pq^.n > 0 do begin
      u := pq^.pop;
      n_settled := n_settled + 1;
      settled[n_settled] := u;

      e := adj[u];
      while e <> nil do begin
         if pq^.key[e^.v] < pq^.key[u] + e^.weight then begin
            e := e^.next;
            continue;
         end;
         if pq^.key[e^.v] > pq^.key[u] + e^.weight then begin
            paths_to[e^.v] := 0;
            pq^.key[e^.v] := pq^.key[u] + e^.weight;
            if pq^.poz[e^.v] = 0 then 
               pq^.push(e^.v)
            else 
               pq^.upheap(pq^.poz[e^.v]);
         end;
         paths_to[e^.v] := (paths_to[e^.v] + paths_to[u]) mod MODC;
         e := e^.next;
      end;
   end;

   for i:=n_settled downto 1 do begin
      u := settled[i];
      paths_from[u] := 1;

      e := adj[u];
      while e <> nil do begin
         if pq^.key[e^.v] < pq^.key[u] + e^.weight then begin
            e := e^.next;
            continue;
         end;

         paths_from[u] := (paths_from[u] + paths_from[e^.v]) mod MODC;

         e^.ret := (e^.ret + int64(paths_to[u])*paths_from[e^.v]) mod MODC;
         e := e^.next;
      end;
   end;
end;

var
   i : longint;

begin
   readln(n, m);
   for i:=1 to n do adj[i] := nil;

   for i:=1 to m do begin
      readln(edge[i].u, edge[i].v, edge[i].weight);
      edge[i].ret := 0;
      edge[i].next := adj[edge[i].u];
      adj[edge[i].u] := @edge[i];
   end;

   for i:=1 to n do
      solve(i);

   for i:=1 to m do
      writeln(edge[i].ret);
end.
