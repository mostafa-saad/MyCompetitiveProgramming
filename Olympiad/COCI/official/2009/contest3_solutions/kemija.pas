program kemija;

var
   ulaz : string;
   i    : integer;

begin
   readln(ulaz);
   i := 1;
   while i <= length(ulaz) do begin
      write(ulaz[i]);
      if pos(ulaz[i], 'aeiou') <> 0 then begin
         i := i+2;
      end;
      i := i+1;
   end;
   writeln;
end.
