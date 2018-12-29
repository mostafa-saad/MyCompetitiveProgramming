(*
  Croatian Olympiad in Informatics 2007
  Task POLICIJA
*)

program policija;

const MAXN = 100000;
const MAXE = 500000;

type 
   pEdge = ^Edge;
   Edge = record 
      u, v : longint;
      next : pEdge;
   end;

var
   N, M, Q : longint;
   glava   : array[1..MAXN] of pEdge;
   edges   : array[1..2*MAXE] of Edge;
   djeca   : array[1..MAXN] of longint;
   it      : pEdge;
   i, j    : longint;
   Time    : longint;
   tip, a, b, c, d, e, f            : longint;
   discover, finish, lowlink, depth : array[1..MAXN] of longint;
   djecabegin, djecaend             : array[0..MAXN] of longint;

procedure swap( var a, b : longint );
var 
   tmp : longint;
begin
   tmp := a;
   a := b;
   b := tmp;
end;

procedure dfs( u, dad, d : longint );
var
   it : pEdge;
begin
   discover[u] := Time;
   lowlink[u] := Time;
   depth[u] := d;
   Time := Time + 1;

   it := glava[u];
   while it <> NIL do begin
      if it^.v <> dad then begin
         if discover[it^.v] = -1 then begin
            dfs( it^.v, u, d+1 );
            if lowlink[it^.v] < lowlink[u] then lowlink[u] := lowlink[it^.v];
         end else begin;
            if discover[it^.v] < lowlink[u] then lowlink[u] := discover[it^.v];
         end;
      end;
      it := it^.next;
   end;
   
   finish[u] := Time;
   Time := Time + 1;
end;

function is_descendant( a, b : longint ) : boolean;
begin
   is_descendant := (discover[b] <= discover[a]) and (finish[a] <= finish[b]);
end;

function find_related_child( me, descendant : longint ) : longint;
var
   lo, hi, mid : longint;
begin
   lo := djecabegin[me];
   hi := djecaend[me] - 1;
   while lo <> hi do begin
      mid := (lo+hi) div 2;
      
      if discover[descendant] > finish[ djeca[mid] ] then lo := mid+1 
      else if finish[descendant] < discover[ djeca[mid] ] then hi := mid-1
      else begin
         lo := mid;
         hi := mid;
      end;     
   end;
   find_related_child := djeca[lo];
end;

begin
   readln( N, M );
   for i := 1 to N do begin
      glava[i] := NIL;
   end;

   for i := 1 to M do begin
      j := 2*i;
      readln( edges[j].u, edges[j].v );
      edges[j].next := glava[edges[j].u];
      glava[edges[j].u] := @edges[j];

      j := j-1;
      edges[j].u := edges[j+1].v;
      edges[j].v := edges[j+1].u;
      edges[j].next := glava[edges[j].u];
      glava[edges[j].u] := @edges[j];
   end;

   for i := 1 to N do begin
      discover[i] := -1;
      finish[i] := -1;
      lowlink[i] := -1;
      depth[i] := -1;
   end;
   

   dfs( 1, 0, 0 );


   djecabegin[0] := 1;
   djecaend[0] := 1;
   for i := 1 to N do begin
      djecabegin[i] := djecaend[i-1];
      djecaend[i] := djecabegin[i];

      it := glava[i];
      while it <> NIL do begin
         if depth[it^.v] = depth[it^.u] + 1 then begin
            djeca[ djecaend[i] ] := it^.v;
            djecaend[i] := djecaend[i] + 1; 
         end;
         it := it^.next;
      end;
   end;


   readln( Q );
   for i := 1 to Q do begin
      read( tip );
      if tip = 1 then begin;
         readln( a, b, c, d );
         if is_descendant( c, d ) then swap( c, d );

         if depth[d] < depth[c]+1 then writeln( 'yes' )
         else if lowlink[d] < discover[d] then writeln( 'yes' )
         else if is_descendant( a, d ) = is_descendant( b, d ) then writeln( 'yes' )
         else writeln( 'no' );
      end else begin
         readln( a, b, c );

         if (not is_descendant( a, c )) and (not is_descendant( b, c )) then writeln( 'yes' )
         else if is_descendant( a, c ) and is_descendant( b, c ) then begin
            e := find_related_child( c, a );
            f := find_related_child( c, b );
            if e = f then writeln( 'yes' )
            else if (lowlink[e] < discover[c]) and (lowlink[f] < discover[c]) then writeln( 'yes' )
            else writeln( 'no' );
         end else begin
            if is_descendant( a, c ) then swap( a, b );
            e := find_related_child( c, b );
            if lowlink[e] < discover[c] then writeln( 'yes' )
            else writeln( 'no' );
         end;
      end;
   end;
	
end.
