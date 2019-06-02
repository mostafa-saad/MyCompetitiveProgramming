(*************************************************************************
 *                                                                       *
 *                       X Olimpiada Informatyczna                       *
 *                                                                       *
 *   Rozwi±zanie zadania: P³ytki drukowane                               *
 *   Plik:                ply.pas                                        *
 *   Autor:               Marcin Kubica                                  *
 *************************************************************************)

{ Wynik obliczeñ dla poduk³adu. }
type wynik = array [0..1, 0..1] of longint;

{ Minimum. }
function min (x, y : longint): longint;
begin
  if x < y then min := x else min := y
end;

{ Wynik dla pojedynczego elementu. }
const pojedynczy : wynik = ((1,1),(1,2));

{ Oblicz wynik dla z³o¿enia szeregowego dwóch uk³adów. }
function szeregowo (x, y : wynik): wynik;
begin
  szeregowo [0, 0] := min(x [0,1] + y [1,0] - 1, x [0,0] + y [0,0]);
  szeregowo [0, 1] := min(x [0,1] + y [1,1] - 1, x [0,0] + y [0,1]);
  szeregowo [1, 0] := min(x [1,1] + y [1,0] - 1, x [1,0] + y [0,0]);
  szeregowo [1, 1] := min(x [1,1] + y [1,1] - 1, x [1,0] + y [0,1])
end;

{ Oblicz wynik dla z³o¿enia równoleg³ego dwóch uk³adów, 
  bez elementów rozga³êziaj±cych. }
function rownolegle (x, y : wynik): wynik;
begin
  rownolegle [0, 0] := x [0, 0] + y [0, 0];
  rownolegle [0, 1] := min(x [0, 1] + y [0, 0], x [0, 0] + y [0, 1]);
  rownolegle [1, 0] := min(x [1, 0] + y [0, 0], x [0, 0] + y [1, 0]);
  rownolegle [1, 1] := min(
                        min(x [0, 0] + y [1, 1], x [1, 1] + y [0, 0]),
                        min(x [1, 0] + y [0, 1], x [0, 1] + y [1, 0])
                      )
end;

{ Oblicz wynik po do³o¿eniu elementów rozga³êziaj±cych. }
function rozgalezienia (x : wynik): wynik;
begin
  rozgalezienia [0, 0] := x [1, 1];
  rozgalezienia [0, 1] := x [1, 0] + 1;
  rozgalezienia [1, 0] := x [0, 1] + 1;
  rozgalezienia [1, 1] := x [0, 0] + 2
end;

function uklad : wynik;
var
  ch   : char;
  i, n : integer;
  a    : wynik;
begin
  read (ch);
  if ch = 'X' then begin
    { Pojedynczy element. }
    uklad := pojedynczy;
    readln
  end else begin
    { Liczba poduk³adów. }
    readln(n);
    if ch = 'R' then begin
      { Z³o¿enie równoleg³e. }
      a := uklad();
      for i := 1 to n - 1 do 
        a := rownolegle(a, uklad());
      uklad := rozgalezienia(a)
    end else begin
      { Z³o¿enie szeregowe. }
      a := uklad();
      for i := 1 to n - 1 do 
        a := szeregowo(a, uklad());
      uklad := a
    end
  end
end;

begin
  writeln(uklad() [0, 0]);
end.
