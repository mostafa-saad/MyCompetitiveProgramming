{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Drzewa (DRZ)                                               *}
{*   Plik:    drz0.pas                                                   *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Rozwi±zanie autorskie, Z³o¿ono¶æ czasowa: O(n logn),       *}
{*            Z³o¿ono¶æ pamiêciowa: O(n)                                 *}
{*                                                                       *}
{*************************************************************************}
const MAX_N = 50000;
const NIESK = 1000000000; (* nieskoñczono¶æ *)
const ROOT = 0; (* numer korzenia w dowolnym drzewie mintree *)


type Node = record
(* Wierzcho³ek drzewa mintree. *)
  lsyn, psyn : LongInt; (* numer lewego i prawego syna *)
  lewy, prawy : LongInt; (* wierzcho³ek reprezentuje przedzia³ [lewy, prawy] *)
  wart : LongInt
end; (* Node *)

type Rec = record
  x, y : LongInt
end; (* Rec *)


(* Tablica drzew mintree
 * 0 - A1, 1 - A2, 2 - A3, 3 - B1, 4 - B2, 5 - B3, 6 - C1, 7 - C2, 8 - C3 *)
var mintree : array[0..8, 0..2 * MAX_N] of Node;
n, i, j : LongInt;
a, b, A1, B1, H1 : LongInt;
h : array[0..MAX_N - 1] of LongInt;
(* Najmniejszy wspó³czynnik nieporz±dku dla zamian danego drzewa. *)
wyn : array[0..MAX_N - 1] of Int64;
wspol, (* Pocz±tkowy wspó³czynnik nieporz±dku. *)
akt : Int64; (* W³a¶nie liczony wspó³czynnik nieporz±dku. *)

(* Tablica dl (drzewo-liczba) reprezentuje funkcjê, która pobiera numer
 * drzewa (miêdzy 0 a n-1) i zwraca jego wysoko¶æ po przenumerowaniu
 * (tak¿e pomiêdzy 0 a n-1).
 * Tablica ld (liczba-drzewo) jest odwróceniem poprzedniej funkcji.
 * Obie tablice s± wyliczane w procedurze przenumeruj. *)
dl, ld : array[0..MAX_N - 1] of LongInt;
(* aktualne pozycje wierzcho³ków tworzonych w drzewach mintree 0-8 *)                   
akt_poz : array[0..8] of LongInt;
(* pomocnicza tablica u¿ywana do sortowania drzew *)
tmp : array[0..MAX_N - 1] of Rec;

(*****************************************************************************)
(* Implementacja operacji na drzewach mintree                                *)
(*****************************************************************************)

function min(a, b : LongInt) : LongInt;
begin
  if a < b then
    min := a
  else
    min := b
end; (* min *)

function max(a, b : LongInt) : LongInt;
begin
  if a < b then
    max := b
  else
    max := a
end; (* min *)

function create(ndrz, l, p : LongInt) : LongInt;
(* Ta funkcja tworzy wierzcho³ek odpowiadaj±cy przedzia³owi [l, p] w drzewie
 * mintree o numerze ndrz. *) 
var sr, v : LongInt;
begin
  sr := (l + p) div 2;
  v := akt_poz[ndrz]; Inc(akt_poz[ndrz]);
  mintree[ndrz, v].lewy := l; mintree[ndrz, v].prawy := p;
  mintree[ndrz, v].wart := NIESK;
  if l = p then
    create := v
  else
  begin
    mintree[ndrz, v].lsyn := create(ndrz, l, sr);
    mintree[ndrz, v].psyn := create(ndrz, sr + 1, p);
    create := v
  end (* else *)
end; (* create *)

procedure build;
(* Ta procedura buduje wszystkie drzewa mintree. *)
var nr : Integer;
begin
  for nr := 0 to 8 do
    akt_poz[nr] := 0;
  for nr := 0 to 8 do
    create(nr, 0, n - 1)
end; (* build *)

procedure insert(ndrz, wierzch, klucz, wart : LongInt);
(* Ta procedura wstawia element charakteryzowany przez parê (klucz,wart)
 * do drzewa mintree o numerze ndrz; wierzch to aktualnie rozwa¿any wierzcho³ek
 * drzewa. *)
var l, p, sr : LongInt;
begin
  mintree[ndrz, wierzch].wart := min(mintree[ndrz, wierzch].wart, wart);
  l := mintree[ndrz, wierzch].lewy; p := mintree[ndrz, wierzch].prawy;
  if l < p then
  begin
    sr := (l + p) div 2;
    if klucz <= sr then
      insert(ndrz, mintree[ndrz, wierzch].lsyn, klucz, wart)
    else
      insert(ndrz, mintree[ndrz, wierzch].psyn, klucz, wart)
  end (* if *)
