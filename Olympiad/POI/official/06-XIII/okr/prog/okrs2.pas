(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: OKR (Okresy s³ów)                              *
 *   Plik:                okrs2.pas                                      *
 *   Autor:               Karol Cwalina                                  *
 *   Opis:                Rozwiazanie O(n^2), modyfikacja rozwiazanie    *
 *                        brutalnego, hashuje lancuchy                   *
 *                                                                       *
 *************************************************************************)

program okresy_slow;
const MaxN=1000000;
const BASE=26;
const PRIME=3021377;
var i,j,k,n : LongInt;
    pref_hash,suf_hash,d : LongInt;
    odp : Int64;
    ok : Boolean;
    tekst : array [1..MaxN] of Char;

begin
    Readln(n);
    for i := 1 to n do Read(tekst[i]);

    odp := 0;
    for i := 1 to n do begin
        pref_hash := 0; suf_hash := 0; d := 1;
        for j := i downto (i+3) div 2 do begin
            pref_hash := (pref_hash + (Ord(tekst[i-j+1])-Ord('a'))*d) mod PRIME;
            suf_hash := (BASE*suf_hash + Ord(tekst[j])-Ord('a')) mod PRIME;
            d := (BASE*d) mod PRIME;
            if pref_hash = suf_hash then begin
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
        end;
    end;

    Writeln (odp);
end.
