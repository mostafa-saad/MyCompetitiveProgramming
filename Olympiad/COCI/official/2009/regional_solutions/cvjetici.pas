program cvjetici;

var
   N, L, R, i, x : longint;
   A : array[1..100000] of longint;
   B : array[0..1000] of longint;
   
begin
   readln( N );
   for i := 1 to N do begin
      readln( L, R );

      writeln( A[L]+B[L div 256] + A[R]+B[R div 256] );

      A[L] := -B[L div 256];
      A[R] := -B[R div 256]; 
      
      x := L+1;
      while (x < R) and (x mod 256 <> 0) do begin
         A[x] := A[x] + 1;
         x := x + 1;
      end;
      
      while x + 256 <= R do begin
         B[x div 256] := B[x div 256] + 1;
         x := x + 256;
      end;

      while (x < R) do begin
         A[x] := A[x] + 1;
         x := x + 1;
      end;      
   end;
end.