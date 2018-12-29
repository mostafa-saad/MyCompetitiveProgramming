{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Odwazniki (ODW)                                            *}
{*   Plik:    odw7.pas                                                   *}
{*   Autor:   Marcin Pilipczuk                                           *}
{*   Opis:    Rozwiazanie wzorcowe. Rozwiazanie rozkladajace pojemniki   *}
{*            na "system" o podstawie odwaznikow                         *}
{*                                                                       *}
{*************************************************************************}
program odw1p;
var k, n, m, a: longint;
    wartosci:array[0..31] of longint;
    licznosc:array[0..31] of longint;
    przelicznik:array[0..31] of longint;
    rozklad:array[0..31] of int64;
    pojemniki:array[0..99999] of longint;

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

var i, j, mnoznik, wynik:longint;
    ile: int64;

begin
    readln(n, m);
    for i:=0 to n-1 do read(pojemniki[i]);
    wczytaj_odwazniki; 
    for i:=0 to n-1 do begin
        a := pojemniki[i];
        for j:=0 to k-1 do begin
            a := a div przelicznik[j];
            if j < k-1 then
                rozklad[j] := rozklad[j] + (a mod przelicznik[j+1])
            else
                rozklad[j] := rozklad[j] + a;
        end;
    end;
    wynik := 0;
    for i:=0 to k-1 do begin
        j := i;
        a := licznosc[i];
        mnoznik := 1;
        while (j < k) AND (a > 0) do begin
            ile := int64(mnoznik) * int64(rozklad[j]);
            if ile > a then ile := a;
            wynik := wynik + ile;
            a := a - ile;
            rozklad[j] := rozklad[j] - (ile + int64(mnoznik - 1)) div int64(mnoznik);
            inc(j);
            if j < k then
                mnoznik := mnoznik * przelicznik[j];
        end;
    end;
    writeln(wynik);
end.
