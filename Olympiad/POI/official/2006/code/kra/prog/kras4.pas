(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: KRA (Kr±¿ki)                                   *
 *   Plik:                kras4.pas                                      *
 *   Autor:               Micha³ Adamaszek                               *
 *   Opis:                Nieoptymalne rozwiazanie zadania Krazki,       *
 *                        Brutalna symulacja.                            *
 *                        Zlozonosc: O(m*n)                              *
 *                                                                       *
 *************************************************************************)

const MAX_N = 1000000;

var
n, m: longint;

(* Szerokosci walcow w rurce *)
szer: array[0..MAX_N] of longint;

(* Wczytanie danych *)
procedure readData;
var
    i: longint;
begin
    read(n, m);

    for i := 0 to n - 1 do
        read(szer[i]);
end;

(* Algorytm, dla kazdego krazka jedziemy od gory *)
function compute: longint;
var
    i, j, dno, krazek: longint;
begin
    dno := n + 1;
    for i := 0 to m - 1 do
    begin
        read(krazek);
        j := 0;
        while (j < dno) and (szer[j] >= krazek) do inc(j);
        dno := j - 1;
    end;

    compute := dno + 1;
end;

(* Program *)
begin
    readData;
    writeln(compute);
end.
