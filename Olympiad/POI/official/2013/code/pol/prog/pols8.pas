(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Polaryzacja                                   *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n^4)                                        *
 *   Zlozonosc pamieciowa: O(n^3)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Programowanie dynamiczne                      *
 *                                                                       *
 *************************************************************************)

const MAX_N = 100;

var
    n, wynik, i, j, k, t : longint;

    (* krawedzie[kr_pocz[v] ... kr_kon[v]] to synowie
    wierzcholka v*)
    kr_pocz, kr_kon, kr_ile : array[1..MAX_N] of longint;
    kr_wszystkie : array[1..MAX_N] of array[1..2] of longint;
    krawedzie : array[1..2*MAX_N] of longint;

    vis : array[1..MAX_N] of boolean;
    stan : array[1..MAX_N] of array[1..MAX_N] of array[1..MAX_N] of longint;
(* stan[v][x][y] = m  oznacza,
 * ze jezeli w poddrzewie T ukorzenionym w v 
 * istnieje x sciezek postaci t ---> v
 * oraz     y sciezek postaci v ---> t,
 * gdzie t jest dowolnym wierzholkiem w poddrzewie T,
 * to m jest maksymalnym wynikiem czesciowym dla 
 * poddrzewa T. *)
    najlepszy : array[0..1] of array[1..MAX_N] of array[1..MAX_N] of longint;
(* najlepszy[0][v][x] : maksymalny wynik czesciowy dla
 * poddrzewa T ukorzenionego w v przy zalozeniu, ze istnieje w nim
 * x sciezek postaci v ---> t
 * najlepszy[1][v][x] :  --||-- postaci t ---> v *)


function max(a, b : longint) : longint;
begin
    if a > b then max := a
    else max := b;
end;

procedure dfs(v : longint);
var
    it, w, i, j, t, k, x, y : longint;
begin
    vis[v] := true;
    for i := 0 to 1 do
        najlepszy[i][v][1] := 0;
    stan[v][1][1] := 0;
    for it := kr_pocz[v] to kr_kon[v] do
    begin
        w := krawedzie[it];
        if not vis[w] then
        begin
            dfs(w);
            for i := n downto 1 do
                for j := n downto 1 do if stan[v][i][j] <> -1 then
                    for t := 0 to 1 do (* t = 1  ==>  krawedz skierowana do v *)
                        for k := 1 to n do
                            if najlepszy[t][w][k] <> -1 then
                            begin
                                x := i + t * k;
                                y := j + (1 - t) * k;
                                stan[v][x][y] := max(stan[v][x][y],
                                    stan[v][i][j] + najlepszy[t][w][k] + 
                                    t * k * j + (1 - t) * k * i);
                                najlepszy[0][v][y] := max(najlepszy[0][v][y], stan[v][x][y]);
                                najlepszy[1][v][x] := max(najlepszy[1][v][x], stan[v][x][y]);
                            end;
        end;
    end;

end;


procedure wczytaj;
var
    i, j, v, a, b : longint;
begin
    readln(n);
    if n > MAX_N then exit;
    
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
        krawedzie[kr_kon[a]] := b;
        krawedzie[kr_kon[b]] := a;
    end;
end;    

begin
    wczytaj;    
    if n > MAX_N then halt(1);
    wynik := 0;
   
    for i := 1 to n do
        for j := 1 to n do
        begin
            for k := 1 to n do
                stan[i][j][k] := -1;
            for t := 0 to 1 do
                najlepszy[t][i][j] := -1;
        end;
   
    for i := 1 to n do vis[i] := false;
    dfs(1);
    for i := 1 to n do
        wynik := max(wynik, najlepszy[0][1][i]);

    writeln(n - 1, ' ', wynik);
end.
