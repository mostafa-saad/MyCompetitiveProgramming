{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Odwazniki (ODW)                                            *}
{*   Plik:    odws6.pas                                                  *}
{*   Autor:   Marcin Pilipczuk                                           *}
{*   Opis:    Odrobine lepszy rozwiazanie brutalne. Wpierw kubelkuje     *}
{*            odwazniki, i probuje kazda mozliwa liczbe odwaznikow do    *}
{*            kontenera                                                  *}
{*                                                                       *}
{*************************************************************************}
program odws2p;

var wynik, n, m, k:longint;
    wartosci, licznosc, przelicznik: array[0..31] of longint;
    kon: array[0..99999] of longint;
    
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

procedure probuj(konid, odwid, gleb:longint);
var i:longint;
begin
    if konid = n then begin
        if wynik < gleb then wynik := gleb;
    end else if odwid = k then
        probuj(konid+1, 0, gleb)
    else begin
        i := 0;
        while (licznosc[odwid] >= 0) and (kon[konid] >= 0) do begin
            probuj(konid, odwid+1, gleb+i);
            kon[konid] := kon[konid] - wartosci[odwid];
            dec(licznosc[odwid]);
            inc(i);
        end;
        kon[konid] := kon[konid] + i * wartosci[odwid];
        licznosc[odwid] := licznosc[odwid] + i;
    end;
end;

var i:longint;
begin
    readln(n, m);
    for i:=0 to n-1 do read(kon[i]);
    wczytaj_odwazniki;
    probuj(0, 0, 0);
    writeln(wynik);
end.
