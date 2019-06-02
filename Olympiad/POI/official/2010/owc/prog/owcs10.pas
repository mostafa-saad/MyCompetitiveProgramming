(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Owce (OWC)                                       *
 *   Plik:              owcs10.pas                                       *
 *   Autor:             Adam Gawarkiewicz                                *
 *   Opis:              Rozwiazanie powolne.                             *
 *                      Bez sprawdzania czy przekatna dzieli pastwisko   *
 *                      na obszary z parzysta liczba owiec.              *
 *   Zlozonosc czasowa: O(n * k * log k + n^3)                           *
 *                                                                       *
 *************************************************************************)


const MAXN=600;
const MAXK=20000;

type Punkt = record
        x, y : LongInt;
    end;

var n, m, k : LongInt;
    x, y : array [0..MAXN] of LongInt; (* wierzcholki pastwiska *)
    p : array [0..MAXK] of Punkt; (* owce *)
    fp : array [0..MAXN, 0..MAXN] of LongInt; (* [i][j] -> ile owiec w trojkacie i, j-1, j *)
    f : array [0..MAXN, 0..MAXN] of LongInt; (* [i][j] -> ile owiec na polplaszczyznie i, j *)
    naPrzekatnej : array [0..MAXN, 0..MAXN] of Boolean; (* czy jakas owca jest na przekatnej *)
    aktP : Punkt; (* punkt, wedlug ktorego sortujemy katowo *)
    wart : array[0..MAXN, 0..MAXN] of LongInt; (* do spamietywania wartosci funkcji licz *)
    czyObl : array[0..MAXN, 0..MAXN] of Boolean; (* czy obliczono wartosc *)

function det(x1, y1, x2, y2, x3, y3 : LongInt) : LongInt;
begin
    det := (x2-x1)*(y3-y1) - (x3-x1)*(y2-y1);
end;

procedure sortuj (l, r:LongInt);
var i, j : LongInt;
    pivot, b : Punkt;
begin 
    if l < r then
    begin
        pivot := p[random(r-l) + l+1]; { losowanie elementu dzielącego }
        i := l-1;
        j := r+1;
        repeat
            repeat i := i+1 until det(aktP.x, aktP.y, pivot.x, pivot.y, p[i].x, p[i].y) <= 0;
            repeat j := j-1 until det(aktP.x, aktP.y, pivot.x, pivot.y, p[j].x, p[j].y) >= 0;
            b := p[i]; p[i] := p[j]; p[j] := b
        until i >= j;
        p[j] := p[i]; p[i] := b;
        sortuj(l, i-1);
        sortuj(i, r)
    end
end;

(* czy w trojkacie a, b, c jest parzysta liczba owiec *)
function sprawdz(a, b, c : LongInt) : LongInt;
var ile : LongInt;
begin
    ile := k - f[a][b] - f[b][c] - f[c][a];
    {writeln('sprawdz ',a,' ',b,' ',c,' = ',ile);}
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

var i, j, a, dl, d : LongInt;
begin
    Read(n); Read(k); Read(m);
    for i := 0 to n-1 do
    begin
        Read(x[i]); Read(y[i]);
    end;
    for i := 0 to k-1 do
    begin
        Read(p[i].x); Read(p[i].y);
    end;
    
    for i := 0 to n-1 do
    begin
        aktP.x := x[i];
        aktP.y := y[i];
        
        sortuj(0, k-1);

        j := 0; a := (i+2) mod n;
        while a <> i do
        begin
            d := det(x[i], y[i], x[a], y[a], p[j].x, p[j].y);
            while (j < k) and (d > 0) do
            begin
                fp[i][a] := fp[i][a] + 1;
                j := j + 1;
                d := det(x[i], y[i], x[a], y[a], p[j].x, p[j].y);
            end;
            if d = 0 then
            begin
                naPrzekatnej[i][a] := true;
                naPrzekatnej[a][i] := true;
            end;
            a := (a+1) mod n;
        end;
    end;

    for i := 0 to n-1 do
        for dl := 2 to n-1 do
            f[i][(i+dl) mod n] := f[i][(i-1+dl) mod n] + fp[i][(i+dl) mod n];
    
    WriteLn(licz(0, n-1));
end.
