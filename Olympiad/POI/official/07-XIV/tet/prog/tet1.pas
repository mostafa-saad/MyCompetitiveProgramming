{*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Tetris attack (TET)                                        *}
{*   Plik:    tet1.pas                                                   *}
{*   Autor:   Pawel Parys                                                *}
{*   Opis:    Rozwiazanie wzorcowe.                                      *}
{*                                                                       *}
{*************************************************************************}
const SIZE = 2*50000;

var 
  dol : array[0..SIZE-1] of longint; { czê¶æ stosu poni¿ej bie¿±cej poz. }
  iledol : longint; { rozmiar dolnej czê¶ci stosu }

  gora : array[0..SIZE-1] of longint; { czê¶æ stosu powy¿ej bie¿±cej poz. }
  goraod, gorakoniec : longint; { gorna czê¶æ stosu znajduje siê 
    w tablicy gora na pozycjach od goraod do gorakoniec-1 }

  jest : array[1..SIZE] of boolean; { czy w dolnej czê¶ci stosu 
    wystêpuje dana liczba }
  N : longint; { ile jest liczb }

  wynik : array[0..1000000-1] of longint; { spamietane ruchy }
  ilew : longint; { ile jest inwersji (ile potrzeba ruchów) }

procedure licz;
var A, B : longint;
begin
  iledol := 0;
  goraod := 0;
  gorakoniec := 2*N;
  while (goraod<>gorakoniec) do
  begin
    A := gora[goraod];
    inc(goraod);
    if (jest[A]) then
    begin
      dec(iledol);
      B := dol[iledol];
      jest[B] := false;
      wynik[ilew] := iledol;
      inc(ilew);
      if (B=gora[goraod]) then { istnieje, bo B ma gdzies u gory pare }
        inc(goraod)
      else
      begin
        dec(goraod);
        gora[goraod] := B;
      end;
      dec(goraod);
      gora[goraod] := A;
      while (iledol>0) and (dol[iledol-1]=gora[goraod]) do
      { gora[goraod] istnieje, bo kazdy z dolu ma pare u gory }
      begin
        dec(iledol);
        inc(goraod);
      end
    end
    else
    begin
      jest[A] := true;
      dol[iledol] := A;
      inc(iledol);
    end
  end
end;

var a : longint;

begin
  read(N);
  for a := 0 to 2*N-1 do
    read(gora[a]);
  ilew := 0;
  licz();
  writeln(ilew);
  for a := 0 to ilew-1 do
    writeln(wynik[a]+1); { +1 bo liczymy od 0 }
end.
