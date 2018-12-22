program prva;

const MAX = 20;

var
   R, C : longint;
   rr, cc : longint;
   puzzle : array[1..MAX] of string;
   solution : string;
   word : string;

procedure append( x : char );
begin
   if x <> '#' then begin

      word := word + x;

   end else begin

      if (length(word) >= 2) and (word<solution) then solution := word;
      word := '';

   end;
end;

begin
   readln( R, C );

   for rr := 1 to R do readln( puzzle[rr] );

   solution := '~';

   for rr := 1 to R do begin
      for cc := 1 to C do
         append( puzzle[rr][cc] );
      append( '#' );
   end;

   for cc := 1 to C do begin
      for rr := 1 to R do
         append( puzzle[rr][cc] );
      append( '#' );
   end;

   writeln( solution );

end.
