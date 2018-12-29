(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Podzial krolestwa (POD)                                   *
 *   Plik:     pods6.pas                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Algorytm prawie optymalny, o zlozonosci: O(V * 2^V).      *
 *             Symulacja wymian na wszystkich podzbiorach.               *
 *                                                                       *
 *************************************************************************)
program podzial;

const MAX=26;

var
    present:array [0..MAX] of longint;                        // reprezentacja polowienia (dla kolejnych miast 0 lub 1)
    sasiedzi:array [0..MAX,0..MAX] of longint;                // tablica list sasiedztwa
    degree:array [0..MAX] of longint;                        // tablica stopni wierzcholkow

    n,m,a,b,i,j,v,ile:longint;                        // ile - liczba miast w polowce z numerem 1
    opt:longint;                                
    opt_subset:array[0..MAX] of longint;        // znalezione optymalne rozwiazanie
    akt:longint;                                // aktualny koszt

procedure xch(a:longint);
var k:longint;
begin
    if (present[a]=1) then dec(ile) else inc(ile); // aktualizacja ile
    present[a]:=present[a] xor 1;
    k:=0;
    for i:=0 to degree[a]-1 do inc(k,present[sasiedzi[a,i]]);
    if (present[a]=1) then
        inc(akt,degree[a]-(k shl 1))
    else
        dec(akt,degree[a]-(k shl 1));
    // aktualizacja aktualnego kosztu
    if ((ile=(n div 2))and(akt<opt)) then
    begin
        opt:=akt;
        for i:=0 to n-1 do opt_subset[i]:=present[i];
    end;
end;
// funkcja zmieniajaca przynaleznosc miasta a

procedure perf(v:longint);        // v - numer miasta ktorego przynaleznosc chcemy dobrac
begin
    if (v<n) then
    begin
        perf(v+1);
        xch(v);
        perf(v+1);
    end;
end;
// funkcja rekurencyjna przegladajaca wszystkie podzialy - przeglada z aktualnie zapisana przynaleznoscia miasta v,
// po czym ja zmienia i przeglada jeszcze raz. po drodze tylko zmienia po jednym 'bicie'

begin
    readln(n,m);
    for i:=0 to n-1 do degree[i]:=0;
    for i:=0 to m-1 do
    begin
        readln(a,b);
        dec(a); dec(b);
        sasiedzi[a,degree[a]]:=b;
        inc(degree[a]);
        sasiedzi[b,degree[b]]:=a;
        inc(degree[b]);
    end;
    // wczytywanie wejscia
    for i:=0 to n do
    begin
        present[i]:=0;
        opt_subset[i]:=0;
    end;
    opt:=1000;
    // ustawianie warunkow poczatkowych
    perf(1);
    v:=opt_subset[0];         // v - zmienna sygnujaca przynaleznosc miasta 1
    for i:=0 to n-1 do
        if (opt_subset[i]=v) then write(i+1,' ');
    writeln;
end.
