program kolekcija;

uses classes;

type
   ppjesma = ^pjesma;
   pjesma = record
      x : longint;
      a, b : longint;
   end;

var
   n, k, m, i : longint;
   pjesme : array[0..300001] of pjesma;
   next : array[0..300000] of longint;
   sorted : array[0..300001] of ppjesma;
   lista : TList;
   memo : array[0..300000,0..1] of longint;
   p : ppjesma;

function cmp( A, B : pointer ) : longint;
var
   aa, bb : ppjesma;
begin
   aa := A; bb := B;
   cmp := aa^.x - bb^.x;
end;

function rec( i, vrh : longint; reconstruct : boolean ) : longint;
var
   j, hi, t : longint;
begin
   if vrh = 1 then j := next[i] else j := i+1;
   if vrh = 1 then hi := sorted[i]^.x+k-1 else hi := sorted[i]^.x;

   if reconstruct then
      for t := i to j-1 do begin
         sorted[t]^.a := hi-k+1;
         sorted[t]^.b := hi;
      end;

   if j > m then begin
      rec := 0;
      exit;
   end;

   if not reconstruct and (memo[i,vrh] >= 0) then begin
      rec := memo[i,vrh];
      exit;
   end;

   if k + rec( j, 1, false ) < sorted[j]^.x-hi + rec( j, 0, false ) then begin
      memo[i,vrh] := k + rec( j, 1, reconstruct );
   end else begin
      memo[i,vrh] := sorted[j]^.x-hi + rec( j, 0, reconstruct );
   end;

   rec := memo[i,vrh];
end;

begin
   readln( n, k );
   readln( m );

   pjesme[0].x := -1000000000;
   for i := 1 to m do readln( pjesme[i].x );
   pjesme[m+1].x := 2000000000;

   lista := TList.create;
   for i := 0 to m+1 do begin
      lista.add( @pjesme[i] );
      memo[i,0] := -1;
      memo[i,1] := -1;
   end;
   lista.sort( @cmp );

   for i := 0 to m+1 do sorted[i] := lista[i];

   next[0] := 1;
   for i := 1 to m do begin
      next[i] := next[i-1];
      while sorted[next[i]]^.x - sorted[i]^.x < k do inc( next[i] );
   end;

   writeln( rec( 0, 0, true ) );

   for i := 1 to m do begin
      p := @pjesme[i];
      if p^.a < 1 then begin p^.a := 1; p^.b := k; end;
      if p^.b > n then begin p^.a := n-k+1; p^.b := n; end;
      writeln( p^.a, ' ', p^.b );
   end;
end.
