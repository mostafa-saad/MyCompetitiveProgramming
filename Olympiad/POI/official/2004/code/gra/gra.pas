{*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Gra                                            *
 *   Plik:                gra.pas                                        *
 *   Autor:               Jakub Pawlewicz                                *
 *************************************************************************}

const MAX_GROUPS = 1000000;

var
	group : array[1..MAX_GROUPS] of
		record
			number, size : longint;
		end;
	groups_nr : longint;
	m, n : longint;
	nim_sum : longint;

function WinningMoves : longint;
var
	retval : longint;
	i : longint;
	next_group_size : longint;
	pieces_to_next_group : longint;
begin
	retval := 0;
	for i := 1 to groups_nr do
		if Odd(group[i].number) then
		begin
			if group[i].size xor nim_sum < group[i].size then
				Inc(retval);
		end
		else if group[i].number <> 2 then
		begin
			if (i = groups_nr) or
			   (group[i+1].number < group[i].number - 1) then
				next_group_size := 0
			else
				next_group_size := group[i+1].size;
			pieces_to_next_group := (next_group_size xor nim_sum)
				- next_group_size;
			if (pieces_to_next_group > 0) and
			   (pieces_to_next_group <= group[i].size) then
				Inc(retval);
		end;
	WinningMoves := retval;
end;

procedure Solve;
var
	pieces_left : longint;
	next_piece : longint;
	group_size : longint;
	last_group_piece : longint;
	group_number : longint;
begin
	Read(m, n);
	groups_nr := 0;
	nim_sum := 0;
	pieces_left := n;
	Read(next_piece);
	repeat
		group_size := 0;
		last_group_piece := next_piece;
		while true do
		begin
			Inc(group_size);
			Dec(pieces_left);
			if pieces_left = 0 then
				break;
			Read(next_piece);
			if next_piece > last_group_piece + 1 then
				break;
			last_group_piece := next_piece;
		end;
		Inc(groups_nr);
		group_number := m - last_group_piece - pieces_left;
		group[groups_nr].number := group_number;
		group[groups_nr].size := group_size;
		if Odd(group_number) then
			nim_sum := nim_sum xor group_size;
	until pieces_left = 0;
	
	if next_piece = m - 1 then
		WriteLn(group_size)
	else if nim_sum = 0 then
		WriteLn(0)
	else
		WriteLn(WinningMoves);
end;

begin
	Solve;
end.