end; (* insert *)

procedure del(ndrz, wierzch, klucz : LongInt);
(* Ta procedura usuwa element o danym kluczu z drzewa mintree o numerze
 * ndrz; wierzch to aktualnie rozwa¿any wierzcho³ek drzewa. *)
var l, p, sr : LongInt;
begin
  l := mintree[ndrz, wierzch].lewy; p := mintree[ndrz, wierzch].prawy;
  if l = p then
  begin
    mintree[ndrz, wierzch].wart := NIESK;
    exit
  end; (* if *)
  sr := (l + p) div 2;
  if klucz <= sr then
    del(ndrz, mintree[ndrz, wierzch].lsyn, klucz)
  else
    del(ndrz, mintree[ndrz, wierzch].psyn, klucz);
  mintree[ndrz, wierzch].wart := 
    min(mintree[ndrz, mintree[ndrz, wierzch].lsyn].wart,
        mintree[ndrz, mintree[ndrz, wierzch].psyn].wart)
end; (* del *)

function min_val(ndrz, wierzch, lewy, prawy : LongInt) : LongInt;
(* Ta funkcja wykonuje operacjê "min_val" na drzewie mintree o numerze
 * ndrz dla przedzia³u I=[lewy,prawy] i wierzcho³ka v=wierzch. *) 
var l, p, sr : LongInt;
begin
  if lewy > prawy then
    min_val := NIESK
  else
  begin
    l := mintree[ndrz, wierzch].lewy; p := mintree[ndrz, wierzch].prawy;
    if (lewy <= l) and (p <= prawy) then
      min_val := mintree[ndrz, wierzch].wart
    else
    begin
      sr := (l + p) div 2;
      if lewy > sr then
        min_val := min_val(ndrz, mintree[ndrz, wierzch].psyn, lewy, prawy)
      else if prawy <= sr then
        min_val := min_val(ndrz, mintree[ndrz, wierzch].lsyn, lewy, prawy)
      else
        min_val := min(min_val(ndrz, mintree[ndrz, wierzch].lsyn, lewy, prawy),
                   min_val(ndrz, mintree[ndrz, wierzch].psyn, lewy, prawy))
    end (* else *)
  end (* else *)
end; (* min_val *)

(*****************************************************************************)
(* Koniec implementacji operacji na drzewach mintree                         *)
(*****************************************************************************)

procedure qsort(l, r : LongInt);
(* Rekurencyjny Quicksort (sortowanie szybkie) *)
var a, b : LongInt;
x, y : Rec;
begin
  a := l; b := r;
  x := tmp[(a + b) div 2];
  repeat
    while tmp[a].x < x.x do
      Inc(a);
    while tmp[b].x > x.x do
      Dec(b);
    if a <= b then
    begin
      y := tmp[a];
      tmp[a] := tmp[b];
      tmp[b] := y;
      Inc(a); Dec(b)
    end; (* if *)
  until a > b;
  if a < r then
    qsort(a, r);
  if l < b then
    qsort(l, b)
end; (* qsort *)


procedure przenumeruj;
(* Ta procedura oblicza tablice dl i ld. Tablica par (wysoko¶æ drzewa,drzewo)
 * zostaje posortowana w kolejno¶ci niemalej±cych wysoko¶ci. *)
var i : LongInt;
begin
  for i := 0 to n - 1 do
  begin
    tmp[i].x := h[i];
    tmp[i].y := i
  end; (* for *)
  qsort(0, n - 1);
  for i := 0 to n - 1 do
  begin
    dl[tmp[i].y] := i;
    ld[i] := tmp[i].y
  end (* for *)
end; (* przenumeruj *)

procedure licz_wspol;
(* Ta procedura liczy pocz±tkowy wspó³czynnik nieporz±dku. *)
var i : LongInt;
begin
  wspol := 0;
  for i := 0 to n - 2 do
    Inc(wspol, Abs(h[i] - h[i + 1]))
end; (* licz_wspol *)

function f1(a, b, h : LongInt) : LongInt;
begin
  f1 := -Abs(a - h) - Abs(h - b) + a + b
end; (* f1 *)

function f2(a, b, h : LongInt) : LongInt;
begin
  f2 := -Abs(a - h) - Abs(h - b) - a + b
end; (* f2 *)

function f3(a, b, h : LongInt) : LongInt;
begin
  f3 := -Abs(a - h) - Abs(h - b) - a - b
