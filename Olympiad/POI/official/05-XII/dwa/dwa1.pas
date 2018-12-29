(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: DWA (Dwa przyjêcia)                            *
 *   Plik:                dwa1.pas                                       *
 *   Autor:               Krzysztof Onak                                 *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                        Jezyk: Pascal                                  *
 *                                                                       *
 *************************************************************************)

Program Dwa_przyjecia_2;
const
    MAXN = 200;
    NOT_FOUND = -1; 

var
    n : Integer; {liczba wierzcho³ków}
    e : array [1..MAXN] of array [1..MAXN] of Boolean; {macierzowa reprezentacja grafu}
    solution: array [1..MAXN] of Boolean; {rozwi±zanie}
    inGraph: array [1..MAXN] of Boolean; { czy nale¿y do rozwa¿anego aktualnie podgrafu? }

{odczytywanie wej¶cia}
procedure readInput;
var
    i, j, d, v : Integer;
begin
    Read(n);
    for i := 1 to n do begin
        for j := 1 to n do begin
            e[i][j] := False;
        end;
        Read(d);
        for j := 1 to d do begin
            Read(v);
            e[i][v] := True;
        end;
    end;
    for i := 1 to n do
       inGraph[i] := True
end;

{ zapisz rozwi±zanie }
procedure writeOutput;
var
    i, counter : Integer;
begin
    counter := 0;
    for i := 1 to n do
        if solution[i] then
            Inc(counter);
    Writeln(counter);
    for i := 1 to n do
        if solution[i] then begin
            Write(i);
            Dec(counter);
            if counter > 0 then
                Write(' ')
        end;
    Writeln
end;

{ znajd¼ wierzcho³ek nieparzystego stopnia w aktualnie }
{   rozpatrywanym grafie }
function odd : Integer;
var
    j, k, neighbors : Integer;
begin
    for k := 1 to n do 
        if inGraph[k] then begin
            neighbors := 0;
            for j := 1 to n do
                if inGraph[j] and e[k][j] then
                    Inc(neighbors);
            if neighbors mod 2 = 1 then
                break;
        end;
    if k = n then
        odd := NOT_FOUND
    else
        odd := k;
end;

{ rekurencyjne rozwi±zanie zgodnie z opracowaniem }
procedure solve;
var
    i, j, v, neighbors, party : Integer;
    who : array [1..MAXN] of Integer;
begin
    { szukamy wierzcho³ka nieparzystego stopnia }
    v := odd;
    if v <> NOT_FOUND then begin
        { znajdujemy wszystkich s±siadów }
        neighbors := 0; 
        for j := 1 to  n do
            if inGraph[j] and e[v][j] then begin
                inc(neighbors);
                who[neighbors] := j;
            end;
        { usuwamy wierzcho³ek v }
        inGraph[v] := False;
        { usuwamy co jest, dodajemy czego nie ma }
        for i := 1 to  neighbors do
            for j := 1 to neighbors do
                if i <> j then
                    e[who[i]][who[j]] := not e[who[i]][who[j]];
        { rozwi±zanie mniejszego problemu }
        solve;
        { przydzia³ do odpowiedniego przyjêcia }
        party := 0;
        for i := 1 to neighbors do
            if solution[who[i]] then
                Inc(party);
        if party mod 2 = 0 then
            solution[v] := True
        else
            solution[v] := False;
    end else begin
        { przydzielamy wszystkich do tego samego przyjêcia }
        for i := 1 to n do
            if inGraph[i] then
                solution[i] := False;
    end
end;

begin
    readInput;
    solve;
    writeOutput;
end.
