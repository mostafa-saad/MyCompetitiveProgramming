(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Hurtownia                                        *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie powolne: algorytm zachlanny          *
 *                                                                       *
 *************************************************************************)

const
    MAXN = 250000;

var
    n: Int64;
    sum, a, b_v: array[0..MAXN] of Int64;
    b_pos: array[0..MAXN] of LongInt;
    result_v: array[0..MAXN] of LongInt;
    result_n, i, j: LongInt;
    hpos: LongInt;
    h_v, trm, arm: Int64;
    h_pos: LongInt;

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

procedure computeSum();
var
    i: LongInt;
begin
    sum[0] := a[0];
    for i := 1 to (n - 1) do begin
        sum[i] := sum[i - 1] + a[i];
    end;
end;

begin
    read(n);
    result_n := 0;
    for i := 0 to (n - 1) do begin
        read(a[i]);
    end;
    computeSum();
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
        if sum[b_pos[i]] >= b_v[i] then begin
            trm := b_v[i];
            j := b_pos[i];
            while trm > 0 do begin
                arm := trm;
                if a[j] < arm then
                    arm := a[j];
                trm := trm - arm;
                a[j] := a[j] - arm;
                dec(j);
            end;
            result_v[result_n] := b_pos[i] + 1;
            computeSum();
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
