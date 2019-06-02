{Uproszczony program grajacy z trywialna strategia Lolka (wersja dla zawodnika)}

program Graj;

uses
  mis;

var
  m, p, mpo : LongInt;
  bm, bp, lm, lp : LongInt;

begin
  ReadLn (m, p, mpo);

  mis.poczatek (m, p, mpo);

  while True do
  begin
    mis.ruch_bolka (m, p, bm, bp);

    m := m - bm;
    p := p - bp;
    
    if (m < 0) or (p < 0) or
       ((bm > 0) and (bp > 0) and (bm <> bp)) or
       (bm > mpo) or (bp > mpo) or
       ((bm = 0) and (bp = 0)) then
    begin
      WriteLn ('Niepoprawny ruch!');
      Halt;
    end;

    if (m = 0) and (p = 0) then
    begin
      WriteLn ('Wygrana Bolka!');
      Halt;
    end;

    {trywialna strategia Lolka}
    lm := 0; lp := 0;
    if m > 0 then lm := 1 else lp := 1;

    m := m - lm;
    p := p - lp;

    if (m = 0) and (p = 0) then
    begin
      WriteLn ('Przegrana Bolka!');
      Halt;
    end;
  end;

end.



