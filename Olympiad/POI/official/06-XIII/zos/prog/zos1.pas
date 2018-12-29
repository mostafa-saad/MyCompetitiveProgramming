(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ZOS (Zosia)                                    *
 *   Plik:                zos1.pas                                       *
 *   Autor:               Krzysztof Dulêba                               *
 *   Opis:                Rozwiazanie wzorcowe.                          *
 *                                                                       *
 * Cel: znalezc minimalne pokrycie wierzcholkowe w grafie,               *
 * z gornym ograniczeniem na rozmiar tego pokrycia wynoszacym 10.        *
 *                                                                       *
 * Rozwiazanie: nalezy wziac wszystkie wierzcholki duzych stopni,        *
 * a na reszcie puscic backtracking.                                     *
 *                                                                       *
 *************************************************************************)

Program Zosia_2;

const
    GRAPH_SIZE          = 1000001;
    MAX_L               = 11;
    REDUCED_GRAPH_SIZE  = (MAX_L * MAX_L * 2 + 1);


{ Lista sasiedztwa }
type 
    PList = ^TList;
    TList = 
        record
            item : LongInt;
            next : PList;
        end;


{ Definicje przydatnych typow }
type
    ListArray   = array[1..GRAPH_SIZE] of PList;
    IntArray    = array[1..GRAPH_SIZE] of LongInt;
    BoolArray   = array[1..GRAPH_SIZE] of Boolean;


{ Zmienne globalne }
var
    n, m, k, l  : LongInt;
    curr_n      : LongInt;

    { graf zadany jako listy sasiedztwa }
    graph       : ListArray;

    { ktore wierzcholki sa w pokryciu }
    res         : BoolArray;
    
    { stopnie wierzcholkow grafu }
    graph_sz    : IntArray;
    sortTab     : array[1..(GRAPH_SIZE * 2)] of LongInt;

    { wierzcholki o dodatnim stopniu, ale za malym, by je usunac }
    { jako wierzcholki duzego stopnia                            }
    avail_nodes : array[1..REDUCED_GRAPH_SIZE] of LongInt;

    erased_nodes: array[1..REDUCED_GRAPH_SIZE] of Boolean;

    { mapowanie z numeracji w pelnym grafie do obcietego }
    id2pos      : array[1..GRAPH_SIZE] of LongInt;



{ Wstaw element na liste }
procedure insert(var list : PList; item : LongInt);
var newHead : PList;
begin
    new(newHead);
    newHead^.item := item;
    newHead^.next := list;

    list := newHead;
end;



{ Quick Sort }
procedure sort(p, q : LongInt);
var
    v, i, j, t : LongInt;
begin
    if (p >= q) then exit;
    v := sortTab[p];
    i := p + 1;
    j := q;
    repeat
        while (i < q) and (sortTab[i] <= v) do inc(i);
        while (j > p) and (sortTab[j] > v) do dec(j);

        if(i < j) then begin
            t := sortTab[i];
            sortTab[i] := sortTab[j];
            sortTab[j] := t;
        end;
    until (i >= j);
    t := sortTab[p];
    sortTab[p] := sortTab[j];
    sortTab[j] := t;
    if (j - 1 > p) then sort(p, j - 1);
    if (j + 1 < q) then sort(j+1, q);
end;



{ Usun zdublowane elementy z listy }
procedure unique(idx : LongInt);
var
    list     : PList;
    i, sz       : LongInt;
begin
    list := graph[idx];
    sz := 0;

    while(list <> nil) do begin
        inc(sz);
        sortTab[sz] := list^.item;
        list := list^.next;
    end;
    
    sort(1, sz);

    list := graph[idx];
    i := 0;
    while(i < sz) do begin
        inc(i);
        list^.item := sortTab[i];
        list := list^.next;
    end;
    list := graph[idx];

    while(list <> nil) do begin
        if((list^.next <> nil) and (list^.next^.item = list^.item)) then begin
            dec(sz);
            list^.next := list^.next^.next;
        end else
            list := list^.next;
    end;
    graph_sz[idx] := sz;
end;



{ Wczytaj dane wejsciowe }
procedure readInput;
var
    i, p, q : LongInt;
begin
    read(n, k, m);
    for i := 1 to n do begin
        graph[i] := nil;
        graph_sz[i] := 0;
        res[i] := false;
    end;

    for i := 1 to m do begin
        read(p, q);
        insert(graph[p], q);
        insert(graph[q], p);
    end;
    
    for i := 1 to n do unique(i);

    l := n - k;
