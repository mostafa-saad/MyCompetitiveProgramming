(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Sejf                                             *
 *   Autor:             Tomasz Kociumaka                                 *
 *   Zlozonosc czasowa: O(sqrt(n)+k*log(n))                              *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      nie korzysta z mapy, lecz z pozycyjnej           *
 *                      reprezentacji dzielnikow - zyskujemy czynnik     *
 *                      log(liczba dzielnikow), ale w fazie              *
 *                      asymptotycznie zdominowanej przez faktoryzacje   *
 *                      nwd(n,m_k) zamiast n                             *
 *                                                                       *
 *************************************************************************)

uses math;

type pbool = ^boolean;
const
    max_k = 500000;
    max_D = 500000;
    max_P = 50;
var
    D, P : longint;
    pDvs : array[0..max_P] of Int64;
    pDvsMlt : array[0..max_P] of longint;
    good : array[0..max_D] of boolean;

    function indexToValue (ps : longint) : int64;
    var 
        dig, i, j : longint;
        res : int64;
    begin
        res := 1;
        for i := 0 to P - 1 do begin
            dig := ps mod (pDvsMlt[i] + 1);
            ps := ps div (pDvsMlt[i] + 1);
            for j := 0 to dig - 1 do res := res * pDvs[i]
        end;
        indexToValue := res;
    end;


    function valueToIndex (dv : int64) : longint;
    var 
        i, res : longint;
    begin
        res := 0;
        for i := P - 1 downto 0 do begin
            res := res * (pDvsMlt[i] + 1);
            while dv mod pDvs[i] = 0 do begin
                dv := dv div pDvs[i];
                inc(res)
            end
        end;
        valueToIndex := res
    end;




    function gcd (a : Int64; b : Int64) : Int64;
    begin
        while b <> 0 do begin
            a := a mod b;
            if a = 0 then a := b;
            b := b mod a
        end;
        gcd := a
    end;

    procedure factor (n : Int64);
    var 
        dv, cnt : longint;
    begin
        P := 0;
        dv := 2;
        while dv * int64(dv) <= n do begin
            if n mod dv = 0 then begin
                cnt := 0;
                repeat 
                    n := n div dv;
                    inc(cnt);
                until n mod dv <> 0;
                pDvs[P] := dv;
                pDvsMlt[P] := cnt;
                inc(P);

            end;
            inc(dv);
        end;
        if n <> 1 then begin
            pDvs[P] := n;
            pDvsMlt[P] := 1;
            inc(P)
        end;
    end;



var
    k : longint;
    n : int64;
    m : array[0..max_k] of int64;

    offset : array[0..max_p+1] of longint;
    i, j : longint;
    best, vl : int64;

begin
    read(n);
    read(k);
    for i := 0 to k - 1 do read(m[i]);
    m[k-1] := gcd(n, m[k-1]);
    for i := 0 to k - 2 do m[i] := gcd(m[k-1], m[i]);
    factor(m[k-1]);

    offset[0] := 1;
    for i := 0 to P - 1 do
        offset[i+1] := offset[i] * (pDvsMlt[i] + 1);

    D := offset[P];


    for i := 0 to D - 1 do good[i] := true;

    for i := 0 to k - 2 do good[valueToIndex(m[i])] := false;

    best := -1;

    for i := D - 1 downto 0 do begin
        if not good[i] then continue;
        for j := 0 to P - 1 do begin
            if ((i + offset[j]) div offset[j+1] = i div offset[j+1]) and not good[i + offset[j]] then begin
                good[i] := false;
                break;
            end;
        end;
        if good[i] then begin
            vl := indexToValue(i);
            best := max(best, n div vl)
        end;
    end;
    writeln(best);
end.

