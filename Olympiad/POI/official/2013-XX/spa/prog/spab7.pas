(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Spacer                                        *
 *   Autor:                Wiktor Kuropatwa                              *
 *   Zlozonosc czasowa:    O(2^n)                                        *
 *   Zlozonosc pamieciowa: O(2^n)                                        *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Probuje przeszukac caly graf.                 *
 *                                                                       *
 *************************************************************************)

const
	GSIZE = 8388608;
	
var
	visited: array[0..GSIZE] of boolean;
	forbidden: array[0..GSIZE] of boolean;
	queue: array[0..GSIZE] of LongInt;
	n,k,i,a,x,y,j: LongInt;
	
function bfs(s: LongInt; t: LongInt): boolean;
var
	v,e,b,next: LongInt;
begin
	queue[0] := s;
	visited[s] := true;
	b := 0;
	e := 1;
	while b <> e do begin
		v := queue[b];
		b := b+1;
		for i := 0 to (n-1) do begin
			next := v xor (1 shl i);
			if((not visited[next]) and (not forbidden[next])) then begin
				visited[next] := true;
				queue[e] := next;
				e := e+1;
			end;
		end;
	end;
	bfs := visited[t];
end;

procedure readXY();
var
	buf: string;
	t: LongInt;
begin
	readln(buf);
	t := 0;
	for i:=1 to n do begin
		if buf[i] = '1' then t := t + (1 shl (n-i));
	end;
	x := t;
	t := 0;
	for i:=1 to n do begin
		if buf[n+i+1] = '1' then t := t + (1 shl (n-i));
	end;
	y := t;
end;

function readBinary(): LongInt;
var
	buf: string;
	res: LongInt;
begin
	readln(buf);
	res := 0;
	for j:= 1 to n do begin
		if buf[j] = '1' then begin
			res := res + (1 shl (n-j));
		end;
	end;
	readBinary := res;
end;

procedure input();
begin
	read(n);
	for i:=0 to ((1 shl n) - 1) do begin
		visited[i] := false;
		forbidden[i] := false;
	end;
	readln(k);
	readXY();
	for i:=1 to k do begin
		a := readBinary();
		forbidden[a] := true;
	end;
end;

begin
	input();
	if bfs(x,y) then writeln('TAK') else writeln('NIE');
end.
