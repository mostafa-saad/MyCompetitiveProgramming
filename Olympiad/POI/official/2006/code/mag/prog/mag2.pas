(*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MAG (Magazyn)                                  *
 *   Plik:                mag2.pas                                       *
 *   Autor:               Marcin Michalski                               *
 *   Opis:                Rozwi±zanie wzorcowe.                          *
 *                        Najpierw obracamy siatkê o 45 stopni,          *
 *                        a potem liczymy mediany.                       *
 *                        Z³o¿ono¶æ czasowa: O(n log n).                 *
 *                                                                       *
 *************************************************************************)

VAR
wynikx,wyniky:longint;
najlepszyx,najlepszyy,n:longint;
px,py,c:longint;

osie:array[1..110000,1..2] of longint;

sklepy: array[1..110000,1..2] of longint;
liczba : array[1..110000] of longint;

Procedure sort(l,r:longint);
VAR i,j:longint; ad,qwe:longint;
begin
i:=l; j:=r; ad:=osie[(i+j) div 2][1];
  repeat
  while (osie[i,1]<ad) do i:=i+1;
  while (osie[j,1]>ad) do j:=j-1;
  if (i<=j) then
  begin
   qwe:=osie[i][1]; osie[i][1]:=osie[j][1]; osie[j][1]:=qwe;
   qwe:=osie[i][2]; osie[i][2]:=osie[j][2]; osie[j][2]:=qwe;
   i:=i+1; j:=j-1;
  end;
  until (i>j);
  if (i<r) then sort(i,r);
  if (l<j) then sort(l,j);
end;


{Rozwi±zanie jednowymiarowego przypadku w metryce miejskiej
Rozwi±zaniem jest mediana.}

Function licz_wynik:longint;
VAR
  wszystkiePunkty: int64;
  naPrawo: int64;
  i:longint;
begin
  sort(1,n);

  wszystkiePunkty := 0;
  for i:=1 to n do
  begin
    wszystkiePunkty:=wszystkiePunkty+osie[i][2];
  end;

  naPrawo := wszystkiePunkty;
  for i:=1 to n do
  begin
    naPrawo := naPrawo - osie[i][2];
    if (naPrawo<=(wszystkiePunkty div 2)) then
    begin
      licz_wynik := osie[i][1];
      break;
    end;
  end;
end;

{Obrót punktów wokó³ punktu (0,0) o 45 stopni
Jednoczesne przeskalowanie pozwala unikn±æ stosowanie typó³ nieca³kowitych}

Procedure obrot(VAR punktx:longint; VAR punkty:longint);
VAR
  tymczx : longint;
  tymczy : longint;
begin

  tymczx := punktx - punkty;
  tymczy := punktx + punkty;
  punktx := tymczx;
  punkty := tymczy;
end;


{Obrót w drug± stronê}

Procedure obrot2(VAR punktx:longint;  VAR punkty:longint);
VAR
  tymczx : longint;
  tymczy : longint;
begin

  tymczx := (punktx + punkty) div 2;
  tymczy := (punkty - punktx) div 2;
  punktx := tymczx;
  punkty := tymczy;
end;


Function max(a1,a2:int64):int64;
begin
max:=a1;
if (a2>a1) then max:=a2;
end;


Procedure wezLepszy(VAR najlepszyx,najlepszyy:longint;kandydatx,kandydaty:longint);
VAR
tymcz,odl1,odl2,dd,roznica :int64;
i:longint;
begin
  roznica := 0;
  for i:=1 to n do
  begin

    odl1 := max(abs(najlepszyx - sklepy[i][1]),abs(najlepszyy-sklepy[i][2]));
    odl2 := max(abs(kandydatx - sklepy[i][1]),abs(kandydaty-sklepy[i][2]));
    dd := odl1 - odl2;
    tymcz := liczba[i];
    roznica := roznica +  dd * tymcz;
  end;
  if (roznica > 0) then
  begin
    najlepszyx := kandydatx;
    najlepszyy := kandydaty;
  end;
end;

VAR
i:longint;
begin
  readln(n);


  {liczba[i] to liczba odwiedzin sklepu dziennie}
  for i:=1 to n do
  begin
    readln(px,py,c);
    px := px * 2;
    py := py * 2;
    sklepy[i][1] := px;
    sklepy[i][2] := py;
    liczba[i] := c;
  end;

  {obracamy wszystkie punkty}
  for i:=1 to n do
  begin
    obrot(sklepy[i][1],sklepy[i][2]);
  end;


  {teraz oddzielamy os x i os y}
  for i:=1 to n do
  begin
    osie[i][1] := sklepy[i][1];
    osie[i][2] := liczba[i];
  end;


  {i liczymy optymalne wyniki dla osi x i osi y}
  wynikx := licz_wynik;


  for i:=1 to n do
  begin
    osie[i][1] := sklepy[i][2];
    osie[i][2] := liczba[i];
  end;


  wyniky := licz_wynik;

  {i obracamy punkty z powrotem}
  obrot2(wynikx,wyniky);
  for i:=1 to n do
  begin
    obrot2(sklepy[i][1],sklepy[i][2]);
  end;
  if (wynikx mod 2 =1)  then
  begin
    najlepszyx := wynikx-1;
    najlepszyy := wyniky-1;

    wezLepszy(najlepszyx,najlepszyy,wynikx-1,wyniky-1);
    wezLepszy(najlepszyx,najlepszyy,wynikx-1,wyniky+1);
    wezLepszy(najlepszyx,najlepszyy,wynikx+1,wyniky-1);
    wezLepszy(najlepszyx,najlepszyy,wynikx+1,wyniky+1);
    wynikx := najlepszyx; wyniky := najlepszyy;
  end;


  writeln(wynikx div 2,' ',wyniky div 2);
end.
