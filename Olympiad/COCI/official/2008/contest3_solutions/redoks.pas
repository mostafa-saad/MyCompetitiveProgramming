program redoks;

const MAX = 250000;

function mod10( x : longint ) : longint;
begin
   if x < 10 then mod10 := x else mod10 := x-10;
end;

type
   PInterval = ^Interval;
   Interval = record
      lo, hi : longint;
      freq : array[0..9] of longint;
      lazy : longint;
      left, right : PInterval;
   end;

var tmp : array [0..9] of longint;

procedure rotate( x : PInterval; rot : longint );
var i : longint;
begin
   for i := 0 to 9 do tmp[i] := x^.freq[i];
   for i := 0 to 9 do x^.freq[mod10(i+rot)] := tmp[i];
   x^.lazy := mod10( x^.lazy + rot );
end;

procedure split( x : PInterval );
begin
   rotate( x^.left, x^.lazy );
   rotate( x^.right, x^.lazy );
   x^.lazy := 0;
end;

procedure join( x : PInterval );
var i : longint;
begin
   for i := 0 to 9 do
      x^.freq[i] := x^.left^.freq[i] + x^.right^.freq[i];
   x^.lazy := 0;
end;

var
   i, n, m : longint;
   start : array [1..MAX] of char;
   root, allocator : Pinterval;
   memory : array [0..2*MAX] of Interval;
   ret : longint;
   A, B : longint;


procedure treeBuild( x : PInterval );
var i, mid : longint;
begin
   if x^.lo = x^.hi then begin

      for i := 0 to 9 do x^.freq[i] := 0;

      x^.freq[ ord(start[x^.lo]) - 48 ] := 1;
      x^.lazy := 0;

   end else begin

      mid := (x^.lo + x^.hi) div 2;

      x^.left := allocator; inc( allocator );
      x^.left^.lo := x^.lo;
      x^.left^.hi := mid;
      treeBuild( x^.left );

      x^.right := allocator; inc( allocator );
      x^.right^.lo := mid+1;
      x^.right^.hi := x^.hi;
      treeBuild( x^.right );

      join( x );

   end;
end;

procedure treeQuery( x : PInterval );
var i : longint;
begin
   if (x^.lo > B) or (x^.hi < A) then exit;
   if (A <= x^.lo) and (x^.hi <= B) then begin

      for i := 0 to 9 do ret := ret + i * x^.freq[i];
      rotate( x, 1 );

   end else begin

      split( x );

      treeQuery( x^.left );
      treeQuery( x^.right );

      join( x );

   end;
end;

begin
   readln( n, m );
   for i := 1 to n do
      read( start[i] );
   readln;

   allocator := @memory[0];
   root := allocator; inc( allocator );

   root^.lo := 1;
   root^.hi := n;
   treeBuild( root );

   for i := 1 to m do begin
      readln( A, B );

      ret := 0;
      treeQuery( root );
      writeln( ret );
   end;
end.
