(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Bajtokomputer                                 *
 *   Autor:                Maciej Matraszek                              *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Rozpatruje wszystkie pary                     *
 *                         (liczba_jedynek, liczba_zer)                  *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000010;
const INFI = 100000000;

var DATA : array[0..MAXN] of longint;
    SUMS : array[0..MAXN] of longint; (* Sumy prefiksowe *)
    ILE0 : array[0..MAXN] of longint; (* Sumy prefiksowe liczby zer. *)
    N : longint;

procedure compsums();
var
    i: longint;
begin
    SUMS[0] := DATA[0];
    if (DATA[0] = 0) then
        ILE0[0] := 1
    else
        ILE0[0] := 0;

    for i:= 1 to N do
    begin
        SUMS[i] := DATA[i] + SUMS[i-1];
        ILE0[i] := ILE0[i-1];
        if (DATA[i] = 0) then
            ILE0[i] += 1;
    end;
end;

{ Suma na [a, b), assert(a <= b) }
function sum(a, b: longint) : longint;
begin
    if a > 0 then
        sum := SUMS[b-1] - SUMS[a-1]
    else
    begin
        if b > 0 then
            sum := SUMS[b-1]
        else
            sum := 0;
    end;
end;

{ Liczba 0 na [a, b), assert(a <= b) }
function zeros(a, b: longint) : longint;
begin
    if a > 0 then
        zeros := ILE0[b-1] - ILE0[a-1]
    else
    begin
        if b > 0 then
            zeros := ILE0[b-1]
        else
            zeros := 0;
    end;
end;

{ Sprawdza czy mozna dokonczyc jedynkami [l1s, N) }
function check1(l1s: longint) : longint;
var
    l1 : longint;
begin
    l1 := N - l1s;
    if ((l1 = 0) or ((l1 <> 0) and (DATA[l1s] = 1))) then
        check1 := l1 - sum(l1s, N)
    else
        check1 := INFI;
end;


{ Sprawdzamy liczbe -1 i liczbe 0. }
function check(l_1, l0: longint) : longint;
var
    m: longint;
begin
    m := 0;

    { Poprawiamy -1 }
    if ((l_1 <> 0) and (DATA[0] <> -1)) then
        m := INFI;

    m += l_1 + sum(0, l_1);

     (* Poprawiamy pierwszy element *)
    if ((l0 <> 0) and (DATA[l_1] <> 0)) then
    begin
        if ((DATA[l_1] = 1) and (l_1 <> 0)) then
            m += 1
        else
            m := INFI;
    end;

    { Sprawdzamy czy w pozostalym przedziale wystepuje nie-zero }
    if ((l0 <> 0) and (zeros(l_1+1, l_1+l0) <> l0-1)) then
         m := INFI;

    (* Pozycja konca samych 0 (tj. pierwszego nie-0) *)
    m += check1(l_1 + l0);

    check := m
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
    compsums();
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

