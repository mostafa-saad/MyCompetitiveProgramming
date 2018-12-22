program bst_haxor;

const maxn = 300000;

var
   n, i, x, k        : longint;
   bio               : array[0..maxn+1] of boolean;
   depth, prev, next : array[0..maxn+1] of longint;
   zbr               : int64;

function max(a, b : longint) : longint; begin if a > b then max := a else max := b; end;

begin
   read(n);

   next[0] := n+1; prev[n+1] := 0;
   bio[0] := true; bio[n+1] := true;
   depth[0] := -1; depth[n+1] := -1;

   zbr := 0;
   for i:=1 to n do begin
      read(x);
      k := 1;

      while not bio[x-k] and not bio[x+k] do k := k+1;

      if bio[x-k] then begin
         prev[x] := x-k; next[x] := next[x-k];
      end;
      if bio[x+k] then begin
         next[x] := x+k; prev[x] := prev[x+k];
      end;

      prev[next[x]] := x;
      next[prev[x]] := x;

      bio[x] := true;
      depth[x] := 1+max(depth[prev[x]], depth[next[x]]);
      zbr := zbr + depth[x];
      writeln(zbr);
   end;
end.
