(* Przykladowa biblioteka interaktywna do zadania Gdzie jest jedynka? *)

unit pgdzlib;

interface
function inicjuj : LongInt;
function f(i, j, d : LongInt) : LongInt;
function g(i, j : LongInt) : LongInt;
procedure odpowiedz(k : LongInt);

implementation

var
czy_zainicjalizowana, n, licznik_f, licznik_g : LongInt;
p : array[1..500000] of LongInt;

function inicjuj : LongInt;
var i : LongInt;
begin
  Assert(czy_zainicjalizowana = 0);
  Read(n);
  for i := 1 to n do
    Read(p[i]);
  licznik_f := 0;
  licznik_g := 0;
  czy_zainicjalizowana := 1;
  
  inicjuj := n;
end;

function f(i, j, d : LongInt) : LongInt;
begin
  Assert(czy_zainicjalizowana = 1);
  Assert((1 <= i) and (i <= n));
  Assert((1 <= j) and (j <= n));
  Assert(d > 0);

  licznik_f := licznik_f + 1;
  if ((p[i] - p[j]) mod d) = 0 then
    f := 1
  else
    f := 0;
end;

function g(i, j : LongInt) : LongInt;
begin
  Assert(czy_zainicjalizowana = 1);
  Assert((1 <= i) and (i <= n));
  Assert((1 <= j) and (j <= n));

  licznik_g := licznik_g + 1;
  if p[i] > p[j] then
    g := 1
  else
    g := 0;
end;

procedure odpowiedz(k : LongInt);
begin
  Assert(czy_zainicjalizowana = 1);
  Assert((1 <= k) and (k <= n));
  if p[k] = 1 then
    WriteLn('OK.')
  else
    WriteLn('ZLA ODPOWIEDZ.');
  WriteLn('Funkcje g wywolano ', licznik_g, ' razy.');
  Halt(0);
end;

end.
