program george;

const inf = 1000000000;

var
   N, M : longint;
   A, B, K, G : longint;
   i, j, t, u, v, d : longint;
   prolazak : array[1..1000,1..1000] of longint;
   t_george : array[1..1000,1..1000] of longint;
   put : array[1..1000] of longint;
   udalj : array[1..1000] of longint;
   bio : array[1..1000] of boolean;

function min( a, b : longint ) : longint;
begin
   if a < b then min := a else min := b;
end;
function max( a, b : longint ) : longint;
begin
   if a > b then max := a else max := b;
end;

begin
   readln( N, M );
   for i := 1 to N do
      for j := 1 to N do begin
         prolazak[i,j] := inf;
         t_george[i,j] := inf;
      end;

   readln( A, B, K, G );
   for i := 1 to G do read( put[i] );
   readln;

   for i := 1 to M do begin
      readln( u, v, d );
      prolazak[u,v] := d;
      prolazak[v,u] := d;
   end;

   t := 0;
   for i := 2 to G do begin
      t_george[put[i-1],put[i]] := t;
      t_george[put[i],put[i-1]] := t;
      t := t + prolazak[put[i-1],put[i]];
   end;

   for i := 1 to N do begin
      udalj[i] := inf;
      bio[i] := false;
   end;
   udalj[A] := K;

   for i := 1 to N do begin
      u := -1;
      for j := 1 to N do begin
         if bio[j] then continue;
         if u = -1 then u := j;
         if udalj[j] < udalj[u] then u := j;
      end;
      bio[u] := true;

      for v := 1 to N do
         if udalj[u] < t_george[u,v] then
            udalj[v] := min( udalj[v], udalj[u] + prolazak[u,v] )
         else
            udalj[v] := min( udalj[v], max( t_george[u,v]+prolazak[u,v], udalj[u] ) + prolazak[u,v] );
   end;

   writeln( udalj[B] - udalj[A] );
end.
