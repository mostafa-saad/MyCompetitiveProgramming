{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Odwazniki (ODW)                                            *}
{*   Plik:    odws7.pas                                                  *}
{*   Autor:   Marcin Pilipczuk                                           *}
{*   Opis:    Rozwiazanie, które dla każdej permutacji odważników,       *}
{*            zachłannie wkłada je do kolejnych pojemników               *}
{*                                                                       *}
{*************************************************************************}
program odws3p;

var pr, n, m, wynik:longint;
    bylo, perm, odw, kon:array[0..100000] of longint;
    t:array[0..12000000] of longint;

procedure umieszczaj;
var i, j, a:longint;
begin
    i := 0;
    for j := 0 to n-1 do begin
        a := kon[j];
        while (i < m) and (a >= perm[i]) do begin
            a := a - perm[i];
            inc(i);
        end;
    end;
    if wynik < i then wynik := i;
end;

procedure probuj(poz:longint);
var i:longint;
begin
    if poz = m then umieszczaj
    else for i := 0 to m-1 do if bylo[i] = 0 then begin
        bylo[i] := 1;
        perm[poz] := odw[i];
        probuj(poz+1);
        bylo[i] := 0;
    end;
end;

var i:longint;
begin
    readln(n, m);
    for i:=0 to n-1 do read(kon[i]);
    for i:=0 to m-1 do read(odw[i]);
    for i:=0 to m-1 do bylo[i] := 0;
    wynik := 0;
    probuj(0);
    writeln(wynik);
end.
