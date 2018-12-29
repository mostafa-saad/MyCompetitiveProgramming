(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Najdzielniejszy dzielnik (NAJ)                            *
 *   Plik:     najs2.pas                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             Uzywa testu Millera-Rabina z mnozeniem rosyjskich chlopow.*
 *             Dodatkowo, nie wykonuje sita.                             *
 *                                                                       *
 *************************************************************************)   

const MAX_N = 600;

function nwd(a, b : Int64) : Int64;
begin
  if b = 0 then
    nwd := a
  else
    nwd := nwd(b, a mod b);
end;

var
  n : LongInt;
  a : array[1 .. MAX_N] of Int64;
  k, c : LongInt;



(******* Test Millera-Rabina *******)

(* Oblicza (a*b) mod p za pomoca algorytmu Rosyjskich chlopow. *)
function mnoz(a, b, p : Int64) : Int64;
var
  wyn : Int64;
begin
  wyn := 0;
  while b > 0 do
  begin
    if b mod 2 = 1 then
      wyn := (wyn + a) mod p;
    b := b div 2;
    a := (2 * a) mod p;
  end;
  mnoz := wyn;
end;

(* Oblicza (x^n) mod p za pomoca szybkiego potegowania binarnego. *)
function potmod(a, n, p : Int64) : Int64;
var
  wyn : Int64;
begin
  wyn := 1;
  while n > 0 do
  begin
    if n mod 2 = 1 then
      wyn := mnoz(wyn, a, p);
    n := n div 2;
    a := mnoz(a, a, p);
  end;
  potmod := wyn;
end;

(* Czy a jest pseudopierwsza przy podstawie p? *)
function psp(a, p : Int64) : Boolean;
var
  ile : LongInt;
  q, b : Int64;
begin
  psp := true;
  q := p - 1;
  ile := 0;
  while q mod 2 = 0 do
  begin
    Inc(ile);
    q := q div 2;
  end;
  a := potmod(a, q, p);
  while ile > 0 do
  begin
    Dec(ile);
    b := mnoz(a, a, p);
    if (b = 1) and (a <> 1) and (a <> p - 1) then
      psp := false;
    a := b;
  end;
  if a <> 1 then
    psp := false;
end;

(* Test pierwszosci Millera-Rabina *)
function Miller_Rabin(p : Int64) : Boolean;
const
  PROBY = 50;
var
  a : LongInt;
begin
  Miller_Rabin := true;
  for a := 2 to PROBY do
    if not psp(a, p) then
      Miller_Rabin := false;
end;






(* Wyznaczamy krotnosc p w ramach N i ewentualnie aktualizujemy k i c. *)
procedure aktualizuj(p : Int64; na_pewno_pierwsza : Boolean);
var
  i : LongInt;
  kr, wklad : LongInt;
begin
  kr := 0;
  for i := 1 to n do
    while a[i] mod p = 0 do
    begin
      a[i] := a[i] div p;
      Inc(kr);
    end;

  wklad := 2;
  if na_pewno_pierwsza or Miller_Rabin(p) then
    wklad := 1;
  if kr > k then
  begin
    k := kr;
    c := wklad;
  end else if kr = k then
  begin
    Inc(c, wklad);
  end;
end;



(* Wypisywanie 2^c-1 - zawiera operacje na duzych liczbach. *)
procedure wypisz(c : LongInt);
var
  wyn : array[1 .. 10000] of LongInt;
  size : LongInt;
  a, i : LongInt;
begin
  (* 2^c *)
  size := 1;
  wyn[size] := 1;
  while c > 0 do
  begin
    Dec(c);
    a := 0;
    for i := 1 to size do
    begin
      wyn[i] := 2 * wyn[i] + a;
      a := 0;
      if wyn[i] >= 10 then
      begin
        Dec(wyn[i], 10);
        a := 1;
      end;
    end;
    if a > 0 then
    begin
      size := size + 1;
      wyn[size] := a;
    end;
  end;

  (* 2^c-1 *)
  Dec(wyn[1]);
  i := 1;
  while wyn[i] < 0 do
  begin
    Inc(wyn[i], 10);
    Inc(i);
    Dec(wyn[i]);
  end;

  (* Wypisywanie. *)
  for i := size downto 1 do
    Write(wyn[i]);
  WriteLn;
end;


var
  i, j : LongInt;
  z : LongInt;
  d : Int64;

begin
  k := 0;
  c := 0;
  (* Odczyt *)
  ReadLn(n);
  for i := 1 to n do
    Read(a[i]);

  (* Faza 1: dzielniki 2 .. 10^6. *)
  for i := 2 to 1000000 do
    aktualizuj(i, true);

  (* Faza 2: dzielniki z nwd *)
  for i := 1 to n do
    for j := i + 1 to n do
    begin
      d := nwd(a[i], a[j]);
      if ((d < a[i]) or (d < a[j])) and (d > 1) then
        aktualizuj(d, true);
    end;

  (* Faza 3: Pierwiastki *)
  for i := 1 to n do
    if a[i] > 1 then
    begin
      z := LongInt(Round(Sqrt(a[i])));
      if Int64(z) * z = a[i] then
        aktualizuj(z, true);
    end;

  (* Faza 4: odroznienie pierwszych od zlozonych *)
  for i := 1 to n do
    if a[i] > 1 then
      aktualizuj(a[i], false);

  WriteLn(k);
  wypisz(c);
end.
