(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Tour de Bajtocja                                 *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n^2 + m)                                       *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Spojne i las budujemy przy pomocy naiwnej        *
 *                      implementacji zbiorow rozlacznych                *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000001;
type
  pelem = ^elem;
  elem = record
    x : longint;
    nx : pelem;
  end;
  pii = record x, y : longint; end;

procedure push(var p : pelem; x : longint);
var tmp : pelem;
begin
  new(tmp);
  tmp^.x := x;
  tmp^.nx := p;
  p := tmp;
end;

function pop(var p : pelem) : longint;
var tmp : pelem;
begin
  tmp := p^.nx;
  pop := p^.x;
  dispose(p);
  p := tmp;
end;

var
  kandydaci : array[1..MAXN] of pii; (* krawedzie o poczatku o numerze <=k *)
  zablokowane : array[1..MAXN] of pii; (* krawedzie, ktore zostana zablokowane *)
  numer : array[1..MAXN] of longint; (* do ktorego zbioru nalezy miasto *)
  zbior : array[1..MAXN] of pelem;  (* miasta nalezace do zbioru *)
  n, m, k, kandydaci_ilosc, zablokowane_ilosc: longint;

procedure make_union(x : longint; y : longint);
var a, b : longint;
begin
  a := numer[x]; b := numer[y];
  if a <> b then
    while zbior[b] <> nil do
    begin
      push(zbior[a], pop(zbior[b]));
      numer[zbior[a]^.x] := a;
    end;
end;

procedure wyznacz_spojne_i_kandydatow;
var a, b, i : longint;
begin
  readln (n, m, k);
  for i := 1 to n do begin numer[i] := i; push(zbior[i], i); end;
  for i := 1 to m do
  begin
    readln (a, b);
    if a > k then
      make_union(a, b)
    else begin
      kandydaci_ilosc := kandydaci_ilosc + 1;
      kandydaci[kandydaci_ilosc].x := a;
      kandydaci[kandydaci_ilosc].y := b;
    end;
  end;
end;

procedure wybierz_zablokowane;
var i : longint;
begin
  for i := 1 to kandydaci_ilosc do
    if numer[kandydaci[i].x] = numer[kandydaci[i].y] then
    begin
      zablokowane_ilosc := zablokowane_ilosc + 1;
      zablokowane[zablokowane_ilosc] := kandydaci[i];
    end else
      make_union(kandydaci[i].x, kandydaci[i].y);
end;

var i : longint;

Begin
  wyznacz_spojne_i_kandydatow;
  wybierz_zablokowane;
  (* wypisujemy wynik *)
  writeln (zablokowane_ilosc);
  for i := 1 to zablokowane_ilosc do
    writeln (zablokowane[i].x, ' ', zablokowane[i].y);
End.
