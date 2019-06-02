(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Morskie opowiesci                             *
 *   Autor:                Mateusz Baranowski                            *
 *   Zlozonosc czasowa:    O(k * n^3 * log d)                            *
 *   Zlozonosc pamieciowa: O(n^2 + k)                                    *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Mnozenie macierzy                             *
 *                                                                       *
 *************************************************************************)

const MAX_K = 1000000;
      MAX_N = 10000;

type opowiesc_t = record
        u, v : longint;
        len : longint;
    end;

var opowiesci : array[1..MAX_K] of opowiesc_t;
    index : array[1..MAX_K] of longint;

procedure quick_sort(a, b : longint);
var l, m, r, c, tmp : longint;
begin
    l := a + random(b - a);
    tmp := index[l];
    c := opowiesci[tmp].len;
    index[l] := index[a];
    index[a] := tmp;
    l := a;
    r := b;
    m := a + 1;
    while m <= r do
    begin
        if c < opowiesci[index[m]].len then
        begin
            tmp := index[m];
            index[m] := index[r];
            index[r] := tmp;
            r := r - 1;
        end else if c = opowiesci[index[m]].len then
        begin
            m := m + 1;
        end else begin
            tmp := index[m];
            index[m] := index[l];
            index[l] := tmp;
            l := l + 1;
        end;
    end;
    if a < l - 1 then quick_sort(a, l - 1);
    if r + 1 < b then quick_sort(r + 1, b);
end;

procedure pomnoz(n : longint; var A, B : array of boolean);
var C : array of boolean;
    i, j, k : longint;
begin
    setlength(C, n * n);
    for i := 0 to n * n - 1 do C[i] := false;
    for i := 0 to n - 1 do
    begin
        for j := 0 to n - 1 do
        begin
            for k := 0 to n - 1 do
            begin
                C[i * n + j] := C[i * n + j] or (A[i * n + k] and B[k * n + j]);
            end;
        end;
    end;
    for i := 0 to n * n - 1 do A[i] := C[i];
end;

var
    n, m, k, i, a, b : longint;
    x, z, potega, len : longint;
    base, path, tab : array of boolean;
    mozliwe : array[1..MAX_K] of boolean;

Begin
    randomize;
    readln(n, m, k);
    setlength(base, n*n);
    setlength(path, n*n);
    setlength(tab, n*n);
    for i := 0 to n * n - 1 do
    begin
            base[i] := false;
            path[i] := false;
            tab[i] := false;
    end;
    while m > 0 do
    begin
        readln(a, b);
        a := a - 1;
        b := b - 1;
        base[a * n + b] := true;
        base[b * n + a] := true;
        path[a * n + b] := true;
        path[b * n + a] := true;
        m := m - 1;
    end;
    for i := 1 to k do
    begin
        readln(opowiesci[i].u, opowiesci[i].v, opowiesci[i].len);
        opowiesci[i].u := opowiesci[i].u - 1;
        opowiesci[i].v := opowiesci[i].v - 1;
        index[i] := i;
    end;
    quick_sort(1, k);
    potega := 1;
    for i := 1 to k do
    begin
        len := opowiesci[index[i]].len;
        if len <> potega then
        begin
            z := len - potega;
            for x := 0 to n * n - 1 do tab[x] := base[x];
            while z > 0 do
            begin
                if z mod 2 = 1 then
                begin
                    z := z - 1;
                    pomnoz(n, path, tab);
                end else begin
                    z := z div 2;
                    pomnoz(n, tab, tab);
                end;
            end;
            potega := len;
        end;
        mozliwe[index[i]] := path[opowiesci[index[i]].u * n + opowiesci[index[i]].v];
    end;
    for i := 1 to k do
        if mozliwe[i] then
            writeln('TAK')
        else
            writeln('NIE');
End.
