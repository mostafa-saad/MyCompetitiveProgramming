(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: KRA (Kr±¿ki)                                   *
 *   Plik:                kras2.pas                                      *
 *   Autor:               Micha³ Adamaszek                               *
 *   Opis:                Nieoptymalne rozwiazanie zadania Krazki,       *
 *                        Wyszukiwanie binarne pozycj nastepnego krazka. *
 *                        Zlozonosc: O(m*log(n))                         *
 *                                                                       *
 *************************************************************************)

const MAX_N = 1000000;
const INF = 2000000000;

var
n, m: longint;

(* Najwieksza szerokosc krazka jaki moze
   doleciec do danej glebokosci *)
szer: array[0..MAX_N + 1] of longint;

(* Wczytanie danych i obliczenie minimalnych szerokosci *)
procedure readData;
var
    i, sz: longint;
begin
    read(n, m);

    szer[0] := INF;
    for i := 1 to n do
    begin
        read(sz);
        if szer[i-1] < sz then szer[i] := szer[i-1]
        else szer[i] := sz;
    end;
    szer[n + 1] := 0;
end;

(* Wyszukiwanie binarne *)
function binary(pocz, kon, krazek: longint): longint;
var
    half: longint;
begin
    if pocz = kon then binary := pocz

    else begin
        half := (pocz + kon + 1) div 2;
        if szer[half] >= krazek then binary := binary(half, kon, krazek)
        else binary := binary(pocz, half - 1, krazek);
    end
end;

(* Algorytm, zaczynamy od dolu rurki, przy dodawaniu
   kolejnego kraza wyszukujemy binarnie jego pozycje *)
function compute: longint;
var
    i, pos, krazek: longint;
begin
    pos := n + 1;
    i := 1;
    while (pos <> 0) and (i <= m) do
    begin
        read(krazek);
        pos := binary(0, pos - 1, krazek);
        inc(i);
    end;

    compute := pos;
end;

(* Program *)
begin
    readData;
    writeln(compute);
end.
