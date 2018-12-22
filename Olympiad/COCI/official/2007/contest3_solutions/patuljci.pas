
/*
  Croatian Open Competition in Informatics 2006/2007
  Contest 3 - Task PATULJCI
  Programming language Pascal
*/

program Patuljci;

var
   broj : array[1..9] of integer;
   i, j, k, suma : integer;

begin
   suma := 0;
   for i := 1 to 9 do begin
      readln( broj[i] );
      suma := suma + broj[i];
   end;

   for i := 1 to 9 do
      for j := i+1 to 9 do
         if suma - broj[i] - broj[j] = 100 then
            for k := 1 to 9 do
               if (k <> i) and (k <> j) then
                  writeln( broj[k] );
end.
