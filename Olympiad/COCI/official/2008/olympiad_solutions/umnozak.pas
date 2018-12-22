program umnozak;

var
   memo : array[0..17,0..29,0..18,0..12,0..10] of int64;
   f : array[1..4] of longint = ( 2, 3, 5, 7 );
   k : array[1..4] of longint = ( 0, 0, 0, 0 );
   code : array[0..9,1..4] of longint = (
      ( 0, 0, 0, 0 ),
      ( 0, 0, 0, 0 ),
      ( 1, 0, 0, 0 ),
      ( 0, 1, 0, 0 ),
      ( 2, 0, 0, 0 ),
      ( 0, 0, 1, 0 ),
      ( 1, 1, 0, 0 ),
      ( 0, 0, 0, 1 ),
      ( 3, 0, 0, 0 ),
      ( 0, 2, 0, 0 )
   );


function rec( digits : longint; a, pot, lo, hi : int64 ) : int64;
var
   b : int64;
   memoize, ok : boolean;
   digit, i : longint;
begin
   b := a + pot-1;
   if (a > hi) or (b < lo) then begin
      rec := 0;
      exit;
   end;

   if digits = 18 then begin
      if (k[1] > 0) or (k[2] > 0) or (k[3] > 0) or (k[4] > 0) then rec := 0 else rec := 1;
      exit;
   end;

   if (a >= lo) and (b <= hi) then memoize := true else memoize := false;

   if memoize and (memo[digits,k[1],k[2],k[3],k[4]] >= 0) then begin
      rec := memo[digits][k[1]][k[2]][k[3]][k[4]];
      exit;
   end;

   pot := pot div 10;

   rec := 0;

   for digit := 0 to 9 do begin
      if (digit = 0) and (a <> 0) then continue;

      ok := true;
      for i := 1 to 4 do
         if code[digit,i] > k[i] then ok := false;
      if not ok then continue;

      for i := 1 to 4 do k[i] := k[i] - code[digit,i];
      rec := rec + rec( digits+1, a + digit*pot, pot, lo, hi );
      for i := 1 to 4 do k[i] := k[i] + code[digit,i];
   end;

   if memoize then memo[digits,k[1],k[2],k[3],k[4]] := rec;
end;

var
   lo, hi, rjesenje : int64;

function ceil( a, b : int64 ) : int64;
begin
   ceil := (a+b-1) div b;
end;

function floor( a, b : int64 ) : int64;
begin
   floor := a div b;
end;

procedure gen( limit, product : int64; factor : longint );
begin
   if (product > 1000000000) or (product*product > limit) then exit;

   if factor > 4 then begin;
      rjesenje := rjesenje + rec( 0, 0, 1000000000000000000, ceil(lo,product), floor(hi,product) );
   end else begin
      gen( limit, product, factor + 1 );
      inc( k[factor] );
      gen( limit, product*f[factor], factor );
      dec( k[factor] );
   end;
end;

   var dig, a, b, c, d : longint;
begin
   readln( lo, hi );

   for dig := 0 to 17 do
   for a := 0 to 29 do
   for b := 0 to 18 do
   for c := 0 to 12 do
   for d := 0 to 10 do
      memo[dig,a,b,c,d] := -1;

   gen( hi, 1, 1 );

   writeln( rjesenje );
end.
