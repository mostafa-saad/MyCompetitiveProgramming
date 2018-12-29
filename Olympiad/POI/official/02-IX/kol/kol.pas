(*************************************************************************
 *                                                                       *
 *                    IX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Koleje                                         *
 *   Plik:                kol.pas                                        *
 *   Autor:               Wojciech Dudek                                 *
 *************************************************************************)
program Kol;

const
  PLIK_WE = 'kol.in';
  PLIK_WY = 'kol.out';
  MAX_SCIEZKA = 20;   {najwiêksza warto¶æ log(n)}

type
  PTDrzewo = ^TDrzewo;
  TDrzewo  = record
      prawy, lewy     :PTDrzewo;
      lisci_w_lewym   :longint;
      max             :longint;
      obciazenie      :longint;
    end;
  TSciezka = record
      wierz       : array [1..MAX_SCIEZKA] of PTDrzewo;
      dlugosc     : longint;
      rozdz       : longint;
  end;

var
  plik1, plik2  :text;
  n , m, z      :longint;
  drzewo        :PTDrzewo;

function Max (a, b :longint) :longint;
begin
  if (a >= b) then Max := a else Max := b;
end;

function Min (a, b :longint) :longint;
begin
  if (a <= b) then Min := a else Min := b;
end;

function BudujDrzewo(il_lisci :longint) :PTDrzewo;
var
  e   :PTDrzewo;
begin
  if il_lisci = 0 then
    BudujDrzewo := nil
  else begin
    New (e);
    with e^ do begin
      max := 0;
      obciazenie := 0;
      if il_lisci > 1 then begin
        lisci_w_lewym := il_lisci - (il_lisci div 2);
        lewy := BudujDrzewo (lisci_w_lewym);
        prawy := BudujDrzewo (il_lisci - lisci_w_lewym);
      end
      else begin
        lisci_w_lewym := 0;
        lewy := nil;
        prawy := nil;
      end;
    end;
    BudujDrzewo := e;
  end;
end;

procedure ZnajdzSciezki (pocz, kon :longint; var s_l, s_p :TSciezka);
var
  e         :PTDrzewo;
  i         :longint;
begin
  e := drzewo;  i := 1;
  s_l.wierz[1] := e;
  s_p.wierz[1] := e;
  while (e^.lisci_w_lewym <> 0) do begin
    if pocz <= e^.lisci_w_lewym then
      e := e^.lewy
    else begin
      pocz := pocz - e^.lisci_w_lewym;
      e := e^.prawy;
    end;
    Inc (i);  s_l.wierz[i] := e;
  end;
  s_l.dlugosc := i;

  e := drzewo;  i := 1;
  while (e^.lisci_w_lewym <> 0) do begin
    if kon <= e^.lisci_w_lewym then
      e := e^.lewy
    else begin
      kon := kon - e^.lisci_w_lewym;
      e := e^.prawy;
    end;
    Inc (i);  s_p.wierz[i] := e;
  end;
  s_p.dlugosc := i;

  i := 1;
  while (i <= s_l.dlugosc) and (i <= s_p.dlugosc) and (s_l.wierz[i] = s_p.wierz[i]) do
    Inc (i);
  s_l.rozdz := i-1; s_p.rozdz := i-1;
{kompresja scie¿ek}
  for i := s_l.dlugosc downto s_l.rozdz+1 do
    if s_l.wierz[i] <> s_l.wierz[i-1]^.lewy then break;
  s_l.dlugosc := i;

  for i := s_p.dlugosc downto s_p.rozdz+1 do
    if s_p.wierz[i] <> s_p.wierz[i-1]^.prawy then break;
  s_p.dlugosc := i;
end;

function ObcMax (var s_l, s_p :TSciezka) :longint;
var
  c,obc_max_l :longint;
  i         :longint;
