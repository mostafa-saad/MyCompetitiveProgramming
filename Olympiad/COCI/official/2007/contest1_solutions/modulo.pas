
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 1 - Task MODULO
  Programming language Pascal
*)

program modulo;

var
   i, sol, x : integer;
   pojavio   : array[0..41] of boolean;

begin
   for i:=1 to 10 do begin
      read(x);
      pojavio[x mod 42] := true;
   end;

   for i:=0 to 41 do
      if pojavio[i] then
         sol := sol + 1;

   writeln( sol );
end.
