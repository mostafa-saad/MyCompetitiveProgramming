program ograda;

var
	i, n, x : longint;
	Q_poc, Q_kr, minQ_poc, minQ_kr, maxQ_poc, maxQ_kr : longint;
	vis, h, Q, minQ, maxQ : array[ 1..1000005 ] of longint;
	rez, kor, last : int64;

procedure Push( a : longint );
begin
	Q[ Q_kr ] := a; inc( Q_kr );
	
	while ( minQ_kr > minQ_poc ) and ( minQ[ minQ_kr - 1 ] > a ) do dec( minQ_kr );
	while ( maxQ_kr > maxQ_poc ) and ( maxQ[ maxQ_kr - 1 ] < a ) do dec( maxQ_kr );
	
	minQ[ minQ_kr ] := a; inc( minQ_kr );
	maxQ[ maxQ_kr ] := a; inc( maxQ_kr );
end;

procedure Pop();
begin
	if minQ[ minQ_poc ] = Q[ Q_poc ] then inc( minQ_poc );
	if maxQ[ maxQ_poc ] = Q[ Q_poc ] then inc( maxQ_poc );
	inc( Q_poc );
end;

function GetMin() : longint;
begin
	GetMin := minQ[ minQ_poc ];
end;

function GetMax() : longint;
begin
	GetMax := maxQ[ maxQ_poc ];
end;

procedure Reset();
begin
	Q_poc := 1; Q_kr := 1;
	minQ_poc := 1; minQ_kr := 1;
	maxQ_poc := 1; maxQ_kr := 1;
end;

begin
	rez := 0; kor := 1;
	last := 1; Reset();
	
	read( n, x );
	for i := 1 to n do
		read( vis[ i ] );
	
	for i := n downto n-x+2 do begin
		Push( vis[ i ] );
		h[ i ] := 0;
	end;
	
	for i := n-x+1 downto 1 do begin
		Push( vis[ i ] );
		h[ i ] := GetMin();
		Pop();
	end;
	
	vis[ n+1 ] := 0; h[ n+1 ] := 0;
	for i := 1 to n-x+1 do
		if ( last+x <= i ) or ( h[ i ] > h[ last ] ) or ( vis[ i+x ] < h[ i ] ) then begin
			last := i; inc( kor );
		end;
	
	Reset();
	for i := 1 to n do begin
		if i <= n-x+1 then Push( h[ i ] );
		if i > x then Pop();
		
		rez := rez + vis[ i ] - GetMax();
	end;
	
	writeln( rez );
	writeln( kor );
end.
