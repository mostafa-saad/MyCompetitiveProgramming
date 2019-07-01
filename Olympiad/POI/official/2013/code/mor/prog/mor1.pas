(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Morskie opowiesci                             *
 *   Autor:                Mateusz Baranowski                            *
 *   Zlozonosc czasowa:    O(n(n + m) + k)                               *
 *   Zlozonosc pamieciowa: O(n + m + k)                                  *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                         Dla kazdego wierzcholka szukamy najkrotszej   *
 *                         sciezki dlugosci parzystej i nieparzystej     *
 *                                                                       *
 *************************************************************************)

const MAX_N = 10000;
const MAX_M = 10000;
const MAX_K = 1000000;
const INFTY = 1000000000;


type przygody_t = record
        u, v : longint;
        len : longint;
    end;

type stack_p = ^stack_t;
     stack_t = record
        v : longint;
        next : stack_p;
     end;

procedure push(var s : stack_p; v : longint);
var tmp : stack_p;
begin
    new(tmp);
    tmp^.v := v;
    tmp^.next := s;
    s := tmp;
end;

function pop(var s : stack_p) : longint;
var tmp : stack_p;
begin
    tmp := s^.next;
    pop := s^.v;
    dispose(s);
    s := tmp;
end;

var
    n, m, k : longint;
    szlaki : array[1..MAX_N] of stack_p;
    przygody : array[1..MAX_K] of przygody_t;
    wyniki : array[1..MAX_K] of boolean;

procedure wczytaj_dane;
var i, u, v, len : longint;
begin
    for i := 1 to n do szlaki[i] := nil;
    readln(n, m, k);
    for i := 1 to m do
    begin
        readln(u, v);
        push(szlaki[u], v);
        push(szlaki[v], u);
    end;
    for i := 1 to k do
    begin
        readln(u, v, len);
        przygody[i].u := u;
        przygody[i].v := v;
        przygody[i].len := len;
    end;
end;

procedure sprawdz_przygody;
var poczatek: array[1..MAX_N] of stack_p;
    r, d, u, v, i, l : longint;
    odl : array[0..1, 1..MAX_N] of longint;
    stack : array[0..1] of stack_p;
    it : stack_p;
begin
    for i := 1 to n do poczatek[i] := nil;
    for i := 1 to k do
    begin
        u := przygody[i].u;
        v := przygody[i].v;
        if poczatek[u] = nil then
            push(poczatek[v], i)
        else
            push(poczatek[u], i);
    end;
    for i := 1 to n do
    begin
        for l := 1 to n do
        begin
            odl[0][l] := INFTY;
            odl[1][l] := INFTY;
        end;
        if poczatek[i] <> nil then
        begin
            { odl[0][i] := 0; }
            stack[0] := nil;
            stack[1] := nil;
            push(stack[0], i);
            r := 0;
            d := 1;
            while stack[r] <> nil do
            begin
                u := pop(stack[r]);
                it := szlaki[u];
                while it <> nil do
                begin
                    if odl[1 - r][it^.v] = INFTY then
                    begin
                        odl[1 - r][it^.v] := d;
                        push(stack[1 - r], it^.v);
                    end;
                    it := it^.next;
                end;
                if stack[r] = nil then
                begin
                    r := 1 - r;
                    d := d + 1;
                end;
            end;
        end;
        it := poczatek[i];
        while it <> nil do
        begin
            d := przygody[it^.v].len;
            u := przygody[it^.v].u;
            if u = i then u := przygody[it^.v].v;
            wyniki[it^.v] := (odl[d mod 2][u] <= d);
            it := it^.next;
        end;
    end;
end;

var i : longint;

Begin
    wczytaj_dane();
    sprawdz_przygody();
    for i := 1 to k do
        if wyniki[i] then
            writeln('TAK')
        else
            writeln('NIE');
End.
