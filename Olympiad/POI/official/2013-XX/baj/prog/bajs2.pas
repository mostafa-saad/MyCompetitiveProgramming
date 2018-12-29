(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Bajtokomputer                                 *
 *   Autor:                Maciej Matraszek                              *
 *   Zlozonosc czasowa:    O(n^3)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Rozpatruje wszystkie pary                     *
 *                         (liczba_jedynek, liczba_zer)                  *
 *                         i dla każdej z nich symuluje operacje         *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000010;
const INFI = 100000000;

var DATA : array[0..MAXN] of longint;
    KOPIA : array[0..MAXN] of longint;
    N : longint;


{ Sprawdzamy liczbe -1 i liczbe 0. }
function check(l_1, l0: longint) : longint;
var
    m, i, l1s: longint;
begin
    m := 0;
    for i := 0 to N-1 do
        KOPIA[i] := DATA[i];

    { Poprawiamy -1 }
    if ((l_1 <> 0) and (KOPIA[0] <> -1)) then
        m := INFI;

    for i := 1 to l_1-1 do
    begin
        m += 1 + KOPIA[i];
        KOPIA[i] += KOPIA[i-1] * (1+KOPIA[i]);
    end;

     (* Poprawiamy pierwszy element *)
    if ((l0 <> 0) and (KOPIA[l_1] <> 0)) then
    begin
        if ((KOPIA[l_1] = 1) and (l_1 <> 0)) then
        begin
            m += 1;
            KOPIA[l_1] += KOPIA[l_1-1];
        end
        else
            m := INFI;
    end;

    { Sprawdzamy czy w pozostalym przedziale wystepuje nie-zero }
    for i := l_1 to l_1+l0-1 do
    begin
        if (KOPIA[i] <> 0) then
            m := INFI;
    end;

    l1s := l_1 + l0;
    if ((m = INFI) or ((l1s <> N) and (KOPIA[l1s] <> 1))) then
        m := INFI
    else
    begin
        if (l1s = 0) then
            l1s := 1;

        for i := l1s to N-1 do
        begin
            m += 1 - KOPIA[i];
            KOPIA[i] += KOPIA[i-1] * (1-KOPIA[i]);
        end;
    end;

    check := m;
end;

var
    tmp, wyn, i, l_1, l0: longint;
begin
    readln(N);
    for i := 0 to N-1 do
    begin
        read(tmp);
        DATA[i] := tmp;
    end;
    wyn := INFI;

    for l_1 := 0 to N do
    begin
        for l0 := 0 to N-l_1 do
        begin
            tmp := check(l_1, l0);
            if (tmp < wyn) then
                wyn := tmp;
        end;
    end;

    if (wyn = INFI) then
        write('BRAK')
    else
        write(wyn);

    writeln();
end.

