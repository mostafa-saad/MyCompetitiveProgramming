(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Prefiksufiks                                     *
 *   Autor:             Jakub Radoszewski                                *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************)

const
  MAX_N = 1000000;
  INFTY = 100000000;

var
  R : array[1 .. MAX_N + 2] of LongInt;
  n : LongInt;
  napis, przeplot : AnsiString;

{ najblizszy[i] = najblizsza kolejna pozycja, na ktorej konczy sie palindrom
  bedacy prefiksem. }
  najblizszy : array[0 .. MAX_N + 1] of LongInt;

function min(a, b : LongInt) : LongInt;
begin
  if a < b then min := a
  else min := b;
end;

function max(a, b : LongInt) : LongInt;
begin
  if a > b then max := a
  else max := b;
end;


{ Promienie palindromow parzystych w czasie O(n).
  R[i] - promien palindromu o srodku miedzy i a (i+1) litera. }
procedure Manacher;
var
  i, j, k : LongInt;
  s : AnsiString;
begin
  s := '$' + przeplot + '#';
  R[1] := 0;
  i := 2; j := 0;
  while (i <= Length(s)) do
  begin
    while s[i - j] = s[i + j + 1] do Inc(j);
    R[i] := j;
    k := 1;
    while (R[i - k] <> R[i] - k) and (k <= j) do
    begin
      R[i + k] := min(R[i - k], R[i] - k);
      Inc(k);
    end;
    j := max(j - k, 0);
    Inc(i, k);
  end;
  for i := 2 to Length(s) do R[i - 1] := R[i];
end;

procedure oblicz_najblizszy;
var
  i : LongInt;
begin
  najblizszy[0] := 0;
  for i := 1 to n + 1 do
    najblizszy[i] := INFTY;
  for i := 1 to n do
    if R[i] = i then
      najblizszy[2 * i] := 2 * i;
  for i := n downto 1 do
    najblizszy[i] := min(najblizszy[i], najblizszy[i + 1]);
end;

var
  i, wynik, pierwszy_palindrom : LongInt;

begin
  ReadLn(n);
  ReadLn(napis);
  przeplot := '';
  for i := 1 to n div 2 do
  begin
    przeplot := przeplot + napis[i];
    przeplot := przeplot + napis[n + 1 - i];
  end;
  n := Length(przeplot);

  Manacher;

  oblicz_najblizszy;

  { Oblicza wynik jako sklejenie dwoch palindromow w przeplocie;
    potencjalnie jeden z palindromow moze byc pusty.}
  wynik := 0;
  for i := 1 to n do
  begin
    pierwszy_palindrom := najblizszy[i - R[i]];
    if pierwszy_palindrom <= i then
      wynik := max(wynik, 2 * i - pierwszy_palindrom);
  end;
  WriteLn(wynik div 2);
end.
