(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SZK (Szko³y)                                   *
 *   Plik:                szks5.pas                                      *
 *   Autor:               Pawe³ Parys                                    *
 *   Opis:                Rozwiazanie nieoptymalne                       *
 *                                                                       *
 *************************************************************************)

const SIZE = 200;  (* maximal number of schools *)
const INF : longint = 1000000000;

var 
  N, best : longint;
  cur, low, high, score : array[0..SIZE-1] of longint;
  used : array[0..SIZE-1] of boolean;

function cost(s, p : longint) : longint;
begin
  cost := abs(cur[s]-p)*score[s];
end;

procedure backtrack(nr, res : longint);
var p : longint;
begin
  if res>=best then exit;
  if nr=N then
  begin
    best := res;
    exit;
  end;
  for p := low[nr] to high[nr] do
  begin
    if used[p] then continue;
    used[p] := true;
    backtrack(nr+1, res+cost(nr, p));
    used[p] := false;
  end;
end;

var a : longint;

begin
  best := INF;
  read(N);
  for a := 0 to N-1 do
  begin
    read(cur[a], low[a], high[a], score[a]);
    dec(cur[a]);
    dec(low[a]);
    dec(high[a]);
    used[a] := false;
  end;
  backtrack(0, 0);
  if (best=INF) then
    writeln('NIE')
  else
    writeln(best);
end.
