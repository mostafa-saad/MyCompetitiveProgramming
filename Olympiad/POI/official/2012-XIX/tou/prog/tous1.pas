(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Tour de Bajtocja                                 *
 *   Autor:             Mateusz Baranowski                               *
 *   Zlozonosc czasowa: O((n + m) * k)                                   *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Dla kolejnych miast kibicow szukamy DFS-em cykli *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000000;
const MAXM = 2000000;
type
  pelem = ^elem;
  elem = record
    x : longint;
    nx : pelem;
  end;
  vector = array of longint;

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
  n, m, k : longint;
  osiagniete, droga_z, droga_do : array[1..MAXM] of longint;
  zablokowane, zablokowane2 : array[1..MAXN] of pelem;
  krawedzie : array[1..MAXN] of vector;
  krawedzie_rozmiar : array[1..MAXN] of longint;

procedure wczytaj_dane;
var i : longint;
begin
  readln (n, m, k);
  for i := 1 to m do
  begin
    readln (droga_z[i], droga_do[i]);
    krawedzie_rozmiar[droga_z[i]] := krawedzie_rozmiar[droga_z[i]] + 1;
    krawedzie_rozmiar[droga_do[i]] := krawedzie_rozmiar[droga_do[i]] + 1;
  end;
  for i := 1 to n do
  begin
    setlength(krawedzie[i], krawedzie_rozmiar[i] + 1);
    krawedzie_rozmiar[i] := 0;
  end;
  for i := 1 to m do
  begin
    krawedzie_rozmiar[droga_z[i]] := krawedzie_rozmiar[droga_z[i]] + 1;
    krawedzie_rozmiar[droga_do[i]] := krawedzie_rozmiar[droga_do[i]] + 1;
    krawedzie[droga_z[i]][krawedzie_rozmiar[droga_z[i]]] := droga_do[i];
    krawedzie[droga_do[i]][krawedzie_rozmiar[droga_do[i]]] := droga_z[i];
  end;
end;

procedure DFS(v : longint);
var j, x : longint;
begin
  osiagniete[v] := k;
  j := 1;
  while j <= krawedzie_rozmiar[v] do
  begin
    x := krawedzie[v][j];
    if osiagniete[x] <> k then DFS(x);
    j := j + 1;
  end;
end;

procedure zablokuj_drogi;
var
  i, j, j2, w : longint;
begin
  for i := 1 to n do osiagniete[i] := 0;
  while k > 0 do
  begin
    osiagniete[k] := k;
    j := 1;
    while j <= krawedzie_rozmiar[k] do
    begin
      w := krawedzie[k][j];
      if osiagniete[w] = k then
      begin
        krawedzie[k][j] := krawedzie[k][krawedzie_rozmiar[k]];
        krawedzie_rozmiar[k] := krawedzie_rozmiar[k] - 1;
        j2 := 1;
        while krawedzie[w][j2] <> k do j2 := j2 + 1;
        krawedzie[w][j2] := krawedzie[w][krawedzie_rozmiar[w]];
        krawedzie_rozmiar[w] := krawedzie_rozmiar[w] - 1;
        if k < w then
          push(zablokowane[w], k)
        else
          push(zablokowane[k], w);
      end else begin
        DFS(w);
        j := j + 1;
      end;
    end;
    k := k - 1;
  end;
end;

var i : longint;

Begin
  wczytaj_dane;
  zablokuj_drogi;
  for i := 1 to n do while zablokowane[i] <> nil do push(zablokowane2[pop(zablokowane[i])], i);
  k := 0;
  for i := 1 to n do
  begin
    m := 0;
    while zablokowane2[i] <> nil do
      if zablokowane2[i]^.x <> m then
      begin
        k := k + 1;
        droga_z[k] := i;
        droga_do[k] := pop(zablokowane2[i]);
        m := droga_do[k];
      end else pop(zablokowane2[i]);
  end;
  writeln (k);
  for i := 1 to k do writeln (droga_z[i], ' ', droga_do[i]);
End.
