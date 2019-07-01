(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Hurtownia                                        *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie powolne: programowanie dynamiczne    *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000; { dla wiecej pamieci nie starczy }

function max(x, y : Int64) : Int64;
begin
  if x > y then max := x
  else max := y;
end;

var
  a, b : array[1 .. MAXN] of Int64;
  t : array[1 .. MAXN, 0 .. MAXN] of Int64;
  skad : array[1 .. MAXN, 1 .. MAXN] of Boolean;
  n, i, j, wynik : LongInt;
  kto : array[1 .. MAXN] of LongInt;
  size_kto : LongInt;

begin
  ReadLn(n);
  for i := 1 to n do Read(a[i]);
  for i := 1 to n do Read(b[i]);

  t[1, 0] := a[1];
  for i := 2 to n do
    t[i, 0] := t[i - 1, 0] + a[i];
  if a[1] >= b[1] then
    t[1, 1] := a[1] - b[1]
  else
    t[1, 1] := Int64(-1000000000)*1000000000;
  skad[1, 1] := true;
  for i := 2 to n do
    t[1, i] := Int64(-1000000000)*1000000000;

  for i := 2 to n do
    for j := 1 to n do
      if t[i - 1, j - 1] + a[i] >= b[i] then begin
        if t[i - 1, j] + a[i] < t[i - 1, j - 1] + a[i] - b[i] then
          skad[i, j] := true;
        t[i, j] := max(t[i - 1, j] + a[i], t[i - 1, j - 1] + a[i] - b[i]);
      end else begin
        t[i, j] := t[i - 1, j] + a[i];
      end;

  wynik := -1;
  for i := 0 to n do
    if t[n, i] >= 0 then
      wynik := i;

  size_kto := 0;
  i := n; j := wynik;
  while j > 0 do begin
    if skad[i, j] then begin
      Inc(size_kto);
      kto[size_kto] := i;
      Dec(j);
    end;
    Dec(i);
  end;
  WriteLn(size_kto);
  for i := size_kto downto 1 do Write(kto[i], ' ');
  WriteLn;
end.
