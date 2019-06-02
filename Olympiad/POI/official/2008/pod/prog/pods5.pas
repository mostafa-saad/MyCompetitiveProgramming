(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Podzial krolestwa (POD)                                   *
 *   Plik:     pods5.pas                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Algorytm nieoptymalny, o zlozonosci:                      *
 *             O(2^V * E / sqrt(V) + V * 2^V).                           *
 *             Przeliczanie kazdego przedzialu.                          *
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

function przelicz():longint;
begin
    przelicz:=0;
    for i:=0 to n-1 do
        for j:=0 to degree[i]-1 do
            inc(przelicz,present[i] xor present[sasiedzi[i,j]]);
end;
// funkcja przeliczajaca koszt polowienia z present

function check():boolean;
var ret:longint;
begin
    ret:=0;
    for i:=0 to n-1 do inc(ret,present[i]);
    check:=(ret=(n div 2));
end;
// funckja sprawdzajaca czy podzial jest polowieniem

procedure perf(v:longint);        // v - numer miasta ktorego przynaleznosc chcemy dobrac
begin
    if (v<n) then
    begin
        present[v]:=0; perf(v+1);
        present[v]:=1; perf(v+1);
        exit;
    end;
    // jesli nie okreslilismy jeszcze wszystkich przynaleznosci, to okreslamy na 2 sposoby

    // a jesli juz tak, to:
    if (check()) then        // sprawdzamy czy mamy polowienie
    begin
        akt:=przelicz();
        if (akt<opt) then
        begin
            opt:=akt;
            opt_subset:=0;
            for i:=0 to n-1 do opt_subset:=opt_subset xor (present[i] shl i);
        end;
        // a jak tak, to przeliczamy je i uaktualniamy optymalne rozwiazanie
    end;
end;
// backtrack - dla wszystkich podzialow sprawdzamy czy to polowienie i zapamietujemy najlepsze

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
        if (i<(n div 2)) then present[i]:=1 else present[i]:=0;
    opt:=przelicz();
    opt_subset:=(1 shl (n div 2))-1;
    // ustawianie warunkow poczatkowych
    perf(1);
    v:=opt_subset and 1;         // v - zmienna sygnujaca przynaleznosc miasta 1
    for i:=0 to n-1 do
        if ((not((opt_subset and (1 shl i))=0))=(v=1)) then write(i+1,' ');
    writeln;
end.