begin
  c := s_l.wierz[s_l.dlugosc]^.max;
  for i := s_l.dlugosc-1 downto s_l.rozdz+1 do begin
    if (s_l.wierz[i]^.prawy <> s_l.wierz[i+1]) then
      c := Max (s_l.wierz[i]^.prawy^.max, c);
    c := c + s_l.wierz[i]^.obciazenie;
  end;
  for i := Min (s_l.rozdz, s_l.dlugosc-1) downto 1 do
    c := c + s_l.wierz[i]^.obciazenie;
  obc_max_l := c;
  c := s_p.wierz[s_p.dlugosc]^.max;

  for i := s_p.dlugosc-1 downto s_p.rozdz+1 do begin
    if (s_p.wierz[i]^.lewy <> s_p.wierz[i+1]) then
      c := Max (s_p.wierz[i]^.lewy^.max, c);
    c := c + s_p.wierz[i]^.obciazenie;
  end;
  for i := Min (s_p.rozdz, s_p.dlugosc-1) downto 1 do
    c := c + s_p.wierz[i]^.obciazenie;
  ObcMax := Max (c, obc_max_l);
end;

procedure Obciaz (var s_l, s_p :TSciezka; o_ile :longint);
var
  i         :longint;
begin
  if (s_l.rozdz = s_l.dlugosc) and (s_p.rozdz = s_p.dlugosc) then begin
    Inc (s_l.wierz[s_l.dlugosc]^.obciazenie, o_ile);
    Inc (s_l.wierz[s_l.dlugosc]^.max, o_ile);
    for i := s_l.rozdz-1 downto 1 do
      s_l.wierz[i]^.max := Max (s_l.wierz[i]^.prawy^.max, s_l.wierz[i]^.lewy^.max) + s_l.wierz[i]^.obciazenie;
  end
  else begin
    Inc (s_l.wierz[s_l.dlugosc]^.obciazenie, o_ile);
    Inc (s_l.wierz[s_l.dlugosc]^.max, o_ile);
    for i := s_l.dlugosc-1 downto s_l.rozdz+1 do begin
      if (s_l.wierz[i+1] <> s_l.wierz[i]^.prawy ) then begin
        Inc (s_l.wierz[i]^.prawy^.obciazenie, o_ile);
        Inc (s_l.wierz[i]^.prawy^.max, o_ile);
      end;
      s_l.wierz[i]^.max := Max (s_l.wierz[i]^.prawy^.max, s_l.wierz[i]^.lewy^.max) + s_l.wierz[i]^.obciazenie;
    end;

    Inc (s_p.wierz[s_p.dlugosc]^.obciazenie, o_ile);
    Inc (s_p.wierz[s_p.dlugosc]^.max, o_ile);
    for i := s_p.dlugosc-1 downto s_p.rozdz+1 do begin
      if (s_p.wierz[i+1] <> s_p.wierz[i]^.lewy ) then begin
        Inc (s_p.wierz[i]^.lewy^.obciazenie, o_ile);
        Inc (s_p.wierz[i]^.lewy^.max, o_ile);
      end;
      s_p.wierz[i]^.max := Max (s_p.wierz[i]^.prawy^.max, s_p.wierz[i]^.lewy^.max) + s_p.wierz[i]^.obciazenie;
    end;

    for i := s_l.rozdz downto 1 do
      s_l.wierz[i]^.max := Max (s_l.wierz[i]^.prawy^.max, s_l.wierz[i]^.lewy^.max) + s_l.wierz[i]^.obciazenie;
  end;
end;

function Zapytanie (pocz, kon, ilosc :longint) :boolean;
var
  sciezka_lewa, sciezka_prawa :TSciezka;
begin
  ZnajdzSciezki (pocz, kon, sciezka_lewa, sciezka_prawa);
  if (ilosc + ObcMax(sciezka_lewa, sciezka_prawa)) <= m then begin
    Obciaz (sciezka_lewa, sciezka_prawa, ilosc);
    Zapytanie := true;
  end
  else
    Zapytanie := false;
end;

var
  p, k, l   :longint;
  i         :longint;

begin
  Assign(plik1, PLIK_WE);
  Reset (plik1);
  Assign(plik2, PLIK_WY);
  Rewrite (plik2);

  ReadLn (plik1,n,m,z);
  drzewo := BudujDrzewo (n-1);
  for i:=1 to z do begin
    ReadLn (plik1, p,k,l);
    if Zapytanie (p,k-1,l) then
      WriteLn (plik2, 'T')
    else
      WriteLn (plik2, 'N');
  end;

  Close (plik1);
  Close(plik2);
end.
