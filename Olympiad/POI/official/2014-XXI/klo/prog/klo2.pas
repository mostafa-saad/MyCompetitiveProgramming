(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Klocki                                        *
 *   Autor:                Karol Farbis                                  *
 *   Zlozonosc czasowa:    O(k log k + n)                                *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************)

const
    N = 1000000;

type
    pair = record
        first, second : longint;
    end;

var
    a : array[1..N] of longint;
    to_sort : array[1..N] of pair;
    tmp : array[1..N] of pair;
    ans : array[1..N] of longint;

function make_pair(st, nd : longint) : pair;
var
    x : pair;
begin
    x.first := st;
    x.second := nd;
    make_pair := x;
end;

function cmp(p1, p2: pair): boolean;
begin
    if p1.first <> p2.first then
        cmp := p1.first > p2.first
    else
        cmp := p1.second > p2.second;
end;

procedure my_swap(var a : longint; var b : longint);
var
    c : longint;
begin
    c := a;
    a := b;
    b := c;
end;

procedure swap_pair(var a : pair; var b : pair);
var
    c : pair;
begin
    c := a;
    a := b;
    b := c;
end;

procedure sort(p, k : longint);
var
    i, s : longint;
    p1, p2: longint;
    idx : longint;
begin
    if p = k then exit;
    if k - p = 1 then begin
        if cmp(to_sort[k], to_sort[p]) then
            swap_pair(to_sort[p], to_sort[k]);
        exit;
    end;
    s := (p+k) div 2;

    sort(p, s);
    sort(s+1, k);

    p1 := p;
    p2 := s+1;
    idx := p;

    while (p1 <= s) or (p2 <= k) do begin
        if p1 > s then begin
            tmp[idx] := to_sort[p2];
            inc(p2);
        end else if (p2 > k) or cmp(to_sort[p1], to_sort[p2]) then begin
            tmp[idx] := to_sort[p1];
            inc(p1);
        end else begin
            tmp[idx] := to_sort[p2];
            inc(p2);
        end;
        inc(idx);
    end;

    for i := p to k do begin
        to_sort[i] := tmp[i];
    end;
end;

procedure main;
var
    k, p, q, i, n, idx, x : longint;
begin
    readln(k, p, q);
    n := 0;
    for i:=1 to k do begin
        read(a[i]);
        n := n + a[i];
    end;

    dec(a[p]);
    if n > 1 then dec(a[q]);

    if (a[p] < 0) or (a[q] < 0) then begin
        writeln('0');
        exit;
    end;

    for i:=1 to k do
        to_sort[i] := make_pair(a[i], i);

    sort(1, k);

    ans[1] := p;
    ans[n] := q;

    idx := 2;
    
    for i:=1 to k do begin
        for x:=1 to to_sort[i].first do begin
            ans[idx] := to_sort[i].second;
            idx := idx + 2;
            if idx >= n then idx := 3;
        end;
    end;

    i := 2;
    while (i <= n-1) and (ans[i-1] = ans[i]) do begin
        my_swap(ans[i], ans[i+1]);
        i := i + 2;
    end;
    
    i := n-1;
    while (i >= 3) and (ans[i] = ans[i+1]) do begin
        my_swap(ans[i], ans[i-1]);
        i := i - 2;
    end;

    for i:=1 to n-1 do begin
        if ans[i] = ans[i+1] then begin
            writeln('0');
            exit;
        end;
    end;

    for i:=1 to n do begin
        write(ans[i], ' ');
    end;

    writeln;
end;

begin
    main
end.
