program poklon;

const MAX = 1000000;
const MAXN = 100000;

type interval = record lo, hi : longint; end;

function cmp( A, B : interval ) : boolean;
begin
   cmp := (A.lo > B.lo) or (A.lo = B.lo) and (A.hi < B.hi);
end;

var
   n : longint;
   intervals, tmp : array[1..MAXN] of interval;
   dp, how : array[1..MAXN] of longint;
   fenwick : array[0..MAX] of longint;
   i, x, ret : longint;

function query( x : longint ) : longint;
var
   i, ret : longint;
begin
   ret := 0;

   i := x;
   while i > 0 do begin
      if (fenwick[i] <> 0) and ((ret = 0) or (dp[fenwick[i]] > dp[ret])) then
         ret := fenwick[i];
      i := i - (i and -i);
   end;

   query := ret;
end;

procedure update( x, v : longint );
var
   i : longint;
begin
   i := x;
   while i <= MAX do begin
      if (fenwick[i] = 0) or (dp[v] > dp[fenwick[i]]) then
         fenwick[i] := v;
      i := i + (i and -i);
   end;
end;

procedure mergesort( lo, hi : longint );
var
   mid : longint;
   i, j, k : longint;
begin
   if lo <> hi then begin
      mid := (lo+hi) div 2;
      mergesort( lo, mid );
      mergesort( mid+1, hi );

      i := lo;
      j := mid+1;
      k := lo;
      while (i <= mid) and (j <= hi) do begin
         if cmp( intervals[i], intervals[j] ) then begin
            tmp[k] := intervals[i];
            i := i + 1;
         end else begin
            tmp[k] := intervals[j];
            j := j + 1;
         end;
         k := k + 1;
      end;
      while i <= mid do begin
         tmp[k] := intervals[i];
         i := i + 1;
         k := k + 1;
      end;
      while j <= hi do begin
         tmp[k] := intervals[j];
         j := j + 1;
         k := k + 1;
      end;
      for i := lo to hi do intervals[i] := tmp[i];
   end;
end;

begin
   readln( n );

   for i := 1 to n do readln( intervals[i].lo, intervals[i].hi );

   mergesort( 1, n );

   ret := 1;
   for i := 1 to n do begin;
      dp[i] := 1;
      how[i] := 0;

      x := query( intervals[i].hi );

      if x <> 0 then begin
         dp[i] := dp[x] + 1;
         how[i] := x;
      end;

      update( intervals[i].hi, i );

      if dp[i] > dp[ret] then ret := i;
   end;

   writeln( dp[ret] );
   while ret <> 0 do begin
      writeln( intervals[ret].lo, ' ', intervals[ret].hi );
      ret := how[ret];
   end;
end.
