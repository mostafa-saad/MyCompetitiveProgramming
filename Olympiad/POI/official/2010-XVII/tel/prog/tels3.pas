(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Teleporty (TEL)                               *
 *   Plik:                 tels3.pas                                     *
 *   Autor:                Łukasz Bieniasz-Krzywiec                      *
 *   Opis:                 Rozwiazanie powolne.                          *
 *                         Nieco usprawniony algorytm brutalny.          *
 *   Zlozonosc czasowa:    O(n^2 * 2^(n^2))                              *
 *   Zlozonosc pamieciowa: O(n^2)                                        *
 *   Kodowanie znaków:     UTF-8                                         *
 *                                                                       *
 *************************************************************************)

program tel;

(*
 * DEKLARACJE STAŁYCH
 *)

const MAXN = 8000;
const MAXM = 1000000;
const INF = MAXN;


(*
 * DEKLARACJE TYPÓW:
 *)

type
  ANL   = array[0..MAXN-1] of longint;
  ANNB  = array[0..MAXN-1] of array[0..MAXN-1] of boolean;


(*
 * DEKLARACJE ZMIENNYCH GLOBALNYCH:
 *)

var
  n, m, w   : longint;  (* liczba wierzchołków, krawędzi, wynik *)
  g         : ANNB;     (* graf w postaci macierzy sąsiedztwa *)
  d, t1, t2 : ANL;      (* tablice pomocnicza *)
  

(*
 * PODPROGRAMY:
 *)

(* Procedura dodaje do grafu krawędź {a,b}. *)
procedure dodajKrawedz(a, b : longint);
begin
  g[a,b] := true;
  g[b,a] := true;
end;

(* Funkcja wczytuje dane. *)
procedure wczytajDane();
var
  a, b, i : longint;
begin
  readln(n, m);

  for i := 1 to m do begin
    readln(a, b);
    dodajKrawedz(a - 1, b - 1);
  end;
end;

(* Przeszukiwanie wszerz. *)
procedure bfs(v : longint; var d : ANL);
var
  i, p, k, u, w  : longint;
  q              : ANL;
begin
  for i := 0 to n - 1 do begin
    d[i] := INF;
  end;
  d[v] := 0; p := 0; k := 1; q[p] := v;
  while (p < k) do begin
    u := q[p]; inc(p);
    for w := 0 to n - 1 do begin
      if g[u,w] then begin
        if d[w] = INF then begin
          d[w] := d[u] + 1;
          if d[w] < 4 then begin
            q[k] := w; inc(k);
          end;
        end;
      end;
    end;
  end;
end;

(* Procedura generuje wszystkie możliwe grafy. *)
procedure dfs(i, j, k : longint);
var
  ni, nj : longint;
begin
  if i = n then begin
    bfs(0, d);
    if (d[1] >= 5) and (k > w) then begin
      w := k;
    end;
  end else begin
    if j = n then begin
      ni := i + 1; nj := ni + 1;
    end else begin
      ni := i; nj := j + 1;
    end;
    dfs(ni, nj, k);
    if (j < n) and (not g[i,j]) and 
       (t1[i] + t2[j] >= 4) and (t1[j] + t2[i] >= 4) then begin
      g[i,j] := true; g[j,i] := true;
      dfs(ni, nj, k + 1);
      g[i,j] := false; g[j,i] := false;
    end;
  end;
end;

(* 
 * Funkcja oblicza moc maksymalnego rozszerzenia grafu.
 *)
procedure obliczWynik();
begin
  bfs(0, t1); bfs(1, t2);
  w := 0;
  dfs(0, 1, 0);
end;

(* Procedura wypisuje wynik. *)
procedure wypiszWynik();
begin
  writeln(w);
end;


(*
 * PROGRAM GŁÓWNY:
 *)

begin
  wczytajDane();
  obliczWynik();
  wypiszWynik()
end.

