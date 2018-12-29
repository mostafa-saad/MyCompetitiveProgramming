(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Stacja (STA)                                              *
 *   Plik:     sta0.pas                                                  *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie o zlozonosci czasowej O(n), wykonuje          *
 *             dwuprzebiegowe programowanie dynamiczne w drzewie.        *
 *                                                                       *
 *************************************************************************)

const MAX_N = 1000000;

type PWezel = ^Wezel;
     Wezel = record
       v : LongInt;
       nast : Pwezel;
     end;

var
  n, i, a, b : LongInt;
  graf : array[0..MAX_N - 1] of PWezel;
  wezly : array[0..MAX_N - 1] of LongInt;
  odw : array[0..MAX_N - 1] of Boolean;
  glowny : PWezel;
  (* Uwaga: Trzeba zastosowac typ 64-bitowy! *)
  drogi : array[0..MAX_N - 1] of Int64;
  wynik : array[0..MAX_N - 1] of Int64;
  wyn : Int64;

procedure wstaw(a, b : LongInt);
var
  w : PWezel;
begin
  New(w);
  w^.v := b;
  w^.nast := graf[a]^.nast;
  graf[a]^.nast := w;
end;
  
(* Liczenie liczb wezlow i sum odleglosci w poddrzewach *)
procedure faza1(v : LongInt);
var
  wezel : PWezel;
  w : LongInt;
begin
  odw[v] := true;
  wezly[v] := 1;
  drogi[v] := 0;
  wezel := graf[v];
  while wezel^.nast <> nil do
  begin
    wezel := wezel^.nast;
    w := wezel^.v;
    if not odw[w] then
    begin
      faza1(w);
      Inc(wezly[v], wezly[w]);
      Inc(drogi[v], drogi[w] + wezly[w]);
    end;
  end;
end;

(* Liczenie wlasciwych wynikow, par to ojciec danego wezla *)
procedure faza2(v, par : LongInt);
var
  wezel : PWezel;
begin
  wynik[v] := wynik[par] - wezly[v] + (n - wezly[v]);
  wezel := graf[v];
  while wezel^.nast <> nil do
  begin
    wezel := wezel^.nast;
    if wezel^.v <> par then
      faza2(wezel^.v, v);
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
    odw[i] := false;
    New(graf[i]);
    graf[i]^.nast := nil;
  end;
  for i := 1 to n - 1 do
  begin
    ReadLn(a, b);
    Dec(a); Dec(b);
    wstaw(a, b);
    wstaw(b, a);
  end;
  
  (* Dwukrotne programowanie dynamiczne *)
  faza1(0);
  wynik[0] := drogi[0];
  glowny := graf[0];
  while glowny^.nast <> nil do
  begin
    glowny := glowny^.nast;
    faza2(glowny^.v, 0);
  end;
  
  (* Wyznaczanie i wypisywanie wyniku *)
  wyn := 0;
  for i := 0 to n - 1 do
    if wynik[i] > wyn then
      wyn := wynik[i];
  for i := 0 to n - 1 do
    if wynik[i] = wyn then
    begin
      WriteLn(i + 1);
      Break;
    end;
  for i := 0 to n - 1 do
    wywal(graf[i]);
end.
