(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Monotonicznosc (MON)                             *
 *   Plik:              mon3.pas                                         *
 *   Autor:             Piotr Niedzwiedz                                 *
 *   Opis:              Rozwiazanie alternatywne.                        *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *                                                                       *
 *************************************************************************)

VAR 
    a, ra: array[0..20003] of longint;
    amap: array[0..1000003] of longint;
    tt, tv: array[0..103, 0..20777] of longint;
    fres: array[0..20003, 0..103] of longint;
    n, k, m: longint;
    i, j, g , rs_tmp, rf_tmp:  longint;
    space: char;
    tmp, mx: array[0..103] of longint;
    tk: array[0..103] of char;
    res, resi: longint;
    resa: array [0..20003] of longint;

function max(a,b:longint):longint;
begin
    if a>b then
        max:=a
    else
        max:=b;
end;


procedure update(x, r: longint);
var 
    rt, p: longint;
begin 
    p:= (r-1) mod k;
    rt:= (r-1) div k;
    if tk[p] = '<' then begin
        if (tt[p][rt] = -1) or (a[tt[p][rt]] > a[x]) then begin
            tt[p][rt]:=x;
            mx[p]:= max(mx[p], rt +1);
        end;
    end;
    if tk[p] = '=' then begin
        if tv[p][a[x]] < res then begin
            tt[p][a[x]]:= x;
            tv[p][a[x]]:= r;
        end;
    end;
    if tk[p] = '>' then begin
        if (tt[p][rt] = -1) or (a[tt[p][rt]] < a[x]) then begin
            tt[p][rt]:=x;
            mx[p]:= max(mx[p], rt +1);
        end;
    end;        
         

end;

BEGIN
    for i:=0 to 1000000 do amap[i]:=0;
    for i:=0 to 100 do begin
        for j:=0 to 20007 do begin
            tt[i][j]:= -1;
            tv[i][j]:= 0;
        end;
        mx[i]:= 0;
    end;

    readln(n,k);
    for i:=0 to n-1 do begin
        read(a[i]);
        amap[a[i]]:= -1;
    end;

    m:=0;
    for i:=0 to 1000000 do begin
        if amap[i] = -1 then begin
           amap[i]:=m;
           ra[m]:=i;
           inc(m);
        end;
    end;
    for i:=0 to n-1 do begin
        a[i]:= amap[a[i]];
    end;
    readln;
    for i:=0 to k-1 do begin 
        read(tk[i]);
        read(space);
    end;
    res:=1;
    resi:=0;
    for i:=0 to n-1 do begin
        for j:=0 to k-1 do begin
            tmp[j]:=0;
            rs_tmp := 0;
            if tk[j] = '<' then begin
                for g:=mx[j]-1 downto 0 do begin
                    if a[tt[j][g]] < a[i] then begin
                        rs_tmp:= g * k + j + 2;
                        rf_tmp:= tt[j][g];
                        break;
                    end;
                end;        
            end;
            if tk[j] = '=' then begin
                if tt[j][a[i]] <> -1 then begin
                    rs_tmp:= tv[j][a[i]]+1;
                    rf_tmp:= tt[j][a[i]];
                end;
            end;
            if tk[j] = '>' then begin
                 for g:=mx[j]-1 downto 0 do begin
                    if a[tt[j][g]] > a[i] then begin
                        rs_tmp:= g * k + j + 2;
                        rf_tmp:= tt[j][g];
                        break;
                    end;
                end;       
            end;        
            if rs_tmp <> 0 then begin
                tmp[j]:= rs_tmp;
                fres[i][(j+1) mod k]:= rf_tmp;
            end;
            if res < tmp[j] then begin
                res:= tmp[j];
                resi:= i;
            end;
        end;
        update(i, 1);
        for j:=0 to k-1 do begin
            if tmp[j] <> 0 then begin
                update(i, tmp[j]);
            end;
        end;
    end;   
    writeln(res);
    for i:=res-1 downto 0 do begin
        resa[i]:= ra[a[resi]];
        resi:= fres[resi][ i mod k ];
    end;
    for i:=0 to res-1 do begin
        write(resa[i],' ');
    end;
    writeln;
END.

