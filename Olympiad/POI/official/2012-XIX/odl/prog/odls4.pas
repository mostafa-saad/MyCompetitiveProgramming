(*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Odleglosc                                        *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n * n * lg(n))                                 *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Dla kazdej wartosci przegladamy cala liste       *
 *                      wartosci z wejscia i znajdujemy najblizsza,      *
 *                      odleglosc obliczamy jako suma wykladnikow        *
 *                      nww(a,b)/nwd(a,b)                                *
 *                                                                       *
 *************************************************************************)

Program odleglosc;
const 
  MAXN = 1000005;
  INF = 1000000000;

var
  n, a, Vmax, i, j, ind, minD, d, e1, e2, Vlist_ind: longint;
  fact, Vlist : array[0 .. MAXN] of longint;

function nwd(a,b:longint) : longint;
begin
  if b = 0 then nwd := a
  else nwd := nwd(b, a mod b);
end;


function max(x, y : longint) : longint;
begin
  if x > y then max := x else max := y;
end;

function expo(a : longint) : longint;
begin
  expo := 0;
  while a <> 1 do begin
    a := a div fact[a];
    inc(expo);
  end;
end;

begin

  Vmax := 0;
  ind := 0;
  Vlist_ind := 0;
  for i := 0 to MAXN do Vlist[i] := 0;
  fact[0] := 0; fact[1] := 0;

  readln(n);
  for i := 0 to n-1 do begin
    readln(a);
    Vlist[Vlist_ind] := a;
    inc(Vlist_ind);
    Vmax := max(Vmax,a);
  end;

  for i := 2 to Vmax do fact[i] := i;
  i := 2; 
  while i * i <= Vmax do begin
    if fact[i] = i then begin
      j := i * i;
      while j <= Vmax do begin
        if fact[j] = j then fact[j] := i;
        j := j + i;
      end;
    end;
    inc(i);
  end;

  for i := 0 to Vlist_ind - 1 do begin
    minD := INF;
    for j := 0 to Vlist_ind - 1 do if i <> j then begin
      d := nwd(Vlist[i],Vlist[j]);
      e1 := expo(Vlist[i] div d);
      e2 := expo(Vlist[j] div d);
      if minD > e1 + e2 then begin
        minD := e1 + e2;
        ind := j + 1;
      end;
    end;
    writeln(ind);
  end;

end.
