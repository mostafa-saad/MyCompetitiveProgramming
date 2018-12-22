program sretan;

var
   K : longint;
   S : string;

procedure load;
begin
   readln(K);
end;

procedure solve;
begin
   inc(K);
   while (K > 1) do begin
      if K mod 2 = 1 then
         S := '7' + S
      else
         S := '4' + S;
      K := K div 2;
   end;
end;

procedure output;
begin
   writeln(S);
end;

begin
   load;
   solve;
   output;
end.
