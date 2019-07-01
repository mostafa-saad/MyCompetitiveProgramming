(******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Tablice kierunkowe                                 *
 *   Zlozonosc czasowa:    O(fn^2m/b), f - liczba losowan, b - dl. slowa      *
 *   Zlozonosc pamieciowa: O(nm)                                              *
 *   Autor programu:       Marek Sokolowski                                   *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************)



program Tab3;



type
	Mask = object
		Data: array[0..3] of QWord;
		procedure ClearAll;
		procedure SetOn(P: LongInt);
	end;
	
procedure Mask.ClearAll;
begin
	Data[0] := 0; Data[1] := 0; Data[2] := 0; Data[3] := 0;
end;

procedure Mask.SetOn(P: LongInt);
begin
	Data[P shr 6] := Data[P shr 6] or (QWord(1) shl (P and 63));
end;

function IsSubset(LHS, RHS: Mask): Boolean;
var I: Integer;
begin
	for I := 0 to 3 do
		if (LHS.Data[I] and RHS.Data[I]) <> LHS.Data[I] then
		begin
			IsSubset := False;
			Exit;
		end;
	IsSubset := True;
end;

operator<(LHS, RHS: Mask) b : Boolean;
var I: LongInt;
begin
	for I := 3 downto 0 do
		if LHS.Data[I] <> RHS.Data[I] then
		begin
			b := (LHS.Data[I] < RHS.Data[I]);
			Exit;
		end;

	b := False;
end;

operator=(LHS, RHS: Mask) b : Boolean;
var I: LongInt;
begin
	b := False;
	for I := 0 to 3 do
		if LHS.Data[I] <> RHS.Data[I] then Exit;
	b := True;
end;

function MaskCopy(LHS: Mask): Mask;
begin
	MaskCopy := LHS;  (* Ugly hack *)
end;


const
	NumRandom: Longint = 30;
{	MaxN:      Longint = 1000;
	MaxM:      LongInt = 200;}
	Infty:     LongInt = 1010101010;


var
	(* Kocham ten jezyk. Nie mozna oczywiscie bylo podac
	 * array[0..MaxN-1, 0..MaxM-1] of Longint; na taka konstrukcje
	 * jestem za glupi albo ja, albo Pascal. *)
	Plates, StartPlates:  array[0..999, 0..199] of LongInt;
	N, M:                 LongInt;


{ wczytywanie danych do wektora tabliczek }
procedure InputPlates;
var I, J: LongInt;
begin
	Readln(N, M);
	for I := 0 to N-1 do
	begin
		for J := 0 to M-1 do
		begin
			Read(Plates[I, J]);
			StartPlates[I, J] := Plates[I, J];
		end;
	end;
end;


{ normalizacja tabliczek wzgledem danej }
procedure NormalizePlates(NumPlate: LongInt);
var
	I, J, Smallest: LongInt;
	CurPlate:       array[0..199] of LongInt;
begin
	for J := 0 to M-1 do
		CurPlate[J] := Plates[NumPlate, J];
	
	for I := 0 to N-1 do
	begin
		Smallest := Infty;

		for J := 0 to M-1 do
		begin
			Plates[I, J] := Plates[I, J] - CurPlate[J];
			if Plates[I, J] < Smallest then
				Smallest := Plates[I, J];
		end;

		for J := 0 to M-1 do
			Plates[I, J] := Plates[I, J] - Smallest;
	end;
end;


var
	PlateMask:                     array[0..999] of Mask;
	AcceptablePlates, FoundPlates: array[0..999] of LongInt;
	NumPlates,        NumFound:    LongInt;
	DP, Origin:                    array[0..999] of LongInt;


type Comparator = function(LHS, RHS: LongInt): Boolean;

{ Wykorzystamy wbudowana procedure sortujaca... oh, wait. }
procedure Sort(var Data: array of LongInt;
               Left:     LongInt;
			   Right:    LongInt;
			   Compare:  Comparator);
var
	Mid, I:           LongInt;
	LPtr, RPtr, MPtr: LongInt;
	Merged:           array of LongInt;
	TakeLeft:         Boolean;
begin
	if Left = Right then
		Exit;

	Mid := (Left+Right) div 2;

	Sort(Data, Left, Mid, Compare);
	Sort(Data, Mid+1, Right, Compare);

	SetLength(Merged, Right-Left+1);

	LPtr := Left;
	RPtr := Mid+1;
	MPtr := 0;

	while (LPtr <= Mid) or (RPtr <= Right) do
	begin
		TakeLeft := False;
		if RPtr = Right+1 then
			TakeLeft := True;
		if (LPtr <= Mid) and (RPtr <= Right) and (Compare(Data[LPtr], Data[RPtr])) then
			TakeLeft := True;

		if TakeLeft then
		begin
			Merged[MPtr] := Data[LPtr];
			Inc(MPtr); Inc(LPtr);
		end else begin
			Merged[MPtr] := Data[RPtr];
			Inc(MPtr); Inc(RPtr);
		end;
	end;

	for I := MPtr-1 downto 0 do
		Data[Left+I] := Merged[I];

	Merged := Nil;
