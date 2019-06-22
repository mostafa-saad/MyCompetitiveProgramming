(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TAN (Tance w kolkach)                          *
 *   Plik:                tan1.pas                                       *
 *   Autor:               Marcin Michalski                               *
 *   Opis:                Rozwiazanie wzorcowe.                          *
 *                                                                       *
 *************************************************************************)

const F1 = 5;
const F2 = 401;
const MAXN = F2;

var
  comb : array [0..F1-1, 0..F2-1] of longint;

  N,K,L : longint;
  wyniki : array [0..1, 0..MAXN] of longint;
  s : longint;
  mn : array [0..MAXN-1] of longint;

function calcul(MODP, N, K : longint) : longint;
var ni, ki, a : longint;
begin
  if (N>MAXN) or ((int64(K))*L>N) then
  begin
    calcul := 0;
    exit;
  end;
  for ni := L to N do
  begin
    mn[ni] := 1;
    for a := ni-L+1 to ni-1 do
      mn[ni] := (mn[ni]*a) mod MODP;
  end;
  for ni := 0 to N do
    wyniki[s][ni] := 0;
  wyniki[s][0] := 1;
  for ki := 1 to K do
  begin
    s := 1-s;
    for ni := 0 to ki*L-1 do
      wyniki[s][ni] := 0;
    for ni := ki*L to N do
      wyniki[s][ni] := ((ni-1)*wyniki[s][ni-1]+mn[ni]*wyniki[1-s][ni-L]) mod MODP;
  end;
  calcul := wyniki[s][N];
end;

function calc(MODP : longint) : longint;
var cp, nK, res : longint;
begin
  cp := N div MODP;
  nK := K-cp;
  if (nK<0) or (MODP<L) then begin
    calc := 0;
    exit;
  end;
  res := calcul(MODP, N mod MODP, nK);
  if (cp and 1)>0 then {cp jest nieparzyste}
    res := (res*(MODP-1)) mod MODP;
  calc := res;
end;

var a : longint;
begin
  s := 0;
  for a := 0 to F1*F2-1 do
    comb[a mod F1, a mod F2] := a;
  read(N, K, L);
  writeln(comb[calc(F1)][calc(F2)]);
end.
