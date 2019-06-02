{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Odwazniki (ODW)                                            *}
{*   Plik:    odw9.pas                                                   *}
{*   Autor:   Marcin Pilipczuk                                           *}
{*   Opis:    Rozwiazanie O((n+m)log n log m), czyli wyszukiwanie binarne*}
{*            + zachlanne pobieranie od najwiekszego pojemnika, ale z    *}
{*            "kubelkami" z listami pojemnikow                           *}
{*                                                                       *}
{*************************************************************************}
program odw4p;

var n, m, k : longint;
    wartosci, licznosc, przelicznik : array[0..31] of longint;

procedure wczytaj_odwazniki;
var wart, ile: array[0..31] of longint;
    i, logarytm, a, b: longint;
begin
    for i:=0 to 31 do begin
        ile[i] := 0;
        wart[i] := -1;
    end;
    for i:=0 to m-1 do begin
        read(a);
        b := a; logarytm := 0;
        if (b AND $ffff0000) <> 0 then begin
            b := b shr 16;
            logarytm := logarytm + 16;
        end;
        if (b AND $ff00) <> 0 then begin
            b := b shr 8;
            logarytm := logarytm + 8;
        end;
        if (b AND $f0) <> 0 then begin
            b := b shr 4;
            logarytm := logarytm + 4;
        end;
        if (b AND $c) <> 0 then begin
            b := b shr 2;
            logarytm := logarytm + 2;
        end;
        if (b AND $2) <> 0 then begin
            b := b shr 1;
            logarytm := logarytm + 1;
        end;
        wart[logarytm] := a;
        inc(ile[logarytm]);
    end;
    for i:=0 to 31 do if wart[i] >= 0 then begin
        wartosci[k] := wart[i];
        licznosc[k] := ile[i];
        inc(k);
    end;
    przelicznik[0] := wartosci[0];
    for i:=1 to k-1 do 
        przelicznik[i] := wartosci[i] div wartosci[i-1];
end;


var poj, pojemniki, lista : array[0..99999] of longint;
    licz, ostlisty, poczatki: array [0..31] of longint;
    nk: longint;

function kubelek_pojemnika(najw, wlk:longint):longint;
var po, ko, c : longint;
begin
    po := 0; ko := najw;
    while po < ko do begin
        c := (po + ko + 1) div 2;
        if wlk < wartosci[c] then ko := c-1
        else po := c;
    end;
    kubelek_pojemnika := po;
end;

function probuj(c:longint):boolean;
var i, nr, nnr : longint;
begin
    nk := 0;
    while c > 0 do begin
        licz[nk] := c;
        if licznosc[nk] < licz[nk] then licz[nk] := licznosc[nk];
        c := c - licz[nk];
        inc(nk);
    end;
    for i := 0 to nk-1 do poczatki[i] := -1;
    for i := 0 to n-1 do if pojemniki[i] > 0 then begin
        nr := kubelek_pojemnika(nk-1, pojemniki[i]);
        if poczatki[nr] = -1 then ostlisty[nr] := i;
        lista[i] := poczatki[nr];
        poczatki[nr] := i;
        poj[i] := pojemniki[i];
    end;
    for i := nk-1 downto 0 do begin
        while licz[i] > 0 do begin
            dec(licz[i]);
            if poczatki[i] = -1 then exit(false);
            nr := poczatki[i];
            poczatki[i] := lista[nr];
            poj[nr] := poj[nr] - wartosci[i];
            if poj[nr] > 0 then begin
                nnr := kubelek_pojemnika(i, poj[nr]);
                if poczatki[nnr] = -1 then ostlisty[nnr] := nr;
                lista[nr] := poczatki[nnr];
                poczatki[nnr] := nr;
            end;
        end;
        if (i > 0) and (poczatki[i] >= 0) then begin
            if poczatki[i-1] = -1 then ostlisty[i-1] := ostlisty[i];
            lista[ostlisty[i]] := poczatki[i-1];
            poczatki[i-1] := poczatki[i];
        end;
    end;
    probuj := true;
end;

var i, po, ko, c: longint;
begin
    readln(n, m);
    for i:=0 to n-1 do read(pojemniki[i]);
    wczytaj_odwazniki;
    for i:=0 to n-1 do pojemniki[i] := pojemniki[i] div wartosci[0];
    for i:=k-1 downto 0 do wartosci[i] := wartosci[i] div wartosci[0];
    po := 0; ko := m;
    while po < ko do begin
        c := (po + ko + 1) div 2;
        if probuj(c) then po := c else ko := c-1;
    end;
    writeln(po);
end. 
