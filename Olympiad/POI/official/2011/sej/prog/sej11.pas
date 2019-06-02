(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Sejf                                             *
 *   Autor:             Tomasz Kociumaka                                 *
 *   Zlozonosc czasowa: O(sqrt(n)+k*log(n))                              *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      szybkie generowanie dzielnikow i faktoryzacja    *
 *                      symuluje mape przez wyszukiwanie binarne         *
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
    pDvsMlt : array[0..max_P] of longint;
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

    procedure qsortDvs (a : longint; b : longint); 
    var 
        l, r : longint; 
        m, tmp : int64;        
    begin            
        m := dvs[(a + b) div 2]; 
        l := a; 
        r := b; 

        repeat
            while (dvs[l] < m) do inc(l); 
            while (dvs[r] > m) do dec(r);  
            if (l <= r) then begin 
                tmp := dvs[l]; 
                dvs[l] := dvs[r]; 
                dvs[r] := tmp; 
                inc(l); 
                dec(r);                    
            end;         
        until l >= r; 
        if (a < r) then qsortDvs(a, r); 
        if (l < b) then qsortDvs(l, b); 
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



    procedure computeDivisors(n : int64);
    var
        deg : array[0..max_P] of longint;
        i, j : longint;
        vl : int64;
    begin
        D := 0;
        factor(n);
        for i := 0 to P - 1 do deg[i] := 0;
        vl := 1;
        while true do begin
            dvs[D] := vl;
            inc(D);
            if vl = n then break;
            for i := P - 1 downto 0 do begin
                if deg[i] < pDvsMlt[i] then begin
                    inc(deg[i]);
                    vl := vl * pDvs[i];
                    break
                end else begin
                    for j := deg[i] downto 1 do begin
                        dec(deg[i]);
                        vl := vl div pDvs[i];
                    end
                end
            end
        end;
        qsortDvs(0, D - 1)
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




    






           








            

    
    
