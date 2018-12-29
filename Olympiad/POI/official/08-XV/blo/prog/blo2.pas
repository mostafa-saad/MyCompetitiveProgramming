(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Blokada (BLO)                                             *
 *   Plik:     blo2.pas                                                  *
 *   Autor:    Marek Cygan                                               *
 *   Opis:     Rozwiazanie wzorcowe, zlozonosc obliczeniowa oraz         *
 *             pamieciowa O(m).                                          *
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
blokada : array [0..MAX_N-1] of Int64; {liczba zablokowanych spotkan dla kazdego wierzcholka}
odwiedzony : array [0..MAX_N-1] of boolean; 
numer, low : array [0..MAX_N-1] of longint; {jako ktory dany wierzcholek zostal odwiedzony, funkcja low}
odwiedzone_wierzcholki : longint;

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

function Min(a, b:longint) : longint;
begin
  if a>=b then Min:=b
  else Min:=a;
end;

{ przeszukiwanie w glab
  funkcja zwraca liczbe wierzcholkow z poddrzewa przeszukiwania }
function Dfs(x, ojciec : longint) : longint;
var 
  liczba_odwiedzonych, liczba_zablokowanych, i, v, rozmiar : longint;
begin
  liczba_odwiedzonych:=1; 
  liczba_zablokowanych:=0;
  odwiedzony[x]:=true;
  numer[x]:=odwiedzone_wierzcholki;
  low[x]:=numer[x];
  inc(odwiedzone_wierzcholki);
  
  blokada[x]:=2*(n-1); {z wierzcholka x (i do wierzcholka x) nie da sie dojechac}
  i:=pierwsza_krawedz[x];
  while i<>-1 do
  begin
    v:=krawedz[i];
    if not odwiedzony[v] then
    begin
      rozmiar:=Dfs(v,x);
      inc(liczba_odwiedzonych,rozmiar);
      if low[v]>=numer[x] then
      begin
        inc(blokada[x],int64(n-1-rozmiar)*int64(rozmiar)); 
        inc(liczba_zablokowanych,rozmiar);
      end else low[x]:=Min(low[x],low[v]);
    end else if v<>ojciec then low[x]:=Min(low[x],numer[v]);
    i:=nastepna_krawedz[i];
  end;
  inc(blokada[x],int64(n-1-liczba_zablokowanych)*int64(liczba_zablokowanych));
  Dfs:=liczba_odwiedzonych;
end;

procedure WypiszWynik;
var i : longint;
begin
  for i:=0 to n-1 do
   writeln(blokada[i]); 
end;

begin
  WczytajGraf();
  Dfs(0,-1);
  WypiszWynik();
end.
