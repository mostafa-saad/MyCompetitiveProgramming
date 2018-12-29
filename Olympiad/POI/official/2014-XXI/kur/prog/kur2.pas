(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Kurierzy                                      *
 *   Autor:                Karol Pokorski                                *
 *   Zlozonosc czasowa:    O((n+m) log n)                                *
 *   Zlozonosc pamieciowa: O(n+m)                                        *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************)

const
	MAXN = 524288;

type Pair = record
	first, second: longint;
end;

var
	t, qcand, res, curSum: array[0..MAXN-1] of longint;
	eq, cand, hand, tmp: array[0..2*MAXN-1] of longint;
	q: array[0..MAXN-1, 0..1] of longint;
	n, m, posX, i: longint;
	mergeRes: Pair;

function MakePair(x, y: longint): Pair;
begin
	MakePair.first := x;
	MakePair.second := y;
end;

function CmpEQ(a, b: longint): boolean;
var
	qa, qb: longint;
begin
	qa := q[a div 2][a mod 2]; qb := q[b div 2][b mod 2];
	if (qa <> qb) then CmpEQ := (qa < qb)
	else if ((a mod 2) <> (b mod 2)) then CmpEQ := ((a mod 2) < (b mod 2))
	else CmpEQ := (a < b);
end;

procedure SwapPair(var a, b: Pair);
var
	tmp: Pair;
begin
	tmp := a;
	a := b;
	b := tmp;
end;

function MergeLead(a, b: Pair): Pair;
begin
	if (a.first = b.first) then MergeLead := MakePair(a.first, a.second+b.second)
	else
	begin
		if (a.second < b.second) then SwapPair(a, b);
		MergeLead := MakePair(a.first, a.second-b.second);
	end;
end;

function GetCand(fromX, toX: longint): longint;
var
	curRes: Pair;
begin
	curRes := MakePair(-1, 0);
	inc(fromX, MAXN); inc(toX, MAXN);
	curRes := MergeLead(curRes, MakePair(cand[fromX], hand[fromX]));
	if (fromX <> toX) then curRes := MergeLead(curRes, MakePair(cand[toX], hand[toX]));

	while ((fromX div 2) <> (toX div 2)) do
	begin
		if (fromX mod 2 = 0) then curRes := MergeLead(curRes, MakePair(cand[fromX+1], hand[fromX+1]));
		if (toX mod 2 = 1) then curRes := MergeLead(curRes, MakePair(cand[toX-1], hand[toX-1]));
		fromX := fromX div 2; toX := toX div 2;
	end;

	GetCand := curRes.first;
end;

procedure Merge(start, center, stop: longint);
var
	posLeft, posRight, posTmp: longint;
begin
	posLeft := start;
	posRight := center+1;
	posTmp := posLeft;

	while ((posLeft <= center) and (posRight <= stop)) do
	begin
		if (CmpEQ(eq[posLeft], eq[posRight])) then
		begin
			tmp[posTmp] := eq[posLeft];
			inc(posLeft);
			inc(posTmp);
		end
		else
		begin
			tmp[posTmp] := eq[posRight];
			inc(posRight);
			inc(posTmp);
		end;
	end;
	while (posLeft <= center) do
	begin
		tmp[posTmp] := eq[posLeft];
		inc(posLeft);
		inc(posTmp);
	end;
	while (posRight <= stop) do
	begin
		tmp[posTmp] := eq[posRight];
		inc(posRight);
		inc(posTmp);
	end;

	for posTmp := start to stop do
		eq[posTmp] := tmp[posTmp];
end;

procedure MergeSort(start, stop: longint);
var
	center: longint;
begin
	if (start <> stop) then
	begin
		center := (start+stop) div 2;
		MergeSort(start, center);
		MergeSort(center+1, stop);
		Merge(start, center, stop);
	end;
end;

begin
	posX := 0;

	readln(n, m);
	for i := 0 to n-1 do begin curSum[i] := 0; read(t[i]); dec(t[i]); end;
	readln;
	for i := 0 to m-1 do
	begin
		readln(q[i][0], q[i][1]);
		dec(q[i][0]); dec(q[i][1]);
		eq[2*i] := 2*i; eq[2*i+1] := 2*i+1;
	end;

	MergeSort(0, 2*m-1);

	for i := 0 to MAXN-1 do
	begin
		if (i < n) then begin cand[MAXN+i] := t[i]; hand[MAXN+i] := 1; end
		else begin cand[MAXN+i] := -1; hand[MAXN+i] := 0; end;
		cand[i] := -1; hand[i] := 0;
	end;
	for i := MAXN-1 downto 1 do
	begin
		mergeRes := MergeLead(MakePair(cand[2*i], hand[2*i]), MakePair(cand[2*i+1], hand[2*i+1]));
		cand[i] := mergeRes.first; hand[i] := mergeRes.second;
	end;

	for i := 0 to m-1 do qcand[i] := GetCand(q[i][0], q[i][1]);

	for i := 0 to 2*m-1 do
	begin
		while ((posX < n) and (posX < q[eq[i] div 2][eq[i] mod 2])) do
		begin
			inc(curSum[t[posX]]); inc(posX);
		end;
		if ((eq[i] mod 2 = 1) and (posX = q[eq[i] div 2][eq[i] mod 2])) then
		begin
			inc(curSum[t[posX]]); inc(posX);
		end;
		if (eq[i] mod 2 = 0) then res[eq[i] div 2] := -curSum[qcand[eq[i] div 2]]
		else inc(res[eq[i] div 2], curSum[qcand[eq[i] div 2]]);
	end;

	for i := 0 to m-1 do
	begin
		if (res[i] > (q[i][1]-q[i][0]+1) div 2) then writeln(qcand[i]+1)
		else writeln(0);
	end;
end.
