program cestarine;

uses classes;

const MAX = 100000;

type
   pint = ^longint;

function cmp_int( A, B : pointer ) : longint;
var
   aa, bb : pint;
begin
   aa := A; bb := B;
   cmp_int := aa^ - bb^;
end;

var
   n : longint;
   i, k : longint;
   a, b : array[1..MAX] of longint;
   dp : array[0..MAX] of int64;
   sorted_a, sorted_b : TList;

function min( a, b : int64 ) : int64;
begin
   if a < b then min := a else min := b;
end;

function calc( a, b : longint ) : int64;
begin
   calc := 1000000000000000;
   if a > b then calc := a - b;
   if b > a then calc := b - a;
end;

function raspodjela( n, k : longint ) : int64;
var
   a1, a2, a3 : pint;
   b1, b2, b3 : pint;
begin
   raspodjela := 1000000000000000;
   if k = 1 then begin
      a1 := sorted_a[n-1];
      b1 := sorted_b[n-1];
      raspodjela := min( raspodjela, calc(a1^, b1^) );
   end;
   if k = 2 then begin
      a1 := sorted_a[n-1]; a2 := sorted_a[n-2];
      b1 := sorted_b[n-1]; b2 := sorted_b[n-2];
      raspodjela := min( raspodjela, calc(a1^, b1^) + calc(a2^, b2^) );
      raspodjela := min( raspodjela, calc(a1^, b2^) + calc(a2^, b1^) );
   end;
   if k = 3 then begin
      a1 := sorted_a[n-1]; a2 := sorted_a[n-2]; a3 := sorted_a[n-3];
      b1 := sorted_b[n-1]; b2 := sorted_b[n-2]; b3 := sorted_b[n-3];
      raspodjela := min( raspodjela, calc(a1^, b1^) + calc(a2^, b2^) + calc(a3^, b3^) );
      raspodjela := min( raspodjela, calc(a1^, b1^) + calc(a2^, b3^) + calc(a3^, b2^) );
      raspodjela := min( raspodjela, calc(a1^, b2^) + calc(a2^, b1^) + calc(a3^, b3^) );
      raspodjela := min( raspodjela, calc(a1^, b2^) + calc(a2^, b3^) + calc(a3^, b1^) );
      raspodjela := min( raspodjela, calc(a1^, b3^) + calc(a2^, b1^) + calc(a3^, b2^) );
      raspodjela := min( raspodjela, calc(a1^, b3^) + calc(a2^, b2^) + calc(a3^, b1^) );
   end;
end;

begin
   readln( n );

   sorted_a := TList.Create;
   sorted_b := TList.Create;

   for i := 1 to n do begin
      readln( a[i], b[i] );

      sorted_a.add( @a[i] );
      sorted_b.add( @b[i] );
   end;

   sorted_a.sort( @cmp_int );
   sorted_b.sort( @cmp_int );

   dp[0] := 0;

   for i := 1 to n do begin
      dp[i] := 1000000000000000;

      for k := 1 to 3 do
         if i-k >= 0 then
            dp[i] := min( dp[i], dp[i-k] + raspodjela( i, k ) );
   end;

   writeln( dp[n] );
end.
