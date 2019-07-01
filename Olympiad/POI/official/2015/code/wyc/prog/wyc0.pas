(******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Wycieczki                                          *
 *   Zlozonosc czasowa:    O(n^3 * log k)                                     *
 *   Autor programu:       Marcin Andrychowicz                                *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************)


{*********************** operacje na macierzach ***********************}

const INF = 1600000000001000000;
const MAX_SIZE = 3*40;
type Matrix = array[0..MAX_SIZE,0..MAX_SIZE] of Int64;
var
	N,M,i,j,k,q,u,v,c,ind,SIZE : Longint;
	KK,res : Int64;
	pow : array[0..65] of Matrix;
	nei : Matrix;
	pot : array[0..65] of Int64;

function mnoz64(a, b : Int64) : Int64;
begin
	if a = 0 then
		mnoz64 := 0
	else
	begin
		mnoz64 := 0;
		if b > INF div a then
			mnoz64 := INF
		else
			mnoz64 := a*b;
	end
end;

function min(a, b : Int64) : Int64;
begin
	if a < b then
		min := a
	else
		min := b;
end;

function mnoz(A, B : Matrix) : Matrix;
begin
	for i := 0 to SIZE do
		for j := 0 to SIZE do
			mnoz[i][j] := 0;	
	for j := 0 to SIZE do
		for i := 0 to SIZE do
			for k := 0 to SIZE do
				mnoz[i][k] := min(INF, mnoz[i][k] + mnoz64(A[i][j], B[j][k]));
end;

{********************** reszta rozwiazania ***************************}

function count_paths(m : Matrix) : Int64;
begin
	count_paths := 0;
	for i := 0 to N-1 do
		count_paths := min(INF, count_paths + m[3*N][3*i]);
end;


begin
	pot[0] := 1;
	for i := 1 to 62 do
		pot[i] := 2 * pot[i-1];
	{ przygotowanie macierzy sasiedztwa }
	Read(N);
	Read(M);
	Read(KK);
	SIZE := 3*N;
	nei[3*N][3*N] := 1;
	for i := 0 to N-1 do
	begin
		nei[3*N][3*i] := 1;
		nei[3*i][3*i+1] := 1;
		nei[3*i+1][3*i+2] := 1;
	end;
	for i := 0 to M-1 do
	begin
		Read(u);
		Read(v);
		Read(c);
		Dec(u);
		Dec(v);
		Inc(nei[3*u+c-1][3*v]);
	end;
	{ rozwiazanie }
	KK := KK + N;
	pow[0] := nei;
	ind := 0;
	while ((pot[ind] <= KK + KK / 2 +7) and (count_paths(pow[ind]) < KK)) do
	begin
		pow[ind + 1] := mnoz(pow[ind], pow[ind]);
		Inc(ind);
	end;
	res := 0;
	if(count_paths(pow[ind]) >= KK) then
	begin
		for q := ind downto 0 do
			if count_paths(mnoz(nei, pow[q])) < KK then
			begin
				nei := mnoz(nei, pow[q]);
				res := res + pot[q];
			end;
		Inc(res);
	end
	else
		res := -1;
	{ wypisanie wyniku }
	Writeln(res);
end.
