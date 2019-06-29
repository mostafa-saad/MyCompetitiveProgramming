(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Mafia (MAF)                                               *
 *   Plik:     maf1.pas                                                  *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie wzorcowe o zlozonosci czasowej O(n),          *
 *             przepisane z maf.cpp na Pascala.                          *
 *                                                                       *
 *************************************************************************)

const MAX_N = 1000000;
const INFTY = 100000000;

type
  PLista = ^Lista;
  Lista = record
    v : LongInt;
    next : Plista;
  end;

var
  s : array[0..MAX_N] of LongInt;
  n, lroots : LongInt;
  i : LongInt;
  v : Plista;
  roots : array[0..MAX_N] of LongInt; (* korzenie skladowych *)
  t : array[0..MAX_N] of PLista;
  ts : array[0..MAX_N] of LongInt; (* wielkosci list *)
  col : array[0..MAX_N] of LongInt; (* "kolory" wierzcholkow *)

(* Jezeli przyp[v]=1, to wierzcholek v musi nalezec do zbioru niezaleznego;
 * przyp[v]=2 to wierzcholek, ktory do tego zbioru nie moze nalezec,
 * a przyp[v]=0 to wierzcholek nieustalony *)
  przyp : array[0..MAX_N] of LongInt;

(* tab[v][x] - ile maksymalnie wierzcholkow w zbiorze niezaleznym moze
 * byc w poddrzewie o ojcu v, jezeli v nie jest wziety (x=0) lub jest wziety
 * (x=1). tab[v][x]=-INFTY oznacza, ze dana sytuacja jest niemozliwa
 * (np. wskutek wartosci przyp[v]). *)
  tab : array[0..MAX_N, 0..1] of LongInt;

  min_ofiar, max_ofiar : LongInt; (* n - poszukiwane_wyniki *)
  skladowa : array[0..2 * MAX_N] of LongInt;
  lskladowa : LongInt;
  

  
(* Przeszukuje slabo spojne skladowe, wyznacza ich korzenie
 * i zle krawedzie. *)
procedure koloruj;
var nr, i, v : LongInt;
begin
  nr := 0;
  lroots := 0;
  for i := 0 to n - 1 do
    if col[i] = 0 then
    begin
      Inc(nr);
      v := i;
      (* idziemy az dojdziemy do cyklu albo do odwiedzonego wierzcholka *)
      while col[v] = 0 do
      begin
        col[v] := nr;
        v := s[v];
      end;
      if col[v] = nr then (* znalezlismy nowy cykl *)
      begin
        (* arbitralnie wybieramy korzen skladowej *)
        roots[lroots] := v;
        Inc(lroots);
      end;
    end;
end;


(* Czy skladowa jest cyklem (tzn. nie wchodzi do niej zadne drzewo). *)
function cykl(root : LongInt) : Boolean;
var v : LongInt;
  czy : Boolean;
begin
  czy := true;
  v := root;
  repeat
    if ts[v] > 1 then
      czy := false;
    v := s[v];
  until v = root;
  cykl := czy;
end;

function max(a, b : LongInt) : LongInt;
begin
  if a > b then
    max := a
  else
    max := b;
end;

(* Wyznaczanie min_ofiar
 * Liczymy tab[v][jak % 2] (jak=2 oznacza, ze nie bierzemy v). *)
function licz(v, jak, root : LongInt) : LongInt;
var w, x : LongInt;
  node : PLista;
