(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SZK (Szko³y)                                   *
 *   Plik:                szk1.pas                                       *
 *   Autor:               Pawe³ Parys                                    *
 *   Opis:                                                               *
 *                                                                       *
 *************************************************************************)

const SIZE = 200;  (* maximal number of schools *)
const INF : longint = 1000000000;

var 
  N : longint;
  cur, low, high, score : array[0..SIZE-1] of longint;
  sch_match, pos_match : array[0..SIZE-1] of longint;
  dist, back : array[0..SIZE-1] of longint;
  changed : array[0..SIZE-1] of boolean;

function cost(s, p : longint) : longint;
begin
  cost := abs(cur[s]-p)*score[s];
end;

procedure go_from_school(s, d : longint);
var a, d2 : longint;
begin
  for a := low[s] to high[s] do
    if a<>sch_match[s] then
    begin
      d2 := d+cost(s, a);
      if d2<dist[a] then
      begin
        dist[a] := d2;
        back[a] := s;
        changed[a] := true;
      end;
    end;
end;

function find_path : longint;
var
  a, ret, retval : longint;
  theend : boolean;
begin
  ret := -1;
  retval := INF;
  for a := 0 to N-1 do
  begin
    dist[a] := INF;
    changed[a] := false;
  end;
  for a := 0 to N-1 do
    if sch_match[a]<0 then
      go_from_school(a, 0);
  while true do
  begin
    theend := true;
    for a := 0 to N-1 do
    begin
      if not changed[a] then continue;
      if (pos_match[a]<0) and (dist[a]<retval) then
      begin
        ret := a;
        retval := dist[ret];
      end;
      changed[a] := false;
      if (pos_match[a]<0) then continue;
      go_from_school(pos_match[a], dist[a]-cost(pos_match[a], a));
      theend := false;
    end;
    if theend then break;
  end;
  find_path := ret;
end;

procedure extend(p : longint);
var s, pp : longint;
begin
  while p>=0 do
  begin
    s := back[p];
    pos_match[p] := s;
    pp := sch_match[s];
    sch_match[s] := p;
    p := pp;
  end;
end;

var a, b, k : longint;

begin 
  read(N);
  for a := 0 to N-1 do
  begin
    read(cur[a], low[a], high[a], score[a]);
    dec(cur[a]);
    dec(low[a]);
    dec(high[a]);
    sch_match[a] := -1;
    pos_match[a] := -1;
  end;
  for a := 0 to N-1 do
  begin
    b := find_path();
    if b<0 then
    begin
      writeln('NIE');
      halt(0);
    end;
    extend(b);
  end;
  k := 0;
  for a := 0 to N-1 do
    k := k+cost(a, sch_match[a]);
  writeln(k);
end.
