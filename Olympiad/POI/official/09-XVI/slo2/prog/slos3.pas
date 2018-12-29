(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Slowa (SLO)                                               *
 *   Plik:     slos3.pas                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie wykladnicze z uzyciem KMP.                    *
 *                                                                       *
 *************************************************************************)

const MAX_N = 100000;
const MAX_M = 4000000;

var
  p : array[0 .. MAX_M] of LongInt; (* funkcja prefiksowa *)

(* KMP z funkcja prefiksowa *)

(* Funkcja prefiksowa dla slowa a. *)
procedure compute(a : AnsiString; n : LongInt);
var
  i, j : LongInt;
begin
  p[0] := 0; p[1] := 0;
  j := 0;
  for i := 2 to n do
  begin
    while (j > 0) and (a[j + 1] <> a[i]) do
      j := p[j];
    if a[j + 1] = a[i] then
      Inc(j);
    p[i] := j;
  end;
end;

(* KMP - zwraca prawde, jezeli jest wystapienie a w b. *)
function kmp(a, b : AnsiString) : Boolean;
var
  i, j, n, m : LongInt;
begin
  n := Length(a); m := Length(b);
  if n > m then
    kmp := false
  else
  begin
    kmp := false;
    j := 0;
    for i := 1 to m do
    begin
      while (j > 0) and ((j >= n) or (a[j + 1] <> b[i])) do
        j := p[j];
      if a[j + 1] = b[i] then
        Inc(j);
      if j = n then
        kmp := true;
    end;
  end;
end;

var
  k : LongInt;
  n : array[0 .. MAX_N] of LongInt;
  fib : array [0 .. MAX_N] of AnsiString;
  wzorzec : AnsiString;
  ile, mx, i : LongInt;
  wynik : LongInt;
  NIE : Boolean;

begin
  ReadLn(ile);
  while ile > 0 do
  begin
    Dec(ile);
    ReadLn(k);
    mx := 0;
    for i := 0 to k - 1 do
    begin
      Read(n[i]);
      if n[i] > mx then
        mx := n[i];
    end;

    fib[0] := '0';
    fib[1] := '1';
    for i := 2 to mx do
      fib[i] := fib[i - 1] + fib[i - 2];
    wzorzec := '';
    for i := 0 to k - 1 do
      wzorzec := wzorzec + fib[n[i]];

    compute(wzorzec, Length(wzorzec));

    wynik := 0;
    NIE := false;
    while not kmp(wzorzec, fib[wynik]) do
    begin
      Inc(wynik);
      if fib[wynik] = '' then
        fib[wynik] := fib[wynik - 1] + fib[wynik - 2];

      (* zagadka: dlaczego ta stala to akurat 8? :-) *)
      if Length(fib[wynik]) > 8 * Length(wzorzec) then
      begin
        WriteLn('NIE');
        NIE := true;
        Break;
      end;
    end;
    if not NIE then
      WriteLn('TAK');
  end;
end.
