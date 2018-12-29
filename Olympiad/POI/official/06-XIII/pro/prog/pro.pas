(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PRO (Profesor Szu)                             *
 *   Plik:                pro.pas                                        *
 *   Autor:               Micha³ Adamaszek                               *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                                                                       *
 *************************************************************************)

program pro;

const NN = 1000001;                (* Liczba domkow *)
const MM = 1000000;                (* Liczba sciezek *)
const INF = 36501;

(* Reprezentacja grafu: tablica list sasiedztwa
   zaszyta w tablicy edge. Tablica firstEdge wskazuje
   na poczatek listy dla danego wierzcholka.

   Przechowujemy graf odwrocony wzgledem wejsciowego.

   Gmachowi przypisujemy numer 0 zamiast n+1
 *)
type TEdge = record
    v: longint;                (* wierzcholek docelowy *)
    next: longint;        (* indeks nastepnego elementu listy lub -1 *)
end;

var
    edge:          array [0..MM-1] of TEdge;
    firstEdge:     array [0..NN-1] of longint;
    n,m:           longint;
    reachable:     array [0..NN-1] of boolean; (* czy wierzcholek jest osiagalny z 0 *)
    inDeg, result: array [0..NN-1] of longint;

(*
 Wczytanie danych.
 *)
procedure input;
var
    i, v, w: longint;
begin
    read(n, m);

    (* inicjalizacja struktur danych *)
    for i := 0 to n do
    begin
        firstEdge[i] := -1;
        reachable[i] := false;
        inDeg[i] := 0;
        result[i] := 0;
    end;

    for i := 0 to m - 1 do
    begin
        read(v, w);
        if v = n+1 then v := 0;
        if w = n+1 then w := 0;

        (* zapamietujemy krawedz odwrotna *)
        edge[i].v := v;
        edge[i].next := firstEdge[w];
        firstEdge[w] := i;
    end
end;

(*
 BFS z wierzcholka 0 (gmachu) w celu znalezienia
 wierzcholkow osiagalnych.
 *)
procedure findReachable;
var
    qs, qe: longint;
    q: array [0..NN-1] of longint; (* obsluga kolejki *)
    v, w, pos: longint;

begin
    reachable[0] := true;
    q[0] := 0;
    qs := 0; qe := 1;

    while qs < qe do
    begin
        v := q[qs];
        Inc(qs);
        pos := firstEdge[v];
        while pos <> -1 do
        begin
            w := edge[pos].v;
            if not reachable[w] then
            begin
                q[qe] := w;
                Inc(qe);
                reachable[w] := true;
            end;
            pos := edge[pos].next;
        end
    end
end;

(*
 Oblicza stopnie wejsciowe wierzcholkow
 w zredukowanym grafie.
 *)
procedure computeInDeg;
var
    i, pos: longint;

begin
    for i := 0 to n do
    begin
        if reachable[i] then
        begin
            pos := firstEdge[i];
            while pos <> -1 do
            begin
                Inc(inDeg[ edge[pos].v ]);
                pos := edge[pos].next;
            end
        end
    end
end;

(*
 Dodaje do wyniki w wierzcholku v wynik wierzcholka w
 *)
procedure addResult(v, w: longint);
begin
    if result[w] = INF then
        result[v] := INF
    else begin
        result[v] := result[v] + result[w];
        if result[v] >= INF then
            result[v] := INF;
    end
end;

(*
 Przeglada po kolei wierzcholki o stopniu
 wejsciowym 0, oblicza dla nich wynik
 i zmniejsza stopnie wejsciowe ich sasiadom.
 Wierzcholki o stopniu 0 sa przechowywane w kolejce.

 W tablicy result sa obliczone wyniki dla wierzcholkow
 osiagalnych: INF oznacza 'zawsze', inna liczba - wynik.
 *)
procedure computeResult;
var
    qe, qs: longint;
    q: array[0..NN-1] of longint;        (* kolejka wierzcholkow stopnia 0 *)
    v, w, pos, i: longint;

begin
    (* sprawdzamy czy gmach jest stopnia zero,
       jesli nie to dla wszystkich osiagalnych jest INF *)
    if inDeg[0] <> 0 then
    begin
        for i := 0 to n do
            result[i] := INF;
    end

    else begin

    q[0] := 0;
    qs := 0; qe := 1;
    result[0] := 1;

    { bierzemy kolejne wierzcholki ktorych inDeg spadl do 0 }
    while qs < qe do
    begin
        v := q[qs];
        Inc(qs);

        pos := firstEdge[v];

        { uaktualniamy wartosci w nastepnikach }
        while pos <> -1 do
        begin
            w := edge[pos].v;
            { interesuja nas tylko osiagalne }
            if reachable[w] then
            begin
                addResult(w, v);
                Dec(inDeg[w]);
                { stopien w spadl do 0, przenosimy go do kolejki }
                if inDeg[w] = 0 then
                begin
                    q[qe] := w;
                    Inc(qe);
                end
            end;
            pos := edge[pos].next;
        end
    end;

    { wszystkim wierzcholkom ktorych stopnie wejsciowe
      nie spadly do zera zaznacz INF }
    for i := 0 to n do
        if inDeg[i] <> 0 then
            result[i] := INF;

    end
end;


(*
 Znajdz maksimum (rozpatrujemy tylko wierzcholki osiagalne)
 i wypisz wynik
 *)
procedure print;
var
    i, maxFound, maxCount: longint;

begin
    maxFound := 0;
    maxCount := 0;

    { znajdz max }
    for i := 1 to n do
        if reachable[i] then
            if result[i] > maxFound then
                maxFound := result[i];

    { znajdz liczbe maksow }
    for i := 1 to n do
        if reachable[i] and (result[i] = maxFound) then
            Inc(maxCount);

    {wypisz }
    if maxFound = INF then
        writeln('zawsze')
    else writeln(maxFound);

    writeln(maxCount);

    for i := 1 to n do
        if reachable[i] and (result[i] = maxFound) then
            write(i, ' ');
    writeln;
end;

(*
 Program glowny
 *)
begin
    input;
    findReachable;
    computeInDeg;
    computeResult;
    print;
end.
