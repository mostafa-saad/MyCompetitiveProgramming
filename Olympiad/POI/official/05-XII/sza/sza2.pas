(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SZA (Szablon)                                  *
 *   Plik:                sza2.pas                                       *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie nadoptymalne                       *
 *                        Program o z³o¿ono¶ci czasowej                  *
 *                        i pamiêciowej O(n), obliczaj±cy d³ugo¶ci       *
 *                        szablonów on-line.                             *
 *                                                                       *
 *************************************************************************)

const MAX_LEN = 500000;

(* Deklaracje zmiennych globalnych. *)
var
  pref_suf : array[0..MAX_LEN] of LongInt;
                             {Tablica d³ugo¶ci najd³u¿szych prefikso-sufiksów}
                             {tak zwana funkcja prefiksowa).}
  sl : array[1..MAX_LEN] of Char; {Rozwa¿ane s³owo.}
  n : LongInt; {D³ugo¶æ rozwa¿anego s³owa.}
  j, b, q : LongInt; {Zmienne pomocnicze programu g³ównego.}
  zakres : array[0..MAX_LEN] of LongInt;
                             {Zakresy s³owa, które mo¿na pokryæ poszczególnymi}
                             {prefiksami s³owa, jako szablonami.}
  szablony : array[0..MAX_LEN] of LongInt;
                             {Najkrótsze szablony dla kolejnych}
                             {prefiksów s³owa.}

procedure odczyt;
var ch : Char;
begin
  n := 0;
  while not Eoln(input) do
  begin
    Read(ch);
    Inc(n);
    sl[n] := ch
  end {while}
end; {odczyt}

(* Procedura wyliczaj±ca warto¶ci funkcji prefiksowej
 * dla podanego w parametrze s³owa. *)
procedure licz_pref_suf;
var k, q : LongInt;
begin
  k := 0;
  (* Inicjalizacja funkcji prefiksowej. *)
  pref_suf[0] := 0;
  pref_suf[1] := 0;
  
  (* Wyliczanie kolejnych warto¶ci funkcji prefiksowej. *)
  for q := 2 to n do
  begin
    (* Niezmiennik: najd³u¿szy prefikso-sufiks prefiksu danego
    s³owa o d³ugo¶ci q ma d³ugo¶æ k. *)
    while (k > 0) and (sl[k + 1] <> sl[q]) do
      k := pref_suf[k];
    if sl[k + 1] = sl[q] then
      Inc(k);
    pref_suf[q] := k
  end {for}
end; {licz_pref_suf}


begin
  (* Odczyt s³owa i wyliczenie funkcji prefiksowej. *)
  odczyt;
  licz_pref_suf;

  (* Obliczanie najkrótszych szablonów dla prefiksów s³owa,
  wykonywane on-line. *)
  for j := 1 to n do
  begin
    szablony[j] := j;
    zakres[j] := j
  end; {for}
  
  (* Pêtla po wszystkich, d³u¿szych ni¿ jeden, prefiksach
  danego s³owa - w j-tym kroku rozwa¿amy j-ty prefiks. *)
  for j := 2 to n do
  begin
    b := pref_suf[j];
    if b > 0 then
    begin
      (* Sprawdzamy, czy szablon najd³u¿szego prefikso-sufiksu
      danego prefiksu s³owa jest dobrym szablonem dla aktualnego
      prefiksu: *)
      q := szablony[b];
      if zakres[q] >= j - q then
      begin
        (* je¿eli tak, to wybieramy jego jako szablon, *)
        szablony[j] := q;
        zakres[q] := j
      end {if}
      (* je¿eli nie, to ju¿ jest ustawione szablony[i]=i. *)
    end {if}
  end; {for}
  
  (* Wypisanie wyniku *)
  WriteLn(szablony[n])
end. {program}