end;



{ Usun wierzcholki duzego stopnia }
procedure eraseBig;
var
    i, erased   : LongInt;
    list, prev  : PList;
begin
    erased := 0;
    for i := 1 to n do begin
        if (graph_sz[i] > l) then begin
            res[i] := true;
            graph[i] := nil;
            graph_sz[i] := 0;
            inc(erased);
        end;
    end;

    { usun krawedzie, ktorych jeden z koncow jest w pokryciu }
    curr_n := 0;
    for i := 1 to n do begin
        if (res[i] = true) then continue;
        list := graph[i];
        prev := nil;
        while (list <> nil) do begin
            if (res[list^.item] = true) then begin
                if(prev = nil) then begin
                    graph[i] := list^.next;
                    dec(graph_sz[i]);
                end else
                    prev^.next := list^.next;
            end else
                prev := list;

            list := list^.next;
        end;

        if(graph_sz[i] > 0) then begin
            inc(curr_n);
            avail_nodes[curr_n] := i;
            id2pos[i] := curr_n;
            if ( curr_n > l * l * 2 ) then begin
                writeln('NIE');
                Exit;
            end;
        end;
    end;
    
    l := l - erased;

    for i := 1 to REDUCED_GRAPH_SIZE do erased_nodes[i] := false;
end;


{ Backtracking                                                          }
{ Bierzemy kolejno krawedzie w grafie. Ktorys z koncow musi lezec       }
{ w pokryciu. Sprawdzamy obie mozliwosci i wybieramy lepsza.            }
{ Gdy depth spanie ponizej zera, to w pokryciu jest juz za duzo         }
{ wierzcholkow i przeszukiwanie przerywamy.                             }
function backtrack(idx : LongInt; edge : PList; depth : LongInt) : LongInt;
var
    i, edge_end             : LongInt;
    orig_erased_nodes       : array[1..REDUCED_GRAPH_SIZE] of Boolean;
    c1, c2                  : LongInt;
    sol1                    : array[1..REDUCED_GRAPH_SIZE] of Boolean;
begin
    if(depth < 0) then exit(-1);
    if(idx > curr_n) then exit(0);

    if(not erased_nodes[idx]) then begin
        while(edge <> nil) do begin
            edge_end := edge^.item;
            if(erased_nodes[id2pos[edge_end]] = true) then begin
                edge := edge^.next;
                continue;
            end;
            
            for i := 1 to REDUCED_GRAPH_SIZE do orig_erased_nodes[i] := erased_nodes[i];

            erased_nodes[idx] := true;
            c1 := backtrack(idx + 1, graph[avail_nodes[idx + 1]], depth - 1);
            for i := 1 to REDUCED_GRAPH_SIZE do sol1[i] := erased_nodes[i];

            for i := 1 to REDUCED_GRAPH_SIZE do erased_nodes[i] := orig_erased_nodes[i];
            erased_nodes[id2pos[edge_end]] := true;
            c2 := backtrack(idx, edge^.next, depth - 1);

            if( c1 > c2) then begin
                c2 := c1;
                for i := 1 to REDUCED_GRAPH_SIZE do erased_nodes[i] := sol1[i];
            end;
            exit(c2);
        end;
    end;

    if(idx + 1 <= curr_n) then begin c2 := backtrack(idx + 1, graph[avail_nodes[idx + 1]], depth); end
    else begin c2 := 0; end;
    if((c2 >= 0) and (not erased_nodes[idx])) then inc(c2);
    exit(c2);
end;


{ przetworz wynik backtrackingu i wypisz odpowiedz }
procedure postBacktrack;
var
    i, res_count : LongInt;
begin
    for i := 1 to curr_n do begin
        if ( erased_nodes[i] = true) then res[avail_nodes[i]] := true;
    end;

    res_count := n;
    for i := 1 to n do begin
        if(res[i] = true) then dec(res_count);
    end;

    if(res_count < k) then begin
        writeln('NIE');
        Exit;
    end;

    writeln(res_count);

    for i := 1 to n do begin
        if(res[i] = false) then write(i, ' ');
    end;
    writeln;
end;


{ Glowna funkcja programu }
begin
    readInput;
    eraseBig;
    if ( curr_n > 0) then backtrack(1, graph[avail_nodes[1]], l);
    postBacktrack;
end.
