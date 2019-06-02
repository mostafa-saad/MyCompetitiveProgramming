{*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Misie-Patysie                                  *
 *   Plik:                misb2.pas                                      *
 *   Autor:               £ukasz Kowalik                                 *
 *************************************************************************}

{Rozwiazanie niepoprawne. Bierze 1 mis albo patys}
unit misb2;

interface

procedure poczatek (m, p, mpo : LongInt);
procedure ruch_bolka (m, p : LongInt; var bm, bp : LongInt);

implementation

procedure poczatek (m, p, mpo : LongInt);
begin
end;


procedure ruch_bolka (m, p : LongInt; var bm, bp : LongInt);
begin
   if m>0 then begin bm:=1; bp:=0; end else begin bm:=0; bp:=1; end;
end;

end.
