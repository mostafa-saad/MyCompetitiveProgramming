
(*
  Croatian Open Competition in Informatics 2006/2007
  Contest 4 - Task JOGURT
  Programming language Pascal
*)

program jogurt;

const maxt = 32768;

var
    i, n, t: integer;
    sol, depth: array[0..maxt] of integer; (* sol pamti stablo u preorderu, depth pamti dubinu nekog cvora *)

procedure next( d: integer );
var i: integer;
begin
     for i := t downto 1 do begin   (* kopiranje stabla dvaput *)
        sol[i] := sol[i-1]*2;
        sol[t+i] := sol[i-1]*2;
        depth[t+i] := depth[i-1]+1;
        depth[i] := depth[i-1]+1;
     end;
     for i := 1 to t+t do   (* dodavanje jedinice nekim elementima *)
        if( (depth[i] = d) xor (i <= t) ) then inc( sol[i] );
     sol[0] := 1;   (* dodavanje korijena *)
     depth[0] := 0;
     t := t+t+1;    (* stablo je sad dvaput vece *)
end;

begin
    depth[0] := 0; (* inicijalizacija, stablo ima samo jedan element *)
    sol[0] := 1;
    t := 1;

    readln( n );

    for i := 1 to n-1 do next( i );   (* udvostruci stablo n puta *)

    for i := 0 to t-1 do writeln( sol[i] ); (* ispisi rjesenje *)

end.
