(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Blokada (BLO)                                             *
 *   Plik:     blos3.pas                                                 *
 *   Autor:    Marek Cygan                                               *
 *   Opis:     Rozwiazanie wolne, zlozonosc obliczeniowa O(n*m),         *
 *             zlozonosc pamieciowa O(m); wynik obliczany jest za        *
 *             pomoca algorytmu dfs dla kazdego wierzcholka artykulacji. *
 *                                                                       *
 *************************************************************************)

const
  MAX_N=100000; {maksymalna liczba wierzcholkow w grafie}
  MAX_M=500000; {maksymalna liczba krawedzi}

var

n : longint; {liczba wierzcholkow}
{reprezentacja grafu, dla kazdego wierzcholka pamietamy numer aktualnej krawedzi,
 a dla kazdej krawedzi pamietamy numer kolejnej krawedzi}
nastepna_krawedz, krawedz : array [0..2*MAX_M-1] of longint;
pierwsza_krawedz : array [0..MAX_N-1] of longint;

odwiedzony : array[0 .. MAX_N-1] of boolean;
{czy dany wierzcholek jest punktem artykujacji,
 wyjatek to wierzcholek 0, dla ktorego zawsze
 wartosc wynosi true}
punkt_artykulacji : array[0..MAX_N-1] of boolean;
numer, low : array[0..MAX_N-1] of longint; {jako ktory dany wierzcholek zostal odwiedzony, funkcja low}
odwiedzone_wierzcholki : longint;

function Min(a, b:longint) : longint;
begin
  if a>=b then Min:=b
  else Min:=a;
end;

{ przeszukiwanie w glab, znajdujace punkty artykulacji }
procedure DfsPunktyArtykujacji(x, ojciec : longint);
var i, v : longint;
begin
  odwiedzony[x]:=true;
  numer[x]:=odwiedzone_wierzcholki;
  low[x]:=numer[x];
  inc(odwiedzone_wierzcholki);
  i:=pierwsza_krawedz[x];
  while i<>-1 do
  begin
    v:=krawedz[i];
    if not odwiedzony[v] then
    begin
      DfsPunktyArtykujacji(v,x);
      if low[v]>=numer[x] then
        punkt_artykulacji[x]:=true
      else
        low[x]:=Min(low[x],low[v]);
    end else if v<>ojciec then low[x]:=Min(low[x],numer[v]);
    i:=nastepna_krawedz[i];
  end;
end;

procedure DodajKrawedz(i,a,b:longint);
begin
  nastepna_krawedz[i]:=pierwsza_krawedz[a];
  krawedz[i]:=b;
  pierwsza_krawedz[a]:=i;
end;

procedure WczytajGraf;
var m, a, b, i:longint;
begin
  readln(n,m);
  for i:=0 to n-1 do pierwsza_krawedz[i]:=-1;
  for i:=0 to m-1 do
  begin
    readln(a,b);
    {dodanie nowej krawedzi nieskierowanej}
    dec(a); dec(b);
    DodajKrawedz(2*i,a,b);
    DodajKrawedz(2*i+1,b,a);
  end;
end;

{ przeszukiwanie w glab znajdujace rozmiar spojnej skladkowej }
function Dfs(x : longint) : longint;
var i, v, odwiedzone_wierzcholki : longint;
begin
  odwiedzone_wierzcholki:=1;
  odwiedzony[x]:=true;
  i:=pierwsza_krawedz[x];
  while i<>-1 do
  begin
    v:=krawedz[i];
    if not odwiedzony[v] then
      inc(odwiedzone_wierzcholki,Dfs(v));
    i:=nastepna_krawedz[i];
  end;
  Dfs:=odwiedzone_wierzcholki;
end;

function ZablokowaneSpotkania(x : longint) : int64;
var
  i, rozmiar : longint;
  wynik : int64;
begin
  wynik:=2*(n-1); {nikt nie spotka sie z mieszkancem miasta x}
  for i:=0 to n-1 do odwiedzony[i]:=false;
  odwiedzony[x]:=true;
  for i:=0 to n-1 do
    if not odwiedzony[i] then
    begin
      rozmiar:=Dfs(i);
      inc(wynik,int64(rozmiar)*int64(n-1-rozmiar));
    end;
  ZablokowaneSpotkania:=wynik;
end;

procedure ObliczWynik;
var i : longint;
begin
  punkt_artykulacji[0]:=true;
  for i:=0 to n-1 do
    if punkt_artykulacji[i] then
      writeln(ZablokowaneSpotkania(i))
    else
      writeln(2*(n-1));
end;

begin
  WczytajGraf;
  DfsPunktyArtykujacji(0,-1);
  ObliczWynik;
end.
