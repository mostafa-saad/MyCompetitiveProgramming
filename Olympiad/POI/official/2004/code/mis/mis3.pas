{*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Misie-Patysie                                  *
 *   Plik:                mis3.pas                                       *
 *   Autor:               £ukasz Kowalik                                 *
 *************************************************************************}

{Lukasz Kowalik, 30.01.2004
 Rozwiazanie nieoptymalne: zlozonosc wykladnicza, sprawdza wszystkie mozliwosci.}
unit mis3;

interface

procedure poczatek (m, p, mpo : LongInt);
procedure ruch_bolka (m, p : LongInt; var bm, bp : LongInt);

implementation

var
  _mpo : LongInt;

procedure poczatek (m, p, mpo : LongInt);
begin
  _mpo := mpo;
end;

procedure ruch_bolka (m, p : LongInt; var bm, bp : LongInt);
var
  lm, lp : LongInt;
begin
  bm := 0;
  bp := 0;

  if (m = 0) and (p = 0) then
    Exit;

  lm := -1;
  lp := -1;

  {probojemy zabierac misie}
  while ((lm <> 0) or (lp <> 0)) and (bm <= _mpo) and (m - bm - 1 >= 0) do
  begin
    Inc (bm);
    ruch_bolka (m - bm, p, lm, lp);
  end;

  if (lm = 0) and (lp = 0) then
    Exit;

  {probojemy zabierac patysie}
  bm := 0;
  while ((lm <> 0) or (lp <> 0)) and (bm <= _mpo) and (p - bp - 1 >= 0) do
  begin
    Inc (bp);
    ruch_bolka (m, p - bp, lm, lp);
  end;

  if (lm = 0) and (lp = 0) then
    Exit;

  {probojemy zabierac misie i patysie}
  bp := 0;
  while ((lm <> 0) or (lp <> 0)) and 
        (bp <= _mpo) and (bm <= _mpo) and 
        (m - bm - 1 >= 0) and (p - bp - 1 >= 0) do
  begin
    Inc (bm);
    Inc (bp);
    ruch_bolka (m - bm, p - bp, lm, lp);
  end;

  if (lm <> 0) or (lp <> 0) then
  begin
    bm := 0;
    bp := 0;
  end;

end;

end.
