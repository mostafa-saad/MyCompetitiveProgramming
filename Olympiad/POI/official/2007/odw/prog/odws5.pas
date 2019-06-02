{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Odwazniki (ODW)                                            *}
{*   Plik:    odws5.pas                                                  *}
{*   Autor:   Marcin Pilipczuk                                           *}
{*   Opis:    Najbardziej prymitywne rozwi¹zanie brutalne. Probuje kazda *}
{*            konfiguracje                                               *}
{*                                                                       *}
{*************************************************************************}
program odws1p;

var n,m, wynik :longint;
    odw, kon: array[0..99999] of longint;

procedure probuj(nr, gleb:longint);
var i:longint;
begin
    if nr = m then begin
        if wynik < gleb then wynik := gleb;
    end else begin
        probuj(nr+1, gleb);
        for i:=0 to n-1 do if kon[i] >= odw[nr] then begin
            kon[i] := kon[i] - odw[nr];
            probuj(nr+1, gleb+1);
            kon[i] := kon[i] + odw[nr];
        end;
    end;
end;

var i:longint;
begin
    readln(n, m);
    wynik := 0;
    for i:=0 to n-1 do read(kon[i]);
    for i:=0 to m-1 do read(odw[i]);
    probuj(0, 0);
    writeln(wynik);
end.
