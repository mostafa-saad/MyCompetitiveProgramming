(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Studnia                                          *
 *   Autor:             Igor Adamski                                     *
 *   Zlozonosc czasowa: O(n * max(x_i))                                  *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Liniowe wyszukiawnie zamiast binarnego           *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000000;

function min(a, b : longint) : longint;
begin
  if a < b then
    min := a
  else
    min := b;
end;

function max(a, b : longint) : longint;
begin
  if a > b then
    max := a
  else
    max := b;
end;

var   n, h, r : longint;
    m : int64; (* liczba ruchow lopaty, na ktore Bajtazar ma sile *)
    sumx : int64;
    x : array[0..MAXN] of longint;
    pom : array[0..MAXN] of longint;
    lewa : array[0..MAXN+1] of int64;
    prawa : array[0..MAXN+1] of int64;
    (* pomocniczna tablica z grubosciami warstw piasku, na ktorej beda wykonywane obliczenia *)

(* Funkcja rozwiazujaca podproblem wyrownania koryta rzeki bez dokopywania sie do wody,
 * tak, zeby liczba z zdefiniowana w tresci nie przekroczyla p.
 * Zwraca potrzebna liczbe ruchow lopaty do osiagniecia tego celu *)

function wyrownaj(p : longint) : int64;
  var  ruchy : int64; (* liczba potrzebnych ruchow *)
      i : longint;
begin
  ruchy := 0;
  
  for i:=1 to n-1 do (* wyrownanie terenu od lewej do prawej *)
  begin
    if pom[i] + p < pom[i+1] then
    begin
      ruchy := ruchy + pom[i+1] - (pom[i] + p);
      pom[i+1] := pom[i] + p;
    end;
  end;
  
  for i:=n downto 2 do (* i od prawej do lewej *)
  begin
    if pom[i] + p < pom[i-1] then
    begin
      ruchy := ruchy + pom[i-1] - (pom[i] + p);
      pom[i-1] := pom[i] + p;
    end;
  end;
  wyrownaj := ruchy;
end;

(* Funkcja zwraca miejsce, w ktorym uda sie dokopac do poziomu 0,
 * tak, zeby liczba z zdefiniowana w tresci nie przekroczyla p,
 * badz -1 jesli takiego miejsca nie ma. *)

function gdzie_kopac(p : longint) : longint;
  var   i, pd, pm : longint;
      ruchy, sl, sp : int64;
begin
  for i:=1 to n do (* przygotowanie tablicy pomocniczej *)
    pom[i] := x[i];
  
  ruchy := wyrownaj(p);
  
  (* jesli Bajtazar nie ma wystarczajaco sily na wyrownanie terenu,
   * to tym bardziej na dokopanie sie do wody *)
  if m < ruchy then
  begin
    gdzie_kopac := -1;
    exit;
  end;
  
  for i:=0 to n+1 do
  begin
    lewa[i] := 0;
    prawa[i] := 0;
  end;
  for i:=1 to n do
  begin
    pd := pom[i] div p;
    pm := pom[i] mod p;
    lewa[i] := lewa[i] + p;
    lewa[min(n+1, i + pd)] := lewa[min(n+1, i + pd)] - p;
    lewa[min(n+1, i + pd)] := lewa[min(n+1, i + pd)] + pm;
    if i + pd <= n then
      lewa[i + pd + 1] := lewa[i + pd + 1] - pm;
    
    prawa[max(1, i - pd + 1)] := prawa[max(1, i - pd + 1)] + p;
    prawa[i+1] := prawa[i+1] - p;
    prawa[max(0, i - pd)] := prawa[max(0, i - pd)] + pm;
    if i - pd >= 1 then
      prawa[i - pd + 1] := prawa[i - pd + 1] - pm;
  end;
  
  (* wyliczenie kosztu dokopania sie do wody w punkcie 1 *)
  for i:=1 to n do
  begin
    if pom[i] <= p*(i-1) then
      break
    else
      ruchy := ruchy + pom[i] - p*(i-1);
  end;
  
  if ruchy <= m then
  begin
    gdzie_kopac := 1;
    exit;
  end;
  
  sl := lewa[1];
  sp := prawa[1];
  for i:=2 to n do
  begin
    (* Aktualizacja kosztu dokopania sie do wody w miejscu i
     * na podstawie poprzedniego kosztu oraz podanego wzoru *)
    sp := sp + prawa[i];
    ruchy := ruchy - sl + sp;
    sl := sl + lewa[i];
    if ruchy <= m then
    begin
      gdzie_kopac := i;
      exit;
    end;
  end;
  
  gdzie_kopac := -1;
end;

var i : longint;

begin
  read(n, m);
  h := 0; (* najgrubsza warstwa piasku *)
  sumx := 0;
  for i:=1 to n do
  begin
    read(x[i]);
    sumx := sumx + x[i];
    h := max(h, x[i]);
  end;
  if sumx <= m then
  begin
    writeln('1 0');
    halt;
  end;
  
  for i:=1 to h do
  begin
    r := gdzie_kopac(i);
    if r <> -1 then
    begin
      writeln(r, ' ', i);
      halt;
    end;
  end;
end.
