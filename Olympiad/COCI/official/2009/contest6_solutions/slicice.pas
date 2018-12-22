const maxn = 100;
      maxd = 1000;
      maxf = maxn+maxd+2;
      source = 0;
      sink = 1;

type node = record
     who, next: longint;
end;

var
   i, j, n, m, d, memc: longint;
   slicice: array[0..maxn] of longint;
   ducan: array[0..maxd,0..1] of longint;
   dad, flow: array[0..maxf] of longint;
   Cc: array[0..maxf,0..maxf] of longint;
   head: array[0..maxf] of longint;
   mem: array[0..500000] of node;
   Q: array[0..maxf] of longint;
   qh, qt: longint;

function newnode( a, b: longint ):longint; begin
   mem[ memc ].who := a;
   mem[ memc ].next := b;
   newnode := memc;
   inc( memc );
end;

procedure qpush( x: longint ); begin
   Q[ qh ] := x;
   inc( qh );
end;

function qpop:longint; begin
   qpop := Q[ qt ];
   inc( qt );
end;

procedure push_back( a, b: longint );
var tmp: longint;
begin
   tmp := newnode( b, head[a] );
   head[ a ] := tmp;
end;

procedure spoji( a, b, c: longint ); begin
   Cc[a][b] := c;
   push_back( a, b );
   push_back( b, a );
end;

function manji( a, b: longint ):longint; begin
   if a < b then manji := a
   else manji := b;
end;

function aug_flow: boolean;
var curr: longint;
begin
     for i := 0 to maxf-1 do begin dad[i] := -1; flow[i] := 0; end;
     qt := 0;
     qh := 0;

     flow[source] := maxf;
     qpush( source );
     while( qh > qt ) do begin
        curr := qpop;

        if curr = sink then begin aug_flow := true; exit; end;

        j := head[curr];
        while( j <> -1 ) do begin
			if (Cc[ curr ][ mem[j].who ] <> 0) and (dad[ mem[j].who ] = -1 ) then begin
			   dad[ mem[j].who ] := curr;
			   flow[ mem[j].who ] := manji( flow[curr], Cc[ curr ][ mem[j].who ] );
			   qpush( mem[j].who );
            end else j := mem[j].next;
        end;
     end;

     aug_flow := false;
end;

procedure max_flow;
begin
	while aug_flow do begin
       j := sink;
       while j <> source do begin
             Cc[ dad[j] ][ j ] := Cc[ dad[j] ][ j ] - flow[sink];
             Cc[ j ][ dad[j] ] := Cc[ j ][ dad[j] ] + flow[sink];
             j := dad[j];
       end;
    end;
end;

procedure output;
var
   tmp: array[0..1] of longint;
   ntmp: longint;
begin
   writeln( d );
   for i := 0 to m-1 do writeln( ducan[i][0], ' ', ducan[i][1], ' ', Cc[ 1+d+ducan[i][0] ][ 2+i ] );

   for i := m to d-1 do begin
       ntmp := 0;
       for j := 0 to n-1 do
           if Cc[ 2+d+j ][ 2+i ] > 0 then begin
              tmp[ ntmp ] := j+1;
              inc( ntmp );
           end;

       if ntmp = 2 then writeln( tmp[0], ' ', tmp[1], ' 1' )
       else
           if tmp[0] = 1 then writeln( tmp[0], ' 2 2' ) else writeln( tmp[0], ' 1 2' );
   end;
end;

begin
     read( n, m );
     for i := 0 to n-1 do begin
         read( slicice[i] );
         d := d + slicice[i];
     end;
     d := d div 2;

     for i := 0 to m-1 do read( ducan[i][0], ducan[i][1] );
     for i := 0 to maxf do head[i] := -1;
     memc := 0;

     // izgradi graf
     for i := 0 to d-1 do spoji( source, 2+i, 2 );
     for i := 0 to m-1 do begin
		spoji( 2+i, 1+d+ducan[i][0], 2 );
		spoji( 2+i, 1+d+ducan[i][1], 2 );
     end;
     for i := m to d-1 do
         for j := 0 to n-1 do spoji( 2+i, 2+d+j, 2 );
     for i := 0 to n-1 do spoji( 2+d+i, sink, slicice[i] );

     max_flow;
     output;
end.