begin
  (* Rekurencja ze spamietywaniem *)
  w := tab[v, jak mod 2];
  if w <> -1 then
    licz := w
  else
  begin
    skladowa[lskladowa] := v; Inc(lskladowa);
    if (przyp[v] > 0) and (przyp[v] <> jak) then
    begin
      w := -INFTY;
      tab[v, jak mod 2] := w;
      licz := w;
    end
    else
    begin
      if jak = 1 then (* bierzemy v do zbioru *)
      begin
        w := 1;
        node := t[v]^.next;
        while node <> nil do
        begin
          if node^.v <> root then
          begin
            x := licz(node^.v, 2, root);
            if x = -INFTY then
              w := -INFTY
            else
              Inc(w, x);
          end;
          node := node^.next;
        end;
        if w < 0 then
          w := -INFTY;
        tab[v, jak mod 2] := w;
        licz := w;
      end
      else (* nie bierzemy v do zbioru *)
      begin
        w := 0;
        node := t[v]^.next;
        while node <> nil do
        begin
          if node^.v <> root then
          begin
            x := max(licz(node^.v, 1, root), licz(node^.v, 2, root));
            if x = -INFTY then
              w := -INFTY
            else
              Inc(w, x);
          end;
          node := node^.next;
        end;
        if w < 0 then
          w := -INFTY;
        tab[v, jak mod 2] := w;
        licz := w;
      end;
    end;
  end;
end;
procedure analizuj(root : LongInt);
var ost_root, ost_sroot, i, wynik : LongInt;
begin
  wynik := 0;
  (* Przypadek 1: Korzen bierzemy do zbioru, no to s[korzen] juz nie. *)
  lskladowa := 0;
  if ((przyp[root] = 0) or (przyp[root] = 1)) and
      ((przyp[s[root]] = 0) or (przyp[s[root]] = 2)) and
      (s[root] <> root) then (* uwaga na cykl jednoelementowy! *)
  begin
    ost_root := przyp[root]; ost_sroot := przyp[s[root]];
    przyp[root] := 1; przyp[s[root]] := 2;
    wynik := max(wynik, licz(root, 1, root));
    przyp[root] := ost_root; przyp[s[root]] := ost_sroot;
  end;
  
  (* Przypadek 2: Korzenia nie bierzemy do zbioru. *)
  for i := 0 to lskladowa - 1 do
  begin
    tab[skladowa[i]][0] := -1;
    tab[skladowa[i]][1] := -1;
  end;
  lskladowa := 0;
  if (przyp[root] = 0) or (przyp[root] = 2) then
  begin
    ost_root := przyp[root];
    przyp[root] := 2;
    wynik := max(wynik, licz(root, 2, root));
    przyp[root] := ost_root;
  end;
  Inc(min_ofiar, wynik);
end;

(* Usuwa liste sasiedztwa z pamieci *)
procedure wywal(v : PLista);
begin
  if v^.next <> nil then
    wywal(v^.next);
  dispose(v);
end;

begin
  Read(n);
  (* Zerujemy listy sasiedztwa *)
  for i := 0 to n - 1 do
  begin
    New(t[i]);
    t[i]^.next := nil;
    ts[i] := 0;
  end;
  for i := 0 to n - 1 do
  begin
    Read(s[i]);
    Dec(s[i]);
    New(v);
    v^.next := t[s[i]]^.next;
    v^.v := i;
    t[s[i]]^.next := v;
    Inc(ts[s[i]]);
  end;
  koloruj;
  (* W max_ofiar zliczamy najpierw liczbe ocalonych, kiedy jest max liczba
   * ofiar. *)
  max_ofiar := 0; min_ofiar := 0;
  for i := 0 to n - 1 do
    przyp[i] := 0;
  for i := 0 to n - 1 do
    if ts[i] = 0 then (* lisc *)
    begin
      Inc(max_ofiar);
      przyp[i] := 1;
      przyp[s[i]] := 2;
    end;
  for i := 0 to n - 1 do
  begin
    tab[i][0] := -1;
    tab[i][1] := -1;
  end;
  for i := 0 to lroots - 1 do
  begin
    (* Cykl o dlugosci wiekszej niz 1. *)
    if cykl(roots[i]) and (s[roots[i]] <> roots[i]) then
      Inc(max_ofiar);
    analizuj(roots[i]);
  end;
  WriteLn(n - min_ofiar, ' ', n - max_ofiar);
  for i := 0 to n - 1 do
    wywal(t[i]);
end.