end; (* f3 *)

function min(a0, a1, a2, a3, a4, a5, a6, a7, a8 : LongInt) : LongInt;
(* Minimum z 9 warto¶ci, potrzebne w g³ównej pêtli. *)
begin
  min := min(min(min(a0,a1),min(a2,a3)),min(min(a4,a5),min(min(a6,a7),a8)))
end; (* min *)

procedure dod_A(i : LongInt);
(* Ta procedura wstawia i-te drzewo do drzew mintree: A1, A2 i A3,
 * przypisuj±c mu warto¶æ równ± sumie warto¶ci z drzewa mintree A i
 * odpowiedniego drzewa mintree Ti. *)
var a, b : LongInt;
begin
  a := min(h[i - 1], h[i + 1]);
  b := max(h[i - 1], h[i + 1]);
  insert(0, ROOT, dl[i], -2 * h[i] + f1(a, b, h[i]));
  insert(1, ROOT, dl[i], f1(a, b, h[i]));
  insert(2, ROOT, dl[i], 2 * h[i] + f1(a, b, h[i]))
end; (* dod_A *)

procedure dod_B(i : LongInt);
(* Ta procedura wstawia i-te drzewo do drzew mintree: B1, B2 i B3,
 * przypisuj±c mu warto¶æ równ± sumie warto¶ci z drzewa mintree B i
 * odpowiedniego drzewa mintree Ti. *)
var a, b : LongInt;
begin
  a := min(h[i - 1], h[i + 1]);
  b := max(h[i - 1], h[i + 1]);
  insert(3, ROOT, dl[i], -2 * h[i] + f2(a, b, h[i]));
  insert(4, ROOT, dl[i], f2(a, b, h[i]));
  insert(5, ROOT, dl[i], 2 * h[i] + f2(a, b, h[i]))
end; (* dod_B *)
 
procedure dod_C(i : LongInt);
(* Ta procedura wstawia i-te drzewo do drzew mintree: C1, C2 i C3,
 * przypisuj±c mu warto¶æ równ± sumie warto¶ci z drzewa mintree C i
 * odpowiedniego drzewa mintree Ti. *)
var a, b : LongInt;
begin
  a := min(h[i - 1], h[i + 1]);
  b := max(h[i - 1], h[i + 1]);
  insert(6, ROOT, dl[i], -2 * h[i] + f3(a, b, h[i]));
  insert(7, ROOT, dl[i], f3(a, b, h[i]));
  insert(8, ROOT, dl[i], 2 * h[i] + f3(a, b, h[i]))
end; (* dod_C *)

(*****************************************************************************)
(* Rozwa¿anie przypadków szczególnych                                        *)
(*****************************************************************************)

function min(a, b : Int64) : Int64;
begin
  if a < b then
    min := a
  else
    min := b
end; (* min *)

function zm_wart(wys, poz : LongInt) : LongInt;
(* Ta funkcja liczy zmianê warto¶ci wspó³czynnika nieporz±dku, kiedy drzewo
 * o wysoko¶ci wys zostaje umiejscowione na pozycji poz. *)
var wyn : LongInt;
begin
  wyn := 0;
  if poz > 0 then
    Inc(wyn, Abs(wys - h[poz - 1]));
  if poz < n - 1 then
    Inc(wyn, Abs(wys - h[poz + 1]));
  zm_wart := wyn
end; (* zm_wart *)

function zm_wart1(poz : LongInt) : LongInt;
(* Ta funkcja liczy zmianê warto¶ci wspó³czynnika nieporz±dku, kiedy drzewa
 * na pozycjach poz i poz+1 zostaj± zamienione miejscami. *)
var wyn : LongInt;
begin
  wyn := 0;
  if poz > 0 then
    Dec(wyn, Abs(h[poz] - h[poz - 1]) - Abs(h[poz + 1] - h[poz - 1]));
  if poz + 1 < n - 1 then
    Dec(wyn, Abs(h[poz + 2] - h[poz + 1]) - Abs(h[poz + 2] - h[poz]));
  zm_wart1 := wyn
end; (* zm_wart1 *)


