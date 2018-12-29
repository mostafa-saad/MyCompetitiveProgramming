(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Podzial krolestwa (POD)                                   *
 *   Plik:     pod4.pas                                                  *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Algorytm wzorcowy O(2^|V| / sqrt(|V|)). Implementacja     *
 *             na maskach bitowych na podstawie pomyslu Marka Cygana.    *
 *                                                                       *
 *************************************************************************)
program podzial;

const MAX=26;
const MAX_labeled=35000;

var
    dig_sum:array [0..MAX_labeled] of longint;  // tablica binarnych sum cyfr
    lst_found:array [0..MAX_labeled,0..1] of longint;        // lst_found[x][c] to najmniejsza pozycja binarna x na ktorej jest cyfra c

    maski:array [0..MAX] of longint;                // maski bitowe reprezentujace wiersze macierzy sasiedztwa
    degree:array [0..MAX] of longint;                // stopnie wierzcholkow
    n,m,k,i,j,t,s,w,n2:longint;
    opt,opt_subset:longint;                        // zapamietany optymalny wynik (koszt i polowienie)
    akt,subset:longint;                                // aktualny koszt i aktualne polowienie (jako maska)

function dig_sum_label(g:longint):longint;
begin
    dig_sum_label:=0;
    for i:=0 to 14 do if ((g and (1 shl i))<>0) then inc(dig_sum_label);
end;

function last_found_label(g,digit:longint):longint;
begin
    for last_found_label:=0 to 15 do
        if ((digit=0)=((g and (1 shl last_found_label))=0)) then break;
    if (last_found_label>14) then last_found_label:=1000;
end;

procedure mk_label();
var i:longint;
begin
    for i:=0 to MAX_labeled do
    begin
        dig_sum[i]:=dig_sum_label(i);
        lst_found[i][0]:=last_found_label(i,0);
        lst_found[i][1]:=last_found_label(i,1);
    end;
end;

function digit_sum(g:longint):longint;
begin
    digit_sum:=dig_sum[g and ((1 shl 15)-1)]+dig_sum[g shr 15];
end;

function last_found(g,digit:longint):longint;
var left,right:longint;
begin
    left:=15+lst_found[g shr 15][digit];
    right:=lst_found[g and ((1 shl 15)-1)][digit];
    if (left>right) then exit(right) else exit(left);
end;

procedure xch(a:longint;b:longint);
begin
    subset:=subset xor (1 shl a);
    k:=digit_sum(maski[a] and subset);
    if ((subset and (1<<a))<>0) then
        inc(akt,degree[a]-(k shl 1))
    else
        dec(akt,degree[a]-(k shl 1));        // aktualizacja aktualnego kosztu

    // wymiana a pomiedzy polowkami

    subset:=subset xor (1 shl b);
    k:=digit_sum(maski[b] and subset);
    if ((subset and (1<<b))<>0) then
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
var seeked:boolean;
    i:longint;
begin
    if (not((a=0) or (b=0))) then
    begin
        seeked:=((subset and (1 shl (a+b-1))<>0) xor true);        // seeked - numer polowki przeciwnej do zawierajacej miasto a+b-1, potem szukany
        if (seeked) then perf(a-1,b) else perf(a,b-1);
        for i:=0 to a+b-1 do
            if ((subset and (1 shl i)<>0)=seeked) then break;        // poszukiwanie miasta do wymiany
        xch(i,a+b-1);                        // i - miasto wymieniane z ostatnim
        if (not(seeked)) then perf(a-1,b) else perf(a,b-1);
    end;
end;
// procedura symulujaca ciag zmian na pierwszych a+b miastach jesli a z nich nalezy do polowki 0, b do 1

begin
    mk_label();
    readln(n,m);
    for i:=0 to n-1 do
    begin
        degree[i]:=0;
        maski[i]:=0;
    end;
    for i:=0 to m-1 do
    begin
        readln(s,t);
        dec(s); dec(t);
        maski[s]:=maski[s] or (1 shl t);
        maski[t]:=maski[t] or (1 shl s);
        inc(degree[s]);
        inc(degree[t]);
    end;
// wczytanie wejscia
    n2:=n shr 1; // n2=n/2
    subset:=(1 shl (n2))-1;
// ustawienie poczatkowego polowienia
    akt:=0;
    for i:=0 to n-1 do
        for j:=0 to n-1 do
            if (((maski[i] and (1 shl j))<>0) and
                    (((subset and (1 shl i))<>0) xor ((subset and (1 shl j))<>0) )
                    ) then inc(akt);
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
