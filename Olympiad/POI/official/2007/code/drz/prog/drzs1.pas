{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Drzewa (DRZ)                                               *}
{*   Plik:    drzs1.pas                                                  *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Rozwiazanie zbyt wolne: zlozonosc czasowa: O(n^3),         *}
{*            zlozonosc pamieciowa: O(n)                                 *}
{*                                                                       *}
{*************************************************************************}
const MAX_N = 50000;

var
  n, i, j : LongInt;
  h : array[1..MAX_N] of LongInt;
  wyn, wsp : Int64;


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

procedure swap(var x, y : LongInt);
var
  z : LongInt;
begin
  z := x;
  x := y;
  y := z
end; (* swap *)

function min(x, y : Int64) : Int64;
begin
  if x < y then
    min := x
  else
    min := y
end; (* min *)

begin
  ReadLn(n);
  for i := 1 to n do
    Read(h[i]);
  wsp := licz;
  for i := 1 to n do begin
    wyn := wsp;
    for j := 1 to n do
    begin
      swap(h[i], h[j]);
      wyn := min(wyn, licz);
      swap(h[i], h[j])
    end; (* for *)
    WriteLn(wyn)
  end (* for *)
end. (* program *)
