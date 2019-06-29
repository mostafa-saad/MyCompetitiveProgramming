(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Wyspa (WYS)                                               *
 *   Plik:     wys5.pas                                                  *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Rozwiazanie wzorcowe O(n+m)                               *
 *                                                                       *
 *************************************************************************)

{ ////////////// punkty: }

type Punkt = record
    x, y : double;
end;

function len(p : Punkt) : double;
begin
  len := sqrt(p.x*p.x+p.y*p.y);
end;

function il_wek(a, b : Punkt) : double;
begin
    il_wek := a.x*b.y-a.y*b.x;
end;

function razy_stala(p : Punkt; k : double) : Punkt;
begin
    p.x := p.x*k;
    p.y := p.y*k;
    razy_stala := p;
end;

function dodaj(a, b : Punkt) : Punkt;
begin
    a.x := a.x+b.x;
    a.y := a.y+b.y;
    dodaj := a;
end;

function odejmij(a, b : Punkt) : Punkt;
begin
    a.x := a.x-b.x;
    a.y := a.y-b.y;
    odejmij := a;
end;


function pkt_przec(a, b, c, d : Punkt) : Punkt;
var p1, p2, k : double;
begin { punkt przeciecia linii a-b z c-d }
    p1 := il_wek(odejmij(a, c), odejmij(d, c)); { pole trojkata a-c-d }
    p2 := il_wek(odejmij(a, b), odejmij(d, c)); { pole czworokata a-b-c-d }
    k := p1/p2;
    pkt_przec := dodaj(a, razy_stala(odejmij(b, a), k)); { a-(b-a)*k }
end;

{///////////// program wlasciwy: }

const MAX_N = 60000;
const MAX_M = 1000000;

{ wszystkie numeracje od 0 }
var 
    punkty : array[0..MAX_N-1] of Punkt;

    { krawedzie, ktorych nie ma (czyli te z wejscia) }
    brakujace_tab, { dokad krawedz }
    brakujace_next : array[0..MAX_M-1] of longint; { wskaznik na nastepna krawedz z tego wierzcholka (lub -1) }
    brakujace_first : array[0..MAX_N-1] of longint; { wskaznik na pierwsza krawedz z tego wierzcholka (lub -1) }

    ostatni : array[0..MAX_N-1] of longint; { najwiekszy wierzcholek, do ktorego mamy krawedz 
       lub -1 jesli nie zadnego wiekszego niz ostatni dla wczesniejszych wierzcholkow }

    czy_obstawiana : array[0..MAX_N-1] of boolean; { tablica tymczasowa: czy krawedz z aktualnego jest blokowana }

    { trasa }
    ile_stos : longint = 0;
    stos_nr : array[0..MAX_N-1] of longint;  { poczatek krawedzi (koniec jest w ostatni[]) }
    stos_prz : array[0..MAX_N-1] of Punkt; { punkt przeciecia z poprzednia (dla pierwszej punkt startowy) }

function czy_na_lewo(p : Punkt; a, b : longint) : boolean;
begin
    czy_na_lewo := il_wek(odejmij(p, punkty[a]), odejmij(punkty[b], punkty[a]))<0;
end;

var
    N, M, a, b, i, j, max_ost, ost, poprz : longint;
    prz : Punkt;
    dl : double;
begin
    { wczytywanie }
    readln(N, M);
    for a := 0 to N-1 do
    begin
        readln(punkty[a].x, punkty[a].y);
        brakujace_first[a] := -1;
    end;
    for a := 0 to M-1 do
    begin
        readln(i, j);
        dec(i); dec(j);
        brakujace_tab[a] := j;
        brakujace_next[a] := brakujace_first[i];
        brakujace_first[i] := a;
    end;
    
    { znajdowanie krawedzi po ktorych w ogole warto chodzic }
    max_ost := 0;
    for a := 0 to N-1 do 
    begin
        i := brakujace_first[a]; 
        while (i>=0) do
        begin
            czy_obstawiana[brakujace_tab[i]] := true;
            i := brakujace_next[i];
        end;
        ostatni[a] := -1;
        for b := N-1 downto max_ost+1 do
            if czy_obstawiana[b] then
                czy_obstawiana[b] := false
            else
            begin
                ostatni[a] := b;
                max_ost := b; { (czyli konczymy petle, dalej nie trzeba zerowac) }
                break;
            end;
        { wewnetrzna petla zrobi w sumie najwyzej M obrotow }
    end; 
    
    { szukanie trasy
      (z zalozenia jakas trasa istnieje) }
    stos_nr[0] := 0;
    stos_prz[0] := punkty[0];
    ile_stos := 1;
    for a := 1 to N-1 do
    begin
        if ostatni[a]<0 then
            continue;
        while true do
        begin
            ost := stos_nr[ile_stos-1];
            prz := pkt_przec(punkty[ost], punkty[ostatni[ost]], punkty[a], punkty[ostatni[a]]);
            { na pewno proste nie sa rownolegle (z zalozenia) }
            if ile_stos>1 then
            begin
                poprz := stos_nr[ile_stos-2]; // przedostatni
                if czy_na_lewo(prz, poprz, ostatni[poprz]) then
                begin { ostatnia krawedz na stosie niepotrzebna }
                    dec(ile_stos);
                    continue;
                end;
            end;
            stos_nr[ile_stos] := a;
            stos_prz[ile_stos] := prz;
            inc(ile_stos);
            break;
        end;
    end;
    
    { liczenie dlugosci trasy }
    stos_prz[ile_stos] := punkty[N-1]; { wstawiamy ostatni punkt }
    dl := 0;
    for a := 0 to ile_stos-1 do
        dl := dl+len(odejmij(stos_prz[a+1], stos_prz[a]));
    
    writeln(dl);
end.
