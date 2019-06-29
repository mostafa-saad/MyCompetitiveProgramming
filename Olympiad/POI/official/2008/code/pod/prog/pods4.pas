(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Podzial krolestwa (POD)                                   *
 *   Plik:     pods4.pas                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Algorytm nieoptymalny, o zlozonosci: O(2^V * E / sqrt(V)).*
 *             Przeliczanie kazdego polowienia tworzonego                *
 *             jak w algorytmie wzorcowym.                               *
 *                                                                       *
 *************************************************************************)
program podzial;

const MAX=26;

var
    present:array [0..MAX] of longint;                        // reprezentacja polowienia (dla kolejnych miast 0 lub 1)
    sasiedzi:array [0..MAX,0..MAX] of longint;                // tablica list sasiedztwa
    degree:array [0..MAX] of longint;                        // tablica stopni wierzcholkow

    n,m,a,b,i,j,v:longint;
    opt,opt_subset:longint;                        // znalezione optymalne rozwiazanie
    akt:longint;                                // aktualny koszt
    subset:longint;                                // aktualne polowienie jako maska bitowa

function przelicz():longint;
begin
    przelicz:=0;
    for i:=0 to n-1 do
        for j:=0 to degree[i]-1 do
            inc(przelicz,present[i] xor present[sasiedzi[i,j]]);
end;
// funkcja przeliczajaca koszt polowienia z present

procedure xch(a,b:longint);
begin
    subset:=subset xor (1 shl a);
    present[a]:=present[a] xor 1;
    // a w drugiej polowce

    subset:=subset xor (1 shl b);
    present[b]:=present[b] xor 1;
    // b w drugiej polowce

    akt:=przelicz();
    if (akt<opt) then
    begin
        opt:=akt;
        opt_subset:=subset;
    end;
    // przeliczamy i aktualizujemy optymalne rozwiazanie
end;
// funkcja wymieniajaca miasta a i b pomiedzy polowkami

procedure perf(k,l:longint);
var seeked,found:longint;
begin
    if ((k=0)or(l=0)) then exit;
    seeked:=present[k+l-1] xor 1; // seeked - numer polowki w ktorej nie ma miasta k+l-1,
                                  // a z ktorej bedziemy szukac miasta do wymiany
    if (seeked=1)then perf(k-1,l) else perf(k,l-1);
    for found:=0 to k+l-1 do
        if (present[found]=seeked) then break;
    xch(found,k+l-1);
    if (seeked=0)then perf(k-1,l) else perf(k,l-1);
end;
// symulacja wymian w ciagu k zer i l jedynek bedacych pierwszymi k+l miastami

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
    subset:=(1 shl (n div 2))-1;
    for i:=0 to n do
        if (i<(n div 2)) then present[i]:=1 else present[i]:=0;
    opt:=przelicz();
    opt_subset:=subset;
    // ustawianie warunkow poczatkowych
    perf((n div 2)-1,n div 2);
    v:=opt_subset and 1;         // v - zmienna sygnujaca przynaleznosc miasta 1
    for i:=0 to n-1 do
        if ((not((opt_subset and (1 shl i))=0))=(v=1)) then write(i+1,' ');
    writeln;
end.
