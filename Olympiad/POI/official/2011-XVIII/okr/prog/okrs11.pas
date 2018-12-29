(*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Okresowosc                                       *
 *   Autor:             Marcin Pilipczuk                                 *
 *   Zlozonosc czasowa: O(n^2 * 2^n)                                     *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************)

const MAXN = 200 * 1000 + 100;

var
  tekst: ansistring;
  n, testy: longint;
  okresy: array[0 .. MAXN-1] of boolean;


function czyokres(o:longint):boolean;
var i:longint;
begin
  czyokres := True;
  for i := 1 to n - o do
    if tekst[i] <> tekst[i + o] then begin
      czyokres := False;
      break;
    end;
end;

var ok: boolean;
    i, k: longint;

begin
  readln(testy);
  while testy > 0 do begin
    dec(testy);
    readln(tekst);
    n := Length(tekst);
    for i := 1 to n - 1 do
      okresy[i] := czyokres(i);
    for i := 1 to n do
      tekst[i] := '0';
    ok := False;
    while not ok do begin
      ok := True;
      for i := 1 to n - 1 do
        if okresy[i] <> czyokres(i) then begin
          ok := False;
          break;
        end;
      if ok then break;
      k := n;
      while tekst[k] = '1' do begin
        tekst[k] := '0';
        dec(k);
      end;
      tekst[k] := '1';
    end;
    writeln(tekst);
  end;
end.
