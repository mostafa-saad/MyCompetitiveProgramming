(******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kolekcjoner Bajtemonow                             *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Zlozonosc pamieciowa: O(sqrt(A))                                         *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************)

program kol5;

uses pkollib;

const
	SQRT = 1 shl 16;

type
	pair = record
		first, second : Longint;
	end;

var
	low, high : array[0 .. SQRT - 1] of Longint;
	candidates : array[0 .. 1] of pair;

procedure add(value : Longint);
var
	i : Longint;
begin
	Inc(low[value mod SQRT]);
	Inc(high[value div SQRT]);

	for i := 0 to 1 do
	begin
		if (candidates[i].first = 0) or (candidates[i].first = value) then
		begin
			candidates[i].first := value;
			Inc(candidates[i].second);
			Exit;
		end;
	end;
end;

procedure main;
var
	value, rep, result, i : LongInt;
begin
	value := karta;
	while value <> 0 do
	begin
		add(value);
		value := karta;
	end;

	rep := candidates[0].second;
	if candidates[1].second > rep then
		rep := candidates[1].second;

	result := 0;

	for i := 0 to SQRT - 1 do
	begin
		if (low[i] mod rep) <> 0 then
			result := result + i;
		if (high[i] mod rep) <> 0 then
			result := result + i * SQRT;
	end;

	if candidates[1].first = 0 then
		result := candidates[0].first;

	odpowiedz(result);
end;

begin
	main
end.
