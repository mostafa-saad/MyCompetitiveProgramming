program datum;

const dana_u_mjesecu : array[1..12] of integer = (31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
const imena : array[0..6] of string = ('Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday');

var
   dd, mm, dan, m : longint;

begin
   read(dd, mm);
   dan := 2+dd;
   for m:=1 to mm-1 do
      dan := dan + dana_u_mjesecu[m];
   writeln(imena[dan mod 7]);
end.
