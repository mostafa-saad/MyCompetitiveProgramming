program tresnja;

var
   A, B : int64;
   p10  : array[0..15] of int64;
   memo : array[0..15, 0..10] of int64;
   i, j : longint;

function min(a, b : int64) : int64; begin if a < b then min := a else min := b; end;
function max(a, b : int64) : int64; begin if a > b then max := a else max := b; end;

function intersect(n : longint; prefix : int64) : int64;
var lo, hi : int64;
begin
   if n < 0 then begin
      intersect := 0;
      exit;
   end;
   lo := max(prefix * p10[n], A);
   hi := min((prefix+1) * p10[n]-1, B);
   intersect := max(0, hi-lo+1);
end;

function rec(n, prev : longint; prefix : int64) : int64;
var
   mini, maxi, ret, t : int64;
   digit, k           : longint;
begin
   mini := prefix * p10[n];
   maxi := (prefix+1) * p10[n] - 1;

   if (mini > B) or (maxi < A) then begin rec := 0; exit; end;
   if (mini >= A) and (maxi <= B) and (memo[n, prev] <> -1) then begin rec := memo[n, prev]; exit; end;

   ret := 0;
   for digit:=0 to 9 do begin
      if digit = prev then continue;

      t := prefix;
      for k:=1 to n do begin
         t := t*10 + digit;
         ret := ret + digit * k * k * (intersect(n-k, t)-intersect(n-k-1, t*10+digit)) + rec( n-k, digit, t );
      end;
   end;
   
   if (mini >= A) and (maxi <= B) then memo[n, prev] := ret;
   rec := ret;
end;

begin
   read(A, B);

   p10[0] := 1;
   for i:=1 to 15 do p10[i] := 10 * p10[i-1];

   for i:=0 to 15 do
      for j:=0 to 10 do
         memo[i, j] := -1;
   writeln(rec(15, 10, 0));
end.
