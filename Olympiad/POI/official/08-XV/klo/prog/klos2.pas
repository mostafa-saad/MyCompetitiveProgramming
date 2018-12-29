(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Klocki (KLO)                                              *
 *   Plik:     klos2.pas                                                 *
 *   Autor:    Krzysztof Duleba                                          *
 *   Opis:     Sposrod n stosow klockow wybrac takie k kolejnych, by ich *
 *             wysokosci mozna bylo wyrownac dokladajac lub zdejmujac jak*
 *             najmniejsza liczbe klockow.                               *
 *             Rozwiazanie nieefektywne: ka¿dorazowe liczenie mediany    *
 *             sortowaniem przez zliczanie.                              *
 *                                                                       *
 *************************************************************************)
Program Klocki_1;

const
    TREE_SIZE           = 400010;
    MAX_N               = 100000;
    MAX_VALUE           = 1000000;

{ Definicje przydatnych typow }
type
    IntArray    = array[1..TREE_SIZE] of LongInt;

{ Zmienne globalne }
var
    n, k  : LongInt;

    { Wynik }
    best_error : Int64;
    best_pos   : LongInt;
    best_val   : LongInt;

    { Dane z wej¶cia }
    vi          : IntArray;

    { Tablica do sortowania przez zliczanie }
    count_tab   : array[0..MAX_VALUE] of LongInt;


{ Mediana przez sortowanie przez zliczanie. }
function median(p, q : LongInt): LongInt;
var
    i, cnt : LongInt;
begin
    for i := 0 to MAX_VALUE do
        count_tab[i] := 0;
    for i := p to q do begin
        inc(count_tab[vi[i]]);
    end;
    cnt := (q + 2 - p) div 2;
    for i := 0 to MAX_VALUE do begin
        if (cnt <= count_tab[i]) then exit(i);
        cnt := cnt - count_tab[i];
    end;
end;


function error(med, p, q : LongInt): Int64;
var
    i   : LongInt;
    err : Int64;
begin
    err := 0;
    for i := p to q do begin
        err := err + abs(vi[i] - med);
    end;
    exit(err);
end;


{ Wczytaj dane wejsciowe }
procedure readInput;
var
    i, p : LongInt;
begin
    read(n, k);
    for i := 1 to n do begin
        read(p);
        vi[i] := p;
    end;
end;

{ Dynamiczna mediana. }
procedure findSolution;
var
    i    : LongInt;
    med  : LongInt;
    cand : Int64;
begin
    best_error := n;
    best_error := best_error * 1000000000;
    best_pos := 0;
    best_val := -1;

    for i := k to n do begin
        med := median(i + 1 - k, i);
        cand := error(med, i + 1 - k, i);
        if (cand < best_error) then begin
            best_error := cand;
            best_pos := i;
            best_val := med;
        end;
    end;
end;

procedure printSolution;
var
    i : LongInt;
begin
    writeln(best_error);
    for i := best_pos + 1 - k to best_pos do
        vi[i] := best_val;
    for i := 1 to n do
        writeln(vi[i]);
end;

{ Glowna funkcja programu }
begin
    readInput;
    findSolution;
    printSolution;
end.
