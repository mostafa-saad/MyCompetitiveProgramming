(*
  Przykladowa biblioteka licytacji dla zawodnikow
*)
unit pliclib;

interface

function inicjuj: longint;

procedure alojzy(x: longint);

function bajtazar: longint;

implementation

var n: longint;
var zainicjowane: boolean = FALSE; { czy zostalo juz wywolana funkcja inicjuj }
var stos, stawka: longint;
var kolej: longint; { aktualny gracz }

{ Inicjuje gre pomiedzy Alojzym i Bajtazarem }
function inicjuj: longint;
begin
  if zainicjowane then begin
    writeln(stderr, 'ERROR: Ponowna inicjalizacja biblioteki :(');
    writeln('ZLE');
    halt(0)
  end else
  begin
    zainicjowane := true;
    writeln(stderr, 'Inicjalizowanie: Podaj wartosc n');
    read(n);
    if n < 1 then
    begin
      writeln(stderr, 'ERROR: Nieprawidlowa wartosc n :(');
      writeln('ZLE');
      halt(0)
    end else
    begin
      stos := 0;
      stawka := 1;
      kolej := 1;
      inicjuj := n
    end;
  end;
end;

{ Aktualizuje stos i stawke, biorac pod uwage ruch x }
procedure wykonaj_ruch(x: longint);
begin
  if x = 1 then
  begin
    stos := stos + stawka;
    stawka := 1
  end else if x = 2 then
  begin
    stawka := stawka * 2
  end else if x = 3 then
  begin
    stawka := stawka * 3
  end;
end;

{ Wykonuje ruch Alojzego }
procedure alojzy(x: longint);
begin
  if not zainicjowane then
  begin
    writeln(stderr, 'ERROR: Brak inicjalizacji biblioteki :(');
    writeln('ZLE');
    halt(0);
  end;
  if kolej <> 1 then
  begin
    writeln(stderr, 'ERROR: Ruch Alojzego bez wczesniejszego ruchu Bajtazara :(');
    writeln('ZLE');
    halt(0);
  end;
  writeln(stderr, 'Ruch Alojzego');
  writeln(stderr, 'Liczba kamykow na stosie: ', stos, ', aktualna stawka: ', stawka);
  if stos + stawka >= n then
  begin
    writeln(stderr, 'Wygrana Bajtazara - program zawodnika uzyskuje 0 punktow :(');
    writeln('ZLE');
    halt(0);
  end;
  if (x < 1) or (x > 3) then
  begin
    writeln(stderr, 'ERROR: Nieprawidlowy ruch Alojzego :(');
    writeln('ZLE');
    halt(0);
  end;
  if x = 1 then writeln(stderr, 'Alojzy pasuje');
  if x = 2 then writeln(stderr, 'Alojzy podwaja stawke');
  if x = 3 then writeln(stderr, 'Alojzy potraja stawke');
  kolej := 2;
  wykonaj_ruch(x);
end;

{ Generuje i wykonuje ruch Bajtazara }
function bajtazar: longint;
var
  x: longint;
begin
  if not zainicjowane then
  begin
    writeln(stderr, 'ERROR: Biblioteka nie zostala zainicjalizowana :(');
    writeln('ZLE');
    halt(0);
  end;
  if kolej <> 2 then
  begin
    writeln(stderr, 'ERROR: Pytanie o ruch Bajtocego przed wykonaniem ruchu Alojzego :(');
    writeln('ZLE');
    halt(0);
  end;
  if stos + stawka >= n then
  begin
    writeln(stderr, 'Bajtazar pasuje, Alojzy wygral :)');
    writeln('OK');
    halt(0);
  end;
  writeln(stderr, 'Ruch Bajtara');
  writeln(stderr, 'Liczba kamykow na stosie: ', stos, ', aktualna stawka: ', stawka);
  writeln(stderr, 'Jaki ruch powinien wykonac Bajtazar? 1: Pas, 2: Podwojenie stawki, 3: Potrojenie stawki?');
  read(x);
  if (x < 1) or (x > 3) then
  begin
    writeln(stderr, 'ERROR: Nieprawidlowy ruch Bajtazara :(');
    writeln('ZLE');
    halt(0);
  end;
  kolej := 1;
  wykonaj_ruch(x);
  bajtazar := x;
end;

end.
