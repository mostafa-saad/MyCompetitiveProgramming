
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 4 - Task SKENER
  Programming language Pascal
*)

program skener;

var
    i, j, r, s, zoomr, zooms: integer;
    grid: array[1..50] of string;

begin
    readln( r, s, zoomr, zooms );
    for i := 1 to r do readln( grid[i] );
    for i := 1 to r*zoomr do begin
        for j := 1 to s*zooms do write( grid[ (i-1) div zoomr + 1 ][ (j-1) div zooms + 1 ] );
        writeln;
    end;
end.
