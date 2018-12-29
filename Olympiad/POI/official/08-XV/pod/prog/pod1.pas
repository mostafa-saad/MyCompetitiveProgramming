(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Podzial krolestwa (POD)                                   *
 *   Plik:     pod1.pas                                                  *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Algorytm wzorcowy O(sqrt(|V|)2^|V|).                      *
 *                                                                       *
 *************************************************************************)
program podzial;

const MAX=26;

var
    present:array [0..MAX] of longint;                // aktualny podzial krolestwa (zerojedynkowo)
    sasiedzi:array [0..MAX,0..MAX] of longint;        // tablica list sasiedztwa
    degree:array [0..MAX] of longint;                // stopnie wierzcholkow
    n,m,k,i,j,t,s,w,n2:longint;
    opt,opt_subset:longint;                        // zapamietany optymalny wynik (koszt i polowienie)
    akt,subset:longint;                                // aktualny koszt i aktualne polowienie (jako maska)

procedure xch(a:longint;b:longint);
begin
    subset:=subset xor (1 shl a);
    present[a]:=present[a] xor 1;
    k:=0;        // licznik sasiadow a z polowki oznaczonej 1
    for i:=0 to degree[a]-1 do
        inc(k,present[sasiedzi[a][i]]);
    if (present[a]=1) then
        inc(akt,degree[a]-(k shl 1))
    else
        dec(akt,degree[a]-(k shl 1));        // aktualizacja aktualnego kosztu

    // wymiana a pomiedzy polowkami

    subset:=subset xor (1 shl b);
    present[b]:=present[b] xor 1;
    k:=0;        // licznik sasiadow b z polowki oznaczonej 1
    for i:=0 to degree[b]-1 do
        inc(k,present[sasiedzi[b][i]]);
    if (present[b]=1) then
        inc(akt,degree[b]-(k shl 1))
    else
        dec(akt,degree[b]-(k shl 1));        // aktualizacja aktualnego kosztu
        
    // wymiana b pomiedzy polowkami
        
    if (akt<opt) then
    begin
        akt:=opt;
        opt_subset:=subset;
    end;
    // aktualizacja optymalnego rozwiazania
end;
// procedura do wymiany miast a i b pomiedzy polowkami

procedure perf(a:longint;b:longint);
var seeked:longint;
begin
    if (not((a=0) or (b=0))) then
    begin
        seeked:=(present[a+b-1] xor 1);        // seeked - numer polowki przeciwnej do zawierajacej miasto a+b-1, potem szukany
        if (seeked=1) then perf(a-1,b) else perf(a,b-1);
        for i:=0 to a+b-1 do
            if (present[i]=seeked) then break;        // poszukiwanie miasta do wymiany
        xch(i,a+b-1);                        // i - miasto wymieniane z ostatnim
        if (seeked=0) then perf(a-1,b) else perf(a,b-1);
    end;
end;
// procedura symulujaca ciag zmian na pierwszych a+b miastach jesli a z nich nalezy do polowki 0, b do 1

begin
    readln(n,m);
    for i:=0 to n-1 do degree[i]:=0;
    for i:=0 to m-1 do
    begin
        readln(s,t);
        dec(s); dec(t);
        sasiedzi[s][degree[s]]:=t;
        inc(degree[s]);
        sasiedzi[t][degree[t]]:=s;
        inc(degree[t]);
    end;
// wczytanie wejscia
    n2:=n shr 1; // n2=n/2
    subset:=(1 shl (n2))-1;
    for i:=0 to n-1 do
        if (i<n2) then present[i]:=1 else present[i]:=0;
// ustawienie poczatkowego polowienia
    akt:=0;
    for i:=0 to n-1 do
        for j:=0 to degree[i]-1 do
            if ((present[i] xor present[sasiedzi[i][j]])=1) then inc(akt);
// przeliczenie kosztu
        
    akt:=(akt shr 1);
    opt:=akt;
    opt_subset:=subset;
    perf(n2-1,n2);
    w:=(opt_subset and 1);        // w - zmienna sygnujaca przynaleznosc miasta nr 1
    k:=1;                        // k - iterator po potegach 2
    for i:=0 to n-1 do
    begin
        if ((not((opt_subset and k)=0))=(w=1)) then write(i+1,' ');
        k:=k shl 1;
    end;
    writeln;
end.
