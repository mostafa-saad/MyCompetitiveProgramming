(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Hurtownia                                        *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n log n)                                       *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************)

const
    MAXN = 250000;
    TS = 262144;

var
    a, n: Int64;
    tree: array[0..TS * 2] of Int64;
    b_v: array[0..MAXN] of Int64;
    b_pos: array[0..MAXN] of LongInt;
    result_v: array[0..MAXN] of LongInt;
    result_n, i: LongInt;
    hpos: LongInt;
    h_v: Int64;
    h_pos: LongInt;

{Standardowa zmiana wartosci w drzewie}
procedure chTree(pos: LongInt; v:Int64);
begin
    pos := pos + TS;
    tree[pos] := v;
    pos := pos div 2;
    while pos > 0 do begin
        tree[pos] := tree[pos * 2] + tree[pos * 2 + 1];
        pos := pos div 2;
    end;
end;

{Zwraca sume do pozycji pos}
function sumTree(pos: LongInt): Int64;
var
    res: Int64;
begin
    res := 0;
    pos := pos + TS + 1;
    while pos > 0 do begin
        if pos mod 2 = 1 then
            res := res + tree[pos - 1];
        pos := pos div 2;
    end;
    sumTree := res;
end;

{Znajduje pierwsza na lewo niezerowa pozycje}
function findNonZeroPos(pos: LongInt): LongInt;
var
    oversum: Int64;
begin
    oversum := sumTree(n) - sumTree(pos);
    pos :=  1;
    while pos < TS do begin
        pos := pos * 2;
        if(tree[pos + 1] > oversum) then inc(pos)
        else oversum := oversum - tree[pos + 1];
    end;
    findNonZeroPos := pos;
end;

{Usuwa oddane v paneli na pozycji pos}
procedure rmTree(pos: LongInt; v: Int64);
var
    av: Int64;
begin
    pos := findNonZeroPos(pos);
    while v > 0 do begin
        av := v;
        if v > tree[pos] then av := tree[pos];
        chTree(pos - TS, tree[pos] - av);
        v := v - av;
        pos := findNonZeroPos(pos - TS);
    end;
end;

Procedure QuickSort(left, right : LongInt);
var
    l_ptr, r_ptr, piv_pos: LongInt;
    pivot: Int64;
begin
    l_ptr := left;
    r_ptr := right;
    pivot := b_v[left];
    piv_pos := b_pos[left];
    while (left < right) do begin
        while (b_v[right] >= pivot) and (left < right) do
            right := right - 1;
        if left <> right then begin
            b_v[left] := b_v[right];
            b_pos[left] := b_pos[right];
            left := left + 1
        end;
        while (b_v[left] <= pivot) and (left < right) do
            left := left + 1;
        if left <> right then begin
            b_v[right] := b_v[left];
            b_pos[right] := b_pos[left];
            right := right - 1
        end
    end;
    b_v[left] := pivot;
    b_pos[left] := piv_pos;
    pivot := left;
    left := l_ptr;
    right := r_ptr;
    if left < pivot then
        QuickSort(left, pivot-1);
    if (right > pivot) then
        QuickSort(pivot+1, right);
end;

Procedure QuickSortResult(left, right : LongInt);
var
    l_ptr, r_ptr: LongInt;
    pivot: Int64;
begin
    l_ptr := left;
    r_ptr := right;
    pivot := result_v[left];
    while (left < right) do begin
        while (result_v[right] >= pivot) and (left < right) do
            right := right - 1;
        if left <> right then begin
            result_v[left] := result_v[right];
            left := left + 1
        end;
        while (result_v[left] <= pivot) and (left < right) do
            left := left + 1;
        if left <> right then begin
            result_v[right] := result_v[left];
            right := right - 1
        end
    end;
    result_v[left] := pivot;
    pivot := left;
    left := l_ptr;
    right := r_ptr;
    if left < pivot then
        QuickSortResult(left, pivot-1);
    if (right > pivot) then
        QuickSortResult(pivot+1, right);
end;

begin
    read(n);
    for i := 1 to (TS * 2) do begin
        tree[i] := 0;
    end;
    result_n := 0;
    for i := 0 to (n - 1) do begin
        read(a);
        chTree(i, a);
    end;
    for i := 0 to (n - 1) do begin
        read(b_v[i]);
        b_pos[i] := i;
    end;
    for i := 0 to (n - 1) do begin
        hpos := random(n);
        h_v := b_v[hpos];
        h_pos := b_pos[hpos];
        b_v[hpos] := b_v[i];
        b_pos[hpos] := b_pos[i];
        b_v[i] := h_v;
        b_pos[i] := h_pos;
    end;

    QuickSort(0, (n - 1));
    for i := 0 to (n - 1) do begin
        if sumTree(b_pos[i]) >= b_v[i] then begin
            rmTree(b_pos[i], b_v[i]);
            result_v[result_n] := b_pos[i] + 1;
            inc(result_n)
        end;
    end;

    for i := 0 to (result_n - 1) do begin
        hpos := random(result_n);
        h_pos := result_v[hpos];
        result_v[hpos] := result_v[i];
        result_v[i] := h_pos;
    end;

    QuickSortResult(0, (result_n - 1));
    writeln(result_n);
    for i := 0 to (result_n - 1) do begin
        write(result_v[i], ' ');
    end;
    writeln();
end.
