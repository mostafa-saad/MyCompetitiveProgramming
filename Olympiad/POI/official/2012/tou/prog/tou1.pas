(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Tour de Bajtocja                                 *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O(n + m)                                         *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      Wyznaczamy spojne podgrafu o wierzcholkach       *
 *                      o numerach >k. Sciagamy je (do wierzcholkow)     *
 *                      i budujemy maksymalny las dla tego grafu.        *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000001;
const MAXM = 2000001;
type
  pelem = ^elem;
  elem = record
    x : longint;
    nx : pelem;
  end;
  pii = record
    x, y : longint;
  end;

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
  krawedzie : array[0..MAXN] of pelem; (* podgraf indukowany wierzcholkow k+1..n *)
  kandydaci : array[0..MAXM] of pii; (* krawedzie o jednym koncu o numerze <=k *)
  uzyte : array[0..MAXM]of boolean; (* czy kandydat zostal uzyty *)
  zablokowane : array[0..MAXM] of pii; (* krawedzie, ktore zostana zablokowane *)
  spojna : array[0..MAXN] of longint; (* do jakich spojnych naleza wierzcholki (bez kandydatow) *)
  spojna2 : array[0..MAXN] of longint; (* do jakich spojnych naleza wierzcholki (caly graf) *)
  n, k, kandydaci_ilosc, zablokowane_ilosc : longint;

procedure wczytaj_dane;
var a, b, m, i : longint;
begin
  readln (n, m, k);
  for i := 1 to n do spojna[i] := i;
  for i := 1 to m do begin
    readln (a, b);
    if a > k then
    begin
      push(krawedzie[a], b);
      push(krawedzie[b], a);
    end else begin
      kandydaci_ilosc := kandydaci_ilosc + 1;
      kandydaci[kandydaci_ilosc].x := a;
      kandydaci[kandydaci_ilosc].y := b;
      uzyte[kandydaci_ilosc] := false;
    end;
  end;
end;

procedure wyznacz_spojne;
var
  wierzcholki : pelem = nil;
  v, w, i : longint;
begin
  for i := k+1 to n do
  begin
    push(wierzcholki, i);
    while wierzcholki <> nil do
    begin
      v := pop(wierzcholki);
      while krawedzie[v] <> nil do
      begin
        w := pop(krawedzie[v]);
        if spojna[w] <> i then
        begin
          spojna[w] := i;
          push(wierzcholki, w);
        end;
      end;
    end;
  end;
end;

procedure wybierz_zablokowane;
var
  wierzcholki : pelem = nil;
  v, x, z, i : longint;
  para : pii;
begin
  (* konwertujemy liste krawedzi do list sasiedztwa *)
  for i := 1 to kandydaci_ilosc do
  begin
    para := kandydaci[i];
    push(krawedzie[para.x], i);
    push(krawedzie[spojna[para.y]], -i); (* ujemny numer oznacza odwrocona krawedz *)
  end;
  (* budujemy las, pozostale krawedzie wrzucamy do zablokowanych *)
  for i := 1 to n do spojna2[i] := i;
  for i := 1 to k do if spojna2[i] = i then
  begin
    push(wierzcholki, i);
    while wierzcholki <> nil do
    begin
      v := pop(wierzcholki);
      while krawedzie[v] <> nil do begin
        z := pop(krawedzie[v]);
        if z >= 0 then (* jezeli ujemny to odwracamy krawedz *)
          x := kandydaci[z].y
        else begin
          z := -z;
          x := kandydaci[z].x;
        end;
        if spojna2[spojna[x]] <> i then begin
          push(wierzcholki, spojna[x]);
          spojna2[spojna[x]] := i;
        end else
          if not uzyte[z] then
          begin
            zablokowane_ilosc := zablokowane_ilosc + 1;
            zablokowane[zablokowane_ilosc] := kandydaci[z];
          end;
        uzyte[z] := true;
      end;
    end;
  end;
end;

var i : longint;

Begin
  wczytaj_dane;
  wyznacz_spojne;
  wybierz_zablokowane;
  (* wypisujemy wynik *)
  writeln (zablokowane_ilosc);
  for i := 1 to zablokowane_ilosc do
    writeln (zablokowane[i].x, ' ', zablokowane[i].y);
End.
