program tajna;

var a : string;
    n : longint;
    R, S : longint;
    rr, ss : longint;

begin
   readln( a );
   n := length( a );

   R := 1;
   for rr := 1 to n do begin
      ss := n div rr;
      if (rr <= ss) and (rr*ss = n) then R := rr;
   end;
   S := n div R;

   for rr := 0 to R-1 do
      for ss := 0 to S-1 do
         write( a[ss*R+rr+1] );
   writeln;
end.