end;


{ funkcja porownujaca najpierw maski, potem numery }
function CompMaskNum(LHS, RHS: LongInt): Boolean;
begin
	if PlateMask[LHS] = PlateMask[RHS] then
		CompMaskNum := (LHS < RHS)
	else
		CompMaskNum := (PlateMask[LHS] < PlateMask[RHS]);
end;

{ przetwarza dane przy zalozeniu, ze selectedPlates tam jest,
  do "foundPlates" wrzuca najlepszy zbior tabliczek }
procedure ProcessData(SelectedPlate: LongInt);
var
	PlateNo, I, Prev:  LongInt;
	BestEnd:           LongInt;
	IsOkay:            Boolean;
	CurMask, PrevMask: Mask;
begin
	NormalizePlates(SelectedPlate);
	NumPlates := 0;

	{ uzyskajmy zbior tabliczek, ktorych znormalizowane odleglosci wynosza
	  jedynie 0 lub 1 }

	for PlateNo := 0 to N-1 do
	begin
		IsOkay := True;
		CurMask.ClearAll;
		for I := 0 to M-1 do
		begin
			if (Plates[PlateNo, I] <> 0) and (Plates[PlateNo, I] <> 1) then
			begin
				IsOkay := False;
				Break;
			end else begin
				if Plates[PlateNo, I] = 1 then
					CurMask.SetOn(M-I-1);
			end;
		end;

		if IsOkay then
		begin
			AcceptablePlates[NumPlates] := PlateNo;
			PlateMask[PlateNo] := CurMask;
			Inc(NumPlates);
		end;
	end;

	{ sortujemy te tabliczki rosnaco - wpierw po masce, potem po numerze }
	Sort(AcceptablePlates, 0, NumPlates-1, @CompMaskNum);

	{ programowanie dynamiczne - najdluzsza sciezka w DAG-u z porzadkiem
	  zawierania masek (w razie rownosci i tak dziala, bo mamy porzadek
	  na numerach tabliczek) }
	
	for PlateNo := 0 to NumPlates - 1 do
	begin
		DP[PlateNo]     := 1;
		Origin[PlateNo] := -1;
		CurMask         := PlateMask[AcceptablePlates[PlateNo]];

		for Prev := 0 to PlateNo - 1 do
		begin
			PrevMask := PlateMask[AcceptablePlates[Prev]];

			if IsSubset(PrevMask, CurMask) then
				if DP[Prev]+1 > DP[PlateNo] then
				begin
					DP[PlateNo]     := DP[Prev]+1;
					Origin[PlateNo] := Prev;
				end;
		end;
	end;

	{ gdzie jest najlepszy koniec? }
	BestEnd := 0;
	for PlateNo := 1 to NumPlates-1 do
		if DP[PlateNo] > DP[BestEnd] then
			BestEnd := PlateNo;

	{ odtwarzamy wynik od konca }
	NumFound := DP[BestEnd];
	while BestEnd <> -1 do
	begin
		FoundPlates[DP[BestEnd]-1] := AcceptablePlates[BestEnd];
		BestEnd := Origin[BestEnd];
	end;

	for I := 0 to NumPlates-1 do
		PlateMask[AcceptablePlates[I]].ClearAll;
end;


{ znowu? }
Function CompSumDist(LHS, RHS: LongInt): Boolean;
var SumLeft, SumRight, I: LongInt;
begin
	SumLeft  := 0;
	SumRight := 0;
	for I := 0 to M-1 do
	begin
		SumLeft  := SumLeft  + StartPlates[LHS][I];
		SumRight := SumRight + StartPlates[RHS][I];
	end;
	CompSumDist := (SumLeft > SumRight);
end;



var
	CurBest:           array[0..999] of LongInt;
	CurSize, Tries, I: LongInt;


begin
	InputPlates;

	{ ziarno generatora }
	RandSeed := 51298471;
	CurSize  := 0;

	{ probujemy }
	for Tries := 0 to NumRandom-1 do
	begin
		ProcessData(Random(N));

		If NumFound > CurSize then
		begin
			CurSize := NumFound;
			for I := 0 to CurSize-1 do
				CurBest[I] := FoundPlates[i];
		end;
	end;

	{ sortujemy po sumie odleglosci }
	Sort(CurBest, 0, CurSize-1, @CompSumDist);

	{ wypisujemy }
	Writeln(CurSize);

	for I := 0 to CurSize-1 do
		Write(CurBest[i]+1, ' ');
	Writeln;
end.


