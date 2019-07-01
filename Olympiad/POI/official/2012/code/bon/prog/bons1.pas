(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Bony                                             *
 *   Autor:             Jakub Pachocki                                   *
 *   Zlozonosc czasowa: O(N^2)                                           *
 *   Opis:              Rozwiazanie powolne, wielokrotnosci przegladamy  *
 *                      zawsze od poczatku                               *
 *                                                                       *
 *************************************************************************)

program Bony;

const max_n = 1000000;

var
  i, m, n, c, a : longint;
  winning : array[1..max_n] of boolean;
  taken : array[1..max_n] of boolean;
  clients : int64;
  res : array[1..max_n] of int64;
  z, buying, remaining : longint;

begin
  for i := 1 to max_n do
  begin
    winning[i] := false;
    taken[i] := false
  end;
  readln(m);
  for i := 1 to m do
  begin
    readln(c);
    winning[c] := true
  end;
  clients := 0;
  z := 0;
  readln(n);
  for i := 1 to n do
  begin
    readln(a);
    buying := 1;
    remaining := a;
    while (remaining > 0) and (buying <= max_n) do
    begin
      if (buying mod a = 0) and (not taken[buying]) then
      begin
        dec(remaining);
        inc(clients);
        if winning[buying] then
        begin
          inc(z);
          res[z] := clients
        end;
        taken[buying] := true
      end;
      inc(buying)
    end;
    inc(clients, remaining)
  end;
  writeln(z);
  for i := 1 to z do
    writeln(res[i])
end.

