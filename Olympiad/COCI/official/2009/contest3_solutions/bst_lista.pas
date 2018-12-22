program bst_lista;

const maxn = 300000;

var
   n, i           : longint;
   prev, next     : array[0..maxn+1] of longint;
   X, M, V, depth : array[0..maxn+1] of longint;
   zbr            : int64;

function max(a, b : longint) : longint; begin if a > b then max := a else max := b; end;

begin
   read(n);
   for i:=1 to n do read(X[i]);

   for i:=1 to n do begin
      prev[i] := i-1;
      next[i] := i+1;
   end;
   prev[1] := 0;
   next[n] := 0;
   depth[0] := -1;

   for i:=n downto 1 do begin
      M[X[i]] := prev[X[i]];
      V[X[i]] := next[X[i]];
      next[prev[X[i]]] := next[X[i]];
      prev[next[X[i]]] := prev[X[i]];
   end;

   zbr := 0;
   for i:=1 to n do begin
      depth[X[i]] := 1+max(depth[M[X[i]]], depth[V[X[i]]]);
      zbr := zbr + depth[X[i]];
      writeln(zbr);
   end;
end.