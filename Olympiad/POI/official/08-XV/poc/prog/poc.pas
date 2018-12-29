(*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Pociagi (POC)                                             *
 *   Plik:     poc.pas                                                   *
 *   Autor:    Piotr Stanczyk                                            *
 *   Opis:     Rozwiazanie poprawne (haszujace).                         *
 *                                                                       *
 *************************************************************************)

const 
  MAXPOC = 1000;
  MAXDL = 128;
  BMAXDL = 7;
  MAXOP = 100000;
  STRMAX = 2*MAXPOC*MAXDL+4*MAXOP;

type 
  operacja = record
    nast, waga, id : longint;
end;
  vert = record
    suma, poc : longint;
    pocz : boolean;
end;
  hashEl = record
    nast : longint;
    val : int64;
end;

var
  PRIME : int64;
  pociagi : array[0..MAXPOC-1,0..MAXDL+1] of char;
  hash : array[0..MAXPOC] of int64;
  off : array[0..MAXDL] of int64;
  op : array[0..STRMAX-1] of operacja;
  hashq : array[0..STRMAX] of hashEL;
  hashh : array[0..STRMAX] of longint;
  hashl : longint;
  lHead : array[0..STRMAX-1] of longint;
  wynik : array[0..MAXPOC-1] of longint;
  idList : array[0..MAXPOC-1] of longint;
  drzewo : array[0..2*STRMAX-1] of vert;
  opU : longint;
  poc, dl, oper : longint;
  p1, p2, o1, o2 : longint;
  x, y, z : longint;
  tmp : char;

procedure HashEr(poc, poz, v : longint);
begin
  hash[poc] := hash[poc] + off[poz]*int64(v);
  if (hash[poc] < 0) then hash[poc] := int64(256)*PRIME + hash[poc];
  hash[poc] := hash[poc] mod PRIME;
end;

function ListLen(l : longint) : longint;
begin
  ListLen := 0;
  while l <> -1 do
  begin
    l := op[l].nast;
    Inc(ListLen);
  end;
end;

function Rzad(v : longint) : longint;
begin
  Rzad := 0;
  while v > 0 do
  begin
    v := v shr 1;
    Inc(Rzad);
  end;
end;

function max(a, b : longint) : longint;
begin
  if a < b then
  begin
    max := b;
  end else
    max := a;
end;

procedure wyliczWynik(l : longint);
var
  len, start, pos, p, x : longint;
  lewy, prawy, res : longint;
begin
  len := ListLen(lHead[l]);
  start := 1 shl Rzad(len);
  pos := len + start - 1;
  p := lHead[l];
  while p <> -1 do
  begin
    drzewo[pos].poc := op[p].id;
    drzewo[pos].suma := op[p].waga;
    if op[p].waga = 1 then
    begin
      drzewo[pos].pocz := true;
    end else
    begin
      drzewo[pos].pocz := false;
    end;
    p := op[p].nast;
    Dec(pos);
  end;
  for x := start + 1 to start + len - 1 do
    Inc(drzewo[x].suma, drzewo[x-1].suma);
  while pos <> 0 do
  begin
    drzewo[pos].suma := max(drzewo[2*pos].suma, drzewo[2*pos+1].suma);
    Dec(pos);
  end;
  for x := start to start + len - 1 do
  begin
    if drzewo[x].pocz then
    begin
      idList[drzewo[x].poc] := x;
    end else
    begin
      lewy := idList[drzewo[x].poc];
      prawy := x;
      res := 0;
      while lewy < prawy do
      begin
        if ((lewy and 1) = 1) then 
        begin
          res := max(res, drzewo[lewy].suma);
          Inc(lewy);
        end;
        if ((prawy and 1) = 0) then 
        begin
          res := max(res, drzewo[prawy].suma);
          Dec(prawy);
        end;
        lewy := lewy shr 1;
        prawy := prawy shr 1;
      end;
      if lewy = prawy then
        res := max(res, drzewo[lewy].suma);
      wynik[drzewo[x].poc] := max(wynik[drzewo[x].poc], res);
    end;
  end;
end;

function HashIt(v : int64) : longint;
var bck, pos : longint;
begin
  bck := v mod STRMAX;
  pos := hashh[bck];
  while (pos <> -1) and (hashq[pos].val <> v) do
  begin
    pos := hashq[pos].nast;
  end;
  if pos = -1 then
  begin
    hashq[hashl].nast := hashh[bck];
    hashh[bck] := hashl;
    hashq[hashl].val := v;
    pos := hashl;
    Inc(hashl);
  end;
  HashIt := pos;
end;

procedure dodajElement(zb : int64; waga, id : longint);
var k : longint;
begin
  k := HashIt(zb);
  if lHead[k] = -1 then
  begin
    lHead[k] := opU;
    op[lHead[k]].nast := -1;
  end else
  begin
    op[opU].nast := lHead[k];
    lHead[k] := opU;
  end;
  op[opU].waga := waga;
  op[opU].id := id;
  Inc(opU);
end;

begin
  PRIME := 705759403;
  PRIME := PRIME*10000000;
  PRIME := PRIME + 7927903;
  hashl := 0;
  opU := 0;
  for x := 0 to STRMAX do hashh[x] := -1;
  for x := 0 to STRMAX-1 do lHead[x] := -1;
  for x := 0 to MAXPOC-1 do wynik[x] := 0;
  ReadLn(poc, dl, oper);
  for x := 0 to poc-1 do
    Readln(pociagi[x]);
  off[0] := 1;
  for x := 0 to dl-2 do 
    off[x+1] := (off[x] * int64(257)) mod PRIME;
  for x := 0 to poc-1 do
    for y := 0 to dl-1 do
      HashEr(x, y, longint(pociagi[x][y]));
  for x := 0 to poc-1 do
    dodajElement(hash[x], 1, x);
  for z := 0 to oper-1 do
  begin
    ReadLn(p1, o1, p2, o2);
    Dec(p1);
    Dec(o1);
    Dec(p2);
    Dec(o2);
    dodajElement(hash[p1], -1, p1);
    if p1 <> p2 then
      dodajElement(hash[p2], -1, p2);
    tmp := pociagi[p1][o1];
    pociagi[p1][o1] := pociagi[p2][o2];
    pociagi[p2][o2] := tmp;
    HashEr(p1, o1, longint(pociagi[p1][o1]) - longint(pociagi[p2][o2]));
    HashEr(p2, o2, longint(pociagi[p2][o2]) - longint(pociagi[p1][o1]));
    if p1 <> p2 then
      dodajElement(hash[p1], 1, p1);
    dodajElement(hash[p2], 1, p2);
  end;
  for x := 0 to poc - 1 do dodajElement(hash[x], -1, x);
  for x := 0 to STRMAX-1 do 
    if lHead[x] <> -1 then
      wyliczWynik(x);
  for x := 0 to poc-1 do 
    WriteLn(wynik[x]);
end.
