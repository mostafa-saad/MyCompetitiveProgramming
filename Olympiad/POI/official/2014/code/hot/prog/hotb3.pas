(*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Hotele                                        *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n^3)                                        *
 *   Zlozonosc pamieciowa: O(n^2)                                        *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Zbyt duza zlozonosc pamieciowa                *
 *                                                                       *
 *************************************************************************)

const MAX_N = 2 * 1000;

var
    n, i1, i2, i3, wynik, dist : longint;
    d : array[1..MAX_N] of array[1..MAX_N] of longint; 
    (* krawedzie[kr_pocz[v] ... kr_kon[v]] to synowie
    wierzcholka v*)
    kr_pocz, kr_kon, kr_ile : array[1..MAX_N] of longint;
    kr_wszystkie : array[1..MAX_N] of array[1..2] of longint;
    krawedzie : array[1..2*MAX_N] of longint;


(* liczymy odleglosc od wierzcholka r *)
procedure dfs(v, r, p, dis : longint);
var 
  i : longint;
begin
  d[v][r] := dis;
  d[r][v] := dis;
  for i := kr_pocz[v] to kr_kon[v] do
    if krawedzie[i] <> p then
      dfs(krawedzie[i], r, v, dis + 1);
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

    for i1 := 1 to n do
      dfs(i1, i1, -1, 0);

    for i1 := 1 to n do
      for i2 := i1 + 1 to n do 
        begin
          dist := d[i1][i2];          
          for i3 := i2 + 1 to n do
            if (d[i1][i3] = dist) and (d[i2][i3] = dist) then
              Inc(wynik);
        end;
    
    writeln(wynik);
end.
