(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KOS (Kosci)                                    *
 *   Plik:                kos1.cpp                                       *
 *   Autor:               Piotr Stañczyk (stanczyk@mimuw.edu.pl)         *
 *   Opis:                Rozwiazanie alternatywne                       *
 *                                                                       *
 *************************************************************************)
Program Kosci_1;

const MAXSIZE = 10000;

type krawe = record
    nast, poprz     : longint;
    pocz, kon       : longint;
    obr             : boolean;
end;

type wierzch = record
    nast, poprz     : longint; // Lista dwukierunkowa wierzcholkow o tym samym stopniu
    knast, kpoprz   : longint; // Lista krawedzi
    stopien         : longint; // Stopien wyjsciowy wierzcholka
    odwiedz         : boolean; // Czy wierzcholek byl odpowiedzony przez BFS
end;

var
    graf            : ARRAY [1..MAXSIZE] of wierzch;
    kraw            : ARRAY [1..MAXSIZE] of krawe;
    stopn           : ARRAY [0..MAXSIZE] of longint;
    stopp           : ARRAY [0..MAXSIZE] of longint;
    gr, roz, actmax : longint;
    kp, kk, x, p, k : longint;
    kolejka         : ARRAY [0..MAXSIZE] of longint;
    zrodlo          : ARRAY [0..MAXSIZE] of longint;
    ojciec          : ARRAY [0..MAXSIZE] of longint;


{ Procedura wstawia krawedz kr na liste krawedzi wierzcholka wie }
procedure WstawKrawedz(kr : longint);
var
    wie : longint;
begin
    wie := kraw[kr].pocz;
    kraw[kr].nast := graf[wie].knast;
    kraw[kr].poprz := 0;
    if (graf[wie].knast <> 0) then
    begin
        kraw[graf[wie].knast].poprz := kr;
    end else
        graf[wie].kpoprz := kr;
    graf[wie].knast := kr;
end;

{ Procedura usuwa krawedz kr z listy incydencji }
procedure UsunKrawedz(kr : longint);
var
    wie : longint;
begin
    wie := kraw[kr].pocz;
    if (kraw[kr].poprz = 0) then
    begin
        graf[wie].knast := kraw[kr].nast;
    end else
    begin
        kraw[kraw[kr].poprz].nast := kraw[kr].nast;
    end;

    if (kraw[kr].nast = 0) then
    begin
        graf[wie].kpoprz := kraw[kr].poprz;
    end else
    begin
        kraw[kraw[kr].nast].poprz := kraw[kr].poprz;
    end;
end;    

{ Procedura wstawia wierzcholek na liste wierzcholkow o okreslonym stopniu }
procedure WstawStopien(wie : longint);
var
    list : longint;
begin
    list := graf[wie].stopien;
    graf[wie].nast := stopn[list];
    graf[wie].poprz := 0;
    if (stopn[list] <> 0) then
    begin
        graf[stopn[list]].poprz := wie;
    end else
        stopp[list] := wie;
    stopn[list] := wie;
end;

{ Procedura usuwa wierzcholek z listy wierzcholkow o danym stopniu }
procedure UsunStopien(wie : longint);
var
    list : longint;
begin
    list := graf[wie].stopien;
    if (graf[wie].poprz = 0) then
    begin
        stopn[list] := graf[wie].nast;
    end else
    begin
        graf[graf[wie].poprz].nast := graf[wie].nast;
    end;

    if (graf[wie].nast = 0) then
    begin
        stopp[list] := graf[wie].poprz;
    end else
    begin
        graf[graf[wie].nast].poprz := graf[wie].poprz;
    end;
end;    


{ Procedura laczy krawedzia dwa wierzcholki }
procedure Polacz(p, k, nr : longint);
begin
    inc(graf[p].stopien);
    kraw[nr].obr := false;
    kraw[nr].pocz := p;
    kraw[nr].kon := k;
    WstawKrawedz(nr);
end;

{ BFS, ktory wyszukuje sciezki laczace wierzcholki o najwiekszym stopniu wyjsciowym   }
{ z wierzcholkami o stopniu o co najmniej 2 mniejszym i odwraca kierunek tych sciezek }
function Zmniejsz : boolean;
var
    iter   : longint;
    iter2  : longint;
    tmp    : longint;
begin
    Zmniejsz := false;
    kp := 0;
    kk := 0;
    for tmp := 1 to gr do
        graf[tmp].odwiedz := false;
    iter := stopn[actmax];
    while (iter <> 0) do
    begin
        zrodlo[kk] := iter;
        graf[iter].odwiedz := true;
        ojciec[iter] := 0;
        kolejka[kk] := iter;
        inc(kk);
        iter := graf[iter].nast;
    end;
    while (kp < kk) do
    begin
        if (graf[zrodlo[kp]].stopien = actmax) then
        begin
            iter := graf[kolejka[kp]].knast;
            while (iter <> 0) do
            begin
                if (graf[kraw[iter].kon].odwiedz = false) then
                begin
                    kolejka[kk] := kraw[iter].kon;
                    graf[kraw[iter].kon].odwiedz := true;
                    ojciec[kraw[iter].kon] := iter;
                    zrodlo[kk] := zrodlo[kp];
                    inc(kk);
                    if (graf[kolejka[kk-1]].stopien < actmax - 1) then
                    begin
                        Zmniejsz := true;
                        UsunStopien(kolejka[kk-1]);
                        inc(graf[kolejka[kk-1]].stopien);
                        WstawStopien(kolejka[kk-1]);
                        UsunStopien(zrodlo[kp]);
                        dec(graf[zrodlo[kp]].stopien);
                        WstawStopien(zrodlo[kp]);
                        iter2 := iter;
                        while (iter2 <> 0) do
                        begin
                            UsunKrawedz(iter2);
                            tmp := kraw[iter2].pocz;
                            kraw[iter2].pocz := kraw[iter2].kon;
                            kraw[iter2].kon := tmp;
                            kraw[iter2].obr := not kraw[iter2].obr;
                            WstawKrawedz(iter2);
                            iter2 := ojciec[kraw[iter2].kon];
                        end;
                        exit;
                    end;
                end;
                iter := kraw[iter].nast;
            end;
        end;
        inc(kp);
    end;
end;

begin
    Readln(gr, roz);
    for x := 1 to gr do
    begin
        graf[x].nast := 0;
        graf[x].poprz := 0;
        graf[x].knast := 0;
        graf[x].kpoprz := 0;
        graf[x].stopien := 0;
        graf[x].odwiedz := false;
    end;
    stopn[0] := 0;
    stopp[0] := 0;
    for x := 1 to roz do
    begin
        stopn[x] := 0;
        stopp[x] := 0;
        kraw[x].nast := 0;
        kraw[x].poprz := 0;
    end;
    for x := 1 to roz do
    begin
        Readln(p, k);
        Polacz(p, k, x);
    end;
    for x := 1 to gr do
        WstawStopien(x);

    actmax := MAXSIZE;
    kk := 0;
    while true do
    begin
        if stopn[actmax] = 0 then 
        begin
            dec(actmax);
        end else
        if (not Zmniejsz()) then
            break;
    end;
    Writeln(actmax);
    for x := 1 to roz do
        if kraw[x].obr = true then
        begin
            Writeln(0);
        end else
            Writeln(1);
end.
