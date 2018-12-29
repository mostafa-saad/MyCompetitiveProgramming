program tamnica;

uses classes;

var
   n : int64;
   k : longint;
   x : array[1..100000] of int64;
   a : array[1..100000] of int64;
   b : array[1..100000] of int64;
   lista : TList;
   where : array[1..100000] of longint;
   best : array[1..100000] of int64;

procedure readInput;
var
   i : longint;
begin
   readln( n );
   readln( k );
   for i := 1 to k do
      readln( x[i] );
end;

function square( x : int64 ) : int64;
begin
   square := x*x;
end;

function previous( x : int64 ) : int64;
var
   lo, hi, mid : int64;
   root, base, edge : int64;
begin
   lo := 0; hi := 100000000;
   while lo <> hi do begin
      mid := (lo+hi) div 2;
      if square( mid ) < x then lo := mid+1 else hi := mid;
   end;
   root := lo;
   base := square( root );
   edge := base - root + 1;

   if x > edge then
      previous := square( root-2 ) + 1 - (base-x)
   else
      previous := square( root-2 ) + 3 - (base-x);
end;

function cmp( A, B : pointer ) : longint;
var
   aa, bb : ^int64;
begin
   aa := A; bb := B;
   if aa^ < bb^ then cmp := -1
   else if aa^ > bb^ then cmp := 1
   else cmp := 0;
end;

procedure init;
var
   i, j : longint;
   tmp : ^int64;
begin
   lista := TList.create;
   for i := 1 to k do lista.add( @x[i] );
   lista.sort( @cmp );

   for i := 1 to k do begin
      tmp := lista[i-1];
      b[i] := tmp^;
   end;

   j := 1;
   for i := 1 to k do begin
      a[i] := previous( b[i] );
      while (j < i) and (b[j] < a[i]) do inc( j );
      where[i] := j;
   end;
end;


procedure update( var what : int64; value : int64 );
begin
   if (what = -1) or (value < what) then what := value;
end;


function solve() : int64;
var
   i : longint;
   solution : int64;
begin
   for i := 1 to k do best[i] := -1;
   solution := n;

   for i := k downto 1 do begin
      update( best[i], abs(n-b[i]) );
      update( best[where[i]], best[i] + b[where[i]] - a[i] + 1 );
      if where[i] = 1 then
         update( solution, best[i] + a[i] )
      else
         update( best[where[i]-1], best[i] + a[i] - b[where[i]-1] + 1 );
   end;

   solve := solution;
end;

begin
   readInput;
   init;
   writeln( solve() );
end.
