(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Tour de Bajtocja                                 *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O((n + m) * log(n + m))                          *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                      Spojne skladowe i las budujemy przy pomocy lasu  *
 *                      zbiorow rozlacznych (prawie find-union)          *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000001;
const MAXM = 2000001;
type
  pii = record x, y : longint; end;

var
  kandydaci : array[1..MAXM] of pii; (* krawedzie o poczatku o numerze <=k *)
  zablokowane : array[1..MAXM] of pii; (* krawedzie, ktore zostana zablokowane *)
  ojciec : array[1..MAXN] of longint; (* las zbiorow rozlacznych *)
  n, m, k, kandydaci_ilosc, zablokowane_ilosc: longint;

function find(x : longint) : longint;
begin
  if x <> ojciec[x] then ojciec[x] := find(ojciec[x]);
  find := ojciec[x];
end;

procedure make_union(a : longint; b : longint);
begin
  a := find(a); b := find(b);
  if a <> b then ojciec[b] := a;
end;

procedure wyznacz_spojne_i_kandydatow;
var a, b, i : longint;
begin
  readln (n, m, k);
  for i := 1 to n do ojciec[i] := i;
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
    if find(kandydaci[i].x) = find(kandydaci[i].y) then
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
