{ Przykˆadowy program nadzoruj¥cy przybieg eksperymentu
  (korzysta z modulu jaj.pas). }
{ Autor: Pawel Wolff }

program test;

uses jajmod, jaj;

var
  ile_rozbitych:Integer;
  liczba_pytan, wyt:Longint;

begin
  Write('Podaj wysokosc drapacza: ');
  Readln(wysokosc);
  Write('Podaj liczbe jajek: ');
  Readln(jajka);
  Write('Podaj wytrzymalosc jajka: ');
  Readln(wyt);

  liczba_pytan:=0;
  ile_rozbitych:=0;
  nowy_eksperyment;
  repeat
    if ile_rozbitych < jajka then begin
      daj_pytanie;
      Inc(liczba_pytan)
    end
    else begin
      Writeln('Wszystkie jajka zostaly juz rozbite!');
      Halt(1)
    end;

    if (pietro < 0) or (pietro > wysokosc) then begin
      Writeln('Pietro poza zakresem!');
      Halt(1)
    end;

    if pietro <= wyt then
      odpowiedz:=TAK
    else begin
      odpowiedz:=NIE;
      Inc(ile_rozbitych)
    end;

    analizuj_odpowiedz

  until wiem = TAK;

  if x = wyt then
    Writeln('OK')
  else
    Writeln('ZLE');
  Writeln('liczba pytan = ', liczba_pytan, ', wyznaczona wytrzymalosc = ', x)
end.
