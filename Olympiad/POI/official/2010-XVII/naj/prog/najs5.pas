(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Najdzielniejszy dzielnik (NAJ)                            *
 *   Plik:     najs5.pas                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             Rozklada kazda z liczb a_i brutalnie.                     *
 *                                                                       *
 *************************************************************************)   

(* Wypisywanie 2^c-1 - zawiera operacje na duzych liczbach. *)
procedure wypisz(c : LongInt);
var
  wyn : array[1 .. 10000] of LongInt;
  size : LongInt;
  a, i : LongInt;
begin
  (* 2^c *)
  size := 1;
  wyn[size] := 1;
  while c > 0 do
  begin
    Dec(c);
    a := 0;
    for i := 1 to size do
    begin
      wyn[i] := 2 * wyn[i] + a;
      a := 0;
      if wyn[i] >= 10 then
      begin
        Dec(wyn[i], 10);
        a := 1;
      end;
    end;
    if a > 0 then
    begin
      size := size + 1;
      wyn[size] := a;
    end;
  end;

  (* 2^c-1 *)
  Dec(wyn[1]);
  i := 1;
  while wyn[i] < 0 do
  begin
    Inc(wyn[i], 10);
    Inc(i);
    Dec(wyn[i]);
  end;

  (* Wypisywanie. *)
  for i := size downto 1 do
    Write(wyn[i]);
  WriteLn;
end;

var
  n, i, j : LongInt;
  gora : LongInt;
  k, c, ile : LongInt;
  a : Int64;
  prime : array[1 .. 20000] of Int64;
  size : LongInt;

begin
  ReadLn(n);
  size := 0;
  while n > 0 do
  begin
    Dec(n);
    Read(a);
    gora := LongInt(Trunc(Sqrt(a)));
    i := 2;
    while i <= gora do
    begin
      if a mod i = 0 then
      begin
        while a mod i = 0 do
        begin
          Inc(size);
          prime[size] := i;
          a := a div i;
        end;
        gora := LongInt(Trunc(Sqrt(a)));
      end;
      Inc(i);
    end;
    if a > 1 then
    begin
      Inc(size);
      prime[size] := a;
    end;
  end;

  k := 1; c := 0;
  for i := 1 to size do
    if prime[i] > 0 then
    begin
      ile := 1;
      for j := i + 1 to size do
        if prime[j] = prime[i] then
        begin
          prime[j] := 0;
          Inc(ile);
        end;
      if ile > k then
      begin
        k := ile;
        c := 1;
      end
      else if ile = k then
        Inc(c);
    end;
  WriteLn(k);
  wypisz(c);
end.
