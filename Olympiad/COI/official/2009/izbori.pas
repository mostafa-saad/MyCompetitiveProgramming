var g, s, m, tren_glas, i, j, k: longint;
    kol, tko, ga: array[0..100] of longint;
    dp: array[0..1, 0..200] of longint;
    sol: array[0..100, 0..1] of longint;
    lower, upper, tmp, max_a, max_b, koji: longint;

function min(a, b: longint): longint;
begin
    if (a < b) then min := a else min := b;
end;

function moze(koja, koliko: longint): boolean;
var ii, i, j, k, dodatno: longint;
begin
    ii := 0;
    if (ga[koja]*20 < g) then moze := true else begin
        for i := 0 to 200 do dp[0, i] := g+100;
        dp[0, 0] := 0;
        for i := 0 to min(s, 21)-1 do if (i <> koja) then begin
            ii := 1-ii;
            for j := 0 to m do begin
                dp[ii, j] := g+100;
                for k := 0 to j do begin
                    dodatno := (ga[koja]*k + koliko) div (koliko+1) - ga[i];
                    if ((((ga[koja]*k) mod (koliko+1)) = 0) and ((tko[i]>tko[koja]) and (k > 0))) then dodatno := dodatno+1;
                    if (dodatno < 0) then dodatno := 0;
                    if ((k > 0) and ((ga[i]+dodatno)*20 < g)) then begin
                        dodatno := dodatno + ((g+19-20*(ga[i]+dodatno)) div 20);
                    end;
                    dp[ii, j] := min(dp[ii, j], dp[1-ii, j-k] + dodatno);
                end;
            end;
        end;
        if (dp[ii, m-koliko] <= g-tren_glas) then moze := true else moze := false;
    end;
end;

begin
   read(g, s, m);
   for i := 0 to s-1 do begin
        read(ga[i]); tko[i] := i;
        j := i; tren_glas := tren_glas + ga[i];
        while ((j > 0) and (ga[j] > ga[j-1])) do begin
            tmp := ga[j]; ga[j] := ga[j-1]; ga[j-1] := tmp;
            tmp := tko[j]; tko[j] := tko[j-1]; tko[j-1] := tmp;
            j := j-1;
        end;
   end;
   for i := 0 to s-1 do begin
       for j := 0 to s-1 do kol[j] := 0;
       ga[i] := ga[i] + (g-tren_glas);
       for j := 0 to m-1 do begin
           max_a := 0; max_b := 1; koji := 0;
           for k := 0 to s-1 do if (ga[k]*20 >= g) then begin
               if (ga[k]*max_b > max_a*(kol[k]+1)) then begin
                   max_a := ga[k];
                   max_b := kol[k]+1;
                   koji := k;
               end;
               if ((ga[k]*max_b = max_a*(kol[k]+1)) and (tko[koji] > tko[k])) then begin
                   max_a := ga[k];
                   max_b := kol[k]+1;
                   koji := k;
               end;
           end;
           kol[koji] := kol[koji]+1;
       end;
       sol[tko[i], 0] := kol[i];
       ga[i] := ga[i] - (g-tren_glas);
   end;
   for i := 0 to s-1 do begin
       lower := 0; upper := m;
       while (lower < upper) do begin
           if (moze(i, (lower+upper) div 2) = true) then begin
               upper := (lower+upper) div 2;
           end else begin
               lower := ((lower+upper) div 2)+1;
           end;
       end;
       sol[tko[i], 1] := lower;
   end;
   for i := 0 to s-1 do begin
       if (i > 0) then write(' ');
       write(sol[i, 0]);
   end; writeln();
   for i := 0 to s-1 do begin
       if (i > 0) then write(' ');
       write(sol[i, 1]);
   end; writeln();
end.