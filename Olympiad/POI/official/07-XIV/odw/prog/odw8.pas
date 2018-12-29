{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Odwazniki (ODW)                                            *}
{*   Plik:    odw8.pas                                                   *}
{*   Autor:   Marcin Pilipczuk                                           *}
{*   Opis:    Rozwiazanie O((n+m)log n log m), czyli wyszukiwanie binarne*}
{*            + zachlanne pobieranie od najwiekszego pojemnika, z        *}
{*            wykorzystaniem wlasnego kopca                              *}
{*                                                                       *}
{*************************************************************************}
program odw3p;

var n, m, kopn: longint;
    odw, kon: array[0..99999] of longint;
    kopiec:array[1..100000] of longint;

procedure upheap(a:longint);
var x:longint;
begin
    x:=kopiec[a];
    while a > 1 do begin
        if kopiec[a shr 1] >= x then break;
        kopiec[a] := kopiec[a shr 1];
        a := a shr 1;
    end;
    kopiec[a] := x;
end;

procedure downheap(a:longint);
var x, e: longint;
begin
    x := kopiec[a];
    while (a shl 1) <= kopn do begin
        e := a shl 1;
        if (e < kopn) then if (kopiec[e] < kopiec[e+1]) then inc(e);
        if kopiec[e] <= x then break;
        kopiec[a] := kopiec[e];
        a := e;
    end;
    kopiec[a] := x;
end;

procedure inicjuj;
var i:longint;
begin
    for i:=0 to n-1 do kopiec[i+1]:= kon[i];
    kopn := n;
    for i:=n downto 1 do downheap(i);
end;

function probuj(c:longint):boolean;
var i, co:longint;
begin
    inicjuj;
    probuj := true;
    for i:= c downto 0 do begin
        if kopn = 0 then begin
            probuj := false;
            break;
        end;
        co := kopiec[1];
        if co < odw[i] then begin
            probuj := false;
            break;
        end;
        kopiec[1] := kopiec[kopn];
        dec(kopn);
        downheap(1);
        co := co - odw[i];
        if co > 0 then begin
            inc(kopn);
            kopiec[kopn] := co;
            upheap(kopn);
        end;
    end;
end;

procedure sortuj_odw(p, k:longint);
var c, p2, k2, e: longint;
begin
    if p < k then begin
        c := odw[p];
        p2 := p + 1;
        k2 := k;
        while (p2 < k2) do begin
            if odw[p2] <= c then begin
                if odw[k2] >= c then dec(k2);
                inc(p2);
            end else if odw[k2] >= c then dec(k2)
            else begin
                e := odw[k2];
                odw[k2] := odw[p2];
                odw[p2] := e;
                inc(p2);
                dec(k2);
            end;
        end;
        while (k2 <= k) and (odw[k2] < c) do inc(k2);
        dec(k2);
        odw[p] := odw[k2];
        odw[k2] := c;
        sortuj_odw(p, k2-1);
        sortuj_odw(k2+1, k);
    end;
end;

var i, najw, p, k, c:longint;
begin
    readln(n, m);
    for i:=0 to n-1 do read(kon[i]);
    for i:=0 to m-1 do read(odw[i]);
    sortuj_odw(0, m-1);
    najw := kon[0];
    for i:=1 to m-1 do if najw < kon[i] then najw := kon[i];
    p := 0; k := m;
    if odw[0] > najw then p := -1
    else begin
        while p + 1 < k do begin
            c := (p+k) div 2;
            if probuj(c) then p := c
            else k := c;
        end;
    end;
    writeln(p+1);
end.
