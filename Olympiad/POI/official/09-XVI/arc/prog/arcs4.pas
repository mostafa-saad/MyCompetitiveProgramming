{*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arc2.pas                                                   *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie nieefektywne czasowo.                          *}
{*            Wyszukuje w czasie liniowym pierwsza niemotonicznosc.      *}
{*            Zlozonosc obliczeniowa: O(n * k)                           *}
{*                                                                       *}
{*************************************************************************}

uses
    parclib;

const
    MAX_K = 1000000; // maksymalna dlugosc szukanego podciagu

type element = ^elem;
     elem = record
        val : longint;
        nex, pre : element;
     end;

    list = record
        begin_ele, end_ele : element;
     end; 

var
    i, a, k : longint;
    cen : element;
    // lista reprezentujaca szukany podciag
    sub : list;

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
    ele^.pre := l.end_ele;
    ele^.nex := NIL;
    ele^.val := _val;
    if l.end_ele <> NIL then
        l.end_ele^.nex := ele;
    if l.begin_ele = NIL then
        l.begin_ele := ele;
    l.end_ele := ele;
    list_push_back := ele;
end;

{ Usuwa element z listy na ktory wskazuje wskaznik [ele] }
procedure list_erase(var l : list; ele : element);
begin
    if ele^.pre <> NIL then
        ele^.pre^.nex := ele^.nex;
    if ele^.nex <> NIL then
        ele^.nex^.pre := ele^.pre;
    if l.begin_ele = ele then
        l.begin_ele := ele^.nex;
    if l.end_ele = ele then
        l.end_ele := ele^.pre;
    dispose(ele);
end;

{ Wypisuje liste od poczatku do konca i zarazem zwalnia zadeklarowana na jej 
  elementy pamiec }
procedure list_print(var l : list);
var
    il, tmp : element;
    a : longint;
begin
    il := l.begin_ele;
    while(il <> NIL)do
    begin
        a := il^.val;
        tmp := il^.nex;
        list_erase(l, il);
        il := tmp;
        wypisz(a);
    end;
end;

begin
    k := inicjuj();
    list_init(sub);
    for i := 0 to k - 1 do
        list_push_back(sub, 0);
    a := wczytaj();
    while(a <> 0)do
    begin
        list_push_back(sub, a);
        cen := sub.begin_ele;
        while(cen^.nex <> NIL)do
        begin
            if cen^.val < cen^.nex^.val then
                break;
            cen := cen^.nex;
        end;
        list_erase(sub, cen);
        a := wczytaj();
    end;
    list_print(sub);
end.
