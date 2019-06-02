(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Meteory                                          *
 *   Autor:             Blazej Osinski                                   *
 *   Zlozonosc czasowa: O((m+k)*lg(m)*lg(k))                             *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                                                                       *
 *************************************************************************)

program met;

const INF = 1000000000;
const CN = 300007;

{-----   Drzewo potêgowe   -----}

const CWD = 524377;

type DrzewoPotegowe = object
  s : Array [1..CWD] of Int64;
  wd : Longint;
  procedure czysc(n : Longint);
  procedure dodajWartosc(a, wart : Longint);
  function suma(w : Longint) : Int64;
  end;

procedure DrzewoPotegowe.czysc(n : Longint);
  var i : Longint;
begin
  wd := 1;
  while (1 shl wd) < n do
    Inc(wd);
  for i := 1 to 1 shl wd do { Moze to mozna wyciac }
    s[i] := 0;
end;

function DrzewoPotegowe.suma (w : Longint) : Int64;
  var wynik : Int64;
      p : Longint;
begin
  wynik := 0;
  p := 1;
  Inc(w);
  while w > 0 do 
  begin
    if (p and w) <> 0 then
    begin
      wynik := wynik + s[w];
      w := w xor p;
    end;
    p := p shl 1;
  end;
  suma := wynik;
end;

procedure DrzewoPotegowe.dodajWartosc(a, wart : Longint);
  var i, p : Longint;
begin
  Inc(a);
  p := 1;
  for i := 0 to wd do
  begin
    if (a and p) <> 0 then
    begin
      s[a] := s[a] + wart;
      a := a + p;
    end;
    p := p shl 1;
  end;
end;

{---------------------------------------------}

type Para = object
  first, second : Longint;
  end;

type ParaWsk = object
  first, second, nast : Longint;
  end;


{---------------------------------------------}

var dpot : DrzewoPotegowe;
    n, m, z, i, zlicz, l, r, a, it : Longint;
    pot, wl, srodki : Array[0..CN-1] of Longint;
    przed : Array[0..CN-1] of Para;
    zGrupy : Array[0..4*CN-1] of ParaWsk;
    pGrupy : Array[0..CN] of Longint;
    suma : Array[0..CN-1] of Int64;

{---------------------------------------------}

procedure dodajDoGrupy(nr, f, s : Longint);
begin
  zGrupy[zlicz].first := f;
  zGrupy[zlicz].second := s;
  zGrupy[zlicz].nast := pGrupy[nr];
  pGrupy[nr] := zlicz;
  Inc(zlicz); 
end;

{---------------------------------------------}



begin
{-  dpm.czysc(10);
  while(true)do
  begin
    Read(a);
    if(a=0)then
    begin
      read(a);
      Writeln('suma = ', dpm.suma(a));
    end
    else
    begin
      read(b);
      dpm.dodajWartosc(b, a);
    end;
  end;
  -}
  { Wczytywanie danych }
  Readln(n, m);
  for i := 0 to m-1 do
  begin
    Read(z);
    Dec(z);
    wl[i] := z;
  end;
  for i := 0 to n-1 do
    Read(pot[i]);
  
  { Wczytywanie zapytañ }
  Read(z);
  for i := 0 to m do
    pGrupy[i] := -1; 
  for i := 0 to z-1 do
  begin
    Read(l, r, a);
    Dec(l);
    Dec(r);
    if l <= r then
    begin
      dodajDoGrupy(l, i, a);
      dodajDoGrupy(r+1, i, -a);
    end
    else
    begin
      dodajDoGrupy(0, i, a);
      dodajDoGrupy(r+1, i, -a);
      dodajDoGrupy(l, i, a);
      dodajDoGrupy(m, i, -a);
    end;
  end;

  { Wspólne wyszukiwanie binarne }
  dpot.czysc(z);
  for i := 0 to n-1 do
  begin
    przed[i].first := 0;
    przed[i].second := z;
  end;
  
  while true do
  begin
    l := 0;
    for i := 0 to n-1 do
    begin
      suma[i] := 0;
      if przed[i].first <> przed[i].second then 
      begin
        srodki[i] := (przed[i].first + przed[i].second) div 2;
        Inc(l);
      end
      else
        srodki[i] := -1;
    end;
    if l = 0 then
      break;

    { Zamiast symulacji przegladamy wydarzenia dla kolejnych stacji. }
    dpot.czysc(z); 
    for i := 0 to m-1 do
    begin
      it := pGrupy[i]; 
      while it <> -1 do
      begin
        dpot.dodajWartosc(zGrupy[it].first, zGrupy[it].second); 
        it := zGrupy[it].nast;
      end;
      if srodki[wl[i]] <> -1 then
      begin
        { W³a¶ciciel tej stacji nie jest jeszcze rozpatrzony. }
        Inc(suma[wl[i]], dpot.suma(srodki[wl[i]]));
        if suma[wl[i]] > INF then
          suma[wl[i]] := INF;
      end; 
    end;
    for i := 0 to n-1 do
    begin
      if przed[i].first <> przed[i].second then
      begin
        if (Int64(pot[i])) <= suma[i] then { i-te pañstwo dosta³o co najmniej tyle co potrzebowa³o. } 
          przed[i].second := srodki[i]
        else
          przed[i].first := srodki[i]+1;
      end;
    end;
  end; 

  { Wypisanie wyniku }
  for i := 0 to n-1 do
  begin
    if przed[i].first < z then
      Writeln(przed[i].first+1)
    else
      Writeln('NIE');
  end; 
end.
