(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Sejf                                             *
 *   Autor:             Tomasz Kociumaka                                 *
 *   Zlozonosc czasowa: O(sqrt(n)+k*log(n))                              *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      proste szukanie dzielnikow, faktoryzacja bez     *
 *                      optymalizacji, symuluje mape przez               *
 *                      wyszukiwanie binarne                             *
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
    dvs : array[0..max_D] of Int64;
    pDvs : array[0..max_P] of Int64;
    _good : array[0..max_D] of boolean;


    function gcd (a : Int64; b : Int64) : Int64;
    begin
        while b <> 0 do begin
            a := a mod b;
            if a = 0 then a := b;
            b := b mod a
        end;
        gcd := a
    end;


    function good (dv : Int64) : pbool;
    var
        b, e, med : longint;
    begin
        b := 0;
        e := D - 1;
        while e >= b do begin
            med := (b + e) div 2;
            if dvs[med] = dv then begin
                good := @_good[med];
                exit
            end else if dvs[med] < dv then b := med + 1
            else e := med - 1
        end;
        assert(false);
    end;


    procedure computeDivisors (n : Int64);
    var 
        m : Int64;
        dv, i : longint;
    begin
        m := n;
        dvs[0] := 1;
        D := 1;
        P := 0;
        dv := 2;
        while dv * int64(dv) <= n do begin
            if n mod dv = 0 then begin
                dvs[D] := int64(dv);
                inc(D);
            
                if m mod dv = 0 then begin
                    pDvs[P] := dv;
                    inc(P);
                    repeat m := m div dv
                    until m mod dv <> 0
                end;
            end;
            inc(dv);
        end;
        if m <> 1 then begin
            pDvs[P] := m;
            inc(P)
        end;
        i := D - 1;
        if dvs[i]*dvs[i] = n then dec(i);
        for i := i downto 0 do begin
            dvs[D] := n div dvs[i];
            inc(D)
        end
    end;


var
    k : longint;
    n : int64;
    m : array[0..max_k] of int64;

    i, j : longint;
    best, di : int64;
    gdi : pbool;

begin
    read(n);
    read(k);
    for i := 0 to k - 1 do begin
        read(m[i]);
        m[i] := gcd(m[i],n)
    end;
    computeDivisors(n);
    for i := 0 to D - 1 do _good[i] := true;

    for i := 0 to k - 2 do good(m[i])^ := false;

    best := -1;

    for i := D - 1 downto 0 do begin
        di := dvs[i];
        gdi := good(di);
        if not gdi^ then continue;
        for j := 0 to P - 1 do begin
            if (n div di) mod pDvs[j] <> 0 then continue;
            if not good(di*pDvs[j])^ then begin
                gdi^ := false;
                break
            end
        end;
        if gdi^ and (m[k-1] mod di = 0) then 
            best := max(best, n div di)
    end;
    writeln(best);
end.




    






           








            

    
    
