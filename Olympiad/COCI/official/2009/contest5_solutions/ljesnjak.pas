program ljesnjak;

const nizovi : array[1..8] of string = ('c-', 'c=', 'd-', 'dz=', 'lj', 'nj', 's=', 'z=');

var
   ulaz      : string;
   i, j, rez : longint;

begin
   readln(ulaz);
   i := 1;
   rez := 0;
   while i <= length(ulaz) do begin
      for j:=1 to 8 do
         if copy(ulaz, i, length(nizovi[j])) = nizovi[j] then begin
            i := i+length(nizovi[j])-1;
            break;
         end;
      inc(i);
      inc(rez);
   end;
   writeln(rez);
end.
