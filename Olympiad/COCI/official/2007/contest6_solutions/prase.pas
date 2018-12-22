
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 6 - Task PRASE
  Programming language Pascal
*)

program prase;

var
   i, j, n   : longint;
   red       : array[1..100] of string;
   dosad, rj : longint;

begin
   readln(n);
   rj := 0;
   for i:=1 to n do begin
      readln(red[i]);
      dosad := 0;
      for j:=1 to i-1 do begin
         if red[i] = red[j] then
            dosad := dosad+1;
      end;
      if dosad > i-1-dosad then
         rj := rj+1;
   end;

   writeln(rj);
end.