procedure przypadki_szczegolne;
var pom : LongInt;
(* Rozwa¿enie wszystkich przypadków szczególnych (w ³±cznym czasie O(n)). *)
begin
  (* Drzewo zerowe *)
  for i := 2 to n - 1 do
  begin
    pom := - zm_wart(h[0], 0) - zm_wart(h[i], i)
           + zm_wart(h[0], i) + zm_wart(h[i], 0);
    wyn[0] := min(wyn[0], wspol + pom);
    wyn[i] := min(wyn[i], wspol + pom)
  end; (* for *)
  (* Drzewo (n-1)-sze *)
  for i := 0 to n - 3 do
  begin
    pom := - zm_wart(h[n - 1], n - 1) - zm_wart(h[i], i)
           + zm_wart(h[n - 1], i) + zm_wart(h[i], n - 1);
    wyn[n - 1] := min(wyn[n - 1], wspol + pom);
    wyn[i] := min(wyn[i], wspol + pom)
  end; (* for *)
  (* Pary s±siednich drzew *)
  for i := 0 to n - 2 do
  begin
    pom := zm_wart1(i);
    wyn[i] := min(wyn[i], wspol + pom);
    wyn[i + 1] := min(wyn[i + 1], wspol + pom)
  end (* for *)
end; (* przypadki_szczegolne *)

(*****************************************************************************)
(* Koniec rozwa¿ania przypadków szczególnych                                 *)
(*****************************************************************************)


begin
  ReadLn(n);
  for i := 0 to n - 1 do
    Read(h[i]);
  build;
  przenumeruj;
  licz_wspol;
  for i := 0 to n - 1 do
    wyn[i] := wspol;
  (* Dodajemy wszystkie drzewa do A1, A2 oraz A3. *)
  for i := 0 to n - 1 do
    if (ld[i] > 0) and (ld[i] < n - 1) then
      dod_A(ld[i]);
  for i := 0 to n - 1 do (* rozwa¿amy i-te drzewo *)
  begin
    (* usuwamy s±siadów i-tego drzewa *)
    for j := 0 to 8 do
    begin
      if ld[i] > 1 then (* s±siad nie jest wyj±tkiem *)
        del(j, ROOT, dl[ld[i] - 1]);
      if ld[i] < n - 2 then (* s±siad nie jest wyj±tkiem *)
        del(j, ROOT, dl[ld[i] + 1])
    end; (* for *)

    if (ld[i] > 0) and (ld[i] < n - 1) then
    (* Ten fragment nie jest wykonywany dla skrajnie lewego oraz skrajnie
     * prawego drzewa. *)
    begin
      (* wyliczamy minimalny wspó³czynnik *)
      a := min(h[ld[i] - 1], h[ld[i] + 1]);
      b := max(h[ld[i] - 1], h[ld[i] + 1]);
      H1 := h[ld[i]]; (* A1=f(a), B1=f(b) *)
      if a = h[ld[i] - 1] then
      begin
        A1 := dl[ld[i] - 1]; B1 := dl[ld[i] + 1]
      end (* if *)
      else
      begin
        A1 := dl[ld[i] + 1]; B1 := dl[ld[i] - 1]
      end; (* else *)
      akt := wspol +
        min(f1(a, b, H1) - 2 * H1 + min_val(0, ROOT, 0, A1 - 1),
            f2(a, b, H1) - 2 * H1 + min_val(1, ROOT, A1, B1),
            f3(a, b, H1) - 2 * H1 + min_val(2, ROOT, B1 + 1 , n - 1),
            f1(a, b, H1) + min_val(3, ROOT, 0, A1 - 1),
            f2(a, b, H1) + min_val(4, ROOT, A1, B1),
            f3(a, b, H1) + min_val(5, ROOT, B1 + 1, n - 1),
            f1(a, b, H1) + 2 * H1 + min_val(6, ROOT, 0, A1 - 1),
            f2(a, b, H1) + 2 * H1 + min_val(7, ROOT, A1, B1),
            f3(a, b, H1) + 2 * H1 + min_val(8, ROOT, B1 + 1, n - 1));
      wyn[ld[i]] := akt
    end; (* if *)

    (* Wstawienie s±siadów z powrotem do odpowiednich drzew mintree -
     * równocze¶nie aktualizujemy drzewa mintree. *)
    if ld[i] > 1 then (* s±siad nie jest wyj±tkiem *)
    begin
      if dl[ld[i] - 2] > i then
        dod_B(ld[i] - 1)
      else
        dod_C(ld[i] - 1)
    end; (* if *)
    if ld[i] < n - 2 then (* s±siad nie jest wyj±tkiem *)
    begin
      if dl[ld[i] + 2] > i then
        dod_B(ld[i] + 1)
      else
        dod_C(ld[i] + 1)
    end (* if *)
  end; (* for *)
  przypadki_szczegolne;
  for i := 0 to n - 1 do
    WriteLn(wyn[i])
end. (* program *)
