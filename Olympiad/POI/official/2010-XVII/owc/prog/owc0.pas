(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Owce (OWC)                                       *
 *   Plik:              owc0.pas                                         *
 *   Autor:             Adam Gawarkiewicz                                *
 *   Opis:              Rozwiazanie wzorcowe.                            *
 *   Zlozonosc czasowa: O(n * k + n^3)                                   *
 *                                                                       *
 *************************************************************************)

const MAXN=600;
const MAXK=20000;

var n, m, k : LongInt;
    x, y : array [0..MAXN] of LongInt; (* wierzcholki pastwiska *)
    px, py : array [0..MAXK] of LongInt; (* owce *)
    fp : array [0..MAXN, 0..MAXN] of LongInt; (* [i][j] -> ile owiec w trojkacie i, j-1, j *)
    przekatna : array [0..MAXN, 0..MAXN] of Boolean; (* czy przekatna jest ok (nie ma owiec na niej i nie dzieli na obszary o nieparzystej ilosci owiec) *)
    wart : array[0..MAXN, 0..MAXN] of LongInt; (* do spamietywania wartosci funkcji licz *)
    czyObl : array[0..MAXN, 0..MAXN] of Boolean; (* czy obliczono wartosc *)

function det(x1, y1, x2, y2, x3, y3 : LongInt) : LongInt;
begin
    det := (x2-x1)*(y3-y1) - (x3-x1)*(y2-y1);
end;

(* na ile sposobow da sie podzielic obszar pocz, pocz+1, ..., kon *)
function licz(pocz, kon : LongInt) : LongInt;
var ret, i : LongInt;
begin
    if kon - pocz <= 2 then licz := 1
    else
    begin
        if not czyObl[pocz][kon] then
        begin
            ret := 0;
            
            for i := pocz + 1 to kon - 1 do
                if przekatna[pocz][i] and przekatna[kon][i] then
                    ret := (ret + licz(pocz, i)*licz(i, kon)) mod m;
            
            wart[pocz][kon] := ret;
            czyObl[pocz][kon] := true;
        end;
        
        licz := wart[pocz][kon];
    end;
end;

var i, j, suma, t, dl, d : LongInt;
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
        for j := 0 to n-1 do
            przekatna[i][j] := true;
        
    for j := 0 to k-1 do
    begin
        t := 1;
        for i := 0 to n-1 do
        begin
            d := det(x[i], y[i], x[t], y[t], px[j], py[j]);
            while (t <> i) and (d <= 0) do
            begin
                if d = 0 then
                begin
                    przekatna[i][t] := false;
                    przekatna[t][i] := false;
                end;
                t := (t+1) mod n;
                d := det(x[i], y[i], x[t], y[t], px[j], py[j]);
            end;
            if t <> i then
                fp[i][t] := fp[i][t] + 1;
        end;
    end;
    
    for i := 0 to n-1 do
    begin
        suma := 0;
        for dl := 2 to n-1 do
        begin
            suma := suma + fp[i][(i+dl) mod n];
            if suma mod 2 <> 0 then
            begin
                przekatna[i][(i+dl) mod n ] := false;
                przekatna[(i+dl) mod n][i] := false;
            end;
        end;
    end;
    
    WriteLn(licz(0, n-1));
end.
