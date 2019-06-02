{*************************************************************************}
{*                                                                       *}
{*                   VIII Olimpiada Informatyczna                        *}
{*                                                                       *}
{*   Rozwi¹zanie zadania: KOPALNIA Z£OTA                                 *}
{*   Plik:                KOP.PAS                                        *}
{*   Autor:               MARCIN SAWICKI                                 *}
{*************************************************************************}

{$A+,B-,D+,E-,F-,G+,I+,L+,N+,O-,P-,Q-,R-,S+,T+,V+,X+,Y+}
{$M 16384,0,655360}

program KopalniaZlota;

type
  ArrInt = array [1..30000] of Integer;

var
  s, w: Integer;
  n: Word;
  x, y: ^ArrInt;
  xd: ^ArrInt;
  MaxX: Integer;

  IlePktowMiotly: Word;
  MiotlaX: ^ArrInt;
  MiotlaSuma: ^ArrInt;
  MiotlaMaxSuma: ^ArrInt;

procedure WczytajDane;
var
  f: Text;
  i: Integer;
begin
  Assign (f, 'kop.in');
  Reset (f);
  ReadLn (f, s, w);
  ReadLn (f, n);
  GetMem (x, SizeOf (Integer) * n);
  GetMem (y, SizeOf (Integer) * n);
  for i := 1 to n do
    ReadLn (f, x^ [i], y^ [i]);
  Close (f);
end;

function Min (a, b: LongInt): Integer;
begin
  if a < b then
    Min := a
  else
    Min := b
end;

function Max (a, b: Integer): Integer;
begin
  if a > b then
    Max := a
  else
    Max := b
end;

procedure ZamienXd (i, j: Integer);
var
  Pom: Integer;
begin
  Pom := xd^ [i]; xd^ [i] := xd^ [j]; xd^ [j] := pom;
end;

procedure StogNaDolXd (D, G: Word);
var
  i, s: Word;
begin
  i := D;
  repeat
    s := 2 * i;
    if s > G then
      Break;
    if s + 1 <= G then
      if xd^ [s + 1] > xd^ [s] then
        Inc (s);
    if xd^ [i] >= xd^ [s] then
      Break;
    ZamienXd (s, i);
    i := s;
  until False;
end;

procedure StogSortXd;
var
  i: Word;
begin
  for i := n downto 1 do
    StogNaDolXd (i, 2 * n);
  for i := 2 * n downto 2 do
  begin
    ZamienXd (1, i);
    StogNaDolXd (1, i - 1);
  end;
end;

procedure RobMiotle;
var
  i, j: Word;
  WysMiotly: Integer;

  AktWezel: Word;
  AktOjciec: Word;
begin
  MaxX := x^ [1];
  for i := 2 to n do
    if x^ [i] > MaxX then
      MaxX := x^ [i];

  GetMem (xd, SizeOf (Integer) * n * 2);

  for i := 1 to n do
  begin
    xd^ [i] := x^ [i];
    xd^ [i + n] := Min (LongInt (x^ [i]) + s + 1, MaxX + 1);
  end;
  StogSortXd;

  IlePktowMiotly := 1;
  for i := 2 to 2 * n do
    if xd^ [i] > xd^ [IlePktowMiotly] then
    begin
      Inc (IlePktowMiotly);
      xd^ [IlePktowMiotly] := xd^ [i];
    end;
      { wpp. zachodzi xd^ [i] = xd^ [IlePktowMiotly] }

  GetMem (MiotlaX, SizeOf (Integer) * IlePktowMiotly);

  WysMiotly := 0;
  j := IlePktowMiotly;
  while j > 0 do
  begin
    Inc (WysMiotly);
    j := j shr 1
  end;

  {budowanie statycznego drzewa -- miotly}

  AktWezel := 1 shl (WysMiotly - 1); {najbardziej lewy wezel drzewa}
  for i := 1 to IlePktowMiotly do
  begin
    { 0 < AktWezel <= IlePktowMiotly }
    MiotlaX^ [AktWezel] := xd^ [i];
    {przechodzimy do nastepnego w kolejnosci inorder wezla}
    if AktWezel * 2 + 1 <= IlePktowMiotly then
    begin {AktWezel ma prawego syna}
      AktWezel := AktWezel * 2 + 1;
      while AktWezel * 2 <= IlePktowMiotly do {szukanym nastepnikiem jest}
        AktWezel := AktWezel * 2; {najbardziej lewy potomek prawego syna}
    end
    else {nie ma prawego syna}
    begin
      while AktWezel mod 2 = 1 do {AktWezel byl prawym synem}
        AktWezel := AktWezel div 2; {szukamy najwczesniejszego potomka,
          dla ktorego AktWezel byl lewym potomkiem}
      AktWezel := AktWezel div 2
    end;
  end;

  GetMem (MiotlaSuma, SizeOf (Integer) * IlePktowMiotly);
  FillChar (MiotlaSuma^, SizeOf (Integer) * IlePktowMiotly, 0);
  GetMem (MiotlaMaxSuma, SizeOf (Integer) * IlePktowMiotly);
  FillChar (MiotlaMaxSuma^, SizeOf (Integer) * IlePktowMiotly, 0);
