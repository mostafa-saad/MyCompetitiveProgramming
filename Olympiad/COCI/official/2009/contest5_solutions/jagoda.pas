program jagoda;

const MAXN = 100000;

var
   box, cup              : array[0..MAXN] of longint;
   N, M, K, A, B, ans, i : longint;

begin
   read(N, M);
   K := trunc(sqrt(N));
   for i:=1 to M do begin
      read(B, A);
      dec(A);
      B := B + A;

      ans := 0;
      while (A < B) and (A mod K <> 0) do begin
         inc(box[A]);
         ans := ans + box[A];
         inc(A);
      end;

      if B <> N then begin
         while (A < B) and (B mod K <> 0) do begin
            dec(B);
            inc(box[B]);
            ans := ans + box[B];
         end;
      end;

      while A < B do begin
         inc(cup[A div K]);
         ans := ans + cup[A div K];
         A := A + K;
      end;
      writeln(ans);
   end;
end.
