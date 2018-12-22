
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 6 - Task MAGIJA
  Programming language Pascal
*)

program magija;

var
   karta      : array[1..200, 1..200] of char;
   r, s, a, b : longint;
   i, j       : longint;

begin
   readln(r, s);
   for i:=1 to r do begin
      for j:=1 to s do begin
         read(karta[i, j]);
         karta[2*r-i+1, j] := karta[i, j];
         karta[i, 2*s-j+1] := karta[i, j];
         karta[2*r-i+1, 2*s-j+1] := karta[i, j];
      end;
      readln;
   end;

   readln(a, b);
   if karta[a, b] = '#' then
      karta[a, b] := '.'
   else
      karta[a, b] := '#';

   for i:=1 to 2*r do begin
      for j:=1 to 2*s do
         write(karta[i, j]);
      writeln;
   end;
end.
