
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 1 - Task OKVIRI
  Programming language Pascal
*)

program okviri;

var
   ulaz       : string;
   i, n, r, s : integer;
   izlaz      : array[1..5] of string;

procedure crtaj(x: char; c: integer; y: char);
var dr, ds : integer;
begin
   izlaz[3][c] := x;
   for dr:=-2 to 2 do
      for ds:=-2 to 2 do
         if abs(dr) + abs(ds) = 2 then
            izlaz[3+dr][c+ds] := y;
end;

begin
   read(ulaz);
   n := length(ulaz);

   for r:=1 to 5 do
      for s:=1 to 4*n+1 do
         izlaz[r] := izlaz[r] + '.';

   for i:=1 to n do
      crtaj( ulaz[i], 4*(i-1)+3, '#' );
   for i:=1 to n div 3 do
      crtaj( ulaz[3*i], 4*(3*i-1)+3, '*' );

   for r:=1 to 5 do
      writeln( izlaz[r] );
end.
