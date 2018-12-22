
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 4 - Task PRSTENI
  Programming language Pascal
*)

program prsteni;

function gcd( a, b: integer ):integer;
begin
    if( b = 0 ) then gcd := a
    else gcd := gcd( b, a mod b );
end;

var i, n, first, k: integer;

begin
    read( n, first );
    for i := 1 to n-1 do begin
        read( k );
        writeln( first div gcd( first, k ), '/', k div gcd( first, k ) );
    end;
end.
