{*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Turniej                                        *
 *   Plik:                tur1.pas                                       *
 *   Autor:               Jakub Pawlewicz                                *
 *************************************************************************}

const
  MAX_NODES = 100000;

type
  NeighboursArray = array[1..MAX_NODES] of longint;
  Neighbours =
  record
    nr : longint;
    list : ^NeighboursArray;
  end;

var
  win : array [1..MAX_NODES] of Neighbours;
  nodes : longint;

procedure read_input;
var
  i, j : longint;
begin
  read(nodes);
  for i := 1 to nodes do
  with win[i] do
  begin
    read(nr);
    if nr > 0 then
    begin
      getmem(list, sizeof(longint) * nr);
      for j := 1 to nr do
        read(list^[j]);
    end;
  end;
end;

var
  order : array[1..MAX_NODES] of longint;

procedure order_nodes;
var
  i, j : longint;
  last_lose_with : array[1..MAX_NODES] of longint;
begin
  for i := 1 to nodes do
    last_lose_with[i] := 0;
  
  order[1] := 1;
  for i := 2 to nodes do
  with win[i] do
  begin
    for j := 1 to nr do
      last_lose_with[list^[j]] := i;
    j := i - 1;
    while (j > 0) and (last_lose_with[order[j]] = i) do
    begin
      order[j + 1] := order[j];
      dec(j);
    end;
    order[j + 1] := i;
  end;
end;

function find_winners_nr : longint;
var
  i, j : longint;
  winners_nr : longint;
  winner : longint;
  last_lose_with : array[1..MAX_NODES] of longint;
begin
  winners_nr := 1;
  for i := 1 to nodes do
    last_lose_with[i] := 0;
  i := 1;
  while (winners_nr < nodes) and (winners_nr >= i) do
  begin
    winner := order[i];
    with win[winner] do
    begin
      for j := 1 to nr do
        last_lose_with[list^[j]] := winner;
      j := nodes;
      while (j > winners_nr) and (last_lose_with[order[j]] = winner) do
        dec(j);
      winners_nr := j;
    end;
    inc(i);
  end;
  find_winners_nr := winners_nr;
end;

procedure solve;
var
  i : longint;
  winner : array[1..MAX_NODES] of boolean;
  winners_nr : longint;
begin
  order_nodes;
  winners_nr := find_winners_nr;
  for i := 1 to winners_nr do
    winner[order[i]] := true;
  for i := winners_nr + 1 to nodes do
    winner[order[i]] := false;
  write(winners_nr);
  for i := 1 to nodes do
    if winner[i] then
      write(' ', i);
  writeln;
end;

begin
  read_input;
  solve;
end.
