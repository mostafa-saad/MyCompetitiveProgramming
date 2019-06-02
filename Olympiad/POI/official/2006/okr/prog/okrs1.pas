(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: OKR (Okresy s³ów)                              *
 *   Plik:                okrs1.pas                                      *
 *   Autor:               Karol Cwalina                                  *
 *   Opis:                Rozwiazanie brutalnie poprawne, czas O(n^3)    *
 *                                                                       *
 *************************************************************************)

program okresy_slow;
const MaxN=1000000;
var i,j,k,n : LongInt;
    odp : Int64;
    ok : Boolean;
    tekst : array [1..MaxN] of Char;

begin
    Readln(n);
    for i := 1 to n do Read(tekst[i]);

    odp := 0;
    for i := 1 to n do
        for j := i downto (i+3) div 2 do begin
            ok := True;
            for k := 0 to i-j do
                if tekst[k+1] <> tekst[k+j] then begin
                    ok := False;
                    break;
                end;
            if ok then begin
                odp := odp+j-1;
                break;
            end;
        end;

    Writeln (odp);
end.
