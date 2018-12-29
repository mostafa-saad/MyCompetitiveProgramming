(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Morskie opowiesci                             *
 *   Autor:                Mateusz Baranowski                            *
 *   Zlozonosc czasowa:    O(k(n + m))                                   *
 *   Zlozonosc pamieciowa: O(n + m)                                      *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Sprawdza kazda opowiesc osobno                *
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
    przygoda : przygody_t;

procedure wczytaj_dane;
var i, u, v : longint;
begin
    for i := 1 to n do szlaki[i] := nil;
    readln(n, m, k);
    for i := 1 to m do
    begin
        readln(u, v);
        push(szlaki[u], v);
        push(szlaki[v], u);
    end;
end;

function sprawdz_przygode(przygoda : przygody_t) : boolean;
var r, d, u, l : longint;
    odl : array[0..1, 1..MAX_N] of longint;
    q : array[0..1, 0..MAX_N] of longint;
    p, k : array[0..1] of longint;
    it : stack_p;
begin
    for l := 1 to n do
    begin
        odl[0][l] := INFTY;
        odl[1][l] := INFTY;
    end;
    p[0] := 0;
    p[1] := 0;
    k[0] := 1;
    k[1] := 0;
    q[0][0] := przygoda.u;
    r := 0;
    d := 1;
    while (p[r] < k[r]) and (odl[przygoda.len mod 2][przygoda.v] = INFTY) do
    begin
        u := q[r][p[r]];
        p[r] := p[r] + 1;
        it := szlaki[u];
        while it <> nil do
        begin
            if odl[1 - r][it^.v] = INFTY then
            begin
                odl[1 - r][it^.v] := d;
                q[1 - r][k[1 - r]] := it^.v;
                k[1 - r] := k[1 - r] + 1;
            end;
            it := it^.next;
        end;
        if p[r] = k[r] then
        begin
            r := 1 - r;
            d := d + 1;
        end;
    end;
    sprawdz_przygode := (odl[przygoda.len mod 2][przygoda.v] <= przygoda.len);
end;

var i : longint;

Begin
    wczytaj_dane();
    for i := 1 to k do
    begin
        readln(przygoda.u, przygoda.v, przygoda.len);
        if sprawdz_przygode(przygoda) then
            writeln('TAK')
        else
            writeln('NIE');
    end;
End.
