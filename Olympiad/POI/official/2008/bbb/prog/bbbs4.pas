(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  BBB (BBB)                                                 *
 *   Plik:     bbbs4.pas                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Algorytm O(n^3) - kwadratowy dynamik dla prostego         *
 *             przypadku implementacja w Pascalu.                        *
 *                                                                       *
 *************************************************************************)

program bbb;
const MAX=1100000;
const inf=2000*1000*1000+100;

var
    input:array[0..MAX] of char;                // wejsciowe slowo +-
    n,p,q,x,y,opt,r:longint;
    { opt - znalezione optimum }
    ch:char;
    i:longint;
    
    nowy:array[0..MAX] of longint;                // nowy wiersz do dynamika do wypelniania
    stary:array[0..MAX] of longint;                // zapamientany stary wiersz

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
var i,j:longint;
begin
    for i:=0 to n-1 do stary[i]:=inf;
    stary[0]:=0;
    // ustawienie sytuacji poczatkowej
    for i:=0 to n-1 do
    begin
        if (input[i+1]='+') then
        begin
            for j:=0 to n-1 do
                if (i+1-2*j>p) then nowy[j]:=inf else
                begin
                    nowy[j]:=stary[j]+1;
                    if ((j>0) and (nowy[j]>stary[j-1])) then nowy[j]:=stary[j-1];
                end;
        end else begin
            for j:=0 to n-1 do
                if (i+1-2*j>p) then nowy[j]:=inf else
                begin
                    nowy[j]:=stary[j];
                    if ((j>0) and (nowy[j]>stary[j-1]+1)) then nowy[j]:=stary[j-1]+1;
                end;
        end;
        // uaktualnienie dynamika odpowiednio dla + i - w ciagu wejsciowym
        for j:=0 to n-1 do stary[j]:=nowy[j];
        // przepisujemy
    end;
    exit(stary[(n+q-p) div 2]);
end;
// funkcja liczaca kwadratowo prosty przypadek

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