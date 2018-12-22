program jabuka;

var i, R, G : longint;

begin
   read(R, G);

   i:=1;
   while i*i <= R do begin
      if R mod i = 0 then begin
         if G mod i = 0 then
            writeln(i, ' ', R div i, ' ', G div i);

         if (i*i <> R) and (G mod (R div i) = 0) then
            writeln(R div i, ' ', i, ' ', G div (R div i));
      end;
      inc(i);
   end;
end.
