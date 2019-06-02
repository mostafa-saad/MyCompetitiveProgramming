(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Hotele                                        *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************)

const MAX_N = 5 * 1000;

type arr = array[1..MAX_N] of int64;

var
    n, it : longint;
    wynik : int64;
    
    (* krawedzie[kr_pocz[v] ... kr_kon[v]] to synowie
    wierzcholka v*)
    kr_pocz, kr_kon, kr_ile : array[1..MAX_N] of longint;
    kr_wszystkie : array[1..MAX_N] of array[1..2] of longint;
    krawedzie : array[1..2*MAX_N] of longint;


(* wzbogacony DFS, zwraca najwieksza odleglosc wierzcholka
 * od korzenia w poddrzewie *)
function przeszukaj(v, p, d : longint; var mnoznik, grupa : arr;
  var wyn : int64) : longint;
var
  i, max_d, new_d : longint;
begin
  max_d := d;
  Inc(grupa[d]);
  Inc(wyn, mnoznik[d]);
  for i := kr_pocz[v] to kr_kon[v] do
    if krawedzie[i] <> p then
      begin
        new_d := przeszukaj(krawedzie[i], v, d + 1, mnoznik, grupa, wyn);
        if new_d > max_d then
          max_d := new_d;
      end;
  przeszukaj := max_d;
end;

(* zwraca liczbe trojek, dla ktorych r jest centralnym wierzcholkiem *)
procedure jako_korzen(r : longint; var wyn : int64);
var
  i, j, s : longint;
  suma, mnoznik, grupa : arr;
begin
  for i := 1 to n do (* zerowanie tablic *)
    begin
      suma[i] := 0;
      mnoznik[i] := 0;
      grupa[i] := 0;
    end;
  for i := kr_pocz[r] to kr_kon[r] do
    begin
      s := przeszukaj(krawedzie[i], r, 1, mnoznik, grupa, wyn);
      for j := 1 to s do
        begin
          Inc(mnoznik[j], suma[j] * grupa[j]);
          Inc(suma[j], grupa[j]);
          grupa[j] := 0;
        end;
    end;
end;

procedure wczytaj;
var
    i, j, v, a, b : longint;
begin
    readln(n);
    
    for i := 1 to n do (* zerowanie tablic *)
    begin
        kr_ile[i] := 0;
    end;

    for i := 1 to n - 1 do
        for j := 1 to 2 do
        begin
            read(v);
            kr_wszystkie[i][j] := v;
            Inc(kr_ile[v])
        end;
    kr_pocz[1] := 1;
    kr_kon[1] := 0;
    for i := 2 to n do
    begin
        kr_pocz[i] := kr_pocz[i - 1] + kr_ile[i - 1];
        kr_kon[i] := kr_pocz[i] - 1;
    end;
    for i := 1 to n - 1 do
    begin
        a := kr_wszystkie[i][1];
        b := kr_wszystkie[i][2];
        Inc(kr_kon[a]);
        Inc(kr_kon[b]);
        krawedzie[kr_kon[a]] := b;
        krawedzie[kr_kon[b]] := a;
    end;
end;    

begin
    wczytaj;    
    wynik := 0;

    for it := 1 to n do 
    (* rozpatrujemy kazdy wierzcholek jako punkt pomiedzy hotelami *)
      jako_korzen(it, wynik);
    
    writeln(wynik);
end.
