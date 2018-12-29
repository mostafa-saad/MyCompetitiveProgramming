(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Randka                                           *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n*(k+log(n)))                                  *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Odleglosc na cyklu oblicza w czasie liniowym     *
 *                                                                       *
 *************************************************************************)

Program randka;
const 
  MAXN = 500005;
  MAXP = 20;

type
  pekst = ^ekst;
  ekst = record
    x : longint;
    next,prev : pekst;
  end;

procedure insert_first(newelement:pekst; var head:pekst);
begin
  newelement^.next:=head;
  if head <> nil then
    head^.prev:=newelement;
  head:=newelement;
end;

procedure remove_element(pos:pekst; var head:pekst);
begin
  if pos^.next<>nil then
    pos^.next^.prev:=pos^.prev;
  if pos^.prev <> nil then
    pos^.prev^.next:=pos^.next
  else
    head:=pos^.next;
  dispose(pos);
end;

var
  n,k,a,b,c,i,j,p,dlg1,dlg2,cyklInd,wyn1,wyn2,topo_ind,temp : longint;
  graf, symbol, gleb, topo : array[0 .. MAXN] of longint;
  l : array[0 .. MAXN, 0 .. MAXP] of longint;
  vis : array[0..MAXN] of boolean;
  kraw : array[0..MAXN] of pekst;
  ipekst : pekst;

procedure swap(var a,b:longint);
var 
  d : longint;
begin
  d := a;
  a := b;
  b := d;
end;

procedure DFS(v : longint);
begin
  vis[v] := true;
  if not vis[graf[v]] then DFS(graf[v]);
  topo[topo_ind] := v;
  inc(topo_ind);
end;

procedure linkuj(x,o : longint);
var 
  ipekst : pekst;
  i : longint;
begin
  gleb[x] := gleb[o] + 1;
  l[x][0] := o;
  for i := 1 to MAXP - 1 do l[x,i] := l[l[x,i - 1],i - 1];
  ipekst := kraw[x];
  while ipekst <> nil do begin 
    if (ipekst^.x <> o) and (symbol[ipekst^.x] > 0) then 
      linkuj(ipekst^.x, x);
    ipekst := ipekst^.next;
  end;
end;

function LCA(a,b : longint) : longint;
begin
  if gleb[a] < gleb[b] then swap(a,b);
  for p := MAXP - 1 downto 0 do
    if gleb[a] - (1 shl p) >= gleb[b] then
      a := l[a][p];
  for p := MAXP - 1 downto 0 do
    if l[a][p] <> l[b][p] then
    begin
      a := l[a][p];
      b := l[b][p];
    end;
  LCA := a;
  if a <> b then LCA := l[a][0];
end;

begin

  // inicjalizacja
  dlg1 := 0; dlg2 := 0; cyklInd := 0; wyn1 := 0; wyn2 := 0; topo_ind := 0;
  ipekst := nil;
  for i := 0 to MAXN do begin
    graf[i] := 0; symbol[i] := 0;
    gleb[i] := 0; topo[i] := 0;
    vis[i] := false;
    kraw[i] := nil;
  end;

  // IN
  read(n,k);
  for i := 1 to n do begin
    read(graf[i]);
    new(ipekst);
    ipekst^.x := i;
    insert_first(ipekst, kraw[graf[i]]);
  end;

  // Sortowanie topologiczne
  for i := 1 to n do 
    if not vis[i] then DFS(i);
  
  // wyznaczanie reprezentantow cykli i drzew
  // numeracja wierzcholkow na cyklu i ich dlugosci
  i := 0;
  while i < n do begin
    if symbol[graf[topo[i]]] = 0 then begin
      symbol[topo[i]] := -graf[topo[i]];
      cyklInd := -graf[topo[i]];
      while topo[i] <> (-cyklInd) do begin
        inc(i);
        symbol[topo[i]] := cyklInd;
      end;
      inc(i);
      continue;
    end;
    if symbol[graf[topo[i]]] < 0 then symbol[topo[i]] := graf[topo[i]]
    else symbol[topo[i]] := symbol[graf[topo[i]]];
    inc(i);
  end;


  // wyznaczenie tablicy LCA dla wierzcholkow
  for i := 1 to n do if symbol[i] < 0 then linkuj(i,i);

  // OUT
  for i := 1 to k do begin
    read(a,b);
    wyn1 := 0;
    wyn2 := 0;
    dlg1 := 0;
    dlg2 := 0;  

    // na jednym poddrzewie
    if(symbol[a] = symbol[b]) and (symbol[a] > 0) then begin
      c := LCA(a,b);
      wyn1 := gleb[a] - gleb[c];
      wyn2 := gleb[b] - gleb[c];
    end;
    
    // spotkanie niemozliwe
    if symbol[abs(symbol[a])] <> symbol[abs(symbol[b])] then begin
      wyn1 := -1;
      wyn2 := -1;
    end;
    
    // jeden na drzewie, drugi na innym drzewie lub cyklu osiagalnym z drzewa
    if(symbol[abs(symbol[a])] = symbol[abs(symbol[b])]) 
        and (symbol[a] <> symbol[b]) then begin
      if symbol[a] > 0 then begin 
        wyn1 := gleb[a] - 1; a := abs(symbol[a]); 
      end;
      if symbol[b] > 0 then begin 
        wyn2 := gleb[b] - 1; b := abs(symbol[b]); 
      end;
    end;
    
    // oba na cyklu i nie s± tym samym wierzcholkiem
    if(symbol[a] = symbol[b]) and ((symbol[a] < 0) and (a <> b)) then begin
      temp := b;
      while temp <> a do begin temp := graf[temp]; inc(dlg2); end;
      temp := a;
      while temp <> b do begin temp := graf[temp]; inc(dlg1); end;

      if dlg2 + wyn2 < dlg1 + wyn1 then wyn2 := wyn2 + dlg2
      else if dlg2 + wyn2 > dlg1 + wyn1 then wyn1 := wyn1 + dlg1
      else if dlg1 < dlg2 then wyn1 := wyn1 + dlg1
      else if dlg1 > dlg2 then wyn2 := wyn2 + dlg2
      else wyn1 := wyn1 + dlg1;
    end;
    
    writeln(wyn1, ' ', wyn2);
  end;
end.



