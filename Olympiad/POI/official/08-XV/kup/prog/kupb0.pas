(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kupno gruntu (KUP)                                        *
 *   Plik:     kupb0.pas                                                 *
 *   Autor:    Jakub Pawlewicz                                           *
 *   Opis:     Rozwiazanie niepoeprawne, zlozonosc O(n^2).               *
 *                                                                       *
 *************************************************************************)

const MAXN = 2000;

var
	stack :
	record
		size :	longint;
		list :	array[0..MAXN] of
			record
				x, y : longint;
			end
	end;
	v : array[0..MAXN, 0..MAXN] of longint;

function S(x1, y1, x2, y2 : longint) : longint;
begin
	S := v[x2, y2] - v[x1 - 1, y2] - v[x2, y1 - 1] + v[x1 - 1, y1 - 1];
end;

procedure InitStack;
begin
	stack.size := 0;
end;

procedure StackPush(x, y : longint);
begin
	stack.list[stack.size].x := x;
	stack.list[stack.size].y := y;
	Inc(stack.size);
end;

procedure StackTop(var x, y : longint);
begin
	x := stack.list[stack.size - 1].x;
	y := stack.list[stack.size - 1].y;
end;

procedure StackPop;
begin
	Dec(stack.size);
end;

procedure PrintResult(x1, y1, x2, y2 : longint);
begin
	WriteLn(x1, ' ', y1, ' ', x2, ' ', y2);
end;

procedure Solve;
var
	k, n : longint;
	x, y : longint;
	a, sx : longint;
	rowsum, rowsum_x1 : longint;
	x1, y1, xp, yp : longint;
	min_allowed_y : array[1..MAXN+1] of longint;
begin
	Read(k, n);
	for x := 0 to n do
		v[x, 0] := 0;
	for x := 1 to n + 1 do
		min_allowed_y[x] := 1;
	for y := 1 to n do
	begin
		sx := 0;
		rowsum := 0;
		rowsum_x1 := 1;
		InitStack;
		StackPush(0, y + 1);
		for x := 1 to n + 1 do
		begin
			v[x - 1, y] := sx + v[x - 1, y - 1];
			if x <= n then
				Read(a)
			else
				a := 2 * k + 1;
			Inc(sx, a);
			if a > 2 * k then
			begin
				min_allowed_y[x] := y + 1;
				rowsum := 0;
				rowsum_x1 := x + 1;
			end else if a >= k then
			begin
				PrintResult(x, y, x, y);
				Exit;
			end else
			begin
				Inc(rowsum, a);
				if rowsum >= k then
				begin
					PrintResult(rowsum_x1, y, x, y);
					Exit;
				end;
			end;
			yp := min_allowed_y[x];
			StackTop(x1, y1);
			xp := x;
			while yp > y1 do
			begin
				xp := x1;
				StackPop;
				if S(x1, y1, x - 1, y) >= k then
				begin
					PrintResult(x1, y1, x - 1, y);
					Exit;
				end;
				StackTop(x1, y1);
			end;
			if y1 > yp then
				StackPush(xp, yp);
		end;
	end;
	WriteLn('NIE');
end;

begin
	Solve;
end.
