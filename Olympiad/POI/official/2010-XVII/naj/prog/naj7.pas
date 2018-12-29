(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Najdzielniejszy dzielnik (NAJ)                            *
 *   Plik:     naj7.pas                                                  *
 *   Autor:    Bartlomiej Wolowiec                                       *
 *   Opis:     Rozwiazanie weryfikujace.                                 *
 *             Dla duzych liczb zlozonych (sprawdzonych testem           *
 *             Millera-Rabina) uzywa heurystyki rho, aby rozlozyc je     *
 *             na czynniki pierwsze.                                     *
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
  p : Int64;
  n : LongInt;
  a : array[1 .. MAX_N] of Int64;
  k, c : LongInt;
  pierwsze : array[1 .. 200000] of LongInt;
  pierwsze_size : LongInt;


(* Sito Eratostenesa w wersji logarytmicznej. *)
procedure sito(m : LongInt);
var
  p : array[1 .. 1000000] of Boolean;
  i, j : LongInt;
begin
  if m < 0 then
    m := 1000000;
  for i := 2 to m do
    p[i] := true;
  for i := 2 to m do
    if p[i] then
    begin
      j := 2 * i;  (* tu mozna by wpisac i*i, ale uwaga na rozmiar typu! *)
      while j <= m do
      begin
        p[j] := false;
        Inc(j, i);
      end;
    end;

  pierwsze_size := 0;
  for i := 2 to m do
    if p[i] then
    begin
      Inc(pierwsze_size);
      pierwsze[pierwsze_size] := i;
    end;
end;



(******* Test Millera-Rabina *******)

(* Oblicza (a*b) mod p za pomoca algorytmu Rosyjskich chlopow. *)
function mnoz(a, b, p : Int64) : Int64;
const
  MLD = 1000000000;
var
  a1, a2, b1, b2, wyn, pom : Int64;
  i : LongInt;
begin
  wyn := 0;
  a1 := a div MLD; a2 := a mod MLD;
  b1 := b div MLD; b2 := b mod MLD;
  Inc(wyn, a2 * b2);
  pom := a1 * b2 + a2 * b1;
  if pom > 0 then
    for i := 1 to 9 do
    begin
      pom := (pom * 2) mod p;
      pom := (pom * 5) mod p;
    end;
  Inc(wyn, pom);
  pom := a1 * b1;
  if pom > 0 then
    for i := 1 to 18 do
    begin
      pom := (pom * 2) mod p;
      pom := (pom * 5) mod p;
    end;
  Inc(wyn, pom);
  mnoz := wyn mod p;
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

function rho(n : Int64) : Int64;
var
    i,x,y,k,d : Int64;
begin
    i:=1;
    x:=123458173 mod n; (* random *)
    y:=x;
    k:=2;
    d:=0;
    while true do
    begin
        i := i+1;
        x := (mnoz(x, x, n) + 1) mod n;
        d := nwd(abs(y-x), n);
        if (d<>1) and (d<>n) then
            begin
                rho:=d;
                break;
            end;
        if i=k then
            begin
                y:=x;
                k:=k*2;
            end;
    end;
end;

(* Test pierwszosci Millera-Rabina *)
function Miller_Rabin(p : Int64) : Int64;
const
  PROBY = 50;
var
  a : LongInt;
begin
  Miller_Rabin := p;
  for a := 2 to PROBY do
      if not psp(a, p) then
      begin
          Miller_Rabin := rho(p);
          break;
      end
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
  if na_pewno_pierwsza then
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
  i : LongInt;

begin
  k := 0;
  c := 0;
  (* Odczyt *)
  ReadLn(n);
  for i := 1 to n do
    Read(a[i]);

  (* Faza 1: dzielniki z sita *)
  sito(-1);
  for i := 1 to pierwsze_size do
    aktualizuj(pierwsze[i], true);

   for i := 1 to n do begin
       if a[i]>1 then begin
           p:=Miller_Rabin(a[i]);
           aktualizuj(p, true);
           if a[i]>1 then
               aktualizuj(a[i], true);
       end;
   end;

  WriteLn(k);
  wypisz(c);
end.
