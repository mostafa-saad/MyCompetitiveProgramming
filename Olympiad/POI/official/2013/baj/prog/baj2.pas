(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Bajtokomputer                                 *
 *   Autor:                Maciej Matraszek                              *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000010;
const INFI = 1000000000;

var DATA : array[0..MAXN] of longint;
    SUMS : array[0..MAXN] of longint;
    NNZ : array[0..MAXN] of longint; (* nastepny niezerowy element (indeks lub N) *)
    N : longint;

procedure compsums();
var
    i: longint;
begin
    SUMS[0] := DATA[0];
    for i:= 1 to N do
        SUMS[i] := DATA[i] + SUMS[i-1];

    NNZ[N] := N;
    for i := N-1 downto 0 do
    begin
        if (DATA[i] <> 0) then
            NNZ[i] := i
        else
            NNZ[i] := NNZ[i+1];
    end
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


{ Sprawdzamy liczbę -1, liczbę 0 zgadujemy. }
function check(l_1: longint) : longint;
var
    m, m1, m2: longint;
begin
    m := 0;

    { Poprawiamy -1 }
    if ((l_1 <> 0) and (DATA[0] <> -1)) then
        m := INFI;

    m += l_1 + sum(0, l_1);

    if ((l_1 = N) or (m >= INFI)) then
        check := m
    else
    begin
        m1 := m;
        m2 := m;

        { m1 = nie próbujemy 0 }
        m1 += check1(l_1);

        (* m2 -> znajdujemy najdłuższy przedział 0
         Poprawiamy pierwszy element *)
        if (DATA[l_1] <> 0) then
        begin
            if ((DATA[l_1] = 1) and (l_1 <> 0)) then
                m2 += 1
            else
                m2 := INFI;
        end;

        (* Pozycja końca samych 0 (tj. pierwszego nie-0) *)
        m2 += check1(NNZ[l_1+1]);

        if (m1 < m2) then
            check := m1
        else
            check := m2;
    end
end;

var
    tmp, wyn, i, l_1: longint;
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
        tmp := check(l_1);
        if (tmp < wyn) then
            wyn := tmp;
    end;

    if (wyn = INFI) then
        write('BRAK')
    else
        write(wyn);

    writeln();
end.

