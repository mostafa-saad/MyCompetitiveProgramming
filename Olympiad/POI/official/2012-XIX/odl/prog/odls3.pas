(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Odleglosc                                        *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n * M / lg(M))                                 *
 *   Opis:              Rozwiazanie powolne, analogiczne do wzorcowego,  *
 *                      tyle ze przegladajac sasiadow, uzywamy listy     *
 *                      wszystkich liczb pierwszych mniejszych od M      *
 *                                                                       *
 *************************************************************************)

Program odleglosc;
const 
  MAXN = 1000005;
  INF = 1000000000;

var
  n, a, Vmax, licznik, i, j: longint;
  source1, source2, fact, perm, ans, Plist, Vlist : array[0 .. MAXN] of longint;
  odw : array[0..MAXN] of boolean;
  Q : array[0..2 * MAXN] of longint;
  Plist_ind, Vlist_ind, Q_start, Q_end : longint;


function mark(x,y:longint) : boolean;
begin
  mark := false;
  if source1[y] = 0 then begin
    source1[y] := source1[x];
    mark := true;
  end else 
  if source2[y] = 0 then begin
    if source1[x] <> source1[y] then begin
      source2[y] := source1[x];
      if source1[y] = y then inc(licznik);
      mark := true;
    end;
    if (source2[x] <> 0) and (odw[x]) then begin
      source2[y] := source2[x];
      if source1[y] = y then inc(licznik);
      mark := true;
    end;
  end;
end;


function max(x, y : longint) : longint;
begin
  if x > y then max := x else max := y;
end;

begin

  Vmax := 0;
  licznik := 0;
  for i := 0 to MAXN do begin
    source1[i] := 0;
    source2[i] := 0;
    fact[i] := 1;
    perm[i] := 0;
    ans[i] := 0;
    Plist[i] := 0;
    Vlist[i] := 0;
    odw[i] := false;
  end;
  Plist_ind := 0;
  Vlist_ind := 0;
  Q_start := 0;
  Q_end := 0;
  fact[0] := 0; fact[1] := 0;

  readln(n);
  for i := 0 to n-1 do begin
    readln(a);
    Vlist[Vlist_ind] := a;
    inc(Vlist_ind);
    Vmax := max(Vmax,a);
    if perm[a] = 0 then begin
      perm[a] := i+1;
      source1[a] := a;
      Q[Q_end] := a;
      inc(Q_end);
    end else begin
      ans[i+1] := perm[a];
      if ans[perm[a]] = 0 then
        ans[perm[a]] := i+1;
    end;
  end;

  for i := 2 to Vmax do fact[i] := i;
  i := 2; 
  while i * i <= Vmax do begin
    if fact[i] = i then begin
      j := i * i;
      while j <= Vmax do begin
        if fact[j] = j then fact[j] := i;
        j := j + i;
      end;
    end;
    inc(i);
  end;
  for i := 2 to Vmax do if fact[i]=i then begin
    Plist[Plist_ind] := i;
    inc(Plist_ind);
  end;

  while(Q_start <> Q_end) and (licznik < n) do begin
    a := Q[Q_start]; 
    inc(Q_start);
    
    for i := 0 to Plist_ind - 1 do 
      if a mod Plist[i] = 0 then
        if mark(a, a div Plist[i]) then begin
          Q[Q_end] := a div Plist[i];
          inc(Q_end);
        end;

    for i := 0 to Plist_ind - 1 do begin 
      if a * Plist[i] > Vmax then break
      else if mark(a,a * Plist[i]) then begin
        Q[Q_end] := a * Plist[i];
        inc(Q_end);
      end;
    end;
    
    odw[a] := true;
  end;

  for i := 0 to Vlist_ind - 1 do 
    if ans[i+1] > 0 then writeln(ans[i+1])
    else writeln(perm[source2[Vlist[i]]]);

end.
