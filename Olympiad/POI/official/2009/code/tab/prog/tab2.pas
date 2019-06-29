(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Tablice (TAB)                                             *
 *   Plik:     tab2.pas                                                  *
 *   Autor:    Blazej Osinski                                            *
 *   Opis:     Rozwiazanie wzorcowe O(n*m+n*log n).                      *
 *                                                                       *
 *************************************************************************)

program Tablice;

const CN=1001;
const INF=2000000007;
const CM=1000000;

type para = object
  wart,nr : Longint;
  end;

var t, n, m, i, j, tnr, nr, mel, nra, nrb, a : Longint;
    tab : Array[1..2,1..CN,1..CN] of Longint;
    tmp : Array[-CM..CM] of Longint;
    perm : Array[1..CN] of Longint;
{ tablice zawieraj± najmniejsze liczby z wierszy tablic a i b oraz numery odpowiadaj±cych wierszy }
    tr : Array[1..2,1..CN] of para;
    pom : Array[0..CN] of para;
    pod : Boolean;


{ sortowanie przez scalanie }
procedure sort(var t : Array of para; p,k : Longint);
var m, i, j, l: Longint;
begin
  if p<k then
  begin
    m := (p+k)div 2;
    sort(t,p,m);
    sort(t,m+1,k);
    i := p;
    j := m+1;
    l := 0;
    while (i<=m) and (j<=k) do
    begin
      if t[i].wart < t[j].wart then
      begin
        pom[l] := t[i];
        inc(i);
      end
      else
      begin
        pom[l] := t[j];
        inc(j);
      end;
      inc(l);
    end;
    while i<=m do
    begin
      pom[l] := t[i];
      inc(i);
      inc(l);
    end;
    while j<=k do
    begin
      pom[l] := t[j];
      inc(j);
      inc(l);
    end;
    for i := p to k do
      t[i] := pom[i-p];
  end;
end;

begin
  Readln(t);
  for i := -CM to CM do
    tmp[i] := 0;
  for tnr := 1 to t do
  begin
    Readln(n,m);
    for nr := 1 to 2 do
    begin
      for i := 1 to n do
      begin
        mel := INF;
        for j := 1 to m do
        begin
          tab[nr,i,j] := 0;
          Read(tab[nr,i,j]);
          if mel>tab[nr,i,j] then
            mel := tab[nr,i,j];
        end;
        tr[nr,i].wart := mel;
        tr[nr,i].nr := i;
      end;
      sort(tr[nr],0,n-1);
    end;
    pod := true;
    for i := 1 to n do
      if tr[1,i].wart <> tr[2,i].wart then
        pod := false;
    if not pod then
    begin
      Writeln('NIE');
      continue;
    end;
    {generowanie permutacji elementów w wierszu}
    nra := tr[1,1].nr;
    nrb := tr[2,1].nr;
    for j:=1 to m do
      tmp[tab[2,nrb,j]] := tnr*CN+j;
    for j:=1 to m do
    begin
      a := tmp[tab[1,nra,j]];
      if a<=tnr*N then
      begin
        pod := false;
        break;
      end;
      a := a - tnr*CN;
      perm[j] := a;
    end;
    if not pod then
    begin
      Writeln('NIE');
      continue;
    end;
    {sprawdzanie czy wyznaczona permutacja zgadza siê dla wszystkich wierszy}
    for i:=2 to n do
    begin
      nra := tr[1,i].nr;
      nrb := tr[2,i].nr;
      for j:=1 to m do
        if tab[1,nra,j] <> tab[2,nrb,perm[j]] then
        begin
          pod := false;
          break;
        end;
      if not pod then
        break;
    end;
    if pod then
      Writeln('TAK')
    else
      Writeln('NIE');
  end;
end.
