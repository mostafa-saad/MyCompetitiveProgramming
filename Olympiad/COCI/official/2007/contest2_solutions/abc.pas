
(*
  Hrvatsko otvoreno natjecanje iz informatike 2006/2007
  2. kolo - Zadatak ABC
  Programski jezik Pascal

  Ucitamo brojeve A, B i C te odredimo pravilan redoslijed sa tri
  usporedbe i zamjenama po potrebi.

  Zatim ucitamo trazeni redoslijed, brojeve A, B i C stavimo u
  pomocni niz u trazenom redoslijedu te ispisemo pomocni niz.
*)

program abc;

var
   a, b, c, t, i : integer;
   str           : string;
   izlaz         : array[1..3] of integer;

begin
   readln( a, b, c );
   if a > b then begin t := a; a := b; b := t; end;
   if a > c then begin t := a; a := c; c := t; end;
   if b > c then begin t := b; b := c; c := t; end;

   readln( str );
   for i:=1 to 3 do begin
      if      str[i] = 'A' then izlaz[i] := a
      else if str[i] = 'B' then izlaz[i] := b
      else if str[i] = 'C' then izlaz[i] := c;
   end;

   writeln( izlaz[1], ' ', izlaz[2], ' ', izlaz[3] );
end.
