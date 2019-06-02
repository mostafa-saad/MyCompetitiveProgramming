(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Owce (OWC)                                       *
 *   Plik:              owcs4.pas                                        *
 *   Autor:             Adam Gawarkiewicz                                *
 *   Opis:              Rozwiazanie powolne.                             *
 *                      Rozwiazanie ze spamietywaniem wartosci           *
 *                      dla wielokata a, a+1, ..., b-1, b.               *
 *   Zlozonosc czasowa: O(n^3 * k)                                       *
 *                                                                       *
 *************************************************************************)

const MAXN=600;
const MAXK=20000;

var n, m, k : LongInt;
    x, y : array [0..MAXN] of LongInt; (* wierzcholki pastwiska *)
    px, py : array [0..MAXK] of LongInt; (* owce *)
    wart : array[0..MAXN, 0..MAXN] of LongInt; (* do spamietywania wartosci funkcji licz *)
    czyObl : array[0..MAXN, 0..MAXN] of Boolean; (* czy obliczono wartosc *)

function abs(a : LongInt) : LongInt;
begin
    if a < 0 then abs := -a else abs := a;
end;

function det(x1, y1, x2, y2, x3, y3 : LongInt) : LongInt;
begin
    det := (x2-x1)*(y3-y1) - (x3-x1)*(y2-y1);
end;

(* czy dany punkt jest wewnatrz danego trojkata *)
function wewnatrz(x1, y1, x2, y2, x3, y3, xa, ya : LongInt) : Boolean;
begin
    wewnatrz := abs(det(x1, y1, x2, y2, x3, y3)) =
        abs(det(xa, ya, x2, y2, x3, y3)) + abs(det(x1, y1, xa, ya, x3, y3)) + abs(det(x1, y1, x2, y2, xa, ya));
end;

(* czy w trojkacie a, b, c jest parzysta liczba owiec *)
function sprawdz(a, b, c : LongInt) : LongInt;
var ile, i : LongInt;
begin
    ile := 0;
    for i := 0 to k-1 do
        if wewnatrz(x[a], y[a], x[b], y[b], x[c], y[c], px[i], py[i]) then
            ile := ile + 1;
    sprawdz := 1 - (ile mod 2);
end;

(* czy na danej krawedzi nie ma zadnych owiec *)
function sprawdzKrawedz(a, b : LongInt) : LongInt;
var ret, i : LongInt;
begin
    ret := 1;
    for i := 0 to k-1 do
        if det(px[i], py[i], x[a], y[a], x[b], y[b])=0 then
            ret := 0;
    sprawdzKrawedz := ret;
end;

(* na ile sposobow da sie podzielic obszar pocz, pocz+1, ..., kon *)
function licz(pocz, kon : LongInt) : LongInt;
var ret, i : LongInt;
begin
    if not czyObl[pocz][kon] then
    begin
        if kon - pocz <= 1 then wart[pocz][kon] := 1
        else if kon - pocz = 2 then wart[pocz][kon] := sprawdzKrawedz(pocz, kon)*sprawdz(pocz, pocz+1, kon)
        else
        begin
            ret := 0;
            
            for i := pocz + 1 to kon - 1 do
                ret := (ret + sprawdz(pocz, i, kon)*sprawdzKrawedz(pocz, kon)*licz(pocz, i)*licz(i, kon)) mod m;
            
            wart[pocz][kon] := ret;
        end;
        czyObl[pocz][kon] := true;
    end;
    licz := wart[pocz][kon];
end;

var i : LongInt;
begin
    Read(n); Read(k); Read(m);
    for i := 0 to n-1 do
    begin
        Read(x[i]); Read(y[i]);
    end;
    for i := 0 to k-1 do
    begin
        Read(px[i]); Read(py[i]);
    end;
    
    WriteLn(licz(0, n-1));
end.