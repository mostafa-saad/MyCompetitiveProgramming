(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Studnia                                          *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n * log(max(x_i)))                             *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000000;

function max(a, b : longint) : longint;
begin
  if a < b then
    max := b
  else
    max := a;
end;

var
  x : array[0..MAXN] of longint; (* grubosc warstwy piasku, dane z wejscia *)
  pom : array[0..MAXN] of longint;
  (* pomocniczna tablica z grubosciami warstw piasku, na ktorej beda wykonywane obliczenia *)

  n : longint;
  m : int64; (* liczba ruchow lopaty, na ktore Bajtazar ma sile *)

(* Funkcja rozwiazujaca podproblem wyrownania koryta rzeki bez dokopywania sie do wody,
 * tak, zeby liczba z zdefiniowana w tresci nie przekroczyla p.
 * Zwraca potrzebna liczbe ruchow lopaty do osiagniecia tego celu *)

function wyrownaj(p : longint) : int64;
  var ruchy : int64;
      i : longint;
begin
  ruchy := 0;
  for i := 1 to n-1 do
    if pom[i-1] + p < pom[i] then
    begin
      ruchy := ruchy + pom[i] - pom[i-1] - p;
      pom[i] := pom[i-1] + p;
    end;
  for i := n-2 downto 0 do
    if pom[i+1] + p < pom[i] then
    begin
      ruchy := ruchy + pom[i] - pom[i+1] - p;
      pom[i] := pom[i+1] + p;
    end;
  wyrownaj := ruchy;
end;

(* oblicza tablice jednostronnych wyrownan terenu w danym punkcie
 * tab - tablica wynikowa
 * s - pozycja startowa
 * k - pozycja koncowa
 * d - strona ktora wyrownujemy
 * g - maksymalna dopuszczalna roznica wysokosci *)

procedure policz_tablice_wyrownan(var out : array of int64; s, k, d, g : longint);
  var brzeg, size : longint;
begin
  size := 1;
  brzeg := s + d;
  out[s] := 0;
  while (brzeg <> k) and (pom[brzeg] > size * g) do
  begin
    out[s] := out[s] + pom[brzeg] - size * g;
    brzeg := brzeg + d;
    size := size + 1;
  end;
  while s + d <> k do
  begin
    s := s + d;
    size := size - 1;
    out[s] := out[s-d];
    if brzeg <> s then
      out[s] := out[s] - pom[s] + size * g
    else begin
      brzeg := brzeg + d;
      size := size + 1;
    end;
    while (brzeg <> k) and (pom[brzeg] > size * g) do
    begin
      out[s] := out[s] + pom[brzeg] - size * g;
      brzeg := brzeg + d;
      size := size + 1;
    end;
  end;
end;

(* Funkcja zwraca miejsce, w ktorym uda sie dokopac do poziomu 0,
 * tak, zeby liczba z zdefiniowana w tresci nie przekroczyla p,
 * badz -1 jesli takiego miejsca nie ma. *)

function gdzie_kopac(p : longint) : longint;
  var ruchy : int64;
    i : longint;
    prawo, lewo : array[0..MAXN] of int64;
begin
  for i := 0 to n-1 do pom[i] := x[i];

  ruchy := wyrownaj(p);
  if ruchy > m then
  begin
    gdzie_kopac := -1;
    exit;
  end;

  policz_tablice_wyrownan(prawo, 0, n, 1, p);
  policz_tablice_wyrownan(lewo, n-1, -1, -1, p);

  for i := 0 to n-1 do
    if ruchy + prawo[i] + lewo[i] + pom[i] <= m then
    begin
      gdzie_kopac := i + 1;
      exit;
    end;

  gdzie_kopac := -1;
end;

var
  max_h : longint = 0;
  i, a, b, c, pozycja, pozycja2 : longint;

Begin
  readln (n, m);
  for i := 0 to n-1 do
  begin
    read(x[i]);
    max_h := max(max_h, x[i]);
  end;

  pozycja := 1;
  a := 0;
  b := max_h;
  while a < b do
  begin
    c := (a + b) >> 1;
    pozycja2 := gdzie_kopac(c);
    if pozycja2 <> -1 then begin
      b := c;
      pozycja := pozycja2;
    end else
      a := c + 1;
  end;
  writeln (pozycja, ' ', a);
End.
