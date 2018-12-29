(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Stacja (STA)                                              *
 *   Plik:     stas4.pas                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie nieoptymalne, o zlozonosci O(n^2),            *
 *             dla kazdego wierzcholka z osobna oblicza sume odleglosci  *
 *             pozostalych od niego. Usprawnienie: Bierze pod uwage      *
 *             tylko liscie.                                             *
 *                                                                       *
 *************************************************************************)

const MAX_N = 1000000;
const INFTY = 100000000;

type PWezel = ^Wezel;
     Wezel = record
       v : LongInt;
       nast : Pwezel;
     end;

var
  n : LongInt;
  t : array[0..MAX_N] of PWezel;
  d, deg, kol : array[0..MAX_N] of LongInt;
  i, a, b, liscie, wierzch, v : LongInt;
  akt, mx : Int64;
  head, tail : LongInt;

procedure wstaw(a, b : LongInt);
var
  w : PWezel;
begin
  New(w);
  w^.v := b;
  w^.nast := t[a]^.nast;
  t[a]^.nast := w;
end;

procedure init;
begin
  head := 0;
  tail := 0;
end;

procedure push(v : LongInt);
begin
  kol[tail] := v;
  Inc(tail);
end;

function pop : LongInt;
begin
  pop := kol[head];
  Inc(head);
end;

function empty : Boolean;
begin
  empty := (head = tail);
end;

procedure bfs(v : LongInt);
var
  i, w : LongInt;
  wezel : PWezel;
begin
  for i := 0 to n - 1 do
    d[i] := INFTY;
  d[v] := 0;
  init;
  push(v);
  while not empty do
  begin
    w := pop;
    wezel := t[w];
    while wezel^.nast <> nil do
    begin
      wezel := wezel^.nast;
      if d[wezel^.v] = INFTY then
      begin
        d[wezel^.v] := d[w] + 1;
        push(wezel^.v);
      end;
    end;
  end;
end;

procedure wywal(wezel : PWezel);
begin
  if wezel^.nast <> nil then
    wywal(wezel^.nast);
  Dispose(wezel);
end;

begin
  (* Odczyt *)
  ReadLn(n);
  for i := 0 to n - 1 do
  begin
    deg[i] := 0;
    New(t[i]);
    t[i]^.nast := nil;
  end;
  for i := 1 to n - 1 do
  begin
    ReadLn(a, b);
    Dec(a); Dec(b);
    wstaw(a, b);
    wstaw(b, a);
    Inc(deg[a]); Inc(deg[b]);
  end;

  liscie := 0;
  for i := 0 to n - 1 do
    if deg[i] = 1 then
      Inc(liscie);
  mx := -1;
  wierzch := 0;
  for v := 0 to n - 1 do
    if deg[v] = 1 then (* lisc *)
    begin
      bfs(v);
      akt := 0;
      for i := 0 to n - 1 do
        Inc(akt, d[i]);
      if akt > mx then
      begin
        mx := akt;
        wierzch := v;
      end;
    end;
  WriteLn(wierzch + 1);
  for i := 0 to n - 1 do
    wywal(t[i]);
end.
