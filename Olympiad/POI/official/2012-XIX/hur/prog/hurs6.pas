(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Hurtownia                                        *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(2^n)                                           *
 *   Opis:              Rozwiazanie powolne: wykladnicze                 *
 *                                                                       *
 *************************************************************************)

const
    MAXN = 250000;

var
    n: Int64;
    a, b: array[0..MAXN] of Int64;
    result_v, act_v: array[0..MAXN] of LongInt;
    result_n, act_n, i: LongInt;

procedure solve(ind: LongInt; sum: Int64);
begin
    if ind = n then begin
        if act_n > result_n then begin
            for i := 0 to act_n - 1 do begin
                result_v[i] := act_v[i];
            end;
            result_n := act_n;
        end
    end else begin
        sum := sum + a[ind];
        solve(ind + 1, sum);
        if b[ind] <= sum then begin
            act_v[act_n] := ind + 1;
            inc(act_n);
            solve(ind + 1, sum - b[ind]);
            dec(act_n);
        end;
    end;
end;

begin
    read(n);
    result_n := 0;
    act_n := 0;
    for i := 0 to (n - 1) do begin
        read(a[i]);
    end;
    for i := 0 to (n - 1) do begin
        read(b[i]);
    end;
    solve(0, 0);
    writeln(result_n);
    for i := 0 to (result_n - 1) do begin
        write(result_v[i], ' ');
    end;
    writeln();
end.
