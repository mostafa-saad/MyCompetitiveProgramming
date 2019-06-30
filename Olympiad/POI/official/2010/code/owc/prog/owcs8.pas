(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Owce (OWC)                                       *
 *   Plik:              owcs8.pas                                        *
 *   Autor:             Adam Gawarkiewicz                                *
 *   Opis:              Rozwiazanie powolne.                             *
 *                      Ze spamietywaniem wartosci dla polplaszczyzn     *
 *                      i, j oraz zakazanych przekatnych.                *
 *   Zlozonosc czasowa: O(n^2 * (n + k))                                 *
 *                                                                       *
 *************************************************************************)

const MAXN=600;
const MAXK=20000;

var n, m, k : LongInt;
    x, y : array [0..MAXN] of LongInt; (* wierzcholki pastwiska *)
    px, py : array [0..MAXK] of LongInt; (* owce *)
    f : array [0..MAXN, 0..MAXN] of LongInt; (* [i][j] -> ile owiec na polplaszczyznie i, j *)
    naPrzekatnej : array [0..MAXN, 0..MAXN] of Boolean; (* czy jakas owca jest na przekatnej *)
    wart : array[0..MAXN, 0..MAXN] of LongInt; (* do spamietywania wartosci funkcji licz *)
    czyObl : array[0..MAXN, 0..MAXN] of Boolean; (* czy obliczono wartosc *)

function det(x1, y1, x2, y2, x3, y3 : LongInt) : LongInt;
begin
    det := (x2-x1)*(y3-y1) - (x3-x1)*(y2-y1);
end;

(* czy w trojkacie a, b, c jest parzysta liczba owiec *)
function sprawdz(a, b, c : LongInt) : LongInt;
var ile : LongInt;
begin
    ile := k - f[a][b] - f[b][c] - f[c][a];
    sprawdz := 1 - (ile mod 2);
end;

(* na ile sposobow da sie podzielic obszar pocz, pocz+1, ..., kon *)
function licz(pocz, kon : LongInt) : LongInt;
var ret, i : LongInt;
begin
    if not czyObl[pocz][kon] then
    begin
        if kon - pocz <= 1 then wart[pocz][kon] := 1
        else if kon - pocz = 2 then
        begin
            if naPrzekatnej[pocz][kon] then
                wart[pocz][kon] := 0
            else
                wart[pocz][kon] := sprawdz(pocz, pocz+1, kon);
        end
        else
        begin
            ret := 0;
            
            for i := pocz + 1 to kon - 1 do
                if not naPrzekatnej[pocz][kon] then
                    ret := (ret + sprawdz(pocz, i, kon)*licz(pocz, i)*licz(i, kon)) mod m;
            
            wart[pocz][kon] := ret;
        end;
        czyObl[pocz][kon] := true;
    end;
    licz := wart[pocz][kon];
end;

var i, j, z, d : LongInt;
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
    
    for i := 0 to n-1 do
        for j := i + 1 to n-1 do
            for z := 0 to k-1 do
            begin
                d := det(x[i], y[i], x[j], y[j], px[z], py[z]);
                if d = 0 then
                begin
                    naPrzekatnej[i][j] := true;
                    naPrzekatnej[j][i] := true;
                end
                else if d > 0 then
                    f[i][j] := f[i][j] + 1
                else
                    f[j][i] := f[j][i] + 1;
            end;
    
    WriteLn(licz(0, n-1));
end.
