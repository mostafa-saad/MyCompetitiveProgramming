(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  BBB (BBB)                                                 *
 *   Plik:     bbbs2.pas                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Algorytm O(n^2) - prosty przypadek n razy, implementacja  *
 *             w Pascalu.                                                *
 *                                                                       *
 *************************************************************************)

program bbb;
const MAX=1100000;
const inf=2000*1000*1000+100;

var
    input:array[0..MAX] of char;                // wejsciowe slowo +-
    n,p,q,x,y,h,a,b,m,opt,r:longint;
    { a,b,m - zgodnie z opracowaniem
      opt - znalezione optimum
      h - aktualna wysokosc balansu w czasie przetwarzania }
    ch:char;
    i:longint;

procedure przesun();
var l:char;
    j:longint;
begin
    l:=input[n];
    for j:=n-1 downto 1 do input[j+1]:=input[j];    
    input[1]:=l;
end;
// funkcja przesuwajaca wejscie cyklicznie o 1

function zrob_prosty():longint;
var j:longint;
begin
    h:=p; a:=p;
    for j:=1 to n do
    begin
        if (input[j]='+') then inc(h) else dec(h);
        if (h<a) then a:=h;
    end;
    // liczymy a
    b:=h-p;
    // liczymy b
    if (a>0) then m:=0 else m:=((-a+1) div 2);
    // liczymy m
    if ((q-p)>(b+2*m)) then
        exit((q-p-b) div 2)
    else
        exit(2*m+((b-(q-p)) div 2));
    // liczymy ile musi byc zmian znaku
end;
// funkcja liczaca liniowo prosty przypadek

begin
    readln(n,p,q,x,y);
    for i:=1 to n do
    begin
        read(ch);
        input[i]:=ch;
    end;
    opt:=inf;
    for i:=0 to n-1 do
    begin
        if (i*y>=opt) then break;        // jesli przesuniecie kosztowniejsze od optimum, uciekamy
        r:=y*i+zrob_prosty()*x;
        if (r<opt) then opt:=r;
        //aktualizacja optimum
        przesun();
    end;
    writeln(opt);
end.