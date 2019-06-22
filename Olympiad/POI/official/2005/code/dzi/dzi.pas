(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: DZI (Dziuple)                                  *
 *   Plik:                dzi.pas                                        *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                        Z³o¿ono¶æ obliczeniowa jak i pamiêciowa jest   *
 *                        liniowa. Przeszukiwanie grafu (DFS) jest       *
 *                        zrealizowane na wlasnym stosie (z powodu       *
 *                        potencjalnie du¿ej g³êboko¶ci rekursji).       *
 *                                                                       *
 *************************************************************************)

program dziuple;

const MAXN = 1000000; {maksymalna liczba wierzcholkow}
type tab = array [1..MAXN] of longint;

var 
  {tablice, w ktorych trzymane sa krawedzie grafu}
  next, last, edge : array [1..2*MAXN] of longint; 
  deg, parent : tab; {stopnie oraz ojcowie wierzcho³ków
                      w drzewie przeszukiwania w g³±b}
  stack : tab; {stos}
  k, r : int64; 
  n, m : longint; {liczba wierzcholkow oraz liczba krawedzi}

(*procedura ta dodaje krawêd¼ (a,b) do grafu, zapisuj±c
 j± na i-tym miejscu w tablicy*)
procedure dodaj(a, b, i: longint);
begin
  inc(deg[a]);
  edge[i] := b;
  next[i] := last[a];
  last[a] := i;
end;

{wczytywanie danych}
procedure czytaj;
var 
  i, a, b: longint;
begin
  readln(n, m, k);
  if (m < n) then
  begin
    for i:=1 to n do
    begin
      last[i] := 0;
      deg[i] := 0;
    end;
    
    for i:=1 to m do
    begin
      readln(a, b);
      dodaj(a, b, 2*i-1);
      dodaj(b, a, 2*i);
    end;
  end; 
end;

{przeszukiwanie grafu w g³±b, zrealizowane na w³±snym stosie}
procedure dfs(x : longint);
var 
  ile : longint; {liczba wierzcholkow na stosie}
  u, v, i, j, wezly, liscie : longint;
begin
  stack[1] := x; 
  parent[x] := x; {x jest jedynym elementem stosu}
  ile := 1;
  wezly := 0; {liczba wierzcho³ków tej spójnej sk³adowej o stopniu >=2}
  while (ile > 0) do
  begin
    v := stack[ile]; {zdejmujemy wierzcho³ek ze stosu}
    dec(ile);
    if (deg[v] >= 2) then
      inc(wezly);
    liscie := 0;
    j := 0;
    i := last[v];
    while (i>0) do
    begin
      u := edge[i];
      if (parent[u] = 0) then
      begin
        {zaznaczamy wierzcho³ek jako odwiedzony i wrzucamy na stos}
        parent[u] := v;
        inc(ile);
        stack[ile] := u;
      end else
        if (u <> parent[v]) then
          r := 0; {skladowa nie jest drzewem}
      if (deg[u] = 1) then
        inc(liscie)
      else 
        inc(j);
      i := next[i];
    end;
    if (j > 2) then r := 0; {graf nie jest pladzielny}
    for i := 2 to liscie do {permutowanie wierzcho³ków stopnia 1}
      r := (r * i) mod k;
  end;
  if (wezly>=2) then {symetria wzgledem prostej poziomej} 
    r := (r * 2) mod k;
end;

{g³ówna procedura progamu, procedura ta zlicza liczbê rozstawieñ ptaszków}
procedure licz;
var
  i, j, izolowane : longint;
begin
  for i := 1 to n do 
    parent[i] := 0; {wierzcho³ki nie s± odwiedzone}
  j := 0; {liczba spójnych sk³adowych}
  izolowane := 0;
  if (m < n) then
    r := 1
  else
    r := 0;
  for i := 1 to n do
    if (parent[i] = 0) then
      if (deg[i] > 0) then 
      begin
        inc(j);
        r := (r * (2 * j)) mod k;
        dfs(i);
      end 
      else inc(izolowane);
    
  {trzeba uwzglêdniæ dowolne rozstawienie wierzcho³ków izolowanych}
  for i:=n+1 downto n + 2 - izolowane do
    r := (r * i) mod k;
  writeln(r);
end;
  
begin
  czytaj;
  licz;
end.
