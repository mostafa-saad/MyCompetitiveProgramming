(*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Usuwanka                                      *
 *   Autor:                Igor Adamski                                  *
 *   Zlozonosc czasowa:    O(n * (n/k))                                  *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie powolne, szukanie brutalne        *
 *                         podciagu o sumie 0                            *
 *                                                                       *
 *************************************************************************)

const MAXN = 1000000;

type
  pnode = ^node;
  node = record
    poz, war : longint;
    next : pnode;
  end;

var ciag, tmp, front, back, prev : pnode;
    C : array[0..MAXN+1] of char;
    wynik : array[0..MAXN] of longint;
    i, j, w, n, k, war, sum : longint;

begin
  ciag := nil;
  w := 0;
  readln(n, k);
  for i:=1 to n do
    read(C[i]);
  for i:=n downto 1 do
  begin
    if C[i] = 'b' then
      war := 1
    else
      war := -k;
    new(tmp);
    tmp^.war := war;
    tmp^.poz := i;
    tmp^.next := ciag;
    ciag := tmp;
  end;
  for j:=1 to n div (k+1) do
  begin
    sum := 0;
    front := ciag;
    for i:=0 to k do
    begin
      sum += front^.war;
      front := front^.next;
    end;
    back := ciag;
    prev := nil;
    while sum <> 0 do
    begin
      prev := back;
      sum -= back^.war;
      back := back^.next;
      sum += front^.war;
      front := front^.next;
    end;
    while back <> front do
    begin
      wynik[w] := back^.poz;
      inc(w);
      if prev = nil then
        ciag := back^.next
      else
        prev^.next := back^.next;
      dispose(back);
      if prev = nil then
        back := ciag
      else
        back := prev^.next;
    end;
  end;
  
  i := n;
  while i > 0 do
  begin
    for j:=i-(k+1) to i-1 do
      write(wynik[j], ' ');
    writeln();
    i -= (k+1);
  end;
end.
