(******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kolekcjoner Bajtemonow                             *
 *   Zlozonosc czasowa:    O(n log n)                                         *
 *   Zlozonosc pamieciowa: O(n)                                               *
 *   Opis:                 Rozwiazanie pamieciochlonne                        *
 *****************************************************************************)
 
program kols3;

uses pkollib;

type
	vector = record
		size : Longint;
		capacity : Longint;
		data : array of Longint;
	end;

procedure push(var v : vector; elem : Longint);
begin
	if v.size = v.capacity then
	begin
		v.capacity := 2 * v.capacity;
		SetLength(v.data, v.capacity);
	end;

	v.data[v.size] := elem;
	Inc(v.size);
end;

procedure pop(var v : vector);
begin
	Dec(v.size);
end;

procedure init(var v : vector);
begin
	v.size := 0;
	v.capacity := 12;
	SetLength(v.data, v.capacity);
end;

procedure Swap(var x, y : LongInt);
var
	tmp : Longint;
begin
	tmp := x;
	x := y;
	y := tmp;
end;

procedure Sort(var L : vector);
var
	n : LongInt;
	i, idx : LongInt;
	cld : LongInt;
begin
	n := L.size;

	for i := 2 to n do
	begin
		idx := i;
		while (idx <> 1) and (L.data[idx - 1] > L.data[idx div 2 - 1]) do
		begin
			Swap(L.data[idx - 1], L.data[idx div 2 - 1]);
			idx := idx div 2;
		end;
	end;

	for i := n downto 2 do
	begin
		Swap(L.data[i - 1], L.data[1 - 1]);
		idx := 1;
		while 2 * idx <= i - 1 do
		begin
			cld := 2 * idx;
			if (2 * idx + 1 <= i - 1) and (L.data[cld - 1] < L.data[2 * idx + 1 - 1]) then
				Inc(cld);

			if L.data[idx - 1] >= L.data[cld - 1] then Break;

			Swap(L.data[idx - 1], L.data[cld - 1]);
			idx := cld;
		end;
	end;
end;

procedure main;
var
	L : vector;
	nowa_karta, k1, k2, i : Longint;
begin
	init(L);
	
	nowa_karta := karta;
	while nowa_karta <> 0 do
	begin
		push(L, nowa_karta);
		nowa_karta := karta;
	end;

	Sort(L);

	if L.data[0] = L.data[L.size - 1] then
	begin
		odpowiedz(L.data[0]);
		Halt;
	end;

	k1 := 0;
	while L.data[k1] = L.data[0] do Inc(k1);
	k2 := L.size - 1;
	while L.data[k2] = L.data[L.size - 1] do Dec(k2);
	if k1 + k2 < L.size - 1 then
	begin
		odpowiedz(L.data[0]);
		Halt;
	end;
	if k1 + k2 > L.size - 1 then
	begin
		odpowiedz(L.data[L.size - 1]);
		Halt;
	end;
	while L.size > 0 do
	begin
		if L.data[L.size - 1] <> L.data[L.size - k1] then
		begin
			odpowiedz(L.data[L.size-1]);
			Halt;
		end;
		for i := 0 to k1 - 1 do
			pop(L);
	end;

	Assert(false);
end;

begin
	main
end.
