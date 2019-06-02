(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Bar salatkowy                                 *
 *   Autor:                Michal Adamczyk                               *
 *   Zlozonosc czasowa:    O(n log^2 n)                                  *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************)

program BarSalatkowy;

const max_n = 1000000;
const max_mm = 2097152;

var
    n, M, st_head, mx, i, tmp : longint;
    sum, mnsuf : array[0..max_mm] of longint;
    st_sum, st_jump : array[0..max_n-1] of longint;
    s : array[0..max_n] of char;

function min(a, b: longint) : longint;
begin
    if a < b then
        min := a
    else
        min := b;
end;

procedure tinit();
begin
    M := 1;
    while (n >= M) do
        M := M * 2;
end;

procedure tinsert(x, vv : longint);
var
    v, ls, rs : longint;
begin
    v := M + x;
    sum[v] := vv; mnsuf[v] := vv;
    while (not (v = 1)) do
    begin
        v := v div 2;
        ls := v << 1;
        rs := ls + 1;
        sum[v] := sum[ls] + sum[rs];
        mnsuf[v] := min(mnsuf[rs], sum[rs]+mnsuf[ls]);
    end;
end;

function mnsuf_query(a, b : longint) : longint;
var
    va, vb, mnsufA, sumA, mnsufB, sumB : longint;
begin
    va := M + a; vb := M+b;
    mnsufA := sum[va]; sumA := sum[va];
    mnsufB := sum[vb]; sumB := sum[vb];
    while (not  ((va div 2) = (vb div 2))) do
    begin
        if (va mod 2) = 0 then
        begin
            mnsufA := min(mnsufA+sum[va+1], mnsuf[va+1]);
            sumA := sumA + sum[va+1];
        end;
        if (vb mod 2) = 1 then
        begin
            mnsufB := min(mnsufB, mnsuf[vb-1]+sumB);
            sumB := sumB + sum[vb-1];
        end;
        va := va div 2;
        vb := vb div 2;
    end;
    if (not (a = b)) then
        mnsuf_query := min(mnsufB, mnsufA + sumB)
    else
        mnsuf_query := mnsufB;
end;

procedure preprocess();
var
    i : longint;
begin
    tinit();
    for i := 0 to n-1 do
        if (s[i] = 'p') then
            tinsert(i, 1)
        else
            tinsert(i, -1);
end;

function max_left_jump(k: longint): longint;
var
    b, e, mid, best : longint;
begin
    b := 0; e := st_head; best := st_head;
    while (b < e) do
    begin
        mid := (b + e) div 2;
        if (mnsuf_query(st_jump[mid], k) >= 0) then
        begin
            e := mid - 1;
            best := mid;
        end else
        begin
            b := mid + 1;
        end;
    end;
    if ((best > 0) and (mnsuf_query(st_jump[best-1], k) >= 0)) then
        dec(best);

    max_left_jump := k - st_jump[best] + 1;
end;

begin
    st_head := 0;
    mx := 0;
    readln(n);
    readln(s);

    preprocess();

    for i := 0 to n-1 do
    begin
        if s[i] = 'p' then
        begin
            st_jump[st_head] := i;
            st_sum[st_head] := 1;
            inc(st_head);
            tmp := max_left_jump(i);
            if (tmp > mx) then
                mx := tmp;
        end else
        begin
            while ((st_head > 0) and (st_sum[st_head-1] = 0)) do
                dec(st_head);
            if st_head > 0 then
                dec(st_sum[st_head-1]);
        end;
    end;
    writeln(mx);
end.
