(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Polaryzacja                                   *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Nieefektywnie liczymy problem plecakowy       *
 *                                                                       *
 *************************************************************************)

const MAX_N = 250000;

var
    n, i, centroid : longint;
    wynik, h : int64;
    (* sz - wielkosc poddrzewa, p - rodzic *)
    sz, p : array[1..MAX_N] of longint; 
    (* wielkosci poddrzew synow centroidu*)
    wielk : array[1..MAX_N] of longint;
    lb_synow : longint;

    (* krawedzie[kr_pocz[v] ... kr_kon[v]] to synowie
    wierzcholka v*)
    kr_pocz, kr_kon, kr_ile : array[1..MAX_N] of longint;
    kr_wszystkie : array[1..MAX_N] of array[1..2] of longint;
    krawedzie : array[1..2*MAX_N] of longint;

    (* Tablica do plecaka *)
    mozliwe : array[0..MAX_N-1] of boolean;

procedure dfs(v : longint);
var
    i, w : longint;
begin
    sz[v] := 1;
    for i := kr_pocz[v] to kr_kon[v] do
        begin
            w := krawedzie[i];
            if sz[w] = 0 then
            begin
                dfs(w);
                p[w] := v;
                sz[v] := sz[v] + sz[w];
                wynik := wynik + int64(sz[w]);
            end;
        end;
end;

function znajdz_centroid(v : longint) : longint;
var
    i, w : longint;
begin
    for i := kr_pocz[v] to kr_kon[v] do
        begin
            w := krawedzie[i];
            if (sz[w] * 2 > n) and (w <> p[v]) then
            begin
                znajdz_centroid := znajdz_centroid(w);
                exit;
            end
        end;
    znajdz_centroid := v
end;

procedure dodaj(x : longint);
var
    i : longint;
begin
    for i := n - 1 downto 0 do
        if mozliwe[i] then mozliwe[i + x] := true
end;


function blisko_polowy : longint;
(* Rozwiazuje problem plecakowy.
    Zwraca liczbe h taka, ze
    suma wielkosci poddrzew pewnych synow centroidu
    jest rowna h oraz |2 * h - (n - 1)| jest minimalne *)
var
    h, i : longint;
begin
    h := 0;
    
    mozliwe[0] := true;
    for i := 1 to n - 1 do 
        mozliwe[i] := false;

    for i := 1 to lb_synow do
        dodaj(wielk[i]);

    i := 0;
    while 2 * i <= n - 1 do
    begin
        if mozliwe[i] then h := i;
        Inc(i);
    end;

    blisko_polowy := h;
end;

procedure wczytaj;
var
    i, j, v, a, b : longint;
begin
    readln(n);
    
    for i := 1 to n do (* zerowanie tablic *)
    begin
        sz[i] := 0;
        kr_ile[i] := 0;
        wielk[i] := 0;
    end;

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
        krawedzie[kr_kon[a]] := b;
        krawedzie[kr_kon[b]] := a;
    end;
end;    

begin
    wczytaj;    
    p[1] := -1;
    dfs(1);
    centroid := znajdz_centroid(1);

    for i := 1 to n do
        sz[i] := 0;
    
    wynik := 0;
    dfs(centroid); (* Obliczenie wielkosci poddrzew *)

    lb_synow := 0;
    for i := kr_pocz[centroid] to kr_kon[centroid] do
    begin
        Inc(lb_synow);
        wielk[lb_synow] := sz[krawedzie[i]];
    end;

    h := blisko_polowy;
    wynik := wynik + h * int64((n - 1) - h);
    writeln(n - 1, ' ', wynik);

end.
