(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Kurierzy                                      *
 *   Zlozonosc czasowa:    O(k(n+m))                                     *
 *   Zlozonosc pamieciowa: O(n+mk)                                       *
 *   Opis:                 Rozwiazanie alternatywne                      *
 *                                                                       *
 *************************************************************************)

const
    MAXN = 500*1000;
    MAXM = 500*1000;
    PROB = 26;

var
    firma, n, m, i, a, b, j, idZapytania, zap : LongInt;
    paczki, firmy, ileZapytan : array[0 .. MAXN + 1] of LongInt;
    pocz, kon : array[0 .. MAXM] of LongInt;
    poczatkiPrzedzialow, odpowiedzi : array[0 .. MAXM] of LongInt;
    potencjalniMonopolisci, potencjalniMonopolisciIloscPaczek : array[0 .. MAXM, 0 .. PROB] of LongInt;
    zapytania : array[0 .. 2 * MAXM] of LongInt;

begin
    Randomize;
    Read(n, m);
    paczki[0] := 0;
    for i := 1 to n do
        Read(paczki[i]);
    paczki[n + 1] := 0;

    for i := 0 to n + 1 do begin
        ileZapytan[i] := 0;
        firmy[i] := 0;
    end;
    for i := 0 to m - 1 do begin
        Read(a, b);
        pocz[i] := a; kon[i] := b;
        Inc(ileZapytan[a]);
        Inc(ileZapytan[b + 1]);
        poczatkiPrzedzialow[i] := a;
        for j := 0 to PROB - 1 do
            potencjalniMonopolisci[i][j] := paczki[a + Random(b - a + 1)];
    end;
    
    for i := 2 to n + 1 do
        ileZapytan[i] := ileZapytan[i] + ileZapytan[i - 1];
    for i := 0 to m - 1 do begin
        zapytania[ileZapytan[pocz[i] - 1] + 1] := i;
        Inc(ileZapytan[pocz[i] - 1]);
        zapytania[ileZapytan[kon[i]] + 1] := -i - 1;
        Inc(ileZapytan[kon[i]]);
    end;
    for i := n + 1 downto 1 do
        ileZapytan[i] := ileZapytan[i - 1];
    ileZapytan[0] := 0;

    for i := 1 to n + 1 do begin
        for zap := ileZapytan[i - 1] + 1 to ileZapytan[i] do begin
            if zapytania[zap] >= 0 then begin
                idZapytania := zapytania[zap];
                for j := 0 to PROB - 1 do begin
                    firma := potencjalniMonopolisci[idZapytania][j];
                    potencjalniMonopolisciIloscPaczek[idZapytania][j] := firmy[firma];
                end
            end else begin
                idZapytania := -zapytania[zap] - 1;
                for j := 0 to PROB - 1 do begin
                    firma := potencjalniMonopolisci[idZapytania][j];
                    if 2 * (firmy[firma]-potencjalniMonopolisciIloscPaczek[idZapytania][j]) >
                            i - poczatkiPrzedzialow[idZapytania] then
                        odpowiedzi[idZapytania] := firma;
                end
            end
        end;
        Inc(firmy[paczki[i]]);
    end;
    for i := 0 to m - 1 do
        Writeln(odpowiedzi[i]);
end.
