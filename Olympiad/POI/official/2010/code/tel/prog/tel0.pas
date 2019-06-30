(*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Teleporty (TEL)                               *
 *   Plik:                 tel0.pas                                      *
 *   Autor:                Łukasz Bieniasz-Krzywiec                      *
 *   Opis:                 Rozwiązanie wzorcowe.                         *
 *   Zlozonosc czasowa:    O(n + m)                                      *
 *   Zlozonosc pamieciowa: O(n + m)                                      *
 *   Kodowanie znaków:     UTF-8                                         *
 *                                                                       *
 *************************************************************************)

program tel;

(*
 * DEKLARACJE STAŁYCH
 *)

const MAXN = 40000;
const MAXM = 1000000;
const INF = MAXN;


(*
 * DEKLARACJE TYPÓW:
 *)


(*
 * STRUKTURY DANYCH:
 *)

(* 
 * Lista jednokierunkowa.
 *)

type
  (* Określa dane przechowywane w każdym elemencie listy. *)
  TListData = longint;

  (* Element listy. *)
  PListElem = ^TListElem;
  TListElem = record
                data : TListData;
                next : PListElem;
              end;

  (* Lista. *)
  TList = record
            size        : longint;
            head, tail  : PListElem;
          end;

(* Procedura inicjalizuje listę 'list'. *)
procedure ListInit(var list : TList);
begin
  list.size := 0;
  list.head := nil;
  list.tail := nil;
end;

(* Procedura usuwa listę 'list'. *)
procedure ListDestroy(var list : TList);
var
  E : PListElem;
  i : longint;
begin
  for i := 1 to list.size do begin
    E := list.head^.next;
    dispose(list.head);
    list.head := E;
  end;
  list.size := 0;
  list.tail := nil;
end;

(*
 * Procedura wstawia do listy 'list' element o kluczu 'data' za elementem 'E'.
 * Jeśli 'E' ma wartość 'nil', to nowy element stanie się głową listy.
 *)
procedure ListInsNext(var list : TList; E : PListElem; data : TListData);
var
  new_elem : PListElem;
begin
  new(new_elem);
  new_elem^.data := data;
  if E = nil then begin
    new_elem^.next := list.head;
    list.head := new_elem;
    if list.size = 0 then begin
      list.tail := new_elem;
    end
  end else begin
    new_elem^.next := E^.next;
    E^.next := new_elem;
    if E = list.tail then begin
      list.tail := new_elem;
    end
  end;
  list.size := list.size + 1;
end;


(*
 * DEKLARACJE ZMIENNYCH GLOBALNYCH:
 *)

var
  n, m, w : longint;  (* liczba wierzchołków, krawędzi, wynik *)
  g       : array[0..MAXN-1] of TList;  (* graf w postaci list sąsiedztwa *)


(*
 * PODPROGRAMY:
 *)

(* Procedura dodaje do grafu krawędź {a,b}. *)
procedure dodajKrawedz(a, b : longint);
begin
  ListInsNext(g[a], nil, b);
  ListInsNext(g[b], nil, a);
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
procedure bfs(v : longint; var d : array of longint);
var
  i, p, k, u, w  : longint;
  q              : array[0..MAXN-1] of longint;
  e              : PListElem;
begin
  for i := 0 to n - 1 do begin
    d[i] := INF;
  end;
  d[v] := 0; p := 0; k := 1; q[p] := v;
  while (p < k) do begin
    u := q[p]; inc(p);
    e := g[u].head;
    while (e <> nil) do begin
      w := e^.data;
      if d[w] = INF then begin
        d[w] := d[u] + 1;
        if d[w] < 2 then begin
          q[k] := w; inc(k);
        end;
      end;
      e := e^.next;
    end;
  end;
end;

function min(a, b : longint) : longint;
begin
  if a < b then min := a else min := b;
end;

(* 
 * Funkcja oblicza moc maksymalnego rozszerzenia grafu.
 * Algorytm wzorcowy.
 *)
procedure obliczWynik();
var
  a, b, c, d, i   : longint;
  t1, t2          : array[0..MAXN-1] of longint;
begin
  a := 0; b := 0; c := 0; d := 0;

  bfs(0, t1);
  bfs(1, t2);

  for i := 0 to n - 1 do begin
    case t1[i] of
      1: inc(a);
      2: inc(b);
    end;
    case t2[i] of
      1: inc(c);
      2: inc(d);
    end;
  end;

  w := n * (n - 1) div 2 - m - (n - 1 - a) - a * (1 + c + d) - b * (1 + c) -
      (n - 1 - c - 1 - a - b) - min(a, c) * (n - 1 - a - b - 1 - c - d);
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

