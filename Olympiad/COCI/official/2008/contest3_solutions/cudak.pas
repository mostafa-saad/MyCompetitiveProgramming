program cudak;

var
   A, B : int64;
   pow10 : array [0..15] of int64;
   memo : array [0..15,0..135] of int64;
   minSolution : int64;
   i, j, S : longint;

function rec( prefix : int64; digits, sum : longint ) : int64;
var ret, mini, maxi : int64;
    dig : longint;
begin
   mini := prefix;
   maxi := prefix + pow10[digits]-1;

   if (sum < 0) or (mini > B) or (maxi < A) then begin
      rec := 0;
      exit;
   end;

   if digits = 0 then begin
      if sum > 0 then
         rec := 0
      else begin
         rec := 1;
         if minSolution = -1 then minSolution := prefix;
      end;

      exit;
   end;

   if (mini >= A) and (maxi <= B) and (memo[digits,sum] <> -1) then begin
      rec := memo[digits,sum];
      exit;
   end;

   ret := 0;
   for dig := 0 to 9 do
      ret := ret + rec( prefix + dig*pow10[digits-1], digits-1, sum-dig );

   if (mini >= A) and (maxi <= B) then memo[digits,sum] := ret;
   rec := ret;
end;

begin
   pow10[0] := 1;
   for i := 1 to 15 do pow10[i] := pow10[i-1] * 10;

   readln( A, B, S );

   for i := 0 to 15 do
      for j := 0 to 135 do
         memo[i,j] := -1;
   minSolution := -1;

   writeln( rec( 0, 15, S ) );
   writeln( minSolution );
end.
