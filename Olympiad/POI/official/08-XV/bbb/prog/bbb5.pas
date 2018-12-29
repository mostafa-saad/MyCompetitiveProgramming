(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  BBB (BBB)                                                 *
 *   Plik:     bbb5.pas                                                  *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie autorskie, zlozonosc O(n). Implementacja      *
 *             w Pascalu.                                                *
 *                                                                       *
 *************************************************************************)

program bbb;
const MAX=1100000;
const inf=2000*1000*1000+100;

var
    input:array[0..MAX] of char;                // wejsciowe slowo +-
    height:array[0..MAX] of longint;                // wysokosci bilansu na koncie
    licz:array[0..4*MAX] of longint;                // tablica licznikowa wystapien kolejnych wysokosci (indeksowana wzgledem p-2*n)
    minimum:array[0..MAX] of longint;                // minima w oknach (wzgledem poczatku
    n,p,q,x,y,h,akt_minimum,k,M,opt,r:longint;
    { akt_minimum - aktualne minimum
      opt - znalezione optimum
      M - 2m z opracowania
      h - aktualna wysokosc balansu w czasie przetwarzania }
    ch:char;
    i:longint;

begin
    readln(n,p,q,x,y);
    h:=0;
    height[0]:=0;
    licz[2*n]:=1;
    akt_minimum:=inf;
    for i:=0 to n-1 do
    begin
        read(ch);
        if (ch='+') then inc(h) else dec(h);
        height[i+1]:=h;
        inc(licz[h+2*n]);
        if (akt_minimum>h) then akt_minimum:=h;
        input[i]:=ch;
    end;
    // przetworzenie slowa
    for i:=n to 2*n-1 do
    begin
        if (input[i-n]='+') then inc(h) else dec(h);
        dec(licz[height[i-n]+2*n]);
        if (licz[akt_minimum+2*n]=0) then inc(akt_minimum);
        inc(licz[h+2*n]);
        if (akt_minimum>h) then akt_minimum:=h;
        minimum[i-n+1]:=p+akt_minimum-height[i-n+1];
    end;
    // przetworzenie zdublowanego slowa i zapamietanie minimow okien
    opt:=inf;
    for i:=1 to n do
    begin
        if (minimum[i]>0) then M:=0 else M:=-minimum[i];
        inc(M,(M mod 2));
        if (q-p>height[n]+M) then
            k:=((q-p-height[n]) div 2)
        else
            k:=M+((height[n]-(q-p)) div 2);
        // obliczenie liczby potrzebnych zmian znaku
        r:=y*(n-i)+x*k;
        if (r<opt) then opt:=r;
        //aktualizacja optimum
    end;
    writeln(opt);
end.