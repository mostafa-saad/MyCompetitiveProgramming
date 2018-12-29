(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Pensje                                           *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n^n)                                           *
 *   Opis:              Rozwiazanie powolne, wykladnicze                 *
 *                                                                       *
 *************************************************************************)


const MAXN = 1000002;
var
    n : longint;
    przelozony, pensja : array[1..MAXN] of longint;
    ile_podwladnych : array[1..MAXN] of longint;
    uzyte : array[0..MAXN] of longint;
    rozwiazanie : array[1..MAXN] of longint;

procedure policz_podwladnych;
var
    stopien, kolejka : array[1..MAXN] of longint;
    pocz, kon : longint;
    akt, przel : longint;
    i : longint;
begin
    pocz := 0;
    kon := 0;
    (* zliczamy bezposrednich *)
    for i := 1 to n do stopien[i] := 0;
    for i := 1 to n do
        if przelozony[i] <> i then
            stopien[przelozony[i]] := stopien[przelozony[i]] + 1;
    for i := 1 to n do
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
        if akt <> przel then
        begin
            stopien[przel] := stopien[przel] - 1;
            if stopien[przel] > 0 then
            begin
                kon := kon + 1;
                kolejka[kon] := przel;
            end;
            ile_podwladnych[przel] := ile_podwladnych[przel] + ile_podwladnych[akt];
        end;
    end;
end;

procedure zapisz_rozwiazanie;
var
    i : longint;
begin
    for i := 1 to n do
        if rozwiazanie[i] = 0 then rozwiazanie[i] := pensja[i]
        else if rozwiazanie[i] <> pensja[i] then rozwiazanie[i] := -1;
end;

procedure iteruj_pensje(p : longint);
var
    j : longint;
begin
    while (p > 0) and (uzyte[p] <> 0) do p := p - 1;
    if p = 0 then zapisz_rozwiazanie()
    else begin
        for j := 1 to n do
            if (ile_podwladnych[j] <= p) and (pensja[j] = 0)
            and ((przelozony[j] = j) or (pensja[przelozony[j]] > p)) then
            begin
                pensja[j] := p;
                iteruj_pensje(p-1);
                pensja[j] := 0;
            end;
    end;
end;

var i : longint;

Begin
    readln(n);
    for i := 1 to n do
    begin
        readln(przelozony[i], pensja[i]);
        rozwiazanie[i] := pensja[i];
    end;
    policz_podwladnych();
    for i := 1 to n do uzyte[pensja[i]] := i;
    iteruj_pensje(n);
    for i := 1 to n do
        if rozwiazanie[i] <> -1 then
            writeln(rozwiazanie[i])
        else
            writeln(0);
End.
