(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: DWU (Dwuszereg)                                *
 *   Plik:                dwub3.pas                                      *
 *   Autor:               Marcin Stefaniak                               *
 *   Opis:                Rozwiazanie niepoprawne                        *
 *                        b³±d polega na tym, ¿e nie zliczamy            *
 *                        min(bz, m - bz) tylko po prostu bz.            *
 *                                                                       *
 *************************************************************************)

program Dwuszereg;

function min(x, y : longint) : longint;
begin
    if x < y then min := x else min := y;
end;

const MAX_N = 50000;        (* maksymalna liczba zolnierzy w szeregu *)
const MAX_W = 100000;        (* maksymalny wzrost zolnierza *)

var 
    wzrost : array[1..2, 1..MAX_N] of longint;        (* tablca wzrostow zolnierzy *)
    n : longint;        (* liczba zolnierzy w szeregu *)

    pozycje : array[1..MAX_W, 1..2] of longint; (* pozycje na ktorych wystepuja zolnierze o danym wzroscie *)
    

procedure wczytajDane();
var i, j : longint;
begin
    read(n);
    for j := 1 to 2 do
        for i := 1 to n do 
                read(wzrost[j, i]);
end;

procedure dodajPozycje(w, p : longint);
begin
    if (pozycje[w][1] = -1) then
        pozycje[w][1] := p
    else if (pozycje[w][2] = -1) then
        pozycje[w][2] := p
    else
        writeln('Blad albo zle dane');
end;
    
procedure indeksujPozycje(); 
var i, j : longint;
begin
    for i := 1 to MAX_W do
        for j := 1 to 2 do 
            pozycje[i, j] := -1;
    for i := 1 to n do begin
        dodajPozycje(wzrost[1, i], i);
        dodajPozycje(wzrost[2, i], i);
    end;
end;

var
    ustalone : array[1..MAX_N] of boolean; (* czy pozycja juz jest ustalona *)    
    z, bz, m : longint; (* liczba zamian, liczba biezacych zamian, wielkosc grupy *)
    tmp : longint;

procedure ustalajWzrost(w : longint);
var p1, p2 : longint;
    konflikt : boolean;
begin
    while(true) do begin
        p1 := pozycje[w, 1]; p2 := pozycje[w, 2];
        if (p2 = -1) or (ustalone[p1] and ustalone[p2]) then
                break;
        if (ustalone[p2]) then begin
                tmp := p1; p1 := p2; p2 := tmp;
        end;
        konflikt := ((wzrost[1, p1] = w) and (wzrost[1, p2] = w)) 
                     or ((wzrost[2, p1] = w) and (wzrost[2, p2] = w));
        if (konflikt) then begin
            inc(bz);
            tmp := wzrost[1, p2]; wzrost[1, p2] := wzrost[2, p2]; wzrost[2, p2] := tmp;
        end;
        ustalone[p2] := true;
        inc(m);
        if (wzrost[1, p2] <> w) then 
            w := wzrost[1, p2]
        else if (wzrost[2, p2] <> w) then
            w := wzrost[2, p2]
        else
            break;
    end;
end;

procedure ustalaj(k : longint);
begin
  bz := 0; m := 1;
  ustalone[k] := true;
  ustalajWzrost(wzrost[1, k]);
  ustalajWzrost(wzrost[2, k]);
end;

procedure ustalajZamiany();
var k : longint;
begin
    for k := 1 to n do 
        ustalone[k] := false;
    z := 0; bz := 0;
    for k := 1 to n do 
        if not ustalone[k] then begin
            ustalaj(k);
            z := z + bz;
            (* z := z + min(bz, m - bz); a powinno byc tak *)
        end;
end;

begin
    wczytajDane();
    indeksujPozycje();
    ustalajZamiany();
    writeln(z);
end.