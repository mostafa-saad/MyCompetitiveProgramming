(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Temperatura                                      *
 *   Autor:             Bartlomiej Wolowiec                              *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *   Zlozonosc czasowa: O(n*lg(n))                                       *
 *                                                                       *
 *************************************************************************)

program tem;

const MN = 1048576; (* 2^20 *)

var
    Drzewo : array [0..(2*MN + 100)] of longint;
    Tmax : array [0..MN] of longint;
    j,i,n,wynik : longint;


function max(a, b : longint) : longint;
begin
    if a > b then
    max := a
    else
    max := b;
end;

(* Maksimum z przedzialu <p,k> *)
function Maks (p, k : longint) : longint;
var ret : longint;
begin
    ret := -1100000000;
    p := p+MN;
    k := k+MN;
    while p<=k do begin
        if (p mod 2) = 1 then ret := max(ret, Drzewo[p]);
        if (k mod 2) = 0 then ret := max(ret, Drzewo[k]);
        p := (p+1) div 2;
        k := (k-1) div 2;
    end;
    Maks := ret;
end;

begin
    wynik := 0;
    read(n);
    for i := 0 to n-1 do
        read(Drzewo[i+MN],Tmax[i]);

    for i := MN-1 downto 1 do
        Drzewo[i] := max(Drzewo[i*2], Drzewo[i*2+1]);

    j := 1;
    for i := 0 to n-1 do begin
        while (j<n) and (Maks(i,j-1) <= Tmax[j]) do inc(j);
        wynik := max(wynik, j-i);
    end;
    writeln(wynik);
end.

