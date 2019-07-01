(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Pensje                                           *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000004;
var
    n : longint; (* ilosc pracownikow *)
    przelozony, pensja : array[1..MAXN] of longint; (* input *)
    uzyte : array[0..MAXN] of longint; (* ktore wartosci sa uzyte *)
    ile_podwladnych : array[0..MAXN] of longint;
    podwladny : array[0..MAXN] of longint; (* bezposredni podwladny (jezeli tylko jeden) *)

procedure policz_podwladnych;
var
    kolejka, stopien : array[1..MAXN] of longint;
    pocz, kon : longint;
    akt, przel : longint;
    i : longint;
begin
    pocz := 0;
    kon := 0;
    for i := 1 to n - 1 do stopien[i] := 0;
    for i := 1 to n - 1 do
        stopien[przelozony[i]] := stopien[przelozony[i]] + 1; (* zliczamy bezposrednich *)
    for i := 1 to n - 1 do
        if stopien[i] = 0 then
        begin
            kon := kon + 1;
            kolejka[kon] := i;
        end;
    while pocz < kon do
    begin
        pocz := pocz + 1;
        akt := kolejka[pocz];
        przel := przelozony[akt];
        if pensja[akt] = 0 then
        begin
            stopien[przel] := stopien[przel] - 1;
            if stopien[przel] = 0 then begin kon := kon + 1; kolejka[kon] := przel; end;
            ile_podwladnych[przel] := ile_podwladnych[przel] + ile_podwladnych[akt] + 1;
        end;
    end;
end;

procedure oznacz_uzyte_pensje;
var i : longint;
begin
    for i := 1 to n - 1 do
        if pensja[i] <> 0 then
            uzyte[pensja[i]] := i
        else if podwladny[przelozony[i]] = 0 then
                podwladny[przelozony[i]] := i
             else podwladny[przelozony[i]] := -1;
end;

var i, ile_wolnych, ile_mozliwych, akt, l : longint;

Begin
    readln(n);
    for i := 1 to n do
    begin
        readln(przelozony[i], pensja[i]);
        if przelozony[i] = i then pensja[i] := n;
        if pensja[i] > 0 then przelozony[i] := n + 1;
    end;
    n := n + 1;
    przelozony[n] := n;
    pensja[n] := n;
    policz_podwladnych;
    oznacz_uzyte_pensje;
    i := 0;
    ile_wolnych := 0;
    ile_mozliwych := 0;
    while i < n-1 do
    begin
        while (i < n-1) and (uzyte[i+1] = 0) do
        begin
            i := i + 1;
            ile_wolnych := ile_wolnych + 1;
            ile_mozliwych := ile_mozliwych + 1;
        end;
        while (i < n-1) and (uzyte[i+1] <> 0) do
        begin
            i := i + 1;
            akt := uzyte[i];
            l := i;
            ile_wolnych := ile_wolnych - ile_podwladnych[akt];
            if ile_wolnych = 0 then
            begin
                while (ile_mozliwych > 0) and (podwladny[akt] > 0) do
                begin
                    ile_mozliwych := ile_mozliwych - 1;
                     while uzyte[l] > 0 do l := l - 1;
                     akt := podwladny[akt];
                     pensja[akt] := l;
                     uzyte[l] := akt;
                end;
                ile_mozliwych := 0;
            end;
            if ile_podwladnych[akt] <> 0 then
                ile_mozliwych := 0;
        end;
    end;
    for i := 1 to n - 1 do
        writeln(pensja[i]);
End.
