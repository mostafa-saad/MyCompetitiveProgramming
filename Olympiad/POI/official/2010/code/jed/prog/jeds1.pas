(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Jedynki (JED)                                 *
 *   Plik:                 jeds1.pas                                     *
 *   Autor:                Przemyslaw Horban                             *
 *   Opis:                 Rozwiazanie powolne.                          *
 *   Zlozonosc czasowa:    O(R); R to liczba ktorej reprezentacja        *
 *                         wczytywana jest z wejscia                     *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *                                                                       *
 *************************************************************************)

const
    MAX_N = 1000000;
var
    n: Longint;

{ Hang function simulates a TLE in sinol }
procedure hang();
begin
    while true do { no-op };
end;

function readRep(): Longint;
var
    i, j, k, n, l, bits, bit: Longint;
begin
    l := 0;
    bit := 1;
    bits := 0;
    readln(n);
    for i := 1 to n do
    begin
        read(k);

        bits := bits + k;
        if bits > 30 then hang();

        for j := 1 to k do
            l := 2 * l + bit;
        bit := 1 - bit;
    end;
    readRep := l;
end;

procedure writeRep(l: Longint);
var
    bt, cnt : array [0..32] of Longint;
    i, j, bit : Longint;
begin
    if l > MAX_N then hang();
    j := 0;
    bt[j] := 0;
    cnt[j] := 0;
    for i := 30 downto 0 do
    begin
        bit := ((l shr i) and 1);
        if bit = bt[j] then
            inc(cnt[j])
        else
        begin
            inc(j);
            bt[j] := bit;
            cnt[j] := 1;
        end;
    end;
    writeln(j);
    for i := 1 to j do
    begin
        write(cnt[i]);
        if i = j then
            writeln('')
        else
            write(' ');
    end;
end;

function singleSKS(l: Longint): Longint;
var
    answ: Longint;
begin
    answ := 0;
    while l mod 2 = 0 do 
        l := l div 2;

    if l mod 4 = 1 then
        inc(answ);

    if l > 1 then
        while l <> 0 do
        begin
            l := l div 2;
            if l = 2 then
                inc(answ);
        end;

    singleSKS := answ;
end;

function sks(n: Longint): Longint;
var
    i, sum: Longint;
begin
    sum := 0;
    for i := 1 to n do
        sum := sum + singleSKS(i);
    sks := sum;
end;

BEGIN
    n := readRep();
    writeRep(sks(n));
END.
