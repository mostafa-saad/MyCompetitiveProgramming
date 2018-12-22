program barica;

const MAXN = 300000;
const inf = 1000000000;

type
   point = record x, y, m : longint end;

var
   i, a, xx, yy, n, k : longint;
   p : array[1..MAXN] of point;

   dp : array[0..MAXN] of longint;
   how : array[1..MAXN] of longint;
   maxX : array[0..100001] of longint;
   maxY : array[0..100001] of longint;
   order, tmp : array[1..MAXN] of longint;

   top : longint;
   S : array[1..MAXN] of longint;

function cmp( a, b : longint ) : boolean;
begin
   if p[a].x <> p[b].x then begin
      if p[a].x < p[b].x then cmp := true else cmp := false;
   end else begin
      if p[a].y < p[b].y then cmp := true else cmp := false;
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
         if cmp( order[i], order[j] ) then begin
            tmp[k] := order[i];
            i := i + 1;
         end else begin
            tmp[k] := order[j];
            j := j + 1;
         end;
         k := k + 1;
      end;
      while i <= mid do begin
         tmp[k] := order[i];
         i := i + 1;
         k := k + 1;
      end;
      while j <= hi do begin
         tmp[k] := order[j];
         j := j + 1;
         k := k + 1;
      end;
      for i := lo to hi do order[i] := tmp[i];
   end;
end;

begin
   readln( n, k );

   for i := 0 to 100000 do begin
      maxX[i] := 0;
      maxY[i] := 0;
   end;

   for i := 1 to n do begin
      readln( p[i].x, p[i].y, p[i].m );
      order[i] := i;
   end;
   mergesort( 1, n );

   dp[0] := -inf;
   for i := 1 to n do begin
      a := order[i];

      dp[a] := -inf;
      if a = 1 then dp[a] := p[a].m;

      xx := maxX[p[a].x];
      yy := maxY[p[a].y];

      if (dp[xx] >= k) and (dp[a] < dp[xx] + p[a].m - k) then begin
         dp[a] := dp[xx] + p[a].m - k;
         how[a] := xx;
      end;
      if (dp[yy] >= k) and (dp[a] < dp[yy] + p[a].m - k) then begin
         dp[a] := dp[yy] + p[a].m - k;
         how[a] := yy;
      end;

      if dp[a] > dp[xx] then maxX[p[a].x] := a;
      if dp[a] > dp[yy] then maxY[p[a].y] := a;
   end;

   top := 0;
   a := n;
   while a <> 1 do begin
      inc( top );
      S[top] := a;
      a := how[a];
   end;
   inc( top );
   S[top] := 1;

   writeln( dp[n] );
   writeln( top );
   while top > 0 do begin;
      writeln( p[S[top]].x, ' ', p[S[top]].y );
      dec( top );
   end;
end.
