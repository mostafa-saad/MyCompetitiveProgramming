(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: DWU (Dwuszereg)                                *
 *   Plik:                dwus2.pas                                      *
 *   Autor:               Marcin Stefaniak                               *
 *   Opis:                Rozwiazanie nieoptymalne                       *
 *                        rozwi±zanie o koszcie O(n^2) (bez indeksowania *
 *                        pozycji wg wzrostu) zaimplementowane w Pascalu.*
 *                                                                       *
 *************************************************************************)

program Dwuszereg;

function min(x, y : longint) : longint;
begin
    if x < y then min := x else min := y;
end;

const MAX_N = 50000;        (* maksymalna liczba zolnierzy w szeregu *)
const MAX_W = 100000;        (* maksymalny wzrost zolnierza *)

var 
    wzrost : array[1..2, 1..MAX_N] of longint;        (* tablca wzrostow zolnierzy *)
    n : longint;        (* liczba zolnierzy w szeregu *)

procedure wczytajDane();
var i, j : longint;
begin
    read(n);
    for j := 1 to 2 do
        for i := 1 to n do 
                read(wzrost[j, i]);
end;

var p1, p2 : longint;

procedure znajdzPozycje(w : longint); 
var i : longint;
    first : boolean;
begin
    first := true; p2 := -1;
    for i := 1 to n do begin
        if wzrost[1][i] = w then begin
            if (first) then p1 := i else p2 := i;
            first := false;
        end;
        if wzrost[2][i] = w then begin
            if (first) then p1 := i else p2 := i;
            first := false;
        end;
    end;
end;


var
    ustalone : array[1..MAX_N] of boolean; (* czy pozycja juz jest ustalona *)
    z, bz, m : longint; (* liczba zamian, liczba biezacych zamian, wielkosc grupy *)
    tmp : longint;


procedure ustalajWzrost(w : longint);
var 
    konflikt : boolean;
begin
    while(true) do begin
        znajdzPozycje(w);
        if (p2 = -1) or (ustalone[p1] and ustalone[p2]) then
                break;
        if (ustalone[p2]) then begin
                tmp := p1; p1 := p2; p2 := tmp;
        end;
        konflikt := ((wzrost[1, p1] = w) and (wzrost[1, p2] = w))
                     or ((wzrost[2, p1] = w) and (wzrost[2, p2] = w));
        if (konflikt) then begin
            inc(bz);
            tmp := wzrost[1, p2]; wzrost[1, p2] := wzrost[2, p2]; wzrost[2, p2] := tmp;
        end;
        ustalone[p2] := true;
        inc(m);
        if (wzrost[1, p2] <> w) then
            w := wzrost[1, p2]
        else if (wzrost[2, p2] <> w) then
            w := wzrost[2, p2]
        else
            break;
    end;
end;

procedure ustalaj(k : longint);
begin
  bz := 0; m := 1;
  ustalone[k] := true;
  ustalajWzrost(wzrost[1, k]);
  ustalajWzrost(wzrost[2, k]);
end;

procedure ustalajZamiany();
var k : longint;
begin
    for k := 1 to n do
        ustalone[k] := false;
    z := 0; bz := 0;
    for k := 1 to n do 
        if not ustalone[k] then begin
            ustalaj(k);
            z := z + min(bz, m - bz);
        end;
end;

begin
    wczytajDane();
    ustalajZamiany();
    writeln(z);
end.