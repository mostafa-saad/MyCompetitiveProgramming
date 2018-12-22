program dobra;

const
	br : array[ 1..3 ] of integer = (5, 1, 20);

var
	sluchaj : array[ 0..105 ] of integer;
	rijec : string; dulj: integer;

function samoglasnik( ch : char ) : boolean;
begin
	samoglasnik := ( ch = 'A' ) or ( ch = 'E' ) or ( ch = 'I' ) or ( ch = 'O' ) or ( ch = 'U' );
end;

function uzastop : boolean;
var tip1, tip2, tip3 : boolean; i : integer;
begin
	uzastop := false;
	for i := 1 to dulj-2 do begin
		tip1 := samoglasnik( rijec[ i+0 ] ) or ( sluchaj[ i+0 ] = 1 );
		tip2 := samoglasnik( rijec[ i+1 ] ) or ( sluchaj[ i+1 ] = 1 );
		tip3 := samoglasnik( rijec[ i+2 ] ) or ( sluchaj[ i+2 ] = 1 );
		
		if ( tip1 = tip2 ) and ( tip2 = tip3 ) then begin
			uzastop := true; exit;
		end;
	end;
end;

function konstruiraj( poz : integer; L : boolean ) : int64;
var komb : int64; i : integer;
begin
	if poz > dulj then begin
		if L and not uzastop() then konstruiraj := 1 else konstruiraj := 0;
	end else if ( rijec[ poz ] >= 'A' ) and ( rijec[ poz ] <= 'Z' ) then begin
		konstruiraj := konstruiraj( poz + 1, L or ( rijec[ poz ] = 'L' ) );
	end else begin
		komb := 0;
		for i := 1 to 3 do begin
			sluchaj[ poz ] := i;
			komb := komb + br[ i ] * konstruiraj( poz + 1, L or ( i = 2 ) );
		end;
		
		konstruiraj := komb;
	end;
end;

begin
	read( rijec );
	dulj := Length( rijec );
	
	writeln( konstruiraj( 1, false ) );
end.
