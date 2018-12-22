program buka;

var a,b,op: string;
    la, lb: longint;

function min( a, b: longint ):longint; begin
     if a < b then min := a
     else min := b;
end;

function max( a, b: longint ):longint; begin
     if a > b then max := a
     else max := b;
end;

procedure nule( k: longint );
var i: longint;
begin
     for i:=1 to k do write( '0' );
end;

begin
     readln( a );
     readln( op );
     readln( b );

     la := length( a );
     lb := length( b );

     if op = '+' then begin
        if la = lb then begin
           write( '2' );
           nule( la-1 );
        end else begin
             write( '1' );
             nule( max( la, lb ) - min( la, lb ) - 1 );
             write( '1' );
             nule( min( la, lb ) - 1 );
        end;
     end else begin
         write( '1' );
         nule( la+lb-2 );
     end;
     writeln;
end.



