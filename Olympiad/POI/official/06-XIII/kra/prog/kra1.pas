(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: KRA (Kr±¿ki)                                   *
 *   Plik:                kra1.pas                                       *
 *   Autor:               Micha³ Adamaszek                               *
 *   Opis:                Rozwiazanie wzorcowe zadania Krazki,           *
 *                        Zlozonosc: O(n+m)                              *
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
    read(n,m);
    szer[0] := INF;
    for i := 1 to n do
    begin
        read(sz);
        if szer[i-1] < sz then szer[i] := szer[i-1]
        else szer[i] :=  sz;
    end;
    szer[n + 1] := 0;
end;

(* Algorytm, zaczynamy od dolu rurki, i dodajemy
   kolejne krazki posuwajac sie do gory *)
function compute: longint;
var
    i, pos, krazek: longint;
begin
    pos := n + 1;
    for i := 0 to m - 1 do
    begin
        read(krazek);
        if pos > 0 then dec(pos);
        while szer[pos] < krazek do dec(pos);
    end;
    compute := pos;
end;

(* Program *)
begin
    readData;
    writeln(compute());
end.
