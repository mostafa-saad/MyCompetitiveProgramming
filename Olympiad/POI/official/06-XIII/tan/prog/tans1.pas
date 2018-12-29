(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TAN (Tance w kolkach)                          *
 *   Plik:                tans1.pas                                      *
 *   Autor:               Pawe³ Parys                                    *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                                                                       *
 *************************************************************************)

const MOD_ = 2005;
const MAXN : longint = 2500000;

var
  N, K, L, s : longint;
  wyniki : array[0..1, 0..2500000] of longint;
  mn : array[0..2500000-1] of longint;

function calcul : longint;
var n2, a : longint;
begin
  if K*L>N then begin
    calcul := 0;
    exit;
  end;
  if N>MAXN then while true do;
  for n2 := L to N do
  begin
    mn[n2] := 1;
    for a := n2-L+1 to n2-1 do
      mn[n2] := mn[n2]*a mod MOD_;
  end;
  for n2 := 0 to N do
    wyniki[s][n2] := 0;
  wyniki[s][0] := 1;
  for k := 1 to K do
  begin
    s := 1-s;
    for n2 := 0 to k*L-1 do
      wyniki[s][n2] := 0;
    for n2 := k*L to N do
      wyniki[s][n2] := ((n2-1)*wyniki[s][n2-1]+mn[n2]*wyniki[1-s][n2-L]) mod MOD_;
  end;
  calcul := wyniki[s][N];
end;

begin
  s := 0;
  read(N, K, L);
  writeln(calcul);
end.
