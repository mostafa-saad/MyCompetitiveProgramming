(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Slowa (SLO)                                               *
 *   Plik:     slo1.pas                                                  *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie wzorcowe O(S)                                 *
 *                                                                       *
 *************************************************************************)

const MAX_N = 100000;

var
  ile, n : LongInt;
  k : array[1 .. MAX_N + 1] of LongInt;

function ewidentnie_zly : Boolean;
var
  i : LongInt;
begin
  ewidentnie_zly := false;
  (* Podslowo (k, 0) dla k!=1 i k!=3 *)
  for i := 2 to n do
    if k[i] = 0 then
    begin
      if (k[i - 1] <> 1) and (k[i - 1] <> 3) then
        ewidentnie_zly := true;
    end;
end;

(* Jezeli k[1]==x, to zmienia k[1] na a. *)
procedure na_poczatku(x, a : LongInt);
begin
  if k[1] = x then
    k[1] := a;
end;

(* Jezeli ostatnia liczba w k to x, to zamiast niej wstawia a, lub nic,
 * jezeli a==-1. *)
procedure na_koncu(x, a : LongInt);
begin
  if k[n] = x then
  begin
    k[n] := a;
    if a = -1 then
      Dec(n);
  end;
end;

var
  k1 : array[1 .. MAX_N] of LongInt;
  n1 : LongInt;

(* Zamienia wszystkie wystapienia (x, 0) na (a, b) lub a, gdy b==-1.
 * Zalozenie: x!=0. *)
procedure wszystkie(x, a, b : LongInt);
var
  i : LongInt;
begin
  k[n + 1] := -1;
  n1 := 1;
  i := 1;
  while i <= n do
  begin
    if (k[i] <> x) or (k[i + 1] <> 0) then
    begin
      k1[n1] := k[i];
      Inc(n1);
      Inc(i);
      continue;
    end;
    k1[n1] := a;
    Inc(n1);
    if b <> -1 then
    begin
      k1[n1] := b;
      Inc(n1);
    end;
    Inc(i, 2);
  end;
  Dec(n1);

  (* Przepisywanie do pomocniczej tablicy. *)
  for i := 1 to n1 do
    k[i] := k1[i];
  n := n1;
end;

procedure zmniejsz(o_ile : LongInt);
var
  i : LongInt;
begin
  for i := 1 to n do
    Dec(k[i], o_ile);
end;

var
  i : LongInt;
  ok : Boolean;

begin
  ReadLn(ile);
  while ile > 0 do
  begin
    Dec(ile);
    ReadLn(n);
    for i := 1 to n do
      Read(k[i]);

    ok := true;
    while n > 1 do
    begin
      if ewidentnie_zly then
      begin
        ok := false;
        break;
      end;
      na_poczatku(0, 2);
      na_koncu(3, 2);
      na_koncu(1, -1);
      wszystkie(1, 2, -1);
      wszystkie(3, 2, 2);
      zmniejsz(1);
    end;
    if ok then
      WriteLn('TAK')
    else
      WriteLn('NIE');
  end;
end.
