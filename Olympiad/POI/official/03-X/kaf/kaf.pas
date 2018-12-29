(*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi±zanie zadania: Kafelki                                        *
 *   Plik:                kaf.pas                                        *
 *   Autor:               Pawe³ Wolff                                    *
 *************************************************************************)

{$I+,R+}

program Kafelki;

const
  MAX_CYFR = 500;

  PLIK_WE = '';
  PLIK_WY = '';


type
  Liczba = array [1..MAX_CYFR] of shortint;

var
  lCyfr: integer;
  n, k, l: Liczba;
  a, b, k1, l1: Liczba;


procedure Kopiuj(var a, b: Liczba);
var
  i: integer;
begin
  for i := 1 to lCyfr do
    a[i] := b[i];
end;


procedure Dodaj(var a, b: Liczba);
var
  i, c: integer;
begin
  c := 0;
  for i := 1 to lCyfr do begin
    a[i] := a[i] + b[i] + c;
    if a[i] >= 10 then begin
      c := 1;
      a[i] := a[i] - 10;
    end
    else
      c := 0;
  end;
end;


procedure Odejmij(var a, b: Liczba);
var
  i, c: integer;
begin
  c := 0;
  for i := 1 to lCyfr do begin
    a[i] := a[i] - b[i] - c;
    if a[i] < 0 then begin
      c := 1;
      a[i] := a[i] + 10;
    end
    else
      c := 0;
  end;
end;


procedure Razy2(var a: Liczba);
var
  i, c: integer;
begin
  c := 0;
  for i := 1 to lCyfr do begin
    a[i] := 2 * a[i] + c;
    if a[i] >= 10 then begin
      c := 1;
      a[i] := a[i] - 10;
    end
    else
      c := 0;
  end;
end;


procedure DzielPrzez2(var a: Liczba);
var
  i, c: integer;
begin
  c := 0;
  for i := lCyfr downto 1 do begin
    a[i] := a[i] + 10 * c;
    c := a[i] mod 2;
    a[i] := a[i] div 2;
  end;
end;


function Porownaj(var a, b: Liczba): integer;
var
  i: integer;
begin
  i := lCyfr;
  while (i > 0) and (a[i] = b[i]) do
    Dec(i);

  if i = 0 then
    Porownaj := 0
  else
    if a[i] < b[i] then
      Porownaj := -1
    else
      Porownaj := 1;
end;


procedure Przypisz_0(var a: Liczba);
var
  i: integer;
begin
  for i := 1 to lCyfr do
    a[i] := 0;
end;


function CzyParzysta(var a: Liczba): boolean;
begin
  CzyParzysta := not Odd(a[1]);
end;


procedure NWD(var a, b, c: Liczba);
{ c := NWD(a, b) }
var
  i, k: integer;
  zero: Liczba;
begin
  Przypisz_0(zero);

  k := 0;
  while (Porownaj(a, zero) <> 0) and (Porownaj(b, zero) <> 0) do begin
    if CzyParzysta(a) then begin
      DzielPrzez2(a);
      if CzyParzysta(b) then begin
        DzielPrzez2(b);
        Inc(k);
      end
    end
    else
      if CzyParzysta(b) then
        DzielPrzez2(b)
      else begin
        if Porownaj(a, b) >= 0 then begin
          Odejmij(a, b);
          DzielPrzez2(a);
        end
        else begin
          Odejmij(b, a);
          DzielPrzez2(b);
        end;
      end;
  end;

  if Porownaj(a, zero) = 0 then
    Kopiuj(c, b)
  else
    Kopiuj(c, a);

  for i := 1 to k do
    Razy2(c);
end;


function WczytajLiczbe(var p: text; var x: Liczba): integer;
var
  i, dl: integer;
  ch: char;
  pom: array [1..MAX_CYFR] of char;
begin
  i := 0;
  while not (Eoln(p) or Eof(p)) do begin
    Inc(i);
    Read(p, ch);
    pom[i] := ch;
  end;
  dl := i;

  if Eoln(p) then
    Readln(p);

  for i := 1 to dl do
    x[i] := Ord(pom[dl - i + 1]) - Ord('0');

  WczytajLiczbe := dl;
end;


procedure ZapiszLiczbe(var p: text; var x: Liczba);
var
  i: integer;
begin
  i := lCyfr;
  while (i > 1) and (x[i] = 0) do
    Dec(i);

  while i > 0 do begin
    Write(p, x[i]);
    Dec(i);
  end;

  Writeln(p);
end;


procedure WczytajDane;
var
  plik: text;
begin
  Assign(plik, PLIK_WE);
  Reset(plik);

  lCyfr := WczytajLiczbe(plik, n);
  Przypisz_0(k);
  WczytajLiczbe(plik, k);
  Przypisz_0(l);
  WczytajLiczbe(plik, l);

  Close(plik);
end;


procedure ZapiszWynik(wynik: Liczba);
var
  plik: text;
begin
  Assign(plik, PLIK_WY);
  Rewrite(plik);
  ZapiszLiczbe(plik, wynik);
  Close(plik);
end;



begin
  WczytajDane;

  Kopiuj(k1, k);
  Kopiuj(l1, l);
  NWD(k1, l1, b);

  Kopiuj(a, k);
  Dodaj(a, l);
  Odejmij(a, b);
  { a = k + l - NWD(k, l) }

  if Porownaj(n, a) <= 0 then begin
    Dodaj(a, b);
    Odejmij(a, n);
    { a = k + l - n }
    ZapiszWynik(a);
  end else
    ZapiszWynik(b);
end.
