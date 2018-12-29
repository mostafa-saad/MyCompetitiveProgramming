(*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SKA (Skarbonki)                                *
 *   Plik:                ska1.pas                                       *
 *   Autor:               Pawe³ Wolff                                    *
 *   Opis:                Rozwi±zanie alternatywne zadania SKARBONKI     *
 *                        (zliczaj±ce liczbê spójnych sk³adowych)        *
 *                                                                       *
 *************************************************************************)
program Skarbonki_1;


const
  MAX_N = 1000000;


type
  WskLista = ^TLista;

  TLista =
    record
      nrSkarbonki: longint;
      nast : WskLista;
    end;
    
    
var
  n: longint;
  skarbonka: array [1..MAX_N] of WskLista;
    { reprezentuje graf nieskierowany skarbonek; dwie (ró¿ne) skarbonki
      s± po³±czone  krawêdzi±, je¶li w jednej z nich znajduje siê klucz
      otwieraj±cy drug± }

  odwiedzona: array [1..MAX_N] of boolean;
  kolejka: array [1..MAX_N] of longint;



procedure Dodaj(a, b: longint);
{ dodaje do listy zwi±zanej z a-t± skarbonk± element wskazuj±cy na b-t±
  skarbonke }
var
  wsk: WskLista;
begin
  wsk := new(WskLista);
  wsk^.nrSkarbonki := b;
  wsk^.nast := skarbonka[a];
  skarbonka[a] := wsk;
end;


procedure WczytajDane;
{ wczytuje dane i jednocze¶nie buduje strukturê grafu w tablicy skarbonka }
var
  i, klucz: longint;
begin
  Readln(n);
  
  for i := 1 to n do
    skarbonka[i] := nil;

  for klucz := 1 to n do begin
    Readln(i);
    if i <> klucz then begin
      Dodaj(i, klucz);
      Dodaj(klucz, i);
    end;
  end;
end;


procedure ZwolnijPamiec;
var
  i: longint;
  wsk, wskPom: WskLista;
begin
  for i := 1 to n do begin
    wsk := skarbonka[i];
    skarbonka[i] := nil;

    while wsk <> nil do begin
      wskPom := wsk^.nast;
      dispose(wsk);
      wsk := wskPom;
    end;
  end;
end;


function IleSkladowych: longint;
{ zlicza liczbê spójnych sk³adowych grafu nieskierowanego zdefiniowanego
  w tablicy skarbonka; w tym celu stosuje algorytm przechodzenia grafu wszerz }

  procedure OdwiedzSkarbonki(l, p: longint);
  var
    i: longint;
    wsk: WskLista;
  begin
    while l <= p do begin
      wsk := skarbonka[kolejka[l]];
      Inc(l);
      while wsk <> nil do begin
        i := wsk^.nrSkarbonki;
        if not odwiedzona[i] then begin
          odwiedzona[i] := true;
          Inc(p);
          kolejka[p] := i;
        end;
        wsk := wsk^.nast;
      end;
    end;
  end;


var
  i, lSkladowych: longint;

begin
  lSkladowych := 0;

  for i := 1 to n do
    odwiedzona[i] := false;
    
  for i := 1 to n do
    if not odwiedzona[i] then begin
      odwiedzona[i] := true;
      Inc(lSkladowych);      
      kolejka[1] := i;
      OdwiedzSkarbonki(1, 1);
    end;

  IleSkladowych := lSkladowych;
end;



begin
  WczytajDane;
  Writeln(IleSkladowych);
  ZwolnijPamiec;
end.
