(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Monotonicznosc (MON)                             *
 *   Plik:              mons2.pas                                        *
 *   Autor:             Piotr Niedzwiedz                                 *
 *   Opis:              Rozwiazanie powolne - bez drzewa przedzialowego. *
 *   Zlozonosc czasowa: O(n^2 * k)                                       *
 *                                                                       *
 *************************************************************************)

VAR 
    a, ra: array[0..20003] of longint;
    amap: array[0..1000003] of longint;
    from, tree: array[0..103, 0..77777] of longint;
    fres: array[0..20003, 0..103] of longint;
    n, k, m: longint;
    i, j , rs_tmp, rf_tmp ,tmp2:  longint;
    space: char;
    tmp: array[0..103] of longint;
    tk: array[0..103] of char;
    res, resi: longint;
    resa: array [0..20003] of longint;

function min(a,b:int64):int64;
begin
    if a<b then
        min:=a
    else
        min:=b;
end;


procedure update(tk, x, v, f: longint);
begin 
    if tree[tk][x] < v then begin
        tree[tk][x]:= v;
        from[tk][x]:= f;
    end;
end;

procedure popraw(tk, x: longint; var rs,rf: longint);
begin
    if rs < tree[tk][x] then begin
        rs:= tree[tk][x];
        rf:= from[tk][x];
    end;
end;

procedure get_range(tk, l, r: longint; var rs,rf: longint);
var
    i: longint;
begin 
    rs:=0;
    rf:=0;
    for i:=l to r do begin
        popraw(tk, i, rs, rf);
    end;
end;



BEGIN
    for i:=0 to 1000000 do amap[i]:=0;
    for i:=0 to 100 do
        for j:=0 to 77777 do begin
            from[i][j]:= 0;
            tree[i][j]:= 0;
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
            if j = 0 then tmp[j]:=1;
            tmp2:= (j-1+k) mod k;
            if tk[tmp2] = '<' then begin
                get_range(j, 0, a[i]-1, rs_tmp, rf_tmp);
            end;
            if tk[tmp2] = '=' then begin
                get_range(j, a[i], a[i], rs_tmp, rf_tmp);
            end;
            if tk[tmp2] = '>' then begin
                get_range(j, a[i]+1, m, rs_tmp, rf_tmp);  
            end;        
            if rs_tmp <> 0 then begin
                tmp[j]:= rs_tmp+1;
                fres[i][j]:= rf_tmp;
            end;
            if res < tmp[j] then begin
                res:= tmp[j];
                resi:= i;

            end;
        end;
        for j:=0 to k-1 do begin
            if tmp[j] <> 0 then
                update((j+1) mod k, a[i], tmp[j], i);
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

