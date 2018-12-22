program ptice;

var 
   i, len, naj : longint;
   aa, bb, cc : longint;
   A, B, C, S : string;

begin
   readln( len );
   readln( S );
   
   naj := 0;
   aa := 0; A := '';
   bb := 0; B := '';
   cc := 0; C := '';
   
   while length(A) < len do A := A + 'ABC';
   while length(B) < len do B := B + 'BABC';
   while length(C) < len do C := C + 'CCAABB';
   
   for i := 1 to len do begin
      if S[i] = A[i] then aa := aa + 1;
      if S[i] = B[i] then bb := bb + 1;
      if S[i] = C[i] then cc := cc + 1;      
   end;
   
   if aa > naj then naj := aa;
   if bb > naj then naj := bb;
   if cc > naj then naj := cc;
   
   writeln( naj );
   if naj = aa then writeln( 'Adrian' );
   if naj = bb then writeln( 'Bruno' );
   if naj = cc then writeln( 'Goran' );
end.