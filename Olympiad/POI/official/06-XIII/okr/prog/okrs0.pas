(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: OKR (Okresy s³ów)                              *
 *   Plik:                okrs0.pas                                      *
 *   Autor:               Karol Cwalina                                  *
 *   Opis:                Znajduje dlugosc pasujacego na danej pozycji   *
 *                        prefiksu, czas O(n^2)                          *
 *                                                                       *
 *************************************************************************)

program okresy_slow;
const MaxN=1000000;
var i,j,max_pref,n : LongInt;
    odp : Int64;
    tekst : array [1..MaxN+1] of Char;
    pref : array [1..MaxN] of LongInt;

begin
    Readln(n);
    for i := 1 to n do Read(tekst[i]);
    tekst[n+1] := '$';

    pref[1] := 0;
    for i := 2 to n do begin
        j := 0;
        while tekst[i+j] = tekst[j+1] do Inc(j);
        pref[i] := j;
    end;

    odp := 0; max_pref := 0;
    for i := 2 to n do begin
        if i+pref[i]-1 > max_pref then max_pref := i+pref[i]-1;
        if max_pref < i then continue;
        for j := i downto (i+3) div 2 do
            if j+pref[j] > i then begin
                odp := odp+j-1;
                break;
            end;
    end;

    Writeln (odp);
end.
