program postmen;

const Max = 500010;

var i, j, N, M, u, v, newv, pp: longint;
    a, b : array [0..Max] of longint;
    k : array [0..2*Max] of longint;
    used : array [0..2*Max] of boolean;
    visited : array [0..Max] of boolean;
    C, P, tmp, pr : array [0..Max] of longint;
    path : array [1..Max] of longint;
    pb : longint;

function getU (i, v : longint) : longint;
begin
    if a[i] = v then getU := b[i]
    else getU := a[i];
end;
    
    
begin
    for i := 1 to Max do begin
        used[i] := false; visited[i] := false;
        C[i] := 0; tmp[i] := 0; pr[i] := 0;
    end;
    
    ReadLn(N, M);
    if (N > 500000) or (M > 500000) then Halt;
    for i := 1 to M do begin
        Readln(a[i], b[i]);
        inc(C[a[i]]); inc(C[b[i]]);
    end;
    P[0] := 1; C[0] := 0;
    for i := 1 to N do begin
        P[i] := P[i-1] + C[i-1];
        pr[i] := 0;
    end;
    
    for i := 1 to M do begin
        k[P[a[i]] + tmp[a[i]]] := i;
        k[P[b[i]] + tmp[b[i]]] := i;
        inc(tmp[a[i]]); inc(tmp[b[i]]);
    end;
    
    pp := -1;
    for i := 1 to N do begin
        v := i;
        pb := 1; //clear path
        path[pb] := v; inc(pb);
        
        while (v <> -1) do begin
            newv := -1; visited[v] := true;
            while (pr[v] < C[v]) do if (not used[k[P[v]+pr[v]]]) then begin
                u := getU(k[P[v]+pr[v]], v);
                used[k[P[v]+pr[v]]] := true;
                inc(pr[v]);
                if not visited[u] then begin
                    //Writeln(pb);
                    path[pb] := u; inc(pb);
                    visited[u] := true;
                    newv := u;
                end else begin
                    while (path[pb-1] <> u) do begin
                        write(path[pb-1], ' ');
                        visited[path[pb-1]] := false; dec(pb);
                    end;
                    writeln (u);
                    newv := u;
                end;
                break;
            end else inc(pr[v]);
            if (newv = -1) then
                if (pb > 2) then begin
                visited[path[pb-1]] := false; dec(pb);
                newv := path[pb-1];
                end else if (pb > 1) then begin
                    visited[path[pb-1]] := false;
                    dec (pb);
                end;
            v := newv;
        end;
    end;
end.
