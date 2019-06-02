(*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Konduktor (KON)                                           *
 *   Plik:     konbo.pas                                                 *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Rozwiazanie wzorcowe O(n^2*k)                             *
 *                                                                       *
 *************************************************************************)

var
  N, KK : integer;
  pas : array[0..1010,0..1010] of longint; { tablica z wejscia }
  prost : array[0..1010,0..1010] of longint; { ilu wsiadlo na >=a i wysiadlo <=b }
  best : array[0..1010,0..1010] of longint; { best[o][k] = ilu pasazerow co najmniej
     trzeba pominac  na pierszych o stacjach przy k kontrolach, ostatnia kontrola po stacji o }
  poprz : array[0..1010,0..1010] of integer; { oraz kiedy poprzednia kontrola }
  wyn : array[0..1010] of integer;
  a, b, k, o, op, ost : integer;
  best_gl : longint;

begin
  readln(N, KK);
  for a := 0 to N-1 do 
  begin
    for b := a+1 to N-1 do
      read(pas[a][b]);
    readln;
  end;
  { preprocesing - liczenie tablicy prost }
  prost[0][0] := 0; { zeby nie bylo warninga }
  for b := 0 to N-1 do
    for a := b-1 downto 0 do
      prost[a][b] := pas[a][b]+prost[a][b-1]+prost[a+1][b]-prost[a+1][b-1];
  { liczenie najlepszych zarobkow }
  for k := 1 to KK do
    for o := k-1 to N-KK+k-2 do
      if k=1 then
        best[o][k] := prost[0][o]
      else
      begin
        best[o][k] := 2000000001;
        for op := k-2 to o-1 do
          if best[op][k-1]+prost[op+1][o]<best[o][k] then
          begin
              best[o][k] := best[op][k-1]+prost[op+1][o];
              poprz[o][k] := op;
          end;
      end;
  { liczenie ogolnego wyniku }
  best_gl := 2000000001;
  ost := -1;
  for o := KK-1 to N-2 do
    if best[o][KK]+prost[o+1][N-1]<best_gl then
    begin
      best_gl := best[o][KK]+prost[o+1][N-1];
      ost := o;
    end;
  { gdzie trzeba sprawdzac }
  for k := KK-1 downto 0 do
  begin
    wyn[k] := ost;
    ost := poprz[ost][k+1];
  end;
  for k := 0 to KK-1 do
  begin
    write(wyn[k]+1);
    if k<KK-1 then
      write(' ')
    else
      writeln;
  end;
end.
