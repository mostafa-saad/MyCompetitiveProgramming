{
// Zadanie MIS
// program generujacy rozgrywke i zwracajacy jej wynik, wersja PAS
// Gracz Lolek gra optymalnie, gracz Bolek jest testowany
// Lukasz Kowalik, 14.02.2004
// Poprawki: Rafal Rusin, 2004.03.16
}
program Graj;

uses
  mis; {tu mozna podmieniac testowanego gracza np. na misb1}


{Zawodnik Lolek - Identyczny z wzorcowym Bolkiem}
const
  MAX_MISIE 		=	10000000;
  MAX_MPO 			=	1000000;
  UNDEF					= -1;

var
  _mpo : LongInt;

  PrzegrKol : array [0..MAX_MPO] of LongInt;
  PrzegrPrz : array [-MAX_MPO..MAX_MPO] of LongInt;

{Niech pula bedzie wygrywajaca gdy Bolek moze wygrac niezaleznie od ruchu Lolka
i przegrywajaca w przec. przypadku.
Procedura poczatek wypelnia PrzegrKol i PrzegrPrz tak ze:
PrzegrKol[k]=w   gdy   pula w misiow i k patysiow jest przegrywajaca
PrzegrPrz[p]=k   gdy   pula k+p misiow i k patysiow jest przegrywajaca

W ten sposob:
* z PrzegrKol[k] mozemy odczytac pole przegrywajace w kolumnie k,
* z PrzegrKol[w] mozemy odczytac pole przegrywajace w wierszu w,
* z PrzegrPrz[p] mozemy odczytac pole przegrywajace w przekatnej p}
procedure poczatek_lolka (m, p, mpo : LongInt);
var
  Kolumna, Przekatna : LongInt;
begin
  _mpo := mpo;

  for Kolumna := 0 to mpo do
    PrzegrKol [Kolumna] := UNDEF;

  for Kolumna := -mpo to mpo do
    PrzegrPrz [Kolumna] := UNDEF;

  PrzegrKol [0] := 0;
  PrzegrPrz [0] := 0;
  Przekatna := 1;

  Kolumna := 1;

  while Kolumna + Przekatna <= mpo do
  begin
    if PrzegrKol [Kolumna] = UNDEF then
    begin
      PrzegrKol [Kolumna] := Kolumna + Przekatna;
      PrzegrKol [Kolumna + Przekatna] := Kolumna;
      PrzegrPrz [Przekatna] := Kolumna;
      PrzegrPrz [-Przekatna] := Kolumna + Przekatna;
      Inc (Przekatna);
    end;
    Inc (Kolumna);
  end;

end;


procedure ruch_lolka (m, p : LongInt; var bm, bp : LongInt);
var
  w, k : LongInt;
begin
  w := m mod (_mpo + 1);
  k := p mod (_mpo + 1);

  if (PrzegrKol [k] <> UNDEF) and (w > PrzegrKol [k]) then
  begin
    bm := w - PrzegrKol [k];
    bp := 0;
  end
  else
  if (PrzegrKol [w] <> UNDEF) and (k > {PrzegrWie [w] = } PrzegrKol [w]) then
  begin
    bp := k - PrzegrKol [w];
    bm := 0;
  end
  else
  if (PrzegrPrz [w - k] <> UNDEF) and (k > PrzegrPrz [w - k]) then
  begin
    bm := k - PrzegrPrz [w - k];
    bp := bm;
  end
  else
  begin
    if m > 0 then begin bm := 1; bp := 0; end else begin bp := 1; bm := 0; end;
  end;
end;
{---}

var
  m, p, mpo : LongInt;
  bm, bp, lm, lp : LongInt;

begin
  ReadLn (m, p, mpo);

  poczatek (m, p, mpo);
  poczatek_lolka(m,p,mpo);

  while True do
  begin
    ruch_bolka (m, p, bm, bp);

    m := m - bm;
    p := p - bp;
    //WriteLn ('bm = ', bm, '; bp = ', bp);
    if (m < 0) or (p < 0) or
       ((bm > 0) and (bp > 0) and (bm <> bp)) or
       (bm > mpo) or (bp > mpo) or
       ((bm = 0) and (bp = 0)) then
    begin
      WriteLn ('WRONG');
      Halt;
    end;

    if (m = 0) and (p = 0) then
    begin
      WriteLn ('OK');
      Halt;
    end;

{    WriteLn ('m = ', m, '; p = ', p);
    Write ('> ');
    ReadLn (lm, lp);}

    ruch_lolka (m, p, lm, lp); //gra przeciwko optymalnemu lolkowi
    //WriteLn ('lm = ', lm, '; lp = ', lp);

    m := m - lm;
    p := p - lp;

    if (m = 0) and (p = 0) then
    begin
      WriteLn ('WRONG');
      Halt;
    end;
  end;

end.



