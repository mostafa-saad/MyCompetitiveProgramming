{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Drzewa (DRZ)                                               *}
{*   Plik:    drzs3.pas                                                  *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Rozwiazanie zbyt wolne: zlozonosc czasowa: O(n^2),         *}
{*            zlozonosc pamieciowa: O(n)                                 *}
{*                                                                       *}
{*************************************************************************}
const MAX_N = 50000;

var
  n, i, j : LongInt;
  h : array[1..MAX_N] of LongInt;
  wyn : array[1..MAX_N] of Int64;
  wyn0 : Int64;
  pom : LongInt;


function licz : Int64;
(* Liczy wspó³czynnik nieporz±dku. *)
var
  wyn : Int64;
  i : LongInt;
begin
  wyn := 0;
  for i := 1 to n - 1 do
    Inc(wyn, Abs(h[i] - h[i + 1]));
  licz := wyn
end; (* licz *)

function min(x, y : Int64) : Int64;
begin
  if x < y then
    min := x
  else
    min := y
end; (* min *)

function zm_wart(wys, poz : LongInt) : LongInt;
(* Ta funkcja liczy zmianê warto¶ci wspó³czynnika nieporz±dku, kiedy drzewo
 * o wysoko¶ci wys zostaje umiejscowione na pozycji poz. *)
var
  wyn : LongInt;
begin
  wyn := 0;
  if poz > 1 then
    Inc(wyn, Abs(wys - h[poz - 1]));
  if poz < n then
    Inc(wyn, Abs(wys - h[poz + 1]));
  zm_wart := wyn
end; (* zm_wart *)

function zm_wart1(poz : LongInt) : LongInt;
(* Ta funkcja liczy zmianê warto¶ci wspó³czynnika nieporz±dku, kiedy drzewa
 * na pozycjach poz i poz+1 zostaj± zamienione miejscami. *)
var
  wyn : LongInt;
begin
  wyn := 0;
  if poz > 1 then
    Dec(wyn, Abs(h[poz] - h[poz - 1]) - Abs(h[poz + 1] - h[poz - 1]));
  if poz + 1 < n then
    Dec(wyn, Abs(h[poz + 2] - h[poz + 1]) - Abs(h[poz + 2] - h[poz]));
  zm_wart1 := wyn
end; (* zm_wart1 *)


begin
  ReadLn(n);
  for i := 1 to n do
    Read(h[i]);
  wyn0 := licz;
  for i := 1 to n do
    wyn[i] := wyn0;
  for i := 1 to n - 1 do
    for j := i + 1 to n do
      if (j > i + 1) then
      begin
        pom := - zm_wart(h[i], i) - zm_wart(h[j], j)
               + zm_wart(h[i], j) + zm_wart(h[j], i);
        wyn[i] := min(wyn[i], wyn0 + pom);
        wyn[j] := min(wyn[j], wyn0 + pom)
      end (* if *)
      else
      begin
        wyn[i] := min(wyn[i], wyn0 + zm_wart1(i));
        wyn[j] := min(wyn[j], wyn0 + zm_wart1(i))
      end; (* else *)
  for i := 1 to n do
    WriteLn(wyn[i])
end. (* program *)
