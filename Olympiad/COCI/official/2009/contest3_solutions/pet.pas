program pet;

var
   max_score, winner, i, sum, j, x : integer;

begin
   max_score := 0;
   for i:=1 to 5 do begin
      sum := 0;
      for j:=1 to 4 do begin
         read(x);
         sum := sum+x;
      end;
      if sum > max_score then begin
         max_score := sum;
         winner := i;
      end;
   end;
   writeln(winner, ' ', max_score);
end.
