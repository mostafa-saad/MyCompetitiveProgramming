program jednakost;

const inf = 1000000000;

var
   n, S : longint;
   i, j : longint;
   znak : char;
   A : array[1..1000] of longint;
   prva_nenula : array[1..1000] of longint;
   memo : array[1..1000,0..5000] of longint;

function opt( i, suma : longint ) : longint;
var
   j, broj : longint;
begin
   if i > n then begin
      if suma = 0 then opt := 0 else opt := inf;
   end else begin
      if memo[i,suma] = -1 then begin
         memo[i,suma] := inf;

         broj := 0;
         for j := prva_nenula[i] to n do begin
            broj := broj * 10 + A[j];
            if broj > suma then break;

            if 1 + opt( j+1, suma-broj ) < memo[i,suma] then
               memo[i,suma] := 1 + opt( j+1, suma-broj );
         end;
      end;
      opt := memo[i,suma];
   end;
end;

procedure ispisi( i, suma : longint );
var
   j, broj : longint;
begin
   if i > n then begin
      writeln( '=', S );
   end else begin
      if i > 1 then write( '+' );

      broj := 0;
      for j := i to n do begin
         write( A[j] );
         broj := broj * 10 + A[j];

         if opt( i, suma ) = 1 + opt( j+1, suma-broj ) then begin
            ispisi( j+1, suma-broj );
            break;
         end;
      end;
   end;
end;

begin
   n := 0;
   read( znak );
   repeat
      n := n + 1;
      A[n] := ord( znak ) - 48;
      read( znak );
   until znak = '=';
   readln( S );

   prva_nenula[n] := n;
   for i := n-1 downto 1 do
      if A[i] = 0 then prva_nenula[i] := prva_nenula[i+1] else prva_nenula[i] := i;

   for i := 1 to n do
      for j := 0 to S do
         memo[i,j] := -1;

   ispisi( 1, S );
end.
