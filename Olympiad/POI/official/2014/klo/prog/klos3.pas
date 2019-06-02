(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Klocki                                        *
 *   Autor:                Karol Farbis                                  *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************)

program klocki;

const
    N = 1000000;

var
    a : array[1..N] of longint;
    ans : array[1..N] of longint;

procedure my_swap(var i : longint; var j : longint);
var
    k : longint;
begin
    k := i;
    i := j;
    j := k;
end;

procedure main;
var
    k, p, q, n, i, j, idx : longint;

begin
    readln(k, p, q);
    n := 0;

    for i := 1 to k do begin
        read(a[i]);
        n := n + a[i];
    end;

    dec(a[p]);
    if n > 1 then dec(a[q]);

    ans[1] := p;
    ans[n] := q;

    if (a[p] < 0) or (a[q] < 0) then begin
        writeln('0');
        exit;
    end;

    idx := 2;

    for i:=1 to k do
        while a[i] <> 0 do begin
            ans[idx]:=i;
            inc(idx);
            dec(a[i]);
        end;

    for j:=1 to n do begin
        for i:=2 to n-2 do begin
            if ans[i] = ans[i-1] then begin
                my_swap(ans[i], ans[i+1]);
            end;
        end;
        for i:=n-1 downto 3 do begin
            if ans[i] = ans[i+1] then begin
                my_swap(ans[i], ans[i-1]);
            end;
        end;
    end;

    for i:=2 to n do
        if ans[i] = ans[i-1] then begin
            writeln('0');
            exit;
        end;

    for i:=1 to n do
        write(ans[i], ' ');

    writeln;
end;

begin
    main
end.
