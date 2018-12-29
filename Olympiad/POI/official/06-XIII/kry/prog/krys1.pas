(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KRY (Kryszta³)                                 *
 *   Plik:                krys1.pas                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        Algorytm brutalny.                             *
 *                                                                       *
 *************************************************************************)

const MAX_N = 50;

var
  n, i : Integer;
  a, t : array[0..MAX_N - 1] of LongWord;
  wynik : QWord;

procedure sprawdz;
var
  i : Integer;
  w : LongWord;
begin
  w := 0;
  for i := 0 to n - 1 do
    w := w xor t[i];
  if w = 0 then
    Inc(wynik)
end; (* sprawdz *)

procedure brutalny(poz : Integer);
var
  i : LongWord;
begin
  if poz = n then
    sprawdz
  else
  for i := 0 to a[poz] do
  begin
    t[poz] := i;
    brutalny(poz + 1)
  end (* for *)
end; (* brutalny *)

procedure pisz(x : QWord);
var
  s : String;
  i : Integer;
begin
  s := '';
  while x > QWord(0) do
  begin
    s := s + Chr(Byte(x mod QWord(10)) + Ord('0'));
    x := x div QWord(10)
  end; (* while *)
  for i := length(s) downto 1 do
    Write(s[i]);
  WriteLn
end; (* pisz *)

begin
  ReadLn(n);
  for i := 0 to n - 1 do
    Read(a[i]);
  wynik := 0;
  brutalny(0);
  pisz(wynik - 1)
end. (* program *)
