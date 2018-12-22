program dostava;

const maxr = 2000;
      maxs = 200;
      inf = -1;

var
   r, s, i, j, k, t, ll, rr: longint;
   grid, sum: array [0..maxr,0..maxs] of longint; // parcijalne sume za svaki redak
   G: array[0..maxr,0..1,0..2] of longint; // G[i][j][k] = tezina brida od (j==0? lijevog: desnog) polja i-tog retka, u smjeru k (vodoravno,gore,dolje)
   dp: array[0..maxr,0..1,0..maxr,0..1] of longint; // dp[i][a][j][b] = najkraci put od i-tog retka do j-tog retka, s kojeg kraja retka odredjuju a i b
   sol: Int64;

function fsum( i, l, r: longint ):longint; begin
   if r = 0 then begin fsum := 0; exit; end;
   if l = 0 then fsum := sum[i][r-1]
   else fsum := sum[i][r-1] - sum[i][l-1];
end;

function manji( a, b: longint ):longint; begin
   if a < b then manji := a else manji := b;
   if a = inf then manji := b;
   if b = inf then manji := a;
end;

// udaljenost od tocke do tocke, od nekoliko mogucih nacina putovanja odaberemo najbolji
function dist( r1, s1, r2, s2: longint ): longint;
var d1, d2, d3, d4: longint;
begin
     d1 := fsum( r1, 0, s1 ) + dp[r1][0][r2][0] + fsum( r2, 1, s2+1 );
     d2 := fsum( r1, 0, s1 ) + dp[r1][0][r2][1] + fsum( r2, s2, s-1 );
     d3 := fsum( r1, s1+1, s ) + dp[r1][1][r2][0] + fsum( r2, 1, s2+1 );
     d4 := fsum( r1, s1+1, s ) + dp[r1][1][r2][1] + fsum( r2, s2, s-1 );

     dist := manji( manji( d1, d2 ), manji( d3, d4 ) );
     if r1 = r2 then begin
        if s1 < s2 then dist := manji( dist, fsum( r1, s1+1, s2+1 ) )
        else dist := manji( dist, fsum( r1, s2, s1 ) );
     end;
end;

begin
     // ucitavanje
     read( r, s );
     for i := 0 to r-1 do
         for j := 0 to s-1 do read( grid[i][j] );

     // parcijalne sume
     for i := 0 to r-1 do begin
         sum[i][0] := grid[i][0];
         for j := 1 to s-1 do sum[i][j] := sum[i][j-1] + grid[i][j];
     end;

     // izgradnja grafa
     for i := 0 to r-1 do begin
         if i = 0 then begin G[i][0][0] := inf; G[i][1][0] := inf; end
         else begin G[i][0][0] := grid[i-1][0]; G[i][1][0] := grid[i-1][s-1]; end;

         if i+1 = r then begin G[i][0][2] := inf; G[i][1][2] := inf; end
         else begin G[i][0][2] := grid[i+1][0]; G[i][1][2] := grid[i+1][s-1]; end;

         G[i][0][1] := fsum( i, 1, s );
         G[i][1][1] := fsum( i, 0, s-1 );
     end;

     // dinamicko popunjavanje tablice
     for i := 0 to r-1 do // inicijalizacija na inf
         for j := 0 to r-1 do begin
             dp[i][0][j][0] := inf;
             dp[i][0][j][1] := inf;
             dp[i][1][j][0] := inf;
             dp[i][1][j][1] := inf;
         end;

     for k := 0 to 1 do begin
         for i := 0 to r-1 do begin
             dp[i][k][i][k] := 0;

             ll := 0;
             rr := 0;
             for j := i to r do begin
				dp[i][k][i][1-k] := manji( dp[i][k][i][1-k], ll+rr+G[j][k][1] );
				if j+1 = r then break;
				ll := ll + G[j][k][2];
				rr := rr + G[j+1][1-k][0];
             end;

             ll := 0;
             rr := 0;
             for j := i downto 0 do begin
				dp[i][k][i][1-k] := manji( dp[i][k][i][1-k], ll+rr+G[j][k][1] );
				if j-1 < 0 then break;
				ll := ll+G[j][k][0];
				rr := rr+G[j-1][1-k][2];
             end;
         end;
     end;

     for t := 1 to r-1 do begin
         for i := 0 to r-t-1 do
             for k := 0 to 1 do begin
				dp[i][k][i+t][k] := manji( dp[i][k][i+t][k], dp[i+1][k][i+t][k] + G[i][k][2] );
				dp[i][k][i+t][k] := manji( dp[i][k][i+t][k], dp[i][k][i][1-k] + G[i][1-k][2] + dp[i+1][1-k][i+t][k] );
				
				dp[i][k][i+t][1-k] := manji( dp[i][k][i+t][1-k], G[i][k][2] + dp[i+1][k][i+t][1-k] );
				dp[i][k][i+t][1-k] := manji( dp[i][k][i+t][1-k], dp[i][k][i][1-k] + G[i][1-k][2] + dp[i+1][1-k][i+t][1-k] );
             end;
	
         for i := t to r-1 do
             for k := 0 to 1 do begin
				dp[i][k][i-t][k] := manji( dp[i][k][i-t][k], dp[i-1][k][i-t][k] + G[i][k][0] );
				dp[i][k][i-t][k] := manji( dp[i][k][i-t][k], dp[i][k][i][1-k] + G[i][1-k][0] + dp[i-1][1-k][i-t][k] );
				
				dp[i][k][i-t][1-k] := manji( dp[i][k][i-t][1-k], G[i][k][0] + dp[i-1][k][i-t][1-k] );
				dp[i][k][i-t][1-k] := manji( dp[i][k][i-t][1-k], dp[i][k][i][1-k] + G[i][1-k][0] + dp[i-1][1-k][i-t][1-k] );
             end;
     end;

     sol := grid[0][0];
     ll := 0;
     rr := 0;

     read( k );
     for t := 1 to k do begin
         read( i, j );
         sol := sol + dist( ll, rr, i-1, j-1 );
         ll := i-1;
         rr := j-1;
     end;

     writeln( sol );
end.