end;

procedure Zamien (i, j: Integer);
var
  Pom: Integer;
begin
  Pom := x^ [i]; x^ [i] := x^ [j]; x^ [j] := Pom;
  Pom := y^ [i]; y^ [i] := y^ [j]; y^ [j] := Pom;
end;

procedure StogNaDolPoY (D, G: Integer);
var
  i, s: Integer;
begin
  i := D;
  repeat
    s := 2 * i;
    if s > G then
      Break;
    if s + 1 <= G then
      if y^ [s + 1] > y^ [s] then
        Inc (s);
    if y^ [i] >= y^ [s] then
      Break;
    Zamien (s, i);
    i := s;
  until False;
end;

procedure StogSortPoY;
var
  i: Integer;
begin
(*  for i := 1 to n {- 1} do
    Assert (10008 + i, y^ [i] = (i - 1) mod 100);*)
  for i := n div 2 downto 1 do
    StogNaDolPoY (i, n);
  for i := n downto 2 do
  begin
    Zamien (1, i);
    StogNaDolPoY (1, i - 1);
  end;
(*  for i := 1 to n {- 1} do
    Assert (8 + i, y^ [i] = (i - 1) div 150);*)
{    Assert (7, y^ [i] <= y^ [i + 1]);}
end;

procedure WstawDoMiotly (x, k: Integer);
var
  Wezel: Word;
  SumaPrawa, MaxSumaLewa, MaxSumaPrawa: Integer;
begin
  Wezel := 1;
  repeat
    { Wezel <= IlePktowMiotly }
    if x < MiotlaX^ [Wezel] then
      Wezel := Wezel * 2
    else
    if x > MiotlaX^ [Wezel] then
      Wezel := Wezel * 2 + 1
    else
      Break;
  until False;
  repeat
    if Wezel * 2 + 1 <= IlePktowMiotly then
    begin
      MaxSumaPrawa := MiotlaMaxSuma^ [Wezel * 2 + 1];
      SumaPrawa := MiotlaSuma^ [Wezel * 2 + 1];
    end
    else
    begin
      MaxSumaPrawa := 0;
      SumaPrawa := 0;
    end;
    if Wezel * 2 <= IlePktowMiotly then
      MaxSumaLewa := MiotlaMaxSuma^ [Wezel * 2]
    else
      MaxSumaLewa := 0;

    Inc (MiotlaSuma^ [Wezel], k);
    MiotlaMaxSuma^ [Wezel] :=
      Max (MaxSumaLewa, MiotlaSuma^ [Wezel] - SumaPrawa + MaxSumaPrawa);
    Wezel := Wezel div 2
  until Wezel = 0;
end;

function Zamiataj: Integer;
var
  YPocz: LongInt;
  jPocz, jKon: Word;
  MaxRozw: Integer;
begin
  YPocz := y^ [1];
  jPocz := 1;
  jKon := 1;
  MaxRozw := 0;
  repeat
    while (jPocz <= n) and (y^ [jPocz] = YPocz) do
    begin
      WstawDoMiotly (x^ [jPocz], 1);
      WstawDoMiotly (Min (LongInt (x^ [jPocz]) + s + 1, MaxX + 1), -1);
      Inc (jPocz);
    end;

    while y^ [jKon] < YPocz - w do
    begin
      WstawDoMiotly (x^ [jKon], -1);
      WstawDoMiotly (Min (LongInt (x^ [jKon]) + s + 1, MaxX + 1), 1);
      Inc (jKon);
    end;

    MaxRozw := Max (MiotlaMaxSuma^ [1], MaxRozw);

    if jPocz > n then
      Break;
    YPocz := y^ [jPocz];
  until False;

  Zamiataj := MaxRozw;
end;

procedure GenerujWynik;
var
  o: Text;
begin
  Assign (o, 'kop.out');
  ReWrite (o);
  WriteLn (o, Zamiataj);
  Close (o);
end;

begin
  WczytajDane;
  RobMiotle;
  StogSortPoY;
  GenerujWynik;
end.
