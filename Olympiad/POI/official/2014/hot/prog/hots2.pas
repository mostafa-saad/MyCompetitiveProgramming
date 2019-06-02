(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Hotele                                        *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n^4)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************)

const MAX_N = 5 * 1000;

var
    n, i1, i2, i3, wynik, dist : longint;
    d, qu : array[1..MAX_N] of longint;
    (* krawedzie[kr_pocz[v] ... kr_kon[v]] to synowie
    wierzcholka v*)
    kr_pocz, kr_kon, kr_ile : array[1..MAX_N] of longint;
    kr_wszystkie : array[1..MAX_N] of array[1..2] of longint;
    krawedzie : array[1..2*MAX_N] of longint;


(* BFS -- liczymy odleglosc miedzy u a v *)
function odl(u, v : longint) : longint;
var 
  w, t, i, be, en : longint;
  znaleziony : boolean;
begin
  be := 1;
  en := 1;
  znaleziony := false;
  qu[1] := u;
  d[u] := 0;
  while not znaleziony do
    begin
      w := qu[be];
      if w = v then
        begin
          znaleziony := true;
          odl := d[w];
        end;
      Inc(be);
      for i := kr_pocz[w] to kr_kon[w] do begin
        t := krawedzie[i];
        if d[t] = -1 then
          begin
            d[t] := d[w] + 1;
            Inc(en);
            qu[en] := t;
          end;
      end;
    end;
  for i := 1 to en do
    d[qu[i]] := -1;
end;

procedure wczytaj;
var
    i, j, v, a, b : longint;
begin
    readln(n);
    
    for i := 1 to n do (* zerowanie tablic *)
    begin
        kr_ile[i] := 0;
        d[i] := -1;
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

    for i1 := 1 to n do
      for i2 := i1 + 1 to n do 
        begin
          dist := odl(i1, i2);          
          for i3 := i2 + 1 to n do
            if (odl(i1, i3) = dist) and (odl(i2, i3) = dist) then
              Inc(wynik);
        end;
    
    writeln(wynik);
end.
