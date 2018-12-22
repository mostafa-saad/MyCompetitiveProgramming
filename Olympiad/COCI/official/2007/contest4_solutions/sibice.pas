
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 4 - Task SIBICE
  Programming language Pascal
*)

program sibice;

var i, j, n, w, h: integer;

begin
    readln( n, w, h );
    for i := 1 to n do begin
        readln( j );
        if( j*j <= w*w + h*h ) then writeln( 'DA' )
        else writeln( 'NE' );
    end;
end.
