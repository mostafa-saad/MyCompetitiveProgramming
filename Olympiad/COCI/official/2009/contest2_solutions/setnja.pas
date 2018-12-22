program setnja;

type
   bigint = record 
      n : longint;
      digits : array[1..800] of longint;
   end;
   
procedure init( var A : bigint; x : longint );
begin
   A.n := 1;
   A.digits[1] := x;
end;

procedure copy( var A, B : bigint );
var 
   i : longint;
begin
   A.n := B.n;
   for i := 1 to A.n do A.digits[i] := B.digits[i];
end;

procedure pribroji( var A, B : bigint );
var
   i, carry, x: longint;
begin
   i := 1; 
   carry := 0;
  
   while (i <= A.n) or (i <= B.n) or (carry > 0) do begin
      x := carry;
      if i <= A.n then x := x + A.digits[i];
      if i <= B.n then x := x + B.digits[i];
         
      if x >= 1000000000 then begin
         A.digits[i] := x - 1000000000;
         carry := 1;
      end else begin 
         A.digits[i] := x;
         carry := 0;
      end;
      i := i + 1;
   end;
   A.n := i-1;
end;
   
procedure output( var A : bigint );
var
   i, j : longint;
   leading : boolean;
   d : array[1..9] of longint;
begin
   leading := true;
   for i := A.n downto 1 do begin
      for j := 1 to 9 do begin
         d[j] := A.digits[i] mod 10;
         A.digits[i] := A.digits[i] div 10;  
      end;
      for j := 9 downto 1 do begin
         if d[j] > 0 then leading := false;
         if not leading then write( d[j] );
      end;
   end;
   writeln;
end;   
   
var
   i : longint;
   s : ansistring;
   currA, currB : bigint;
   nextA, nextB : bigint;

begin
   readln( s );
   
   init( currA, 1 );
   init( currB, 0 );
   
   for i := length( s ) downto 1 do begin
      init( nextA, 0 );
      init( nextB, 0 );
     
      if (S[i] = '*') or (S[i] = 'P') then begin
         pribroji( nextA, currA );
         pribroji( nextB, currB );        
      end;

      if (S[i] = '*') or (S[i] = 'L') then begin
         pribroji( nextA, currA );
         pribroji( nextA, currA );
         pribroji( nextB, currB );        
      end;

      if (S[i] = '*') or (S[i] = 'R') then begin
         pribroji( nextA, currA );
         pribroji( nextA, currA );
         pribroji( nextB, currA );
         pribroji( nextB, currB );        
      end;

      copy( currA, nextA );
      copy( currB, nextB );
   end;   
     
   pribroji( currA, currB );  
   output( currA );   
end.