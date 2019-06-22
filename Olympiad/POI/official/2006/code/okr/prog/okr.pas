(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi-zanie zadania: OKR (Okresy s³ów)                              *
 *   Plik:                okr.pas                                        *
 *   Autor:               Karol Cwalina                                  *
 *   Opis:                Rozwiazanie optymalne.                         *
 *                        Zlozonosc obliczeniowa O(n)                    *
 *                                                                       *
 *************************************************************************)

program okresy_slow;
const MaxN=1000000;
var i,n : LongInt;
    odp : Int64;
    tekst : array [1..MaxN] of Char;
    P, MinP : array [0..MaxN] of LongInt;
    
    procedure LiczP;
    var i,t : LongInt;
    begin
        P[0] := 0; P[1] := 0;
        t := 0;
        for i := 2 to n do begin
            while (t > 0) and (tekst[i] <> tekst[t+1]) do t := P[t];
            if tekst[i] = tekst[t+1] then Inc(t);
            P[i] := t;
        end;
    end;
    
begin
    Readln(n);
    for i := 1 to n do Read(tekst[i]);
    
    LiczP;
    odp := 0;
    for i := 1 to n do begin
        if P[i] = 0 then begin
            MinP[i] := 0;
            continue;
        end;
        if P[P[i]] = 0 then
            MinP[i] := P[i]
        else
            MinP[i] := MinP[ P[i] ];
        odp := odp+i-MinP[i];
    end;

    Writeln (odp);
end.