(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Polaryzacja                                   *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(2^n * n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Sprawdzamy wszystkie mozliwe skierowania      *
 *                         krawedzi.                                     *
 *                                                                       *
 *************************************************************************)

const MAX_N = 100;

var
    n, wynik, mn, mx, i : longint;
    t : longword;
    (* t reprezentuje stan skierowania *)
    wyn : array[1..MAX_N] of longint;
    (* wynik dla poddrzewa *)

    (* krawedzie[kr_pocz[v] ... kr_kon[v]] to synowie
    wierzcholka v*)
    kr_pocz, kr_kon, kr_ile : array[1..MAX_N] of longint;
    kr_wszystkie : array[1..MAX_N] of array[1..2] of longint;
    krawedzie : array[1..2*MAX_N] of array[1..2] of longint;
    (* krawedz wychodzaca reprezentowana jako para
    (wierzcholek do ktorego prowadzi, indeks) *)

procedure dfs(v : longint);
var
    i : longint;
begin
    wyn[v] := 0;
    for i := kr_pocz[v] to kr_kon[v] do
        if (v < krawedzie[i][1]) = ((t and (1 << krawedzie[i][2])) <> 0) then
        begin
            if wyn[krawedzie[i][1]] = -1 then
                dfs(krawedzie[i][1]);
            wyn[v] := wyn[v] + 1 + wyn[krawedzie[i][1]];
        end;
    wynik := wynik + wyn[v]; 
end;


procedure wczytaj;
var
    i, j, v, a, b : longint;
begin
    readln(n);
    if n >= 32 then exit;
    
    for i := 1 to n do 
        kr_ile[i] := 0;

    for i := 1 to n - 1 do
        for j := 1 to 2 do
        begin
            read(v);
            kr_wszystkie[i][j] := v;
            Inc(kr_ile[v])
        end;
    kr_pocz[1] := 1;
    kr_kon[1] := 0;
    for i := 2 to n do
    begin
        kr_pocz[i] := kr_pocz[i - 1] + kr_ile[i - 1];
        kr_kon[i] := kr_pocz[i] - 1;
    end;
    for i := 1 to n - 1 do
    begin
        a := kr_wszystkie[i][1];
        b := kr_wszystkie[i][2];
        Inc(kr_kon[a]);
        Inc(kr_kon[b]);
        krawedzie[kr_kon[a]][1] := b;
        krawedzie[kr_kon[b]][1] := a;
        krawedzie[kr_kon[a]][2] := i;
        krawedzie[kr_kon[b]][2] := i;
    end;
end;    

begin
    wczytaj;    
    if n >= 32 then halt(1);
    mn := n * n;
    mx := 0;

    for t := 0 to (1 << n) do
    begin
        wynik := 0;
        for i := 1 to n do 
            wyn[i] := -1;
        for i := 1 to n do
            if wyn[i] = -1 then
                dfs(i);
        if wynik > mx then mx := wynik;
        if wynik < mn then mn := wynik;
    end;
    
    writeln(mn, ' ', mx);
end.
