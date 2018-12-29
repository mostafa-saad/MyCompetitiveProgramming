(******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Nim z utrudnieniem                                 *
 *   Autor programu:       Pawel Parys                                        *
 *   Zlozonosc czasowa:    O(m*d)                                             *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************)

const MOD_ = 1000*1000*1000+7;
const MAXN = 500000;
const MAXVAL = 1024*1024;

var 
  a, v, v2, r, N, D, cursize : longint;
  stosy : array[0..MAXN-1] of longint;
  tab : array[0..MAXVAL-1, 0..10-1] of longint; { [v][d] - na ile sposobow mozna uzyskac xor v przy liczbie usunietych stosow przystajacej do d }
  pom : array[0..1, 0..10-1] of longint;

procedure sortuj_stosy;
var ile : array[1..MAXVAL] of longint;
begin
  for v := 1 to MAXVAL do
    ile[v] := 0;
  for a := 0 to N-1 do
    inc(ile[stosy[a]]);
  N := 0;
  for v := 1 to MAXVAL do 
    for a := 1 to ile[v] do begin
      stosy[N] := v;
      inc(N);
    end;
end;

begin
  cursize := 1; { potega dwojki wieksza niz ostatnie niezerowe pole tablicy }
  readln(N, D);
  for a := 0 to N-1 do
    read(stosy[a]);
  sortuj_stosy;
  for v := 0 to MAXVAL-1 do
    for r := 0 to D-1 do
      tab[v, r] := 0;
  tab[0, 0] := 1;
  for a := 0 to N-1 do begin
    for v := 0 to cursize-1 do begin
      v2 := v xor stosy[a];
      if v2>v then begin
        for r := 0 to D-1 do begin
          pom[0, r] := (tab[v2, r]+tab[v, (r+D-1) mod D]) mod MOD_;
          pom[1, r] := (tab[v, r]+tab[v2, (r+D-1) mod D]) mod MOD_;
        end;
        for r := 0 to D-1 do begin
          tab[v, r] := pom[0, r];
          tab[v2, r] := pom[1, r];
        end;
      end;
    end;
    while cursize<=stosy[a] do
      cursize := cursize*2;
  end;
  if (N mod D)=0 then { odejmujemy 1 sposob - wszystkie stosy puste }
    tab[0, 0] := (tab[0, 0]+MOD_-1) mod MOD_;
  writeln(tab[0, 0]);
end.
