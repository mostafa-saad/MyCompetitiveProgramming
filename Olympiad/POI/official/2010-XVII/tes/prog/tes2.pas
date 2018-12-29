(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Test na inteligencję (TES)                       *
 *   Plik:              tes2.pas                                         *
 *   Autor:             Bartosz Górski                                   *
 *   Opis:              Rozwiązanie wzorcowe.                            *
 *   Złożoność czasowa: O(m + l + |A|)                                   *
 *   Kodowanie znaków:  UTF-8                                            *
 *                                                                       *
 *************************************************************************)

const
    MAX_M = 1000000; // maksymalna długość ciągu a_i
    MAX_A = 1000000; // maksymalny wyraz ciągu

type element = ^elem; 
     elem = record // element listy
        val : longint;
        nex : element;
     end;

    list = record // lista
        begin_ele, end_ele : element;
     end; 

var
    m, n, k, w, i, j : longint;
    a : array [0..MAX_M - 1] of longint;
    tmp : list;
    b : array [0..MAX_M - 1] of list;
    nr : array [0..MAX_A - 1] of list;

{ Inicjuje liste }
procedure list_init(var l : list);
begin
    l.begin_ele := NIL;
    l.end_ele := NIL;
end;

{ Sprawdza czy lista jest pusta }
function list_empty(var l : list) : boolean;
begin
    if l.begin_ele = NIL then
        list_empty := true
    else
        list_empty := false;
end;

{ Dodaje [_val] na koniec listy }
function list_push_back(var l : list; _val : longint) : element;
var
    ele : element;
begin
    new(ele);
    ele^.nex := NIL;
    ele^.val := _val;
    if l.end_ele <> NIL then
        l.end_ele^.nex := ele;
    if l.begin_ele = NIL then
        l.begin_ele := ele;
    l.end_ele := ele;
    list_push_back := ele;
end;

{ Usuwa element z początku listy }
procedure list_pop_front(var l : list);
var
    ele : element;
begin
    ele := l.begin_ele;
    if l.end_ele = ele then
        l.end_ele := NIL;
    l.begin_ele := l.begin_ele^.nex;
    dispose(ele);
end;

{ Kasuje zawartość listy }
procedure list_clear(var l : list);
var
    il : element;
begin
    il := l.begin_ele;
    while(il <> NIL)do
    begin
        il := il^.nex;
        list_pop_front(l);
    end;
end;

{ Zamiana dwóch list }
procedure list_swap(var l1, l2 : list);
var
    l3 : list;
begin
    l3.begin_ele := l1.begin_ele;
    l3.end_ele := l1.end_ele;
    l1.begin_ele := l2.begin_ele;
    l1.end_ele := l2.end_ele;
    l2.begin_ele := l3.begin_ele;
    l2.end_ele := l3.end_ele;
end;

begin

    for i := 0 to MAX_A - 1 do
        list_init(nr[i]);

    // wczytanie ciągu a_i
    readln(m);
    for i := 0 to m - 1 do
        read(a[i]);
    readln;

    // wczytanie wszystkich zapytań
    readln(n);
    for i := 0 to n - 1 do
    begin
        readln(k);
        list_init(b[i]);
        for j := 0 to k - 1 do
        begin
            read(w);
            list_push_back(b[i], w);
        end;
        list_push_back(nr[b[i].begin_ele^.val - 1], i);
    end;

    list_init(tmp);
    for i := 0 to m - 1 do
    begin
        list_clear(tmp);
        list_swap(tmp, nr[a[i] - 1]);
        while not list_empty(tmp) do
        begin
            list_pop_front(b[tmp.begin_ele^.val]);
            if not list_empty(b[tmp.begin_ele^.val]) then
                list_push_back(nr[b[tmp.begin_ele^.val].begin_ele^.val - 1],
                    tmp.begin_ele^.val);
            list_pop_front(tmp);
        end;
    end;

    for i := 0 to n - 1 do
    begin
        if list_empty(b[i]) then
            writeln('TAK')
        else begin
            writeln('NIE');
            list_clear(nr[b[i].begin_ele^.val - 1]);
            list_clear(b[i]);
        end;
    end;
end.

