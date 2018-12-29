uses zga;

const
  PREC = 12;
  ILE_ZESTAWOW = 1000000;
  PUSTE = -1;

  WYPLATA = 423.99;
  DOPLATA = 13.53;

function daj_losowa : Double;
var
  i : Integer;
  x : Double;
begin
  x := 0.0;
  repeat
    for i := 1 to PREC do
      x := (x + random (10)) / 10;
  until x <> 0.0;
  daj_losowa := x;
end;

var
  wygrane : LongInt;
  i : LongInt;
  j, k, pozycja : Integer;
  t : array [0..ILE_LICZB-1] of Double;
  s : array [0..ILE_LICZB] of Double;
  wygrana, powtorzyl : Boolean;
  pkt : Integer;

begin
  wygrane := 0;

  Randomize;

  inicjalizuj;

  for i := 1 to ILE_ZESTAWOW do
  begin
    nowa_rozgrywka;

    s [0] := 0;
    for j := 1 to ILE_LICZB do
      s [j] := PUSTE;

    for j := 0 to ILE_LICZB - 1 do
    begin
      repeat
        t[j] := daj_losowa;
        powtorzyl := False;
        for k := 0 to j - 1 do
          if t [j] = t [k] then
            powtorzyl := True;
      until not powtorzyl;

      pozycja := kolejna_liczba (t [j]);
      if (pozycja >= 1) and (pozycja <= ILE_LICZB) then
        s [pozycja] := t [j];
    end;

    //sprawdzanie, czy tablica s jest posortowana
    wygrana := True;
    for j :=1 to ILE_LICZB do
      if (s[j] = PUSTE) or (s [j] <= s [j-1]) then
        wygrana := False;

    if wygrana then
      Inc (wygrane);

  end;

  pkt := Round (1e-4 * (wygrane * WYPLATA - (ILE_ZESTAWOW - wygrane) * DOPLATA));

  if pkt < 0 then pkt := 0;
  if pkt > 100 then pkt := 100;

  WriteLn ('Liczba wygranych: ', wygrane);
  WriteLn ('Liczba punktów: ', pkt);

end.
