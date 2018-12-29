(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Prefiksufiks                                     *
 *   Autor:             Jakub Radoszewski                                *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie powolne: sprawdzanie rownowaznosci   *
 *                      cyklicznej slow za pomoca KMP                    *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000005;

var
  p : array[1 .. MAXN] of LongInt;
  n : LongInt;
  t, t1 : AnsiString;


{ KMP z funkcja prefiksowa. }

{ Funkcja prefiksowa dla slowa t1[1..a]. }
procedure prefiksowa(a : LongInt);
var
  i, j : LongInt;
begin
  j := 0;
  p[1] := 0;
  for i := 2 to a do
  begin
    while (j > 0) and (t1[j + 1] <> t1[i]) do
      j := p[j];
    if t[j + 1] = t[i] then
      Inc(j);
    p[i] := j;
  end;
end;

{ Wyszukuje wzorzec t1[1..a] w tekscie t1[n - a + 1..n + a] }
function kmp(a : LongInt) : Boolean;
var
  i, j : LongInt;
begin
  prefiksowa(a);
  j := 0;
  kmp := false;
  for i := 1 to 2 * a do
  begin
    while (j > 0) and (t1[j + 1] <> t1[i + n - a]) do
      j := p[j];
    if t1[j + 1] = t1[i + n - a] then
      Inc(j);
    if j = a then
    begin
      kmp := true;
      Break;
    end;
  end;
end;

function cycEq(len : LongInt) : Boolean;
var
  i : LongInt;
begin
  t1 := t;
  for i := n - len + 1 to n do
    t1 := t1 + t[i];
  cycEq := kmp(len);
end;

var
  i : LongInt;
  czy : Boolean;

begin
  ReadLn(n);
  ReadLn(t);
  czy := false;
  for i := n div 2 downto 1 do
    if cycEq(i) then
    begin
      WriteLn(i);
      czy := true;
      Break;
    end;
  if not czy then
    WriteLn(0);
end.
