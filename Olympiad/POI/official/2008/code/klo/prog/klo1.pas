(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Klocki (KLO)                                              *
 *   Plik:     klo1.pas                                                  *
 *   Autor:    Krzysztof Duleba                                          *
 *   Opis:     Sposrod n stosow klockow wybrac takie k kolejnych, by ich *
 *             wysokosci mozna bylo wyrownac dokladajac lub zdejmujac jak*
 *             najmniejsza liczbe klockow.                               *
 *             Dla ustalonych k kolejnych stosow optymalna wysokoscia    *
 *             jest mediana wysokosci. Koszt to suma odleg³osci          *
 *             wysokosci stosów od mediany. Wystarczy wiêc policzyæ      *
 *             dynamiczn± medianê.                                       *
 *                                                                       *
 *************************************************************************)
Program Klocki_1;

const
    TREE_SIZE           = 400010;
    MAX_N               = 100000;
    MAX_VALUE           = 1000000;

{ Wierzcho³ek drzewa }
type
    TreeNode = record
        value_        : Int64;
        count_        : LongInt;
        subtree_size_ : LongInt;
        subtree_sum_  : Int64;
    end;

{ Definicje przydatnych typow }
type
    TreeArray   = array[1..TREE_SIZE] of TreeNode;
    IntArray    = array[1..TREE_SIZE] of LongInt;

{ Zmienne globalne }
var
    n, k  : LongInt;

    { Wynik }
    best_error : Int64;
    best_pos   : LongInt;
    best_val   : LongInt;

    { Statyczne drzewo BST }
    tab         : TreeArray;

    { Dane z wej¶cia }
    vi          : IntArray;
    vi_sorted   : IntArray;

    { Tablica do sortowania przez zliczanie }
    count_tab   : array[0..MAX_VALUE] of LongInt;



{ Buduj drzewo }
procedure buildTree(p1, p2, idx : LongInt);
var
    pm : LongInt;
begin
    if (p1 + 1 = p2) then begin
        tab[idx].value_ := vi_sorted[p1];
    end else if p1 + 1 < p2 then begin
        pm := p1 + (p2 - p1) div 2;
        tab[idx].value_  := vi_sorted[pm];
        buildTree(p1, pm, idx * 2);
        buildTree(pm + 1, p2, idx * 2 + 1);
    end;
end;

{ Znajd¼ element w drzewie. }
function find(x : LongInt) : LongInt;
var
    idx : LongInt;
begin
    idx := 1;
    while (True) do begin
        if (x < tab[idx].value_) then begin
            idx := idx * 2;
        end else if (x > tab[idx].value_) then begin
            idx := idx * 2 + 1;
        end else begin
            exit(idx);
        end
    end;

end;

{ Popraw liczno¶æ poddrzew oraz sumê warto¶ci na ¶cie¿ce od idx do korzenia. }
procedure fix(idx : LongInt);
var
    idx2 : LongInt;
begin
    while (idx <> 1) do begin
        idx := idx div 2;
        idx2 := idx * 2;
        tab[idx].subtree_size_ := tab[idx].count_ + tab[idx2].subtree_size_ + tab[idx2 + 1].subtree_size_;
        tab[idx].subtree_sum_ := tab[idx].value_ * tab[idx].count_ + tab[idx2].subtree_sum_ + tab[idx2 + 1].subtree_sum_;
    end;
end;

{ Wstaw element do drzewa. }
procedure insert(x : LongInt);
var
    idx : LongInt;
begin
    idx := find(x);
    inc(tab[idx].count_);
    inc(tab[idx].subtree_size_);
    tab[idx].subtree_sum_ := tab[idx].subtree_sum_ + tab[idx].value_;
    fix(idx);
end;

{ Usuñ element z drzewa. }
procedure erase(x : LongInt);
var
    idx : LongInt;
begin
    idx := find(x);
    dec(tab[idx].count_);
    dec(tab[idx].subtree_size_);
    tab[idx].subtree_sum_ := tab[idx].subtree_sum_ - tab[idx].value_;
    fix(idx);
end;

function median : LongInt;
var
    sz   : LongInt;
    idx  : LongInt;
    idx2 : LongInt;
begin
    sz := tab[1].subtree_size_ div 2 + 1;
    idx := 1;
    while (True) do begin
        idx2 := idx * 2;
        if (sz <= tab[idx2].subtree_size_) then begin
            idx := idx2;
        end else if (sz <= tab[idx2].subtree_size_ + tab[idx].count_) then begin
            exit(tab[idx].value_);
        end else begin
            sz := sz - tab[idx2].subtree_size_ - tab[idx].count_;
            idx := idx2 + 1;
        end;
    end;
end;

function error: Int64;
var
    med  : Int64;
    err  : Int64;
    sz   : LongInt;
    idx  : LongInt;
    idx2 : LongInt;
begin
    med := median();
    err := 0;
    sz := tab[1].subtree_size_ div 2 + 1;
    idx := 1;
    while (True) do begin
        idx2 := idx * 2;
        if (sz <= tab[idx2].subtree_size_) then begin
            { Mediana jest po lewej, czyli jest mniejsza od aktualnej warto¶ci. }
            err := err + (tab[idx].value_ - med) * tab[idx].count_;
            err := err + tab[idx2 + 1].subtree_sum_ - med * tab[idx2 + 1].subtree_size_;
            idx := idx2;
        end else if (sz <= tab[idx2].subtree_size_ + tab[idx].count_) then begin
            err := err + med * tab[idx2].subtree_size_ - tab[idx2].subtree_sum_;
            err := err + tab[idx2 + 1].subtree_sum_ - med * tab[idx2 + 1].subtree_size_;
            exit(err);
        end else begin
            { Mediana jest po prawej, czyli jest wiêksza od aktualnej warto¶ci. }
            err := err + (med - tab[idx].value_) * tab[idx].count_;
            err := err + med * tab[idx2].subtree_size_ - tab[idx2].subtree_sum_;
            sz := sz - tab[idx2].subtree_size_ - tab[idx].count_;
            idx := idx2 + 1;
        end
    end;
end;

{ Sortowanie przez zliczanie. }
procedure sort(p, q : LongInt);
var
    i, j, t : LongInt;
begin
    for i := 0 to MAX_VALUE do
        count_tab[i] := 0;
    for i := p to q do begin
        inc(count_tab[vi_sorted[i]]);
    end;
    t := p;
    for i := 0 to MAX_VALUE do begin
        for j := 1 to count_tab[i] do begin
            vi_sorted[t] := i;
            inc(t);
        end;
    end;
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
        vi_sorted[i] := p;
    end;

    sort(1, n);
end;

{ Dynamiczna mediana. }
procedure findSolution;
var
    i    : LongInt;
    cand : Int64;
begin
    best_error := n;
    best_error := best_error * 1000000000;
    best_pos := 0;
    best_val := -1;

    for i := 1 to k - 1 do
        insert(vi[i]);
    for i := k to n do begin
        insert(vi[i]);
        cand := error();
        if (cand < best_error) then begin
            best_error := cand;
            best_pos := i;
            best_val := median();
        end;
        erase(vi[i + 1 - k]);
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
    buildTree(1, n + 1, 1);
    findSolution;
    printSolution;
end.
