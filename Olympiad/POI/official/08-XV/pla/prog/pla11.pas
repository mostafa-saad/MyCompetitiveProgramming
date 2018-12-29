(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Plakatowanie (PLA)                                        *
 *   Plik:     pla11.pas                                                 *
 *   Autor:    Marek Cygan, Michal Pilipczuk                             *
 *   Opis:     Rozwiazanie wzorcowe O(n*log n) - prostsza wersja: drzewo *
 *             licznikowe.                                               *
 *                                                                       *
 *************************************************************************)
const zz=262200;
const MAX=270000;
const MAX2=700000;
const inf=200000000;

type Para = record
              x, num : longint;
            end;

var 
  tree : array[0..MAX2-1] of longint;
  dosor : array[0..MAX-1] of Para;
  p, q, n, dump, wynik, c, i, j : longint;

function porownaj(p1, p2 : Para) : longint;
begin
  if p1.x <> p2.x then
    porownaj := p1.x-p2.x
  else 
    porownaj := p1.num-p2.num;
end;

procedure czysc;
var i : longint;
begin
  for i := 0 to 2*MAX-1 do
    tree[i] := 0;
end;

procedure wstaw(gdzie : longint);
begin
  p := gdzie + zz;
  while p > 0 do
  begin
    inc(tree[p]);
    p := p shr 1;
  end;
end;

procedure count(a, b : longint);
begin
  p := zz + a - 1;
  q := zz + b + 1;
  c := 0;
  while (p shr 1) <> (q shr 1) do
  begin
    if p mod 2 = 0 then 
      inc(c,tree[p+1]);
    if q mod 2 = 1 then
      inc(c,tree[q-1]);
    p := p shr 1;
    q := q shr 1;
  end
end;

procedure zamien(var a, b : Para);
var c : Para;
begin
  c := a;
  a := b;
  b := c;
end;

procedure qsort(l, r : longint);
var a, b : longint;
    x : Para;
begin
  a := l; b := r;
  zamien(dosor[l+random(r-l+1)], dosor[(l + r) div 2]);
  x := dosor[(l + r) div 2];
  repeat
    while porownaj(dosor[a], x) < 0 do inc(a);
    while porownaj(dosor[b], x) > 0 do dec(b);
    if a <= b then
    begin
      zamien(dosor[a], dosor[b]);
      inc(a); dec(b);
    end
  until a > b;
  if a < r then qsort(a, r);
  if l < b then qsort(l, b);
end;


begin
  czysc;
  read(n);
  for i := 0 to n-1 do 
  begin
    read(dump, dosor[i].x);
    dosor[i].num := i;
  end;
  qsort(0,n-1);
  wynik := 0;
  j := 0;
  while j < n do
  begin
    inc(wynik);
    wstaw(dosor[j].num);
    while (j < n-1) and (dosor[j].x = dosor[j+1].x) do
    begin
      wstaw(dosor[j+1].num);
      count(dosor[j].num+1,dosor[j+1].num-1);
      if c>0 then inc(wynik);
      inc(j);
    end;
    inc(j);
  end;
  writeln(wynik);
end.
