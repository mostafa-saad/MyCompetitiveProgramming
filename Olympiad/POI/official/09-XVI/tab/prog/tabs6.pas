(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Tablice (TAB)                                             *
 *   Plik:     tabs6.pas                                                 *
 *   Autor:    Blazej Osinski                                            *
 *   Opis:     Rozwiazanie wolne. Sprowadza do postaci kanonicznej bez   *
 *             sortowania O(min(n,m)*m*n).                               *
 *                                                                       *
 *************************************************************************)

program Tablice_wolne;

const CN=1001;
const INF=2000000007;
const CM=1000000;

type Macierz = Array[1..CN,1..CN] of Longint;

var t, n, m, i, j, tnr, nr : Longint;
    tab : Array[1..2,1..CN,1..CN] of Longint;
    odp : Boolean;

procedure swap(var x,y : Longint);
var tmp : Longint;
begin
  tmp := x;
  x := y;
  y := tmp;
end;

procedure ustalPostac(var t : Macierz );
var i, j, kon, w, l, k, mw : Longint;
begin
  if n < m then
    kon := n
  else
    kon := m;
  for l:=1 to kon do
  begin
    mw := INF;
    w := l;
    k := l;
    for i:=l to n do
      for j:=l to m do
        if t[i,j]<mw then 
        begin
          w := i;
          k := j;
          mw := t[i,j];
        end;
    {zamiana odpowiednich wierszy i kolumn}
    if w<>l then
      for j:=1 to m do
        swap(t[w,j],t[l,j]);
    if k<>l then
      for i:=1 to n do
        swap(t[i,k],t[i,l]);
  end;

  {sortowanie leksykograficzne nadmiarowych wierszy lub kolumn}
  if kon < n then
  begin
    for l := kon+1 to n do
    begin
      w := l;
      for i := l+1 to n do
        if t[i,1] < t[w,1] then
          w := i;
      if w <> l then
        for j:= 1 to m do
          swap(t[w,j],t[l,j]);
    end;
  end;
  if kon < m then
  begin
    for l := kon+1 to m do
    begin
      k := l;
      for j:= l+1 to m do
        if t[1,j] < t[1,k] then
          k := j;
      if k <> l then
        for i := 1 to n do
          swap(t[i,k],t[i,l]);
    end;
  end;
end;

begin
  Readln(t);
  for tnr := 1 to t do
  begin
    Readln(n,m);
    for nr := 1 to 2 do
    begin
      for i := 1 to n do
        for j := 1 to m do
        begin
          tab[nr,i,j] := 0;
          Read(tab[nr,i,j]);
        end;
      ustalPostac(tab[nr]);
    end;
    odp := true;
    for i:=1 to n do
    begin
      for j:=1 to m do
        if tab[1,i,j] <> tab[2,i,j] then
        begin
          odp := false;
          break;
        end;
        if not odp then
          break;
    end;
    if odp then
      Writeln('TAK')
    else
      Writeln('NIE');
  end;
end.
