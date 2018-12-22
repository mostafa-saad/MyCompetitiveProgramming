
(*
  Hrvatsko otvoreno natjecanje iz informatike 2006/2007
  2. kolo - Zadatak R2
  Programski jezik Pascal

  Po definiciji aritmeticke sredine vrijedi s=(r1+r2)/2. Iz te
  jednadzbe slijedi r2=2*s-r1.
*)

program r2;

var r1, s : integer;

begin
   readln(r1, s);
   writeln(2*s - r1);
end.
